#ifndef _INT_LIST_
#define _INT_LIST_

#include <iostream>

namespace data_structures
{

    class list
    {
    public:
        list();
        list(const list &v);
        ~list();
        int size() const { return _size; }
        int empty() const { return _size == 0; }
        void push_front(int item);
        void push_back(int item);
        void pop_front();
        void pop_back();
        int front() const;
        int back() const;
        list &operator=(const list &v);
        bool operator==(const list &v) const;
        bool operator!=(const list &v) const { return !(*this == v); }

        friend std::ostream &operator<<(std::ostream &os, const list &v);

    private:
        struct list_node
        {
            int value;
            list_node *left;
            list_node *right;
            list_node(int value = 0, list_node *left = nullptr, list_node *right = nullptr) : value(value), left(left), right(right) {}
        };

        int _size;
        list_node *_head;
        list_node *_tail;
    };

} // end of namespace

#endif