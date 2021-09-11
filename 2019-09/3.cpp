#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

static uint8_t charToHex(char ch)
{
	if (ch >= 'a')
		ch -= 'a' - 0xa;
	else if (ch >= 'A')
		ch -= 'A' - 0xA;
	else
		ch -= '0';
	return ch;
}

static char hexToChar(char hex)
{
	if (hex <= 9)
		hex += '0';
	else
		hex += 'A' - 0xA;
	return hex;
}

static char convert(char high4bits, char low4bits)
{
	return ((charToHex(high4bits) << 4) | charToHex(low4bits));
}

static char *format(char *output, uint8_t num)
{
	char x__ = num / 100;
	char _x_ = (num % 100) / 10;
	char __x = num % 10;

	char *p = output;
	if (x__ != 0)
		p += sprintf(p, "\\x%X\\x%X", hexToChar(x__), hexToChar(_x_));
	else if (_x_ != 0)
		p += sprintf(p, "\\x%X", hexToChar(_x_));

	sprintf(p, "\\x%X", hexToChar(__x));
	return output;
}

int main(void)
{
	int width, height;
	int w, h;
	cin >> width >> height >> w >> h;
	cin.ignore(8, '\n');

	int nblkw = width / w;
	int nblkh = height / h;

	vector<vector<int>> red(nblkh, vector<int>(nblkw, 0));
	vector<vector<int>> green(nblkh, vector<int>(nblkw, 0));
	vector<vector<int>> blue(nblkh, vector<int>(nblkw, 0));

	char buf[32];
	uint8_t r, g, b;
	for (int hh = 0; hh < height; hh++) {
		int blkh = hh / h;
		for (int ww = 0; ww < width; ww++) {
			cin.getline(buf, sizeof(buf));
			if (buf[2] == 0) {
				r = g = b = convert(buf[1], buf[1]);
			} else if (buf[4] == 0) {
				r = convert(buf[1], buf[1]);
				g = convert(buf[2], buf[2]);
				b = convert(buf[3], buf[3]);
			} else {
				r = convert(buf[1], buf[2]);
				g = convert(buf[3], buf[4]);
				b = convert(buf[5], buf[6]);
			}
			int blkw = ww / w;
			red[blkh][blkw] += r;
			green[blkh][blkw] += g;
			blue[blkh][blkw] += b;
		}
	}

	int wh = w * h;
	char redbuf[16];
	char greenbuf[16];
	char bluebuf[16];
	for (int hh = 0; hh < nblkh; hh++) {
		r = g = b = 0;
		for (int ww = 0; ww < nblkw; ww++) {
			uint8_t rr = (red[hh][ww] / wh);
			uint8_t gg = (green[hh][ww] / wh);
			uint8_t bb = (blue[hh][ww] / wh);
			if (rr == r && gg == g && bb == b) {
				printf("\\x20");
				continue;
			}
			if (rr == 0 && gg == 0 && bb == 0) {
				printf("\\x1B\\x5B\\x30\\x6D\\x20");
			} else {
				printf("\\x1B\\x5B\\x34\\x38\\x3B\\x32\\x3B%s\\x3B%s\\x3B%s\\x6D\\x20",
						format(redbuf, rr), format(greenbuf, gg), format(bluebuf, bb));
			}
			r = rr;
			g = gg;
			b = bb;
		}
		if (r == 0 && g == 0 && b == 0)
			printf("\\x0A");
		else
			printf("\\x1B\\x5B\\x30\\x6D\\x0A");
	}

	return 0;
}