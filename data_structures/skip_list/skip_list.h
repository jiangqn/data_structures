#ifndef _INT_SKIP_LIST_
#define _INT_SKIP_LIST_

#include <vector>
#include <map>

namespace data_structures
{
    class skip_list
    {
    public:
        skip_list();
        skip_list(const skip_list &v);
        ~skip_list();

        int size() const { return _size; }
        bool empty() const { return _size == 0; }
        int layers() const { return _layers.size(); }
        void insert(int item);
        bool search(int item) const;
        void remove(int item);
        void clear();

        skip_list &operator=(const skip_list &v);
        bool operator==(const skip_list &v) const;
        bool operator!=(const skip_list &v) const { return !(*this == v); }

    private:
        struct skip_list_node
        {
            int value;
            skip_list_node *left;
            skip_list_node *right;
            skip_list_node *up;
            skip_list_node *down;
            skip_list_node(int value = 0, skip_list_node *left = nullptr, skip_list_node *right = nullptr, skip_list_node *up = nullptr, skip_list_node *down = nullptr)
            {
                this->value = value;
                this->left = left;
                this->right = right;
                this->up = up;
                this->down = down;
            }
        };

        struct layer
        {
            skip_list_node *head;
            skip_list_node *tail;
            layer(skip_list_node *head, skip_list_node *tail) : head(head), tail(tail) {}
        };

        std::vector<layer> _layers;
        int _size;
        static const int _inf = 0x3f3f3f3f;

        bool roll() const;
        void add_layer();

    public:
        class iterator
        {
        public:
            int &operator*() const { return _node->value; }
            iterator &operator++();
            iterator operator++(int);
            iterator &operator--();
            iterator operator--(int);
            bool operator==(const iterator &v) const { return _container == v._container && _node == v._node; }
            bool operator!=(const iterator &v) const { return !(*this == v); }

        private:
            const skip_list *_container;
            skip_list_node *_node;
            iterator(skip_list *container, skip_list_node *node) : _container(container), _node(node) {}
            friend class skip_list;
        };

        iterator begin() { return iterator(this, _layers.head->right); }
        iterator end() { return iterator(this, _layers[0].tail); }
        iterator reverse_begin() { return iterator(this, _layers[0].tail->left); }
        iterator reverse_end() { return iterator(this, _layers[0].head); }
    };
} // end of namespace

#endif