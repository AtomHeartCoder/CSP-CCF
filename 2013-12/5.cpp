#include <iostream>
#include <cstring>

using namespace std;

int R, C;
char map[52][52];
bool been[52][52];

// int walk(int x, int y)
// {
//     if (x < 0 || x >= R || y < 0 || y >= C || map[x][y] == '#') {
//         return -1;
//     }
//     been[x][y] = true;
//     switch(map[x][y]) {
//         case 'S':
//         case '+':
//             walk(x, y);
//             walk(x, y);
//             walk(x, y);
//             walk(x, y);
//         case '-':
//         case '|':
//         case '.':
//         case 'T':


//     }
// }


int main(void)
{
    cin >> R >> C;
    int S_x, S_y;
    int T_x, T_y;
    memset(map, '#', 52 * 52);
    for (int r = 1; r <= R; r++) {
        for (int c = 1; c <= C; c++) {
            cin >> map[r][c];
            been[r][c] = false;
            if (map[r][c] == 'S') {
                S_x = r, S_y = c;
            } else if (map[r][c] == 'T') {
                T_x = r, T_y = c;
            }
        }
    }
    // walk(S_x, S_y);



    return 0;
}
