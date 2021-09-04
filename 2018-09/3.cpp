#include <stdio.h>
#include <iostream>
#include <cstring>
#include <list>
#include <limits>

#define LENGTH	128

using namespace std;

struct Element {
	int line;
	int level;
	char *label;
	char *id;
	list<Element *> children;
	Element *parent;
	Element(int ln, char *linebuf) {
		this->line = ln;

		int lv = 0;
		while (*linebuf == '.') {
			linebuf++;
			lv++;
		}
		this->level = lv / 2;

		this->id = nullptr;
		char *p = linebuf;
		while (*p) {
			if (*p == ' ') {
				*p = 0;
				id = strdup(p + 1);
				break;
			}
			p++;
		}

		this->label = strdup(strlwr(linebuf));
		this->parent = nullptr;
	}
	void adopt(Element *child) {
		this->children.push_back(child);
		child->parent = this;
	}
};

static int lineno[LENGTH];
static int nmatch;

bool match(Element *elem, char *filter)
{
	char *sub = filter;
	bool subflag = false;
	while (*sub) {
		if (*sub == ' ') {
			*sub = 0;
			subflag = true;
			break;
		}
		sub++;
	}

	bool matched;
	
	if (*filter == '#') {
		if (elem->id == nullptr)
			matched = false;
		else
			matched = (strcmp(elem->id, filter) == 0);
	} else {
		strlwr(filter);
		matched = (strcmp(elem->label, filter) == 0);
	}

	if (subflag) {
		*sub = ' ';
		if (matched) {
			matched = false;
			for (auto it = elem->children.begin(); it != elem->children.end(); it++) {
				if (match(*it, sub + 1)) {
					matched = true;
				}
			}
		} else {
			for (auto it = elem->children.begin(); it != elem->children.end(); it++) {
				if (match(*it, filter)) {
					matched = true;
				}
			}
		}
	}
	else {
		if (matched)
			lineno[nmatch++] = elem->line;
		if (*filter == '#' && !matched) {
			for (auto it = elem->children.begin(); it != elem->children.end(); it++) {
				if (match(*it, filter)) {
					return true;
				}
			}
		} else if (*filter != '#') {
			for (auto it = elem->children.begin(); it != elem->children.end(); it++) {
				if (match(*it, filter)) {
					matched = true;
				}
			}
		}
	}
	
	return matched;
}

int main(void)
{
	int n, m;
	char buf[LENGTH];

	cin >> n >> m;
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

	Element *root = nullptr;
	Element *cur = nullptr;
	for (int i = 1; i <= n; i++) {
		cin.getline(buf, LENGTH);
		
		Element *elem = new Element(i, buf);
		if (root == nullptr)
			root = cur = elem;
		else {
			while (cur->level >= elem->level)
				cur = cur->parent;
			cur->adopt(elem);
			cur = elem;
		}
	}

	for (int i = 0; i < m; i++) {
		cin.getline(buf, LENGTH);
		nmatch = 0;
		match(root, buf);
		cout << nmatch;
		for (int i = 0; i < nmatch; i++) {
			printf(" %d", lineno[i]);
		}
		cout << endl;
	}

	return 0;
}


/*

void printElement(Element *elem)
{
	cout << elem->line << '\t';
	for (int i = 0; i < elem->level; i++) {
		cout << "..";
	}
	cout << elem->label;
	if (elem->id != nullptr)
		cout << ' ' << elem->id;
	cout << endl;

	for (auto it = elem->children.begin(); it != elem->children.end(); it++)
		printElement(*it);
}

11 5
html
..head
....title
..body
....h1
....p #subtitle
....div #main
......h2
......p #one
......div
........p #two

*/