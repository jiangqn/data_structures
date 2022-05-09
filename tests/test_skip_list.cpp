#include <iostream>
#include "../data_structures/skip_list/skip_list.h"
#include <algorithm>

using namespace std;
using namespace data_structures;

void print_vector(const vector<int> &v)
{
    int n = v.size();
    cout << "print vector with " << n << " items." << endl;
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << (i == n - 1 ? '\n' : ' ');
    }
}

int main()
{
    vector<int> vec;
    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }
    random_shuffle(vec.begin(), vec.end());
    print_vector(vec);
    skip_list v;
    cout << v.size() << endl;
    for (auto x : vec)
    {
        v.insert(x);
    }
    cout << v.size() << endl;
    for (int i = 3; i < 8; i++)
    {
        v.remove(i);
    }
    for (int i = -5; i < 20; i++)
    {
        cout << i << " " << v.search(i) << endl;
    }
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    for (auto it = v.reverse_begin(); it != v.reverse_end(); --it)
    {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}