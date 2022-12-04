
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <regex>
#include <unordered_map>
#include <fstream>

#define REGEX string
#define token_type string

using namespace std;

template<class _r, class _l>
ostream& operator<<(ostream& os, const pair<_r, _l>& pair_)
{
	os << pair_.first << " : " << pair_.second << endl;
	return os;
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	os << "{";
	for (T i : v)
	{
		os << i << ", ";
	}
	os << "}";
	return os;
}

template <class T>
vector<T> sub_vector(const vector<T>& v, long long start, long long stop, long long step = 1)
{
	vector<T> sub;
	if (step > 0)
	{
		for (auto c_iter = v.begin() + start; c_iter != v.end() - stop; c_iter += step)
		{
			sub.push_back(*(c_iter));
		}
	}
	else
	{
		for (auto c_iter = v.rbegin() + start; c_iter != v.rend() - stop; c_iter += -step)
		{
			sub.push_back(*(c_iter));
		}
	}
	return sub;
}


const vector<pair<string, string>> tokens_type = {
	{"COLON", ":"},
	{"NUMBER", "[0-9]+"},
	{"ASSIGN", "="},
	{"TYPE", "\\b(?=(?:int|float|string|list|dyn_type|map)\\b)\\w+"},
	{"KEY WORD", "\\b(?=(?:while|if|else|for|and|or|return|break|continue|import)\\b)\\w+"},
	{"ID", "\\b(?!(?:int|float|class|double|func|string|list|map|constructor|const|operator|public|protected|dyn_type|private|import|while|if|else|for|and|or|return|break|continue|\\d+\\w*)\\b)\\w+"},
	{"LPAR", "\\("},
	{"RPAR", "\\)"},
	{"PLUS", "\\+"},
	{"MINUS", "-"},
	{"STAR", "\\*"},
	{"DIVISION", "/"},
	{"FUNCTION", "func"},
	{"CLASS", "class"},
	{"NEXT LINE", "\\n"},
	{"INDENT", "\\t"},
	{"DOUBLE QUOTE", "\\\""},
	{"SINGLE QUOTE", "\\\'"},
	{"LARROW", ">"},
	{"RARROW", "<"},
	{"SHARP", "#"},
	{"SEMICOLON", ";"},
	{"DOT","\\."},
	{"REF", "&"},
	{"CONST", "const"},
	{"NOT", "!"},
	{"COMMA", ","},
	{"OVERLOAD OPERATOR", "operator"},
	{"L CURLY BRACKETS", "\\{"},
	{"R CURLY BRACKETS", "\\}"},
	{"L SQUARE BRACKETS", "\\["},
	{"R SQUARE BRACKETS", "\\]"},
	{"CONSTRUCTOR OF CLASS", "constructor"},
	{"GUARD", "(public|protected|private)"}, 
	{"SPACE", " "}
};

vector<pair<string, string>> tokenize(vector<string> split_code)
{
	vector<pair<string, string>> tokens;
	for (string code_iter : split_code)
	{
		int find = 0;
		for (pair<token_type, REGEX> token_type_iter : tokens_type)
		{
			find = -1;
			regex reg(token_type_iter.second);
			cmatch match;
			if (regex_match(code_iter.c_str(), match, reg))
			{
				if (match.str() == "\t")
				{
					tokens.push_back(make_pair(token_type_iter.first, "\"\\t\""));
				}
				else if (match.str() == "\n")
				{
					tokens.push_back(make_pair(token_type_iter.first, "\"\\n\""));
				}
				else
				{
					tokens.push_back(make_pair(token_type_iter.first, "\"" + match.str() + "\""));
				}
			}
		}

	}
	return tokens;
}



vector<string> split_code(const string& code)
{
	vector<string> split_code;
	string temp_str;
	for (char iter : code)
	{
		if (iter == '(' || iter == ')' ||
			iter == '{' || iter == '}' ||
			iter == '[' || iter == ']' ||
			iter == '|' ||
			iter == '*' || iter == '+' || iter == '-' ||iter == '/' ||
			iter == ' ' || iter == '\t' || iter == '\n' ||
			iter == '\"' || iter == '\'' ||
			iter == '<' || iter == '>' ||
			iter == '#' ||
			iter == ':' || iter == ';' || 
			iter == '.' ||
			iter == '&' ||
			iter == '=' ||
			iter == '!' ||
			iter == ',')
		{
			if (!(temp_str.empty()))
			{
				split_code.push_back(temp_str);
			}
			split_code.push_back(string(1, iter));
			temp_str = "";
		}
		else
		{
			temp_str += iter;
		}
	}
	split_code.push_back(temp_str);
	return split_code;
}

template<class _key, class _value>
ostream& operator<<(ostream& os, const unordered_map<_key, _value>& umap)
{
	os << "{\n";
	for (pair<_key, _value> iter : umap)
	{
		os << "\t" << iter.first << " : " << iter.second << endl;
	}
	os << "}\n";
	return os;
}

unordered_map<string, vector<pair<string, string>>> values = {
	{"int", {}},
	{"float", {}},
	{"string", {}},
};

string execute(vector<pair<string, string>> tokens)
{
	string exec = "";
	return exec;
}


int main(int argc, char** argv)
{
	if (argc == 1)
	{
		cout << "SimpleScript 0.0.0.1\nPlease write your code\n";
		int empty_input = 0;
		while (true)
		{
			cout << ">>> ";
			char input[2048];
			cin.getline(input, 2048);
			if (input == "\n")
			{
				empty_input++;
			}
			if (empty_input == 3)
			{
				break;
			}
			string code = input;
			vector<string> codes = { code };
			vector<pair<string, string>> tokens = tokenize(split_code(code));
			int empty_string = 0;
			if (tokens.at(tokens.size() -1) == make_pair(string("COLON"), string(":")))
			{
				cout << "... ";
				char s_input[2048];
				cin.getline(s_input, 2048);
				if (s_input == "\n")
				{
					empty_string++;
				}
				if (empty_string == 3)
				{
					break;
				}
				codes.push_back(s_input);
			}
			string new_code = "";
			for (string code : codes)
			{
				new_code += code;
			}
			vector<pair<string, string>> new_tokens = tokenize(split_code(code));
			new_tokens.size() > 0 ? cout << "tokens = " << new_tokens << endl : cout << "ERROR\n";
			//vector<int> v_int = { 1,2,3,4,5,6,7,8,9,10 };
			//cout << sub_vector(v_int, 0, 0, -1) << endl;
			//cout << sub_vector(v_int, 0, 0, 1) << endl;
		}


	}
	else
	{
		ifstream _code(argv[1]);
		string code((std::istreambuf_iterator<char>(_code)),
			(std::istreambuf_iterator<char>()));
		cout << "tokens = " << tokenize(split_code(code)) << endl << tokenize(split_code(code)).size();
		system("pause");
	}
	return 0;
}