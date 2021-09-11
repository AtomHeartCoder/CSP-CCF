#include <iostream>
#include <stdio.h>

using namespace std;

#define BUFFER_SIZE		(1024 * 128)

static inline void outchar(char ch)
{
	putchar(ch);
}

struct Terminal {
	int x;
	int y;
	int width;
	int padding;
	void write(char ch) {
		if (x >= width) {
			x = 0;
			y++;
			outchar('\n');
		}
		for (; x < padding; x++)
			outchar(' ');
		if (ch == ' ' && x == padding)
			return;
		outchar(ch);
		x++;
	}
	void newParagraph() {
		x = padding = 0;
		y += 2;
		outchar('\n');
		outchar('\n');
	}
	void newItem() {
		if (x != 0) {
			y++;
			outchar('\n');
		}
		x = padding = 3;
		outchar(' ');
		outchar('*');
		outchar(' ');
	}
};

// IO
char input[BUFFER_SIZE + 1];
Terminal tty = { 0, 0, 0, 0 };

// state
bool newline = true;
bool asterisk = false;
bool item = false;
bool item1st = false;

// counter
int nspace = 0;
int nline = 0;

int main(void)
{
	tty.x = tty.y = tty.padding = 0;
	scanf("%d\n", &tty.width);

	int readcnt;
	while ((readcnt = fread(input, 1, BUFFER_SIZE, stdin)) > 0)
	{
		char *scan = input;
		input[readcnt] = 0;
		while (*scan)
		{
			switch (*scan) {
			case '\n':
				nline++;
				if (asterisk) {
					if (newline && item && nspace < 2) {
						item = false;
						tty.newParagraph();
					}
					asterisk = false;
					tty.write('*');
				}
				if (item && item1st)
					item1st = false;
				nspace = 0;
				newline = true;
				break;
			case ' ':
				if (asterisk) {
					item = item1st = true;
					asterisk = false;
					tty.newItem();
				} else {
					nspace++;
				}
				break;
			case '*':
				if (newline && !asterisk && nspace == 0) {
					asterisk = true;
					if ((!item && nline > 0) || nline > 1) {
						tty.newParagraph();
					}
					nline = 0;
					break;
				}
			default:
				if (newline) {
					if (nline > 1) {
						item = false;
						tty.newParagraph();
					} else if (nline == 1) {
						tty.write(' ');
					}
					if (item && !item1st && nspace < 2) {
						item = false;
						if (nline <= 1)
							tty.newParagraph();
					}
					newline = false;
					nline = 0;
					nspace = 0;
				}
				if (asterisk) {
					asterisk = false;
					tty.write('*');
				} else {
					while (nspace > 0) {
						tty.write(' ');
						nspace--;
					}
				}
				tty.write(*scan);
			}
			scan++;
		}
	}

	outchar('\n');
	outchar('\n');
	printf("%d\n", tty.y + 1);

	return 0;
}