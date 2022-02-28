#include <iostream>
#include "generator.h"
#include <fstream>
#include <iostream>
using namespace std;


// метод печатает что угодно, у чего есть возможность запускать цикл for (auto x: )
template <class T>
void Print(T someList) {
    for (auto& x : someList) cout << " " << x;
    cout << endl;
}

int main() {
    int m, n;
    cin >> m >> n;
    Generator g(m, n);
    //g.GenerateAll();
    g.GenerateRecursive();

    for (int i = 0; i < g.getCount(); i++) {
        Print(g.GetResult(i));
    }

    cout << "\n" << g.getCount();
    return 0;
}