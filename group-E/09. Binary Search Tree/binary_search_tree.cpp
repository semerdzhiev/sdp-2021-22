#include <iostream>
#include <vector>

template <class T>
class binary_search_tree
{
public:
    binary_search_tree(const T &value) : value{value}
    {
    }
    ~binary_search_tree()
    {
        delete left;
        delete right;
    }
    binary_search_tree(const binary_search_tree<T> &other)
    {
        value = other.value;
        if (other.left)
        {
            left = new binary_search_tree<T>(*other.left);
        }
        if (other.right)
        {
            right = new binary_search_tree<T>(*other.right);
        }
    }
    binary_search_tree<T> &operator=(const binary_search_tree<T> &other)
    {
        auto cpy = other;
        std::swap(cpy.value, value);
        std::swap(cpy.right, right);
        std::swap(cpy.left, left);
        return *this;
    }

    void insert(const T &value)
    {
        recursive_insert(this, value);
    }
    binary_search_tree<T> *delete_value(const T &value)
    {
        return recursive_delete_value(this, value);
    }
    std::vector<T> inorder() const
    {
        std::vector<T> elements;
        if (left)
        {
            elements = left->inorder();
        }
        elements.push_back(value);
        if (right)
        {
            std::vector<T> right_tree = right->inorder();
            elements.insert(elements.end(), right_tree.begin(), right_tree.end());
        }
        return elements;
    }

private:
    binary_search_tree<T> *recursive_delete_value(binary_search_tree<T> *tree, const T &value)
    {
        if (!tree)
        {
            return nullptr;
        }
        if (tree->value < value)
        {
            tree->left = recursive_delete_value(tree->left, value);
        }
        else if (tree->value > value)
        {
            tree->right = recursive_delete_value(tree->right, value);
        }
        else
        {
            if (!tree->left && !tree->right)
            {
                return nullptr;
            }
            else if (!tree->left)
            {
                auto temp = tree->right;
                delete tree;
                return temp;
            }
            else if (!tree->right)
            {
                auto temp = tree->left;
                delete tree;
                return temp;
            }
            else
            {
                auto node = find_minimal_value(tree->right);
                tree->value = node->value;
                tree->right = recursive_delete_value(tree->right, node->value);
            }
        }
        return tree;
    }
    binary_search_tree<T> *find_minimal_value(binary_search_tree<T> *tree)
    {
        auto current = tree;
        while (current && current->left)
        {
            current = current->left;
        }
        return current;
    }
    binary_search_tree<T> *recursive_insert(binary_search_tree<T> *current, const T &value)
    {
        if (!current)
        {
            return new binary_search_tree<T>{value};
        }
        if (current->value < value)
        {
            current->right = recursive_insert(current->right, value);
        }
        else
        {
            current->left = recursive_insert(current->left, value);
        }
        return current;
    }
    T value;
    binary_search_tree<T> *left{};
    binary_search_tree<T> *right{};
};

int main()
{
    binary_search_tree<int> b(10);
    b.insert(20);
    b.insert(4);
    b.insert(7);
    binary_search_tree<int> c = b;
    c.insert(14);
    b.insert(20);
    binary_search_tree<int> d(47);
    d = b;
    b.insert(57);
    std::cout << std::endl;
    auto b1 = b.inorder();
    auto c1 = c.inorder();
    auto d1 = d.inorder();
    for (auto i : b1)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (auto i : c1)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (auto i : d1)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}