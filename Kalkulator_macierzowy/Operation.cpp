#include "Operation.h"

void Operation::load()
{
	cout << "Podaj dzia³anie: " << endl;
	getline(cin, infix);
}
int Operation::amountMatrix()
{
	regex pattern("V\\d+");
	auto matches_begin = sregex_iterator(infix.begin(), infix.end(), pattern);
	auto matches_end = sregex_iterator();
	int count = distance(matches_begin, matches_end);
	return count;
}

void Operation::transpone(Matrix* tab)
{
	regex pattern("V\\d+\\%");
	auto matches_begin = std::sregex_iterator(infix.begin(),infix.end(), pattern);
	auto matches_end = std::sregex_iterator();

	char mark;
	int number;
	for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
		smatch match = *i;
		string match_str = match.str();
		mark = match_str[1];
		number = mark - '0';
		tab[number - 1].transpone();
	}
	infix.erase(remove(infix.begin(), infix.end(), '%'), infix.end());
}

void Operation::inverse(Matrix* tab)
{
	regex pattern("V\\d+\\$");
	auto matches_begin = std::sregex_iterator(infix.begin(), infix.end(), pattern);
	auto matches_end = std::sregex_iterator();

	char mark;
	int number;
	for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
		smatch match = *i;
		string match_str = match.str();
		mark = match_str[1];
		number = mark - '0';
		tab[number - 1].inverse();
	}
	infix.erase(remove(infix.begin(), infix.end(), '$'), infix.end());
}

void Operation::exponentation(Matrix* tab)
{
	regex pattern("V\\d+\\^\\d+");
	auto matches_begin = std::sregex_iterator(infix.begin(), infix.end(), pattern);
	auto matches_end = std::sregex_iterator();

	char mark;
	int number;
	int exponential;
	for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
		smatch match = *i;
		string match_str = match.str();
		mark = match_str[1];
		exponential = match_str[3] - '0';
		number = mark - '0';
		tab[number - 1].exponentation(exponential);
	}
	regex pattern_2("\\^\\d+");
	infix = regex_replace(infix, pattern_2, "");

}

bool Operation::isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int Operation::getPrecedence(char op)
{
	if (op == '+' || op == '-') {
		return 1;
	}
	else if (op == '*' || op == '/') {
		return 2;
	}
	return 0;
}

void Operation::infixToPostfix()
{
	for (char c : infix) {
		if (isdigit(c) || c == '.' || c == 'V') {
			postfix += c;
		}
		else if (c == '(') {
			stack.push(c);
		}
		else if (c == ')') {
			while (!stack.empty() && stack.top() != '(') {
				postfix += ' ';
				postfix += stack.top();
				stack.pop();
			}
			stack.pop(); // Usuñ otwieraj¹cy nawias '('
		}
		else if (isOperator(c)) {
			while (!stack.empty() && getPrecedence(stack.top()) >= getPrecedence(c)) {
				postfix += ' ';
				postfix += stack.top();
				stack.pop();
			}
			postfix += ' ';
			stack.push(c);
		}
	}

	while (!stack.empty()) {
		postfix += ' ';
		postfix += stack.top();
		stack.pop();
	}
	//cout << postfix;

}

Matrix& Operation::calculate(Matrix* tab)
{
	istringstream iss(postfix);
	std::stack<std::string> m_stack;
	string token;
	regex pattern("V\\d+");

	while (iss >> token) {
		if (regex_match(token, pattern) || (isdigit(token[0]) || (token.length() > 1 && (token[0] == '-' || token[0] == '+')))) {
			// Jeœli token jest macierz¹ lub liczb¹, wrzuæ j¹ na stos
			m_stack.push(token);
		}
		else {
			// Token jest operatorem, wykonaj operacjê
			if (m_stack.size() < 2) {
				throw std::invalid_argument("Nieprawid³owe wyra¿enie.");
			}

			string secondOperand = m_stack.top();
			//cout << secondOperand << endl;
			m_stack.pop();
			string firstOperand = m_stack.top();
			//cout << firstOperand << endl;
			m_stack.pop();

			Matrix* fOp_m = nullptr;
			double fOp_d;
			Matrix* sOp_m = nullptr;
			double sOp_d;
			bool f = false;
			bool s = false;

			if (firstOperand[0] == 'V')
			{
				fOp_m = &tab[(firstOperand[1]-'0') - 1];
				f = true;
			}
			else
			{
				fOp_d = stod(firstOperand);
			}
			if (secondOperand[0] == 'V')
			{
				sOp_m = &tab[(secondOperand[1] - '0') - 1];
				s = true;
			}
			else
			{
				sOp_d = stod(secondOperand);
			}


			if (token == "+") {
					*fOp_m + *sOp_m;
					m_stack.push(firstOperand);
			}
			else if (token == "-") {
				*fOp_m - *sOp_m;
				m_stack.push(firstOperand);
			}
			else if (token == "*") {
				if (f && s)
				{
					*fOp_m * *sOp_m;
					m_stack.push(firstOperand);
				}
				else if (f && !s)
				{
					*fOp_m * sOp_d;
					m_stack.push(firstOperand);
				}
				else
				{
					*sOp_m * fOp_d;
					m_stack.push(secondOperand);
				}
			}
			else if (token == "/") {
				(*fOp_m) / (*sOp_m);
				m_stack.push(firstOperand);
			}
			else {
				throw std::invalid_argument("Nieznany operator.");
			}
		}
	}

	if (m_stack.size() != 1) {
		throw std::invalid_argument("Nieprawid³owe wyra¿enie.");
	}

	string result = m_stack.top();
	return tab[(result[1] - 1) - '0'];
}

void Operation::clear()
{
	infix = "";
	postfix = "";
	stack = std::stack<char>();
}
