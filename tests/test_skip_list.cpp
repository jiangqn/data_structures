#include <iostream>
#include "../data_structures/skip_list/skip_list.h"

using namespace std;
using namespace data_structures;

int main()
{
    skip_list v;
    cout << v.size() << endl;
    auto x = v.begin();
    return 0;
}