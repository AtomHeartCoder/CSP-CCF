#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

static uint8_t daysOfMonths[13] = {
	0,
	31, 28, 31, 30, 31, 30,
	31, 31, 30, 31, 30, 31
};

static map<string, int> word2num = {
	{"jan", 1}, {"feb", 2}, {"mar", 3}, {"apr", 4}, {"may", 5}, {"jun", 6},
	{"jul", 7}, {"aug", 8}, {"sep", 9}, {"oct", 10}, {"nov", 11}, {"dec", 12},
	{"sun", 0}, {"mon", 1}, {"tue", 2}, {"wed", 3}, {"thu", 4}, {"fri", 5}, {"sat", 6}
};

struct Time {
	uint16_t	year;
	uint8_t		month;
	uint8_t		dayOfMonth;
	uint8_t		dayOfWeek;
	uint8_t		hour;
	uint8_t		minute;
	void tick(void) {
		if (++minute >= 60) {
			minute = 0;
			if (++hour >= 24) {
				hour = 0;
				int days = daysOfMonths[month];
				if (month == 2) {
					bool isLeapYear = (year % 100 == 0) ? (year % 400 == 0) : (year % 4 == 0);
					if (isLeapYear) days++;
				}
				if (++dayOfMonth > days) {
					dayOfMonth = 1;
					if (++month > 12) {
						month = 1;
						year++;
					}
				}
				if (++dayOfWeek >= 7)
					dayOfWeek = 0;
			}
		}
	}
	bool operator<(const Time &t) const {
		if (year != t.year)
			return year < t.year;
		if (month != t.month)
			return month < t.month;
		if (dayOfMonth != t.dayOfMonth)
			return dayOfMonth < t.dayOfMonth;
		if (hour != t.hour)
			return hour < t.hour;
		return minute < t.minute;
	}
	int daysTo(const Time &t) const {
		int days = 0;
		auto y = year;
		auto m = month;
		for (; y < t.year - 1; y++)
			days += ((y % 100 == 0) ? (y % 400 == 0) : (y % 4 == 0)) ? 366 : 365;
		while (y < t.year || m != t.month) {
			days += daysOfMonths[m];
			if (m == 2 && ((y % 100 == 0) ? (y % 400 == 0) : (y % 4 == 0)))
				days += 1;
			if (++m > 12) {
				m = 1;
				y++;
			}
		}
		days += t.dayOfMonth - dayOfMonth;
		return days;
	}
};

struct Event {
	uint64_t	minute;
	uint32_t	hour;
	uint32_t	dayOfMonth;
	uint16_t	month;
	uint8_t		dayOfWeek;
	string		command;
	Event(void) {
		minute = 0;
		hour = 0;
		dayOfMonth = 0;
		month = 0;
		dayOfWeek = 0;
	}
	bool isTime(Time &time) {
		if (!((1ULL << time.minute) & minute))
			return false;
		if (!((1ULL << time.hour) & hour))
			return false;
		if (!((1ULL << time.dayOfMonth) & dayOfMonth))
			return false;
		if (!((1ULL << time.month) & month))
			return false;
		if (!((1ULL << time.dayOfWeek) & dayOfWeek))
			return false;
		return true;
	}
};

static void parseTime(Time &time, long long raw)
{
	Time standard = { 1970, 1, 1, 4, 0, 0 };
	time.minute = raw % 100;
	raw /= 100;
	time.hour = raw % 100;
	raw /= 100;
	time.dayOfMonth = raw % 100;
	raw /= 100;
	time.month = raw % 100;
	raw /= 100;
	time.year = raw;
	time.dayOfWeek = (standard.dayOfWeek + standard.daysTo(time)) % 7;
}

static uint64_t parseInput(char *&input)
{
	while (*input == ' ')
		input++;
	if (*input == '*') {
		input++;
		return ~0;
	}

	uint64_t bitset = 0;
	int begin, end;
	bool range = false;
	bool letter = false;
	char *p = input;
	bool gotspace = false;
	while (!gotspace) {
		if (*p == ',' || *p == ' ') {
			if (*p == ' ')
				gotspace = true;
			*p = 0;
			if (letter) {
				letter = false;
				end = word2num[strlwr(input)];
			} else {
				end = atoi(input);
			}
			if (range) {
				range = false;
			} else {
				begin = end;
			}
			while (begin <= end) {
				bitset |= 1ULL << begin;
				begin++;
			}
			input = p + 1;
		} else if (*p == '-') {
			range = true;
			*p = 0;
			if (letter) {
				letter = false;
				begin = word2num[strlwr(input)];
			} else {
				begin = atoi(input);
			}
			input = p + 1;
		} else if (*p > '9') {
			letter = true;
		}
		p++;
	}

	return bitset;
}

static void parseEvent(Event &event, char *input)
{
	event.minute = parseInput(input);
	event.hour = parseInput(input);
	event.dayOfMonth = parseInput(input);
	event.month = parseInput(input);
	event.dayOfWeek = parseInput(input);
	while (*input == ' ')
		input++;
	event.command.assign(input);
}

#define LENGTH 128

int main(void)
{
	int n;
	long long s, t;
	cin >> n >> s >> t;
	cin.ignore(100, '\n');

	Time now;
	Time end;
	parseTime(now, s);
	parseTime(end, t);

	char input[LENGTH];
	vector<Event> events(n);
	for (int i = 0; i < n; i++) {
		cin.getline(input, LENGTH);
		parseEvent(events[i], input);
	}

	while (now < end) {
		for (int i = 0; i < n; i++) {
			Event &event = events[i];
			if (event.isTime(now)) {
				printf("%04d%02d%02d%02d%02d ", now.year, now.month, now.dayOfMonth, now.hour, now.minute);
				cout << event.command.c_str() << endl;
			}
		}
		now.tick();
	}

	return 0;
}