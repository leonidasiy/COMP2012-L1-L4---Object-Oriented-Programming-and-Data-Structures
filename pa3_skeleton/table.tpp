/* TODO: Implement the functions for the class Table and Table::Filter */
/* Write your code below */
template <typename T>
void Table::addPrimitiveColumn(string name, const T& default_value) {
    PrimitiveField<T>* primitive_field = new PrimitiveField<T>(name, default_value);
    default_fields.insert(name, primitive_field);
    BST<T, HashTable<Entry*>>* field_BST = new BST<T, HashTable<Entry*>>();
    index_trees.insert(name, field_BST);
    if (entries.size()) {
        for (Entry*& entry : entries.to_vector()) {
            primitive_field->handleAddEntryToIndexTree(field_BST, entry);
        }
    }
}

template <typename T>
void Table::addListColumn(string name, const vector<T>& default_value) {
    ListField<T>* list_field = new ListField<T>(name, default_value);
    default_fields.insert(name, list_field);
    BST<T, HashTable<Entry*>>* field_BST = new BST<T, HashTable<Entry*>>();
    index_trees.insert(name, field_BST);
    if (entries.size()) {
        for (Entry*& entry : entries.to_vector()) {
            list_field->handleAddEntryToIndexTree(field_BST, entry);
        }
    }
}

void Table::addEntry(const Entry& entry) {
    Entry* entry_new = new Entry(entry);
    if (entries.insert(entry_new)) {
        // vector<string> entry_fields = {};
        // for (BaseField*& field : entry_new->getFields().getInorder()) {
        //     entry_fields.push_back(field->getName());
        // }

        for (BaseField*& field : default_fields.getInorder()) {
            BaseBST* field_BST = *(index_trees.get(field->getName()));
            // cout << (entry_field == nullptr);
            // if (find(entry_fields.begin(), entry_fields.end(), field->getName()) != entry_fields.end()) {
            if (entry_new->getFields().get(field->getName())) {
                // cout << (*entry_field);
                BaseField* entry_field = *(entry_new->getFields().get(field->getName()));
                entry_field->handleAddEntryToIndexTree(field_BST, entry_new);
            } else {
                field->handleAddEntryToIndexTree(field_BST, entry_new);
            }
        }
    }
}

// void clear_and_copy_HT(HashTable<Entry*>& hashtable, HashTable<Entry*>& other_hashtable) {
//     vector<Entry*> all_entries = hashtable.to_vector();
//     for (Entry*& entry : all_entries) {
//         delete entry;
//         entry = nullptr;
//     }
//     hashtable = other_hashtable;
//     vector<Entry*> all_entries_new = hashtable.to_vector();
//     for (Entry*& entry : all_entries_new) {
//         entry = new Entry(*entry);
//     }
// }

Table& Table::operator=(const Table& other) {
    if (this == &other) {
        return *this;
    }

    vector<Entry*> all_entries = entries.to_vector();
    for (Entry*& entry : all_entries) {
        delete entry;
        entries.remove(entry);
    }

    vector<BaseField*> all_default_fields = default_fields.getInorder();
    for (BaseField*& field : all_default_fields) {
        delete field;
    }
    default_fields.clear();

    vector<BaseBST*> all_index_trees = index_trees.getInorder();
    for (BaseBST*& index_tree : all_index_trees) {
        // vector<HashTable<Entry*>> all_entry_HT = index_tree->getInorder();
        // for (HashTable<Entry*>& entries : all_entry_HT) {
        //     vector<Entry*> all_entries = entries.to_vector();
        //     for (Entry*& entry : all_entries) {
        //         delete entry;
        //     }
        // }
        delete index_tree;
    }
    index_trees.clear();

    // default_fields = other.default_fields;
    vector<BaseField*> oth_default_fields = other.default_fields.getInorder();
    for (BaseField*& field : oth_default_fields) {
        default_fields.insert(field->getName(), field->clone());
    }

    // vector<BaseBST*> all_index_trees = index_trees.getInorder();
    // for (BaseBST*& index_tree : all_index_trees) {
    //     BaseBST* bst_index_tree = index_tree->clone();
    //     bst_index_tree = 
    //     vector<HashTable<Entry*>> all_entry_HT = index_tree->getInorder();
    //     for (HashTable<Entry*>& entries : all_entry_HT) {
    //         vector<Entry*> all_entries = entries.to_vector();
    //         for (Entry*& entry : all_entries) {
    //             delete entry;
    //             entry = nullptr;
    //         }
    //     }
    //     delete index_tree;
    //     index_tree = nullptr;
    // }
    // index_trees = other.index_trees;
    vector<BaseBST*> oth_index_trees = other.index_trees.getInorder();
    int i = 0;
    for (BaseBST*& index_tree : oth_index_trees) {
        BaseBST* tree_copy = index_tree->clone();
        tree_copy->clear();
        index_trees.insert(oth_default_fields[i++]->getName(), tree_copy);
    }

    // entries = other.entries;
    // vector<Entry*> all_entries_new = entries.to_vector();
    // for (Entry*& entry : all_entries_new) {
    //     entry = new Entry(*entry);
    // }
    for (Entry*& entry : other.entries.to_vector()) {
        addEntry(*entry);
    }

    return *this;
}

Table::Table(const Table& other) {
    vector<BaseField*> oth_default_fields = other.default_fields.getInorder();
    for (BaseField*& field : oth_default_fields) {
        default_fields.insert(field->getName(), field->clone());
    }

    vector<BaseBST*> oth_index_trees = other.index_trees.getInorder();
    int i = 0;
    for (BaseBST*& index_tree : oth_index_trees) {
        BaseBST* tree_copy = index_tree->clone();
        tree_copy->clear();
        index_trees.insert(oth_default_fields[i++]->getName(), tree_copy);
    }

    for (Entry*& entry : other.entries.to_vector()) {
        addEntry(*entry);
    }
}

Table::~Table() {
    vector<Entry*> all_entries = entries.to_vector();
    for (Entry*& entry : all_entries) {
        delete entry;
    }

    vector<BaseField*> all_default_fields = default_fields.getInorder();
    for (BaseField*& field : all_default_fields) {
        delete field;
    }

    vector<BaseBST*> all_index_trees = index_trees.getInorder();
    for (BaseBST*& index_tree : all_index_trees) {
        // vector<HashTable<Entry*>> all_entry_HT = index_tree->getInorder();
        // for (HashTable<Entry*>& entries : all_entry_HT) {
        //     vector<Entry*> all_entries = entries.to_vector();
        //     for (Entry*& entry : all_entries) {
        //         delete entry;
        //     }
        // }
        delete index_tree;
    }
}

template <typename T>
Table Table::Filter<T>::operator==(const T& value) const {
    BaseBST* basebst_ptr = *(table->index_trees.get(field_name));
    BST<T, HashTable<Entry*>>* index_tree = dynamic_cast<BST<T, HashTable<Entry*>>*>(basebst_ptr);
    vector<Entry*> filtered_entries = index_tree->get(value)->to_vector();
    Table filtered_table = Table();
    // for (Entry*& entry : filtered_entries) {
    //     filtered_table->entries.insert(entry);
    // }

    // filtered_table->default_fields = table->default_fields;   
    vector<BaseField*> all_default_fields = table->default_fields.getInorder();
    for (BaseField*& field : all_default_fields) {
        filtered_table.default_fields.insert(field->getName(), field->clone());
    }

    vector<BaseBST*> all_index_trees = table->index_trees.getInorder();
    int i = 0;
    for (BaseBST*& index_tree : all_index_trees) {
        BaseBST* tree_copy = index_tree->clone();
        tree_copy->clear();
        filtered_table.index_trees.insert(all_default_fields[i++]->getName(), tree_copy);
    }

    for (Entry*& entry : filtered_entries) {
        filtered_table.addEntry(*entry);
    }

    return filtered_table;
}
