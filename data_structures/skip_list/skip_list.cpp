#include "skip_list.h"

#include <random>
#include <algorithm>
#include <assert.h>

namespace data_structures
{
    skip_list::skip_list()
    {
        _size = 0;
        add_layer();
    }

    skip_list::skip_list(const skip_list &v)
    {
        // to be complete
    }

    skip_list::~skip_list()
    {
        for (auto &l : _layers)
        {
            skip_list_node *head = l.head;
            while (head != nullptr)
            {
                skip_list_node *tmp = head->right;
                delete head;
                head = tmp;
            }
        }
        _size = 0;
    }

    void skip_list::clear()
    {
        for (auto &l : _layers)
        {
            skip_list_node *head = l.head;
            while (head != nullptr)
            {
                skip_list_node *tmp = head->right;
                delete head;
                head = tmp;
            }
        }
        _size = 0;
        add_layer();
    }

    void skip_list::insert(int item)
    {
        std::vector<skip_list_node *> path = get_path(item);
        reverse(path.begin(), path.end());
        skip_list_node *down_node = nullptr;
        bool flag = true;
        for (int i = 0; i < path.size(); i++)
        {
            if (i > 0 && !roll())
            {
                flag = false;
                break;
            }
            down_node = increase_layer(down_node, path[i], item);
        }
        while (flag && roll())
        {
            add_layer();
            down_node = increase_layer(down_node, _layers.back().head, item);
        }
        _size += 1;
    }

    bool skip_list::search(int item) const
    {
        return get_path(item).back()->value == item;
    }

    void skip_list::remove(int item)
    {
        skip_list_node *node = get_path(item).back();
        if (node->value == item)
        {
            while (node != nullptr)
            {
                node->left->right = node->right;
                node->right->left = node->left;
                skip_list_node *tmp = node->up;
                delete node;
                node = tmp;
            }
            _size -= 1;
        }
    }

    bool skip_list::roll() const
    {
        return rand() % 2 == 0;
    }

    void skip_list::add_layer()
    {
        skip_list_node *head = new skip_list_node(-_inf);
        skip_list_node *tail = new skip_list_node(_inf);
        head->right = tail;
        tail->left = head;
        if (!_layers.empty())
        {
            layer last_layer = _layers.back();
            last_layer.head->up = head;
            head->down = last_layer.head;
        }
        _layers.push_back(layer(head, tail));
    }

    std::vector<skip_list::skip_list_node *> skip_list::get_path(int item) const
    {
        std::vector<skip_list_node *> path;
        skip_list_node *node = _layers.back().head;
        while (node != nullptr)
        {
            if (node->right != nullptr && node->right->value <= item)
            {
                node = node->right;
            }
            else
            {
                path.push_back(node);
                node = node->down;
            }
        }
        return path;
    }

    skip_list::skip_list_node *skip_list::increase_layer(skip_list_node *down_node, skip_list_node *left_node, int item)
    {
        skip_list_node *node = new skip_list_node(item, left_node, left_node->right, nullptr, down_node);
        if (down_node != nullptr)
        {
            down_node->up = node;
        }
        left_node->right->left = node;
        left_node->right = node;
        return node;
    }

    skip_list::iterator &skip_list::iterator::operator++()
    {
        skip_list_node *tail = _container->_layers.front().tail;
        assert(_node != tail);
        _node = _node->right;
        return *this;
    }

    skip_list::iterator skip_list::iterator::operator++(int)
    {
        skip_list_node *tail = _container->_layers.front().tail;
        assert(_node != tail);
        iterator copy_iterator(*this);
        _node = _node->right;
        return copy_iterator;
    }

    skip_list::iterator &skip_list::iterator::operator--()
    {
        skip_list_node *head = _container->_layers.front().head;
        assert(_node != head);
        _node = _node->left;
        return *this;
    }

    skip_list::iterator skip_list::iterator::operator--(int)
    {
        skip_list_node *head = _container->_layers.front().head;
        assert(_node != head);
        iterator copy_iterator(*this);
        _node = _node->left;
        return copy_iterator;
    }

} // end of namespace