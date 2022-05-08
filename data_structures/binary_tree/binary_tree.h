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
        std::vector<std::vector<int>> layerorder_traverse() const;

        binary_tree &operator=(const binary_tree &v);
        bool operator==(const binary_tree &v) const { return _size == v._size && dfs_equal(_root, v._root); }
        bool operator!=(const binary_tree &v) const { return !(*this == v); }

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
        tree_node *dfs_remove(tree_node *node, int item);
        tree_node *subtrees_merge(tree_node *left_subtree, tree_node *right_subtree);
        int dfs_count(tree_node *node, int item) const;
        bool dfs_equal(tree_node *node1, tree_node *node2) const;
        tree_node *dfs_copy(tree_node *node) const;

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
            const binary_tree *_container;
            tree_node *_node;
            iterator(const binary_tree *container, tree_node *node) : _container(container), _node(node) {}
            tree_node *move_left(tree_node *node) const;
            tree_node *move_right(tree_node *node) const;
            friend class binary_tree;
        };

        iterator begin() const;
        iterator end() const { return iterator(this, nullptr); }
        iterator reverse_begin() const;
        iterator reverse_end() const { return iterator(this, nullptr); }
    };
} // end of namespace

#endif