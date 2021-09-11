#include <iostream>
#include <map>

using namespace std;

static inline bool isNumber(char ch) {
	return ch >= '0' && ch <= '9';
}
static inline bool isLower(char ch) {
	return ch >= 'a' && ch <= 'z';
}
static inline bool isUpper(char ch) {
	return ch >= 'A' && ch <= 'Z';
}

static char *extractNumber(char *expr, int *pnum)
{
	int num;
	if (isNumber(*expr)) {
		char *p = expr + 1;
		while (isNumber(*p))
			p++;
		char origin = *p;
		*p = 0;
		num = atoi(expr);
		*p = origin;
		expr = p;
	} else {
		num = 1;
	}
	*pnum = num;
	return expr;
}

static char *extract(char *p, int *pcoeff, bool *pparen)
{
	if (*p == '(') {
		p++;
		for (int off = 1; off > 0; p++) {
			if (*p == '(')
				off++;
			else if (*p == ')')
				off--;
		}
		*pparen = true;
	}
	else if (isUpper(*p)) {
		if (isLower(*++p))
			p++;
		*pparen = false;
	}
	return extractNumber(p, pcoeff);
}

static char *extractFormula(char **expr, int *pcoeff)
{
	char *p = *expr;
	if (*p == '=' || *p == 0) {
		if (*p == '=')
			*expr = p + 1;
		return nullptr;
	}
	while (*p == '+')
		p++;
	p = extractNumber(p, pcoeff);
	*expr = p;
	while (*p != '+' && *p != '=' && *p != 0)
		p++;
	return p;
}

static void parseFormula(char *start, char *end, map<int, int> &elemCnt)
{
	while (start != end) {
		int coefficient; 
		bool parenthesis;
		char *next = extract(start, &coefficient, &parenthesis);
		if (parenthesis) {
			map<int, int> localCnt;
			start++;
			char *end2 = next - 1;
			while (*end2 != ')')
				end2--;
			parseFormula(start, end2, localCnt);
			for (auto it = localCnt.begin(); it != localCnt.end(); it++) {
				auto elem = elemCnt.find(it->first);
				if (elem == elemCnt.end())
					elemCnt[it->first] = coefficient * it->second;
				else
					elem->second += coefficient * it->second;
			}
		} else {
			int key = *start;
			key <<= 8;
			if (isLower(*++start))
				key |= *start;
			auto elem = elemCnt.find(key);
			if (elem == elemCnt.end())
				elemCnt[key] = coefficient;
			else
				elem->second += coefficient;
		}
		start = next;
	}
}

static char *parseExpression(char *expr, map<int, int> &elemCnt)
{
	for (;;)
	{
		int coefficient;
		char *next = extractFormula(&expr, &coefficient);
		if (next == nullptr)
			break;

		map<int, int> localCnt;
		parseFormula(expr, next, localCnt);
		
		for (auto it = localCnt.begin(); it != localCnt.end(); it++) {
			auto elem = elemCnt.find(it->first);
			if (elem == elemCnt.end())
				elemCnt[it->first] = coefficient * it->second;
			else
				elem->second += coefficient * it->second;
		}

		if (next == nullptr)
			break;
		expr = next;
	}
	return expr;
}

static bool isEqual(map<int, int> &left, map<int, int> &right)
{
	if (left.size() != right.size())
		return false;
	for (auto l = left.begin(); l != left.end(); l++) {
		auto r = right.find(l->first);
		if (r == right.end() || r->second != l->second)
			return false;
	}
	return true;
}

int main(void)
{
	int n;
	cin >> n;
	cin.ignore(100, '\n');

	char input[1024];
	while (n-- > 0)
	{
		cin.getline(input, sizeof(input));

		map<int, int> left;
		map<int, int> right;
		
		char *p = parseExpression(input, left);
		parseExpression(p, right);

		cout << (isEqual(left, right) ? 'Y' : 'N') << endl;
	}

	return 0;
}