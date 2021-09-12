#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <list>

using namespace std;

struct Dentry {
	string name;
	bool dir;
	uint64_t size;
	uint64_t ld;
	uint64_t lr;
	uint64_t d_sum;
	uint64_t r_sum;
	Dentry *parent;
	list<Dentry *> children;
	
	Dentry(const char *filename, bool isdir, uint64_t filesize, Dentry *parent) {
		name.assign(filename);
		dir = isdir;
		this->parent = parent;
		ld = lr = d_sum = r_sum = 0;
		size = isdir ? 0 : filesize;
	}
	Dentry *lookup(const char *filename) const {
		for (Dentry *d : children) {
			if (strcmp(d->name.c_str(), filename) == 0)
				return d;
		}
		return nullptr;
	}
	Dentry *create(const char *filename, bool isdir, uint64_t filesize) {
		Dentry *dentry = new Dentry(filename, isdir, filesize, this);
		children.push_back(dentry);
		return dentry;		
	}
	bool unlink(const char *childname) {
		for (auto it = children.begin(); it != children.end(); it++) {
			Dentry *child = *it;
			if (strcmp(child->name.c_str(), childname) == 0) {
				if (child->dir)
					quotaUpdateParent(-child->r_sum);
				else
					quotaUpdate(-child->size);
				child->truncate();
				delete child;
				children.erase(it);
				return true;
			}
		}
		return false;
	}
	void truncate(void) {
		for (auto it = children.begin(); it != children.end();) {
			Dentry *child = *it;
			child->truncate();
			delete child;
			it = children.erase(it);
		}
	}
	bool quotaBreakLD(int64_t diff_size) {
		return ld && d_sum + diff_size > ld;
	}
	bool quotaBreakLR(int64_t diff_size) {
		if (lr && r_sum + diff_size > lr)
			return true;
		if (parent != nullptr)
			return parent->quotaBreakLR(diff_size);
		return false;
	}
	void quotaUpdate(int64_t diff_size) {
		if (diff_size == 0)
			return;
		d_sum += diff_size;
		quotaUpdateParent(diff_size);
	}
	void quotaUpdateParent(int64_t diff_size) {
		r_sum += diff_size;
		if (parent != nullptr)
			parent->quotaUpdateParent(diff_size);
	}
};

Dentry root("", true, 0, nullptr);

Dentry *create(Dentry *dir, const char *filename, bool isdir, uint64_t filesize)
{
	Dentry *dentry = dir->lookup(filename);
	if (dentry == nullptr) {
		if (dir->quotaBreakLR(filesize) ||
			(!isdir && dir->quotaBreakLD(filesize)))
			return nullptr;
		dentry = dir->create(filename, isdir, isdir ? 0 : filesize);
		if (!isdir)
			dir->quotaUpdate(filesize);
	} else {
		if (isdir != dentry->dir)
			return nullptr;
		if (!isdir && !dentry->dir) {
			int64_t diff = filesize - dentry->size;
			if (diff > 0 && (dir->quotaBreakLR(diff) || dir->quotaBreakLD(diff)))
				return nullptr;
			dentry->size = filesize;
			dir->quotaUpdate(diff);
		}
	}
	return dentry;
}

char *skipelem(char *path, char **pname)
{
	while (*path == '/')
		path++;
	*pname = path;
	if (*path == 0)
		return nullptr;
	while (*path != '/' && *path != 0)
		path++;
	if (*path == 0)
		return nullptr;
	*path++ = 0;
	return path;
}

bool createFile(char *path, uint64_t filesize)
{
	Dentry *dentry = &root;
	char *name;
	while (path != nullptr)
	{
		path = skipelem(path, &name);
		if (*name == 0)
			return false;
		Dentry *next = create(dentry, name, path != nullptr, filesize);
		if (next == nullptr)
			return false;
		dentry = next;
	}
	return true;
}

bool removeFile(char *path)
{
	Dentry *dentry = &root;
	char *name;
	for (;;)
	{
		path = skipelem(path, &name);
		if (*name == 0)
			return false;
		if (path == nullptr)
			return dentry->unlink(name);

		Dentry *next = dentry->lookup(name);
		if (next == nullptr || !next->dir)
			return false;
		dentry = next;
	}
}

bool quotaFile(char *path, uint64_t ld, uint64_t lr)
{
	Dentry *dentry = &root;
	char *name;
	for (;;)
	{
		path = skipelem(path, &name);
		if (*name) {
			Dentry *next = dentry->lookup(name);
			if (next == nullptr || !next->dir)
				return false;
			dentry = next;
		}
		if (path == nullptr) {
			if ((ld && dentry->d_sum > ld) || (lr && dentry->r_sum > lr))
				return false;
			dentry->ld = ld;
			dentry->lr = lr;
			return true;
		}
	}
}

int main(void)
{
	int n;
	cin >> n;
	cin.ignore(100, '\n');

	char command;
	char path[256];
	uint64_t arg1, arg2;
	while (n-- > 0) {
		cin >> command;
		cin >> path;
		bool res;
		switch (command) {
		case 'C':
			cin >> arg1;
			res = createFile(path, arg1);
			break;
		case 'R':
			removeFile(path);
			res = true;
			break;
		case 'Q':
			cin >> arg1 >> arg2;
			res = quotaFile(path, arg1, arg2);
			break;
		default:
			res = false;
		}
		cout << (res ? 'Y' : 'N') << endl;
	}
	return 0;
}