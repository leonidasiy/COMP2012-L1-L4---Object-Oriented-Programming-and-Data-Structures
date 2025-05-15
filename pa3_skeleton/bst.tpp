/* TODO: Implement the functions for the class BST */
/* Write your code below */
template <typename K, typename V>
vector<V> BST<K, V>::getInorder(Node* node) const {
    if (!node) {
        return vector<V>();
    }

    vector<V> l = getInorder(node->left);
    V cur = node->value;
    vector<V> r = getInorder(node->right);
    l.insert(l.end(), cur);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

template <typename K, typename V>
vector<V> BST<K, V>::getInorderWithUpperBound(Node* node, const K& upper_bound) const {
    if (!node) {
        return vector<V>();
    }

    if (node->key >= upper_bound) {
        return getInorderWithUpperBound(node->left, upper_bound);
    }

    vector<V> l = getInorderWithUpperBound(node->left, upper_bound);
    V cur = node->value;
    vector<V> r = getInorderWithUpperBound(node->right, upper_bound);
    
    l.insert(l.end(), cur);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

template <typename K, typename V>
vector<V> BST<K, V>::getInorderWithLowerBound(Node* node, const K& lower_bound) const {
    if (!node) {
        return vector<V>();
    }

    if (node->key <= lower_bound) {
        return getInorderWithLowerBound(node->right, lower_bound);
    }

    vector<V> l = getInorderWithLowerBound(node->left, lower_bound);
    V cur = node->value;
    vector<V> r = getInorderWithLowerBound(node->right, lower_bound);
    
    l.insert(l.end(), cur);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}
