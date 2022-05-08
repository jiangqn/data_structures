#include "skip_list.h"

#include <random>

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
        // to be complete
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
            last_layer.first->up = head;
            head->down = last_layer.first;
        }
        _layers.push_back(layer(head, tail));
    }

} // end of namespace