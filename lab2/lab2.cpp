#include <iostream>
#include <vector>
#include <span>

template <typename T>
int linear_search(std::span<T> arr, const T &key)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == key)
        {
            return i;
        }
    }
    return -1;
}

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

Node *binary_tree_search(Node *root, int key)
{
    if (root == nullptr || root->data == key)
    {
        return root;
    }

    if (root->data < key)
    {
        return binary_tree_search(root->right, key);
    }

    return binary_tree_search(root->left, key);
}

template <typename T>
int binary_search(std::span<T> arr, const T &key)
{
    auto left = 0;
    auto right = arr.size() - 1;

    while (left <= right)
    {
        auto mid = left + (right - left) / 2;

        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

template <typename T>
int interpolation_search(std::span<T> arr, const T &key)
{
    auto low = 0;
    auto high = arr.size() - 1;

    while (low <= high && key >= arr[low] && key <= arr[high])
    {
        auto pos = low + ((key - arr[low]) * (high - low) / (arr[high] - arr[low]));

        if (arr[pos] == key)
        {
            return pos;
        }
        else if (arr[pos] < key)
        {
            low = pos + 1;
        }
        else
        {
            high = pos - 1;
        }
    }

    return -1;
}

int main()
{
    std::vector v_unsort {27, 15, 5, 8, 3, 30};
    const auto v_unsort_span = std::span(v_unsort);
    std::cout << "Index of value 15: " << linear_search(v_unsort_span, 15) << std::endl;
    Node left2 {8};
    Node right1 {5};
    Node left1 {15};
    left1.left = &left2;
    Node root {27};
    root.left = &left1;
    root.right = &right1;
    std::cout << "Index of value 15: " << (binary_tree_search(&root, 15) == &left1) << std::endl;

    std::vector v_sort {3, 5, 8, 15, 27, 30};
    const auto v_sort_span = std::span(v_sort);
    std::cout << "Index of value 15: " << binary_search(v_sort_span, 15) << std::endl;
    std::cout << "Index of value 15: " << interpolation_search(v_sort_span, 15)<< std::endl;

    return 0;
}