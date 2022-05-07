#include <assert.h>

#include "list.h"

namespace data_structures
{
    list::list()
    {
        _size = 0;
        _head = new list_node;
        _tail = new list_node;
        _head->right = _tail;
        _tail->left = _head;
    }

    list::~list()
    {
        list_node *current = _head;
        do
        {
            list_node *tmp = current->right;
            delete current;
            current = tmp;
        } while (current == nullptr);
    }

    void list::push_front(int item)
    {
        list_node *node = new list_node(item, _head, _head->right);
        _head->right->left = node;
        _head->right = node;
        _size += 1;
    }

    void list::pop_front()
    {
        assert(_size > 0);
        list_node *node = _head->right;
        node->right->left = _head;
        _head->right = node->right;
        delete node;
        _size -= 1;
    }

    std::ostream &operator<<(std::ostream &os, const list &v)
    {
        os << "\nlist with " << v._size << " items.\n";
        list::list_node *current = v._head->right;
        while (current != v._tail)
        {
            os << current->value << (current->right == v._tail ? '\n' : ' ');
            current = current->right;
        }
        return os;
    }
} // end of namespace