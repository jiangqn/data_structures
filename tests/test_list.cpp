#include <iostream>

#include "../data_structures/include/list.h"

using namespace std;
using namespace data_structures;

int main()
{
    list v;
    for (int i = 0; i < 5; i++)
    {
        v.push_front(i);
    }
    // cout << v << endl;
    for (int i = 0; i < 2; i++)
    {
        v.pop_front();
    }
    // cout << v << endl;
    for (int i = 0; i < 5; i++)
    {
        v.push_back(i);
    }
    // cout << v << endl;
    for (int i = 0; i < 3; i++)
    {
        v.pop_back();
    }
    cout << v << endl;
    // cout << v.front() << " " << v.back() << endl;
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        *iter = 0;
        // cout << *iter << endl;
    }
    cout << v << endl;
    return 0;
}
