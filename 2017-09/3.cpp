#include <iostream>
#include <cstring>
#include <map>
#include <stack>

using namespace std;

enum Type {
	STRING,
	OBJECT,
};

struct Value;

struct Object {
	map<string, Value *> kv;
	Value *getValue(char *key) {
		string str(key);
		auto it = kv.find(str);
		return it == kv.end() ? nullptr : it->second;
	}
	void putValue(char *key, Value *val) {
		string str(key);
		kv[str] = val;
	}
};

struct Value {
	Type type;
	union {
		char *str;
		Object *obj;
	} v;
	Value(Type t) {
		type = t;
		if (t == OBJECT) {
			v.obj = new Object();
		} else {
			v.str = nullptr;
		}
	}
};

static char *parseString(char *input, char *output)
{
	input++;
	while (*input != '"') {
		if (*input == '\\')
			input++;
		*output++ = *input++;
	}
	*output = 0;
	return input;
}

#define LENGTH 128

int main(void)
{
	int n, m;
	cin >> n >> m;
	cin.ignore(100, '\n');

	Object root;
	Object *cur = nullptr;
	stack<Object *> objstack;

	char input[LENGTH];
	char buf[LENGTH];
	bool gotKey = false;
	while (n-- > 0) {
		cin.getline(input, LENGTH);
		char *p = input;

		for (;;) {
			switch (*p) {
			case '{':
				if (cur == nullptr) {
					cur = &root;
					objstack.push(cur);
				} else {
					Value *val = new Value(OBJECT);
					cur->putValue(buf, val);
					objstack.push(cur);
					cur = val->v.obj;
				}
				break;
			case '}':
				cur = objstack.top();
				objstack.pop();
				break;
			case '"': {
				Value *val = nullptr;
				if (gotKey) {
					val = new Value(STRING);
					cur->putValue(buf, val);
					gotKey = false;
				}
				p = parseString(p, buf);
				if (val != nullptr) {
					val->v.str = strdup(buf);
				}
				break;
			}
			case ':':
				gotKey = true;
				break;
			default:
				break;
			}
			if (*p == 0)
				break;
			p++;
		}
	}

	while (m-- > 0) {
		cin.getline(input, LENGTH);
		
		cur = &root;
		char *p = input;
		Value *val = nullptr;
		bool hit = true;
		while (*p) {
			char *cut = p;
			while (*cut && *cut != '.')
				cut++;
			if (*cut == '.')
				*cut++ = 0;

			val = cur->getValue(p);
			if (val == nullptr || (val->type == STRING && *cut != 0)) {
				cout << "NOTEXIST" << endl;
				hit = false;
				break;
			}
			if (val->type == OBJECT)
				cur = val->v.obj;
			p = cut;
		}
		if (hit) {
			if (val->type == STRING) {
				cout << "STRING " << val->v.str << endl;
			} else {
				cout << "OBJECT" << endl;
			}
		}
	}

	return 0;
}