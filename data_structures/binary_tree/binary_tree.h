#ifndef _INT_BINARY_TREE_
#define _INT_BINARY_TREE_

#include <vector>

namespace data_structures
{
    class binary_tree
    {
    public:
        binary_tree();
        binary_tree(const binary_tree &v);
        ~binary_tree();
        int size() const { return _size; }
        bool empty() const { return _size == 0; }
        void insert(int item);
        bool search(int item) const;
        void remove(int item);
        int count(int item) const;
        void clear();

        std::vector<int> preorder_traverse() const;
        std::vector<int> inorder_traverse() const;
        std::vector<int> postorder_traverse() const;

    private:
        struct tree_node
        {
            int value;
            tree_node *parent;
            tree_node *left;
            tree_node *right;
            tree_node(int value = 0, tree_node *parent = nullptr, tree_node *left = nullptr, tree_node *right = nullptr) : value(value), left(left), right(right) {}
        };
        int _size;
        tree_node *_root;

        void dfs_clear(tree_node *node);
        tree_node *dfs_insert(tree_node *node, int item);
        bool dfs_search(tree_node *node, int item) const;
        void dfs_remove(tree_node *node, int item);
        int dfs_count(tree_node *node, int item) const;

    public:
        class iterator
        {
        public:
            int &operator*();
            iterator &operator++();
            iterator operator++(int);
            iterator &operator--();
            iterator operator--(int);
            bool operator==(const iterator &v) const;
            bool operator!=(const iterator &v) const { return !(*this == v); }

        private:
            const binary_tree *_container;
            tree_node *_node;
            iterator(const binary_tree *container, tree_node *node) : _container(container), _node(node) {}
            friend class binary_tree;
        };

        iterator begin() const;
        iterator end() const;
        iterator reverse_begin() const;
        iterator reverse_end() const;
    };
} // end of namespace

#endif