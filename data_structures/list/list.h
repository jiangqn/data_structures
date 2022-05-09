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
        int &front() const;
        int &back() const;
        void clear();
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

    public:
        class iterator
        {
        public:
            int &operator*() const { return _node->value; }
            iterator &operator++();
            iterator operator++(int);
            iterator &operator--();
            iterator operator--(int);
            iterator(const iterator &it) : _container(it._container), _node(it._node) {}
            iterator &operator=(const iterator &);
            bool operator==(const iterator &it) const { return _container == it._container && _node == it._node; }
            bool operator!=(const iterator &it) const { return !(*this == it); }

        private:
            const list *_container;
            list_node *_node;
            iterator(const list *container, list_node *node) : _container(container), _node(node) {}
            friend class list;
        };
        iterator begin() const { return iterator(this, _head->right); }
        iterator end() const { return iterator(this, _tail); }
        iterator reverse_begin() const { return iterator(this, _tail->left); }
        iterator reverse_end() const { return iterator(this, _head); }
    };

} // end of namespace

#endif