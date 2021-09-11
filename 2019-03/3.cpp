#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

#define DATA_SIZE		(2 * 40 * 1024)
#define CHAR_PER_BLK	(sizeof(uint32_t) * 2)

struct Disk {
	char data[DATA_SIZE];
	uint32_t read(unsigned blockno) {
		char *p = data + blockno * CHAR_PER_BLK;
		uint32_t blockdata = 0;
		for (int i = 0; i < CHAR_PER_BLK; i++) {
			char ch = *p++;
			if (ch <= '9')
				ch -= '0';
			else if (ch >= 'A')
				ch -= 'A' - 0xA;
			blockdata = (blockdata << 4) | (0xf & ch);
		}
		return blockdata;
	}
};

struct Raid {
	int stripesz;
	unsigned nblock;
	unsigned ndiskblock;
	vector<Disk *> disks;
	Raid(int disk, int strpsz) : disks(disk, nullptr), stripesz(strpsz) {}
	bool read(unsigned blockno, uint32_t *data) {
		if (blockno >= nblock)
			return false;

		int const stripeidx = blockno / stripesz;
		int const datadisks = disks.size() - 1;
		int const stripeno = stripeidx / datadisks;
		int const redundant = datadisks - (stripeno % (datadisks + 1));
		int const diskno = (redundant + 1 + stripeidx % datadisks) % (datadisks + 1);
		int const blkno = stripeno * stripesz + blockno % stripesz;
		
		Disk *disk = disks[diskno];
		if (disk == nullptr) {
			uint32_t rescue = 0;
			for (int i = 0; i < datadisks + 1; i++) {
				if (i == diskno)
					continue;
				Disk *d = disks[i];
				if (d == nullptr)
					return false;
				rescue ^= d->read(blkno);
			}
			*data = rescue;
		} else {
			*data = disk->read(blkno);
		}
		return true;
	}
};

int main(void)
{
	int n, s, l;
	scanf("%d %d %d", &n, &s, &l);

	Raid raid(n, s);
	while (l-- > 0) {
		int diskno;
		scanf("%d ", &diskno);
		Disk *disk = new Disk();
		raid.disks[diskno] = disk;
		fgets(disk->data, DATA_SIZE, stdin);
	}

	for (auto disk : raid.disks) {
		if (disk != nullptr) {
			int len = strlen(disk->data);
			raid.ndiskblock = len / CHAR_PER_BLK;
			raid.nblock = raid.ndiskblock * (raid.disks.size() - 1);
			break;
		}
	}

	int m;
	cin >> m;
	while (m-- > 0) {
		unsigned blockno;
		scanf("%d", &blockno);

		uint32_t data;
		if (!raid.read(blockno, &data))
			printf("-\n");
		else
			printf("%08X\n", data);
	}

	return 0;
}