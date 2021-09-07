#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct User;
struct Role;

struct Category {
	string name;
	int level;
	map<User *, int> users;
	Category() {}
	Category(char *name, int level) : name(name), level(level) {}
};

struct User {
	string name;
	User() {}
	User(char *name) : name(name) {}
};

struct Role {
	string name;
	map<Category *, int> categories;
	Role() {}
	Role(char *name) : name(name) {}
};

map<string, Category> categories;
map<string, Role> roles;
map<string, User> users;

static Category *getCategory(char *name, int *plevel)
{
	char *p = name;
	int level = -1;
	while (*p && *p != ':')
		p++;
	if (*p == ':') {
		*p = 0;
		level = atoi(p + 1);
	}
	auto it = categories.find(name);
	if (it == categories.end())
		return nullptr;
	*plevel = level;
	return &it->second;
}

static void parseCategory(char *input)
{
	char *p = input;
	int level = -1;
	while (*p && *p != ':')
		p++;
	if (*p == ':') {
		*p = 0;
		level = atoi(p + 1);
	}
	categories[input] = Category(input, level);
}

static void parseRole(char *input)
{
	int nctgry;
	cin >> input;
	cin >> nctgry;

	Role &role = roles[input] = Role(input);
	while (nctgry-- > 0) {
		cin >> input;
		int level;
		Category *cptr = getCategory(input, &level);
		auto it = role.categories.find(cptr);
		if (it == role.categories.end())
			role.categories[cptr] = level;
		else if (level > it->second)
			it->second = level;
	}
}

static void parseUser(char *input)
{
	int nrole;
	cin >> input;
	cin >> nrole;

	User &user = users[input] = User(input);
	while (nrole-- > 0) {
		cin >> input;
		Role &role = roles[input];
		for (auto it = role.categories.begin(); it != role.categories.end(); it++) {
			Category *cptr = it->first;
			int level = it->second;

			auto itu = cptr->users.find(&user);
			if (itu == cptr->users.end()) {
				cptr->users[&user] = level;
			} else if (itu->second < level) {
				itu->second = level;
			}
		}
	}
}

int main(void)
{
	int n;
	char input[64];
	
	cin >> n;
	cin.ignore(100, '\n');
	while (n-- > 0) {
		cin >> input;
		parseCategory(input);
	}

	cin >> n;
	cin.ignore(100, '\n');
	while (n-- > 0) {
		parseRole(input);
	}

	cin >> n;
	cin.ignore(100, '\n');
	while (n-- > 0) {
		parseUser(input);
	}

	cin >> n;
	cin.ignore(100, '\n');
	while (n-- > 0) {
		cin >> input;
		int level;
		auto it = users.find(input);
		cin >> input;
		if (it == users.end()) {
			level = -2;
		} else {
			User &user = it->second;
			Category *cptr = getCategory(input, &level);
			if (cptr == nullptr) {
				level = -2;
			} else {
				auto it2 = cptr->users.find(&user);
				if (it2 == cptr->users.end()) {
					level = -2;
				} else if (level >= 0) {
					level = level <= it2->second ? -1 : -2;
				} else if (it2->second >= 0) {
					level = it2->second;
				}
			}
		}

		if (level < -1) {
			cout << "false";
		} else if (level < 0) {
			cout << "true";
		} else {
			cout << level;
		}
		cout << endl;
	}

	return 0;
}