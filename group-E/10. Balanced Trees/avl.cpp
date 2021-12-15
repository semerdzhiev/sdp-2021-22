#include <algorithm>
#include <vector>
#include <iostream>

template <class T>
class avl_tree
{
public:
    template <class U>
    struct node
    {
        U value{};
        node<U> *left{};
        node<U> *right{};
        int height{};
    };

    const node<T> *find(const T &value) const
    {
        return recursive_find(root, value);
    }

    avl_tree() = default;
    // Ro3

    void insert(const T &value)
    {
        root = recursive_insert(root, value);
    }

    void remove(const T &value)
    {
        root = recursive_delete_value(root, value);
    }

    std::vector<T> inorder() const
    {
        return recursive_inorder(root);
    }

private:
    const node<T> *recursive_find(const node<T> *current, const T &value) const
    {
        if (!current)
        {
            return nullptr;
        }
        if (current->value < value)
        {
            return recursive_find(current->right, value);
        }
        else if (current->value > value)
        {
            return recursive_find(current->left, value);
        }
        return current;
    }

    node<T> *recursive_insert(node<T> *current, const T &value)
    {
        if (!current)
        {
            return new node<T>{value, nullptr, nullptr, 1};
        }
        if (current->value < value)
        {
            current->right = recursive_insert(current->right, value);
        }
        else if (current->value > value)
        {
            current->left = recursive_insert(current->left, value);
        }
        else
        {
            return current;
        }

        current->height = std::max(height(current->left), height(current->right)) + 1;

        int balance = balance_factor(current);

        if (balance > 1)
        {
            int balance_left = balance_factor(current->left);
            if (balance_left >= 0)
            {
                return right_rotation(current);
            }
            else
            {
                current->left = left_rotation(current->left);
                return right_rotation(current);
            }
        }
        else if (balance < -1)
        {
            int balance_right = balance_factor(current->right);
            if (balance_right > 0)
            {
                current->right = right_rotation(current->right);
                return left_rotation(current->right);
            }
            else
            {
                return left_rotation(current);
            }
        }
        return current;
    }

    node<T> *right_rotation(node<T> *current)
    {
        auto left_child = current->left;
        auto right_subtree = left_child->right;

        left_child->right = current;
        current->left = right_subtree;

        current->height = std::max(height(current->left), height(current->right)) + 1;
        left_child->height = std::max(height(left_child->left), height(left_child->right)) + 1;
        return left_child;
    }

    node<T> *left_rotation(node<T> *current)
    {
        auto right_child = current->right;
        auto left_subtree = right_child->left;

        right_child->left = current;
        current->right = left_subtree;

        current->height = std::max(height(current->left), height(current->right)) + 1;
        right_child->height = std::max(height(right_child->left), height(right_child->right)) + 1;

        return right_child;
    }

    int balance_factor(node<T> *node) const
    {
        if (!node)
            return 0;
        return height(node->left) - height(node->right);
    }

    int height(node<T> *node) const
    {
        return node ? node->height : 0;
    }

    node<T> *recursive_delete_value(node<T> *curr, const T &value)
    {
        if (!curr)
        {
            return nullptr;
        }
        if (curr->value > value)
        {
            curr->left = recursive_delete_value(curr->left, value);
        }
        else if (curr->value < value)
        {
            curr->right = recursive_delete_value(curr->right, value);
        }
        else
        {
            if (!curr->left && !curr->right)
            {
                return nullptr;
            }
            else if (!curr->left)
            {
                auto temp = curr->right;
                delete curr;
                return temp;
            }
            else if (!curr->right)
            {
                auto temp = curr->left;
                delete curr;
                return temp;
            }
            else
            {
                auto node = find_minimal_value(curr->right);
                curr->value = node->value;
                curr->right = recursive_delete_value(curr->right, node->value);
            }
        }

        curr->height = std::max(height(curr->left), height(curr->right)) + 1;

        int balance = balance_factor(curr);

        if (balance > 1)
        {
            int balance_left = balance_factor(curr->left);
            if (balance_left >= 0)
            {
                return right_rotation(curr);
            }
            else
            {
                curr->left = left_rotation(curr->left);
                return right_rotation(curr);
            }
        }
        else if (balance < -1)
        {
            int balance_right = balance_factor(curr->right);
            if (balance_right > 0)
            {
                curr->right = right_rotation(curr->right);
                return left_rotation(curr->right);
            }
            else
            {
                return left_rotation(curr);
            }
        }

        return curr;
    }

    node<T> *find_minimal_value(node<T> *node)
    {
        auto current = node;
        while (current && current->left)
        {
            current = current->left;
        }
        return current;
    }

    std::vector<T> recursive_inorder(node<T> *node) const
    {
        std::vector<T> inordr;
        if (node->left)
        {
            inordr = recursive_inorder(node->left);
        }
        inordr.push_back(node->value);
        if (node->right)
        {
            auto right_inorder = recursive_inorder(node->right);
            inordr.insert(inordr.end(), right_inorder.begin(), right_inorder.end());
        }
        return inordr;
    }

    node<T> *root{};
};

int main()
{
    avl_tree<int> tr;
    tr.insert(10);
    tr.insert(4);
    tr.insert(72);
    tr.insert(10);
    tr.insert(34);
    tr.insert(14);
    tr.insert(8);
    auto v = tr.inorder();
    for (int i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    tr.remove(72);
    v = tr.inorder();
    for (int i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    auto node = tr.find(8);
    return 0;
}