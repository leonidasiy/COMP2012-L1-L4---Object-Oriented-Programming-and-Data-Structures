/* TODO: Implement the functions for the subclasses of BaseField */
/* Write your code below */
template <typename T>
void PrimitiveField<T>::handleAddEntryToIndexTree(BaseBST* index_tree, Entry* entry) const {
    BST<T, HashTable<Entry*>>* field_BST = dynamic_cast<BST<T, HashTable<Entry*>>*>(index_tree);
    HashTable<Entry*>* entry_HT = field_BST->get(value);
    if (!entry_HT) {
        field_BST->insert(value, HashTable<Entry*>());
        field_BST->get(value)->insert(entry);
    } else {
        entry_HT->insert(entry);
    }
}

template <typename T>
void ListField<T>::handleAddEntryToIndexTree(BaseBST* index_tree, Entry* entry) const {
    BST<T, HashTable<Entry*>>* field_BST = dynamic_cast<BST<T, HashTable<Entry*>>*>(index_tree);
    for (const T& value: values) {
        HashTable<Entry*>* entry_HT = field_BST->get(value);
        if (!entry_HT) {
            field_BST->insert(value, HashTable<Entry*>());
            field_BST->get(value)->insert(entry);
        } else {
            entry_HT->insert(entry);
        }
    }
}

