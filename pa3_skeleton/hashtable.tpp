/* TODO: Implement the functions for the class HashTable */
/* Write your code below */
template <typename T>
HashTable<T>::HashTable(int base_exponent, double max_load_factor) {
    total_size = 0;
    this->max_load_factor = max_load_factor;
    head_node = new TableNode();
    head_node->table_size = 0;
    head_node->exponent_size = base_exponent;
    int buckets = 1 << head_node->exponent_size;
    head_node->table = new vector<T>[buckets];
    head_node->next = nullptr;
    cur_node = head_node;
}

template <typename T>
HashTable<T>::~HashTable() {
    TableNode* cur = head_node;
    TableNode* temp;
    while (cur) {
        temp = cur->next;
        // int buckets = 1 << cur->exponent_size;
        // for (int i = 0; i < buckets; i++) {
        //     for (T& element :cur->table[i]) {
        //         delete element;
        //     }
        // }
        delete[] cur->table;
        delete cur;
        cur = temp;
    }
}

template <typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& other) {
    if (this == &other) {
        return *this;
    }

    TableNode* cur = head_node;
    TableNode* temp;
    while (cur) {
        temp = cur->next;
        // int buckets = 1 << cur->exponent_size;
        // for (int i = 0; i < buckets; i++) {
        //     for (T& element : cur->table[i]) {
        //         delete element;
        //         element = nullptr;
        //     }
        // }
        delete[] cur->table;
        delete cur;
        cur->table = nullptr;
        cur = nullptr;
        cur = temp;
    }

    total_size = other.total_size;
    max_load_factor = other.max_load_factor;
    head_node = new TableNode();
    head_node->table_size = other.head_node->table_size;
    head_node->exponent_size = other.head_node->exponent_size;
    int buckets = 1 << head_node->exponent_size;
    head_node->table = new vector<T>[buckets];
    for (int i = 0; i < buckets; i++) {
        head_node->table[i] = other.head_node->table[i];
        // for (int j = 0; j < head_node->table[i].size(); j++) {
        //     head_node->table[i][j] = new T(*(other.head_node->table[i][j]));
        // }
    }
    head_node->next = nullptr;
    cur_node = head_node;

    TableNode* oth_cur = other.head_node->next;
    while (oth_cur) {
        cur_node->next = new TableNode();
        cur_node = cur_node->next;
        cur_node->table_size = oth_cur->table_size;
        cur_node->exponent_size = oth_cur->exponent_size;
        int buckets = 1 << cur_node->exponent_size;
        cur_node->table = new vector<T>[buckets];
        for (int i = 0; i < buckets; i++) {
            cur_node->table[i] = oth_cur->table[i];
            // for (int j = 0; j < cur_node->table[i].size(); j++) {
            //     cur_node->table[i][j] = new T(*(oth_cur->table[i][j]));
            // }
        }
        cur_node->next = nullptr;
        oth_cur = oth_cur->next;
    }

    return *this;
}

template <typename T>
HashTable<T>::HashTable(const HashTable<T>& other) {
    total_size = other.total_size;
    max_load_factor = other.max_load_factor;
    head_node = new TableNode();
    head_node->table_size = other.head_node->table_size;
    head_node->exponent_size = other.head_node->exponent_size;
    int buckets = 1 << head_node->exponent_size;
    head_node->table = new vector<T>[buckets];
    for (int i = 0; i < buckets; i++) {
        // table[i] = vector<T>(other.head_node->table->begin(), other.head_node->table->end());
        head_node->table[i] = other.head_node->table[i];
    }
    head_node->next = nullptr;
    cur_node = head_node;

    TableNode* oth_cur = other.head_node->next;
    while (oth_cur) {
        cur_node->next = new TableNode();
        cur_node = cur_node->next;
        cur_node->table_size = oth_cur->table_size;
        cur_node->exponent_size = oth_cur->exponent_size;
        int buckets = 1 << cur_node->exponent_size;
        cur_node->table = new vector<T>[buckets];
        for (int i = 0; i < buckets; i++) {
            cur_node->table[i] = oth_cur->table[i];
            // for (int j = 0; j < cur_node->table[i].size(); j++) {
            //     cur_node->table[i][j] = new T(*(oth_cur->table[i][j]));
            // }
        }
        cur_node->next = nullptr;
        oth_cur = oth_cur->next;
    }
}

template <typename T>
bool HashTable<T>::exists(const T& value) const {
    TableNode* cur = head_node;
    while (cur) {
        int index = pa3_hash(value) % (1 << cur->exponent_size);
        // if (find(cur->table[index].begin(), cur->table[index].end(), value) != cur->table[index].end()) {
        for (int i = 0; i < cur->table[index].size(); i++) {
            if (cur->table[index][i] == value) {
                return true;
            }
        }
        cur = cur->next;
    }
    return false;
}

template <typename T>
bool HashTable<T>::insert(const T& value) {
    if (exists(value)) {
        return false;
    }

    int buckets = 1 << cur_node->exponent_size;
    if (cur_node->table_size * 1.0 / buckets < max_load_factor) {
        int index = pa3_hash(value) % buckets;
        cur_node->table[index].push_back(value);
        total_size++;
        cur_node->table_size++;
    } else {
        cur_node->next = new TableNode();
        int temp = cur_node->exponent_size;
        cur_node = cur_node->next;
        cur_node->table_size = 0;
        cur_node->exponent_size = temp + 1;
        buckets = 1 << cur_node->exponent_size;
        cur_node->table = new vector<T>[buckets];
        // for (int i = 0; i < buckets; i++) {
        //     cur_node->table[i] = {};
        // }
        cur_node->next = nullptr;
        
        int index = pa3_hash(value) % buckets;
        cur_node->table[index].push_back(value);
        total_size++;
        cur_node->table_size++;
    }
    return true;
}

template <typename T>
bool HashTable<T>::remove(const T& value){
    if (!exists(value)) {
        return false;
    }

    // typename vector<T>::const_iterator found = find(cur_node->table[index].begin(), cur_node->table[index].end(), value);
    // cur_node->table[index].erase(found);
    TableNode* cur = head_node;
    bool found = false;
    while (cur && !found) {
        int buckets = 1 << cur->exponent_size;
        int index = pa3_hash(value) % buckets;

        // if (find(cur->table[index].begin(), cur->table[index].end(), value) != cur->table[index].end()) {
        for (int i = 0; i < cur->table[index].size(); i++) {
            if (cur->table[index][i] == value) {
                cur->table[index].erase(cur->table[index].begin() + i);
                cur->table_size--;
                found = true;
                break;
            }
        }
        cur = cur->next;
    }
    total_size--;
    if (cur_node->table_size == 0 && cur_node != head_node) {
        delete[] cur_node->table;
        delete cur_node;
        cur_node->table = nullptr;
        
        TableNode* cur = head_node;
        while (cur->next != cur_node) {
            cur = cur->next;
        }
        cur->next = nullptr;
        cur_node = cur;
    }
    return true;
}

template <typename T>
vector<T> HashTable<T>::to_vector() const {
    vector<T> elements = {};
    TableNode* cur = head_node;
    while (cur) {
        int buckets = 1 << cur->exponent_size;
        for (int i = 0; i < buckets; i++) {
            elements.insert(elements.end(), cur->table[i].begin(), cur->table[i].end());
        }
        cur = cur->next;
    }
    return elements;
}
