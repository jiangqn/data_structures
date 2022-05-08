#include <iostream>
#include <algorithm>
#include <vector>
#include "../data_structures/binary_tree/binary_tree.h"

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
    binary_tree v;
    for (auto x : vec)
    {
        v.insert(x);
    }
    print_vector(v.inorder_traverse());
    binary_tree u(v);
    print_vector(u.inorder_traverse());
    cout << (u == v) << endl;
    u.remove(0);
    u.insert(3);
    cout << (u == v) << endl;
    print_vector(u.inorder_traverse());
    return 0;
}