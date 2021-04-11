#include <iostream>

using namespace std;

struct Child {
    int num;
    Child *next;
    Child(int n, Child *p) {
        num = n, next = p;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;
    Child *head, *p;
    head = new Child(1, 0);
    head->next = head;
    for (int i = n; i > 1; i--) {
        head->next = new Child(i, head->next);
    }
    p = head;
    int num = 1;
    for (p = head; p != p->next; num++) {
        if ((num % k) == 0 || (num % 10) == k) {
            Child *kick = p->next;
            p->num = p->next->num;
            p->next = p->next->next;
            delete kick;
        } else {
            p = p->next;
        }
    }
    cout << p->num << endl;
    return 0;
}
