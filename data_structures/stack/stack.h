#ifndef _INT_STACK_
#define _INT_STACK_

#include <iostream>
#include "../list/list.h"

namespace data_structures
{
    class stack
    {
    public:
        stack();
        void push(int item) { _data.push_back(item); }
        void pop() { _data.pop_back(); }
        int top() { return _data.back(); }
        int size() { return _data.size(); }
        bool empty() { return _data.size() == 0; }
        bool operator==(const stack &v) const { return _data == v._data; }
        bool operator!=(const stack &v) const { return !(*this == v); }

        friend std::ostream &operator<<(std::ostream &os, const stack &v);

    private:
        list _data;
    };
} // end of namespace

#endif