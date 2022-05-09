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

    list::list(const list &v)
    {
        _size = v._size;
        _head = new list_node;
        _tail = new list_node;
        list_node *target = _head;
        list_node *source = v._head->right;
        while (source != v._tail)
        {
            target->right = new list_node(source->value, target, nullptr);
            target = target->right;
            source = source->right;
        }
        target->right = _tail;
        _tail->left = target;
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

    void list::push_back(int item)
    {
        list_node *node = new list_node(item, _tail->left, _tail);
        _tail->left->right = node;
        _tail->left = node;
        _size += 1;
    }

    void list::pop_back()
    {
        assert(_size > 0);
        list_node *node = _tail->left;
        node->left->right = _tail;
        _tail->left = node->left;
        delete node;
        _size -= 1;
    }

    int &list::front() const
    {
        assert(_size > 0);
        return _head->right->value;
    }

    int &list::back() const
    {
        assert(_size > 0);
        return _tail->left->value;
    }

    void list::clear()
    {
        list_node *current = _head;
        do
        {
            list_node *tmp = current->right;
            delete current;
            current = tmp;
        } while (current == nullptr);
        _size = 0;
        _head = new list_node;
        _tail = new list_node;
        _head->right = _tail;
        _tail->left = _head;
    }

    list &list::operator=(const list &v)
    {
        if (this != &v)
        {
            clear();
            _size = v._size;
            list_node *target = _head;
            list_node *source = v._head->right;
            while (source != v._tail)
            {
                target->right = new list_node(source->value, target, nullptr);
                target = target->right;
                source = source->right;
            }
            target->right = _tail;
            _tail->left = target;
        }
        return *this;
    }

    bool list::operator==(const list &v) const
    {
        bool flag = true;
        if (this != &v)
        {
            if (_size == v._size)
            {
                list_node *current = _head->right;
                list_node *v_current = v._head->right;
                while (current != nullptr || v_current != nullptr)
                {
                    if (current == nullptr || v_current == nullptr)
                    {
                        flag = false;
                        break;
                    }
                    if (current->value != v_current->value)
                    {
                        flag = false;
                        break;
                    }
                    current = current->right;
                    v_current = v_current->right;
                }
            }
            else
            {
                flag = true;
            }
        }
        return flag;
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

    list::iterator &list::iterator::operator++()
    {
        assert(_node != _container->_tail);
        _node = _node->right;
        return *this;
    }

    list::iterator list::iterator::operator++(int)
    {
        assert(_node != _container->_tail);
        list::iterator copy_iterator(*this);
        _node = _node->right;
        return copy_iterator;
    }

    list::iterator &list::iterator::operator--()
    {
        assert(_node != _container->_head);
        _node = _node->left;
        return *this;
    }

    list::iterator list::iterator::operator--(int)
    {
        assert(_node != _container->_head);
        list::iterator copy_iterator(*this);
        _node = _node->left;
        return copy_iterator;
    }

    list::iterator &list::iterator::operator=(const iterator &it)
    {
        assert(_container == it._container);
        _node = it._node;
        return *this;
    }

} // end of namespace