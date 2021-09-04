#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <utility>

using namespace std;

enum ModeType {
	NONE, STR, INT, PATH,
};

#define LENGTH 128

struct Mode {
	ModeType type;
	char *pattern;
	struct Mode *subMode;
	Mode(ModeType t, char *p) {
		type = t;
		pattern = p;
		subMode = nullptr;
	}
};

static struct Mode *parsePattern(char *modestr)
{
	ModeType type = NONE;
	if (modestr[0] == '<') {
		char tail = 0;
		if (strncmp(modestr, "<str>", 5) == 0) {
			type = STR;
			tail = modestr[5];
		}
		else if (strncmp(modestr, "<int>", 5) == 0) {
			type = INT;
			tail = modestr[5];
		}
		else if (strncmp(modestr, "<path>", 6) == 0) {
			type = PATH;
			tail = modestr[6];
		}
		if (tail != '/' && tail != 0)
			type = NONE;
	}
	
	char *pattern = type == NONE ? strdup(modestr) : nullptr;
	return new Mode(type, pattern);
}

static struct Mode *parseMode(char *modestr)
{
	struct Mode *head = nullptr, *tail;
	for (;;)
	{
		while (*modestr && *modestr == '/')
			modestr++;
		if (*modestr == 0)
			break;

		char *p = modestr + 1;
		int end = 0;
		while (*p && *p != '/')
			p++;
		if (*p == 0)
			end = 1;
		else
			*p = 0;

		struct Mode *mode = parsePattern(modestr);
		if (!head)
			head = tail = mode;
		else {
			tail->subMode = mode;
			tail = mode;
		}

		if (end)
			break;
		modestr = p + 1;
	}
	return head;
}

static char outbuf[LENGTH];
static char *pout;
static char legal[] = "/-_.";

static bool matchstr(char ch, int str)
{
	if ((ch >= '0' && ch <= '9') ||
		(ch >= 'A' && ch <= 'Z') ||
		(ch >= 'a' && ch <= 'z') ||
		strchr(legal + str, ch))
	{
		return true;
	}
	return false;
}

static bool matchMode(struct Mode *mode, char *url)
{
	bool match;
	switch (mode->type) {
	case NONE:
		match = strcmp(mode->pattern, url) == 0;
		break;
	case INT:
		match = true;
		for (char *p = url; *p; p++)
			if (*p < '0' || *p > '9') {
				match = false;
				break;
			}
		if (match) {
			pout += sprintf(pout, " %d", atoi(url));
		}
		break;
	case STR:
		match = true;
		for (char *p = url; *p; p++)
			if (!matchstr(*p, 1)) {
				match = false;
				break;
			}
		if (match) {
			pout += sprintf(pout, " %s", url);
		}
		break;
	}
	return match;
}

static bool matchURL(struct Mode *head, char *url)
{
	for (;;)
	{
		while (*url == '/')
			url++;
		if (*url == 0)
			return head == nullptr;			

		if (head == nullptr)
			return false;

		if (head->type == PATH) {
			for (char *p = url; *p; p++)
				if (!matchstr(*p, 0)) {
					return false;
				}
			sprintf(pout, " %s", url);
			return true;
		}

		char *p = url + 1;
		bool end = false;
		while (*p && *p != '/')
			p++;
		if (*p == 0)
			end = true;
		else
			*p = 0;

		if (!matchMode(head, url)) {
			if (!end)
				*p = '/';
			return false;
		}

		url = p;
		if (!end) {
			url++;
			*p = '/';
		}
		head = head->subMode;
	}
	return true;
}

int main(void)
{
	int n, m;
	cin >> n >> m;

	char buf[LENGTH];
	vector<pair<Mode *, char *>> modes(n);
	for (int i = 0; i < n; i++) {
		scanf("%s", buf);
		modes[i].first = parseMode(buf);
		scanf("%s", buf);
		modes[i].second = strdup(buf);	// name
	}

	for (int i = 0; i < m; i++) {
		scanf("%s", buf);
		bool match = false;
		for (int j = 0; j < n; j++) {
			pout = outbuf;
			if (matchURL(modes[j].first, buf)) {
				printf("%s%s\n", modes[j].second, outbuf);
				match = true;
				break;
			}
		}
		if (!match) {
			cout << "404" << endl;
		}
	}

	return 0;
}