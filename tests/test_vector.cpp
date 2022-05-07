#include <iostream>

#include "../data_structures/vector/vector.h"

using namespace std;
using namespace data_structures;

int main()
{
    vector v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    vector u(v);
    cout << u << endl;
    cout << (v == u) << endl;
    u[3] = 100;
    v = u;
    cout << v << endl;
    u[4] = 0;
    cout << u << v << endl;
    cout << v.back() << " " << u.back() << endl;
    cout << v[0] << " " << u[0] << endl;
    return 0;
}