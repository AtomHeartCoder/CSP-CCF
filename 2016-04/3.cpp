#include <iostream>
#include <map>
#include <stack>
#include <cstring>

using namespace std;

struct Entry {
	string name;
	map<string, Entry *> children;
	Entry *parent;
	Entry(const char *filename, Entry *p) :name(filename) {
		this->parent = p == nullptr ? this : p;
	}
};

Entry *root, *cwd;

static Entry *getCWD(char *input)
{
	Entry *curr = root;
	for (;;) {
		while (*input == '/')
			input++;
		if (*input == 0)
			break;

		char *p = input;
		bool gotnull = false;
		while (*p && *p != '/')
			p++;
		if (*p == 0)
			gotnull = true;
		else
			*p++ = 0;

		Entry *entry = new Entry(input, curr);
		curr->children[input] = entry;
		curr = entry;

		if (gotnull)
			break;
		input = p;
	}
	return curr;
}

static Entry *namei(char *path)
{
	Entry *curr = (*path == '/') ? root : cwd;
	bool gotnull = false;
	char *p;
	for (p = path; !gotnull; path = p) {
		while (*path == '/')
			path++;
		if (*path == 0)
			break;

		for (p = path; *p && *p != '/'; p++);
		if (*p == 0)
			gotnull = true;
		else
			*p++ = 0;
		
		if (strcmp(path, ".") == 0) {
			continue;
		}
		else if (strcmp(path, "..") == 0) {
			curr = curr->parent;
		}
		else {
			auto it = curr->children.find(path);
			if (it != curr->children.end()) {
				curr = it->second;
			} else {
				Entry *entry = new Entry(path, curr);
				curr->children[path] = entry;
				curr = entry;
			}
		}
	}
	return curr;
}

#define LENGTH	1024

int main(void)
{
	int P;
	cin >> P;
	cin.ignore(100, '\n');

	root = new Entry("", nullptr);

	char input[LENGTH];
	cin.getline(input, LENGTH);
	cwd = getCWD(input);
	
	stack<Entry *> entries;
	while (P-- > 0) {
		cin.getline(input, LENGTH);
		Entry *entry = namei(input);
		if (entry == root) {
			cout << '/' << endl;
		}
		else {
			while (entry != root) {
				entries.push(entry);
				entry = entry->parent;
			}
			while (!entries.empty()) {
				entry = entries.top();
				entries.pop();
				cout << '/' << entry->name.c_str();
			}
			cout << endl;
		}
	}

	return 0;
}