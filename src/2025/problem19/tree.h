#pragma once

#include <utility>

template<typename Key, typename T>
struct tree {
    struct node {
        node *left;
        node *right;
        std::pair<Key, T> value;

        constexpr node(const std::pair<Key, T>& value);
        constexpr ~node();
        constexpr const node* next(Key key) const;
    };

    node *root;

    constexpr tree();
    constexpr ~tree();
    constexpr int insert(const std::pair<Key, T>& value);

private:
    constexpr int insert(node*& curr, const std::pair<Key, T>& value);
};

template<typename Key, typename T>
constexpr tree<Key, T>::node::node(const std::pair<Key, T>& value)
    : left(nullptr), right(nullptr), value(value) {
}

template<typename Key, typename T>
constexpr tree<Key, T>::node::~node() {
    delete left;
    delete right;
}

template<typename Key, typename T>
constexpr const tree<Key, T>::node* tree<Key, T>::node::next(Key key) const {
    return key == value.first
        ? this
        : key < value.first
            ? left
            : right;
}

template<typename Key, typename T>
constexpr tree<Key, T>::tree()
    : root(nullptr) {
}

template<typename Key, typename T>
constexpr tree<Key, T>::~tree() {
    delete root;
}

template<typename Key, typename T>
constexpr int tree<Key, T>::insert(const std::pair<Key, T>& value) {
    return insert(root, value);
}

template<typename Key, typename T>
constexpr int tree<Key, T>::insert(tree<Key, T>::node*& curr, const std::pair<Key, T>& value) {
    return curr == nullptr
        ? curr = new node(value), 1
        : value.first != curr->value.first
            ? insert(value.first < curr->value.first ? curr->left : curr->right, value) + 1
            : 0;
}
