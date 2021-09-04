#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

#define LENGTH	256

static void parseLink(char **pline, char **pdst);

static void parseEmphasis(char **pline, char **pdst)
{
	char *line = *pline;
	char *dst = *pdst;
	while (*line == '_')
		line++;

	char *p = line;
	while (*p != '_')
		p++;
	*p++ = 0;
	*pline = p;

	dst += sprintf(dst, "<em>");
	p = line;
	while (*p) {
		if (*p == '[') {
			parseLink(&p, &dst);
		} else {
			*dst++ = *p++;
		}
	}
	dst += sprintf(dst, "</em>");
	*pdst = dst;
}

static void parseLink(char **pline, char **pdst)
{
	char *line = *pline;
	char *dst = *pdst;
	while (*line == '[')
		line++;

	char *text = line;
	while (*line != ']')
		line++;
	*line++ = 0;
	while (*line != '(')
		line++;
	
	char *link = ++line;
	while (*line != ')')
		line++;
	*line++ = 0;
	*pline = line;

	dst += sprintf(dst, "<a href=\"%s\">", link);
	while (*text) {
		if (*text == '_') {
			parseEmphasis(&text, &dst);
		} else {
			*dst++ = *text++;
		}
	}
	dst += sprintf(dst, "</a>");
	*pdst = dst;
}

static void parseEmphAndLink(char *line)
{
	char buf[LENGTH];
	char *pbuf = buf;
	char *p = line;

	while (*p) {
		if (*p == '_') {
			parseEmphasis(&p, &pbuf);
		} else if (*p == '[') {
			parseLink(&p, &pbuf);
		} else {
			*pbuf++ = *p++;
		}
	}
	*pbuf = 0;
	strcpy(line, buf);
}

static void parseHeader(char *line)
{
	int level = 0;
	while (*line && *line++ == '#')
		level++;
	while (*line && *line == ' ')
		line++;
	if (*line == 0)
		return;
	if (level > 6)
		level = 6;
	parseEmphAndLink(line);
	printf("<h%d>%s</h%d>\n", level, line, level);
}

static void parseList(char *line)
{
	while (*line++ == '*')
		;
	while (*line == ' ')
		line++;

	parseEmphAndLink(line);
	printf("<li>%s</li>\n", line);
}

int main(void)
{
	enum BlockState {
		NONE,
		HEAD,
		PARA,
		LIST,
	};

	BlockState state = NONE;
	char line[LENGTH];
	while (cin.getline(line, LENGTH)) {
		if (line[0] == '#') {
			parseHeader(line);
			state = HEAD;
			continue;
		}

		if (line[0] == '*') {
			if (state == NONE) {
				state = LIST;
				printf("<ul>\n");
			}
			parseList(line);
			continue;
		}

		if (line[0] == 0) {
			if (state == PARA) {
				printf("</p>\n");
			} else if (state == LIST) {
				printf("</ul>\n");
			}
			state = NONE;
			continue;
		}

		if (state == NONE) {
			state = PARA;
			printf("<p>");
		} else if (state == PARA) {
			putchar('\n');
		}

		parseEmphAndLink(line);
		printf("%s", line);
	}

	if (state == PARA) {
		printf("</p>\n");
	} else if (state == LIST) {
		printf("</ul>\n");
	}

	return 0;
}
