#include "binary_tree.h"

#include <stack>

namespace data_structures
{
    binary_tree::binary_tree()
    {
        _size = 0;
        _root = nullptr;
    }

    binary_tree::binary_tree(const binary_tree &v)
    {
        // to be complete
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
            }
            else // item >= node->value
            {
                node->right = dfs_insert(node->right, item);
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
        // to be complete
    }

    // int binary_tree::count(int item)
    // {
    //     // to be complete
    // }

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

    // binary_tree::iterator binary_tree::begin() const
    // {
    //     // to be complete
    // }

    // binary_tree::iterator binary_tree::end() const
    // {
    //     // to be complete
    // }

    // binary_tree::iterator binary_tree::reverse_begin() const
    // {
    //     // to be complete
    // }

    // binary_tree::iterator binary_tree::reverse_end() const
    // {
    //     // to be complete
    // }

} // end of namespace