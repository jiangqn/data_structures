#include <iostream>

#include "../data_structures/list/list.h"

using namespace std;
using namespace data_structures;

int main()
{
    list v;
    for (int i = 0; i < 5; i++)
    {
        v.push_front(i);
    }
    v.pop_front();
    cout << v << endl;
    return 0;
}