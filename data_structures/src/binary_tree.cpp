#include "../include/binary_tree.h"

#include <stack>
#include <queue>
#include <map>
#include <assert.h>

namespace data_structures
{
    binary_tree::binary_tree()
    {
        _size = 0;
        _root = nullptr;
    }

    binary_tree::binary_tree(const binary_tree &v)
    {
        _size = v._size;
        _root = dfs_copy(v._root);
    }

    binary_tree::~binary_tree()
    {
        clear();
    }

    void binary_tree::clear()
    {
        dfs_clear(_root);
        _root = nullptr;
        _size = 0;
    }

    void binary_tree::dfs_clear(tree_node *node)
    {
        if (node != nullptr)
        {
            dfs_clear(node->left);
            dfs_clear(node->right);
            delete node;
        }
    }

    void binary_tree::insert(int item)
    {
        _root = dfs_insert(_root, item);
        _size += 1;
    }

    binary_tree::tree_node *binary_tree::dfs_insert(tree_node *node, int item)
    {
        if (node != nullptr)
        {
            if (item < node->value)
            {
                node->left = dfs_insert(node->left, item);
                node->left->parent = node;
            }
            else // item >= node->value
            {
                node->right = dfs_insert(node->right, item);
                node->right->parent = node;
            }
            return node;
        }
        else
        {
            return new tree_node(item);
        }
    }

    bool binary_tree::search(int item) const
    {
        return dfs_search(_root, item);
    }

    bool binary_tree::dfs_search(tree_node *node, int item) const
    {
        if (node != nullptr)
        {
            if (item == node->value)
            {
                return true;
            }
            else if (item < node->value)
            {
                return dfs_search(node->left, item);
            }
            else // item > node->value
            {
                return dfs_search(node->right, item);
            }
        }
        else
        {
            return false;
        }
    }

    void binary_tree::remove(int item)
    {
        _root = dfs_remove(_root, item);
        _size -= 1;
    }

    binary_tree::tree_node *binary_tree::dfs_remove(tree_node *node, int item)
    {
        if (node != nullptr)
        {
            if (item < node->value)
            {
                node->left = dfs_remove(node->left, item);
                if (node->left != nullptr)
                {
                    node->left->parent = node;
                }
                return node;
            }
            else if (item > node->value)
            {
                node->right = dfs_remove(node->right, item);
                if (node->right != nullptr)
                {
                    node->right->parent = node;
                }
                return node;
            }
            else // item == node->value
            {
                tree_node *new_node = subtrees_merge(node->left, node->right);
                delete node;
                return new_node;
            }
        }
        else
        {
            return nullptr;
        }
    }

    binary_tree::tree_node *binary_tree::subtrees_merge(tree_node *left_subtree, tree_node *right_subtree)
    {
        if (left_subtree == nullptr)
        {
            return right_subtree;
        }
        else if (right_subtree == nullptr)
        {
            return left_subtree;
        }
        else
        {
            right_subtree->left = subtrees_merge(left_subtree, right_subtree->left);
            return right_subtree;
        }
    }

    int binary_tree::count(int item) const
    {
        return dfs_count(_root, item);
    }

    int binary_tree::dfs_count(tree_node *node, int item) const
    {
        if (node != nullptr)
        {
            if (item < node->value)
            {
                return dfs_count(node->left, item);
            }
            else if (item > node->value)
            {
                return dfs_count(node->right, item);
            }
            else // item == node->value
            {
                return 1 + dfs_count(node->left, item) + dfs_count(node->right, item);
            }
        }
        else
        {
            return 0;
        }
    }

    std::vector<int> binary_tree::preorder_traverse() const
    {
        std::stack<tree_node *> s;
        std::vector<int> res;
        tree_node *node = _root;
        while (node != nullptr || !s.empty())
        {
            while (node != nullptr)
            {
                res.push_back(node->value);
                s.push(node);
                node = node->left;
            }
            node = s.top()->right;
            s.pop();
        }
        return res;
    }

    std::vector<int> binary_tree::inorder_traverse() const
    {
        std::stack<tree_node *> s;
        std::vector<int> res;
        tree_node *node = _root;
        while (node != nullptr || !s.empty())
        {
            while (node != nullptr)
            {
                s.push(node);
                node = node->left;
            }
            node = s.top();
            s.pop();
            res.push_back(node->value);
            node = node->right;
        }
        return res;
    }

    std::vector<int> binary_tree::postorder_traverse() const
    {
        std::stack<tree_node *> s;
        std::vector<int> res;
        tree_node *node = _root;
        tree_node *prev = nullptr;
        while (node != nullptr || !s.empty())
        {
            while (node != nullptr)
            {
                s.push(node);
                node = node->left;
            }
            node = s.top();
            s.pop();
            if (node->right == nullptr || node->right == prev)
            {
                res.push_back(node->value);
                prev = node;
                node = nullptr;
            }
            else
            {
                s.push(node);
                node = node->right;
            }
        }
        return res;
    }

    std::vector<std::vector<int>> binary_tree::layerorder_traverse() const
    {
        typedef std::pair<tree_node *, int> queue_node;
        std::queue<queue_node> que;
        std::vector<std::vector<int>> res;
        if (_root != nullptr)
        {
            que.push(queue_node(_root, 0));
        }
        while (!que.empty())
        {
            queue_node qnode = que.front();
            que.pop();
            tree_node *node = qnode.first;
            int depth = qnode.second;
            if (res.size() <= depth)
            {
                std::vector<int> empty;
                res.push_back(empty);
            }
            res[depth].push_back(node->value);
            if (node->left != nullptr)
            {
                que.push(queue_node(node->left, depth + 1));
            }
            if (node->right != nullptr)
            {
                que.push(queue_node(node->right, depth + 1));
            }
        }
        return res;
    }

    bool binary_tree::dfs_equal(tree_node *node1, tree_node *node2) const
    {
        if (node1 == nullptr && node2 == nullptr)
        {
            return true;
        }
        else if (node1 == nullptr || node2 == nullptr)
        {
            return false;
        }
        else
        {
            return dfs_equal(node1->left, node2->left) && dfs_equal(node1->right, node2->right);
        }
    }

    binary_tree &binary_tree::operator=(const binary_tree &v)
    {
        if (this != &v)
        {
            clear();
            _size = v._size;
            _root = dfs_copy(v._root);
        }
        return *this;
    }

    binary_tree::tree_node *binary_tree::dfs_copy(tree_node *node) const
    {
        if (node != nullptr)
        {
            tree_node *copy_left = dfs_copy(node->left);
            tree_node *copy_right = dfs_copy(node->right);
            tree_node *copy_node = new tree_node(node->value, nullptr, copy_left, copy_right);
            if (copy_left != nullptr)
            {
                copy_left->parent = copy_node;
            }
            if (copy_right != nullptr)
            {
                copy_right->parent = copy_node;
            }
            return copy_node;
        }
        else
        {
            return nullptr;
        }
    }

    const binary_tree::iterator binary_tree::begin() const
    {
        tree_node *node = _root;
        while (node != nullptr && node->left != nullptr)
        {
            node = node->left;
        }
        return iterator(this, node);
    }

    const binary_tree::iterator binary_tree::reverse_begin() const
    {
        tree_node *node = _root;
        while (node != nullptr && node->right != nullptr)
        {
            node = node->right;
        }
        return iterator(this, node);
    }

    binary_tree::iterator &binary_tree::iterator::operator++()
    {
        assert(_node != nullptr);
        _node = move_right(_node);
        return *this;
    }

    binary_tree::iterator binary_tree::iterator::operator++(int)
    {
        assert(_node != nullptr);
        iterator copy_iterator(*this);
        _node = move_right(_node);
        return copy_iterator;
    }

    binary_tree::iterator &binary_tree::iterator::operator--()
    {
        assert(_node != nullptr);
        _node = move_left(_node);
        return *this;
    }

    binary_tree::iterator binary_tree::iterator::operator--(int)
    {
        assert(_node != nullptr);
        iterator copy_iterator(*this);
        _node = move_left(_node);
        return copy_iterator;
    }

    binary_tree::tree_node *binary_tree::iterator::move_left(tree_node *node) const
    {
        if (node != nullptr)
        {
            if (node->left != nullptr)
            {
                node = node->left;
                while (node->right != nullptr)
                {
                    node = node->right;
                }
                return node;
            }
            else
            {
                while (node->parent != nullptr)
                {
                    if (node == node->parent->right)
                    {
                        return node->parent;
                    }
                    else
                    {
                        node = node->parent;
                    }
                }
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }

    binary_tree::tree_node *binary_tree::iterator::move_right(tree_node *node) const
    {
        if (node != nullptr)
        {
            if (node->right != nullptr)
            {
                node = node->right;
                while (node->left != nullptr)
                {
                    node = node->left;
                }
                return node;
            }
            else
            {
                while (node->parent != nullptr)
                {
                    if (node == node->parent->left)
                    {
                        return node->parent;
                    }
                    else
                    {
                        node = node->parent;
                    }
                }
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }

    binary_tree::iterator &binary_tree::iterator::operator=(const iterator &it)
    {
        assert(_container == it._container);
        _node = it._node;
        return *this;
    }

} // end of namespace
