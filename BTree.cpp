//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <fstream>
//#include <string>
//#include <bits/stdc++.h>
//#ifndef BTREE_H
//#define BTREE_H
//using namespace std;
//
//class Node;
//
//class element {
//public:
//    int key;
//    int address;
//    Node *next;
//
//    element(int k, int a = -1) {
//        key = k;
//        address = a;
//        next = nullptr;
//    }
//
//};
//
//struct SortByKey {
//    bool operator()(element const &l, element const &r) {
//        return (l.key) < (r.key);
//    }
//
//};
//
////#define nullptr NULL
//class Node {
//public:
//    //m
//    int capacity;
//    int nonLeaf;
//    int *valOfFreenode;
//    vector<element> node;
//    bool isleaf = true;
//
//    Node() {};
//
//    Node(int m, int next) {
//        this->capacity = m * 2;
//        this->nonLeaf = -1;
//        valOfFreenode = new int[(m * 2)];
//        valOfFreenode[0] = next;
//        for (int i = 1; i < (m * 2); ++i) {
//            valOfFreenode[i] = -1;
//        }
//    }
//
//
//    void setCapacity(int s) {
//        capacity = s;
//    }
//
//    int getKey(int i) {
//        return node[i].key;
//    }
//
//    void changeKeyAt(int index, int value) {
//        node[index].key = value;
//    }
//
//    bool is_full() {
//        int size = node.size();
//        if (size == capacity) {
//            return true;
//        } else {
//            return false;
//        }
//    }
//
//    int getSize() {
//        return node.size();
//    }
//
//    //sort the vector according to the key
//    void sort() {
//        std::sort(node.begin(), node.end(), SortByKey());
//    }
//
//    //to create and add element to Node
//    void add(int id, int ref) {
//        element e(id, ref);
//        node.push_back(e);
//        this->sort();
//    }
//    //add element to Node
//
//    void addEle(element e) {
//        node.push_back(e);
//        this->sort();
//    }
//
//    element getfront() {
//        return node.front();
//    }
//
//    void popFront() {
//        node.erase(node.begin());
//
//    }
//
//    int getMaxKey() {
//        return node.back().key;
//    }
//
//    //returns the next Node of an element
//    Node *getNext(int i) {
//        return node[i].next;
//
//    }
//
//    void sortNode(int *arr, int indx) {
//        vector<pair<int, int>> v;
//        for (int i = 0; i <= indx; i += 2) {
//            v.emplace_back(arr[i], arr[i + 1]);
//        }
//        ::sort(v.begin(), v.end());
//        for (int i = 0, j = 0; i <= indx; i += 2, j++) {
//            arr[i] = v[j].first;
//            arr[i + 1] = v[j].second;
//        }
//    }
//};
//
//class BTree {
//public:
//    fstream BTreeFile;
//    int line = 1;
//    Node *root = nullptr;
//    int m, numberOfRecords;
//
//    BTree(int m, int numberOfRecords) {
//        this->m = m;
//        this->numberOfRecords = numberOfRecords;
//    }
//
//    void CreateIndexFileFile(const char *filename, int numberOfRecords, int m);
//
//    void DisplayIndexFileContent(const char *filename);
//
//    Node search(int k) {
//        Node x(0, 1);
//        return x;
//    }
//
//    Node *getNode(int key);
//
//    Node *getleafparent(int key);
//
//    void del_key(char *filename, int x);
//
//
//    void merge(Node *current, Node *sibling, Node *parent);
//
//    Node *getParent(int key, Node *start);
//
//    Node *getLeaf(int key, Node *start);
//
//    int deletenleaf(Node &x, int key);
//
//    Node *getParent(Node *node, Node *child) {
//        if (node->isleaf) {
//            return NULL;
//        }
//        for (int i = 0; i < m; i++) {
//            if (node->node[i].next == child) {
//                return node;
//            }
//            Node *parent = getParent(node->node[i].next, child);
//            if (parent != nullptr) {
//                return parent;
//            }
//        }
//        return NULL;
//    }
//
//    void insert(char *filename, int key, int offset) {
//        if (root == nullptr) {
//            root = new Node;
//            root->isleaf = true;
//            root->addEle(element(key, offset));
//            return;
//        }
//
//        Node *node = root;
//        Node *parent = nullptr;
//
//        while (!node->isleaf) {
//            parent = node;
//
//            int i = 0;
//            while (i < node->node.size() - 1 && key > node->node[i].key) {
//                i++;
//            }
//
//            if (i < node->node.size() && node->node[i].next != nullptr) {
//                node = node->node[i].next;
//            } else {// No more child nodes to traverse
//                break;
//            }
//        }
//
//        node->addEle(element(key, offset));
//
//        if (parent != nullptr) {
//            // Update parent node with the maximum value from the child
//            int maxKeyIndex = parent->node.size() - 1;
//            if (parent->node[maxKeyIndex].key < node->node[node->node.size() - 1].key) {
//                parent->node[maxKeyIndex] = node->node[node->node.size() - 1];
//            }
//        }
//
//        if (node->node.size() > m) {
//            split(node);
//        }
//    }
//
//
//    void split(Node *node) {
//        Node *left = new Node;
//        left->isleaf = true;
//        Node *right = new Node;
//        right->isleaf = true;
//        int mid = node->node.size() / 2;
//        for (int i = 0; i < mid; i++) {
//            left->addEle(element(node->node[i].key, node->node[i].address));
//        }
//
//        for (int i = mid; i < node->node.size(); i++) {
//            right->addEle(element(node->node[i].key, node->node[i].address));
//        }
//
//        if (!node->isleaf) {
//            for (int i = 0; i < mid; i++) {
//                left->node[i].next = node->node[i].next;
//            }
//            for (int i = mid; i < node->node.size(); i++) {
//                right->node[i - mid].next = node->node[i].next;
//            }
//        }
//
//        if (node == root) {
//            root = new Node;
//            root->isleaf = true;
//            root->addEle(element(node->node[mid - 1].key, node->node[mid - 1].address));
//            root->addEle(element(node->node[node->node.size() - 1].key, node->node[node->node.size() - 1].address));
//            root->node[0].next = left;
//            root->node[1].next = right;
//
//        } else {
//            Node *parent = getParent(root, node);
//            int i = 0;
//            while (i < parent->node.size() - 1 && node->node[mid].key > parent->node[i].key) {
//                i++;
//            }
//            parent->addEle(element(node->node[mid - 1].key, node->node[mid - 1].address));
//            // shift children to the right
//            for (int j = parent->node.size() - 1; j > i; j--) {
//                parent->node[j + 1].next = parent->node[j].next;
//            }
//            parent->node[i].next = left;
//            parent->node[i + 1].next = right;
//            if (parent->node.size() > m) {
//                split(parent);
//            }
//        }
//    }
//
//
//    void writeBTree(string filename, int maxKeys, Node *root);
//
//    string writeRecord(Node *node);
//
//    void writeBTree(string filename);
//};
//
//
//void BTree::CreateIndexFileFile(const char *filename, int numberOfRecords, int m) {
//    fstream Btree;
//    Btree.open(filename, ios::in | ios::out | ios::binary | ios::app);
//    for (int i = 0; i < numberOfRecords - 1; i++) {
//        Node write(m, i + 1);
//        Btree.write((char *) &write, sizeof(write));
//
//    }
//    Node write(m, -1);
//    Btree.write((char *) &write, sizeof(write));
//    Btree.close();
//}
//
//void BTree::DisplayIndexFileContent(const char *filename) {
//    fstream Btree;
//    Btree.open(filename, ios::in | ios::out | ios::binary | ios::app);
//    Btree.seekg(0, ios::beg);
//    Node read;
//    while (Btree.read((char *) &read, sizeof(read))) {
//        cout << read.nonLeaf << " ";
//        for (int i = 0; i < read.capacity; ++i) {
//            cout << read.valOfFreenode[i] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//    Btree.close();
//}
//
//Node *BTree::getNode(int key) {
//    if (root == nullptr) {
//        return nullptr;
//    }
//
//    Node *temp = root;
//    int count = 0;
//    while (count < numberOfRecords) {
//        for (auto i: temp->node) {
//            if (i.key == key) {
//                return temp;
//            }
//        }
//        int counter = 0;
//        for (auto i: temp->node) {
//            if (i.key > key) {
//                temp = i.next;
//                break;
//            }
//            counter++;
//        }
//        count++;
//
//    }
//    return nullptr;
//}
//
//Node *BTree::getleafparent(int key) {
//    if (root == nullptr) {
//        return nullptr;
//    }
//    Node *pre = root;
//    Node *temp = root;
//    int count = 0;
//    while (count < numberOfRecords) {
//        for (auto i: temp->node) {
//            if (i.key == key) {
//                return pre;
//            }
//        }
//        int counter = 0;
//        for (auto i: temp->node) {
//            if (i.key > key) {
//                pre = temp;
//                temp = i.next;
//                break;
//            }
//            counter++;
//        }
//        count++;
//
//    }
//    return nullptr;
//}
//
//void BTree::del_key(char *filename, int x) {
//    Node *target = getNode(x);
//    if (target == nullptr) {
//        cout << "key not found \n";
//        return;
//    }
//    if (target->isleaf) {
//        if (target->node.size() > 2) {
//            for (int i = 0; i < target->node.size(); i++) {
//                if (x == target->node[i].key) {
//                    target->node.erase(target->node.begin() + i);
//                }
//            }
//        } else {
//            for (int i = 0; i < target->node.size(); i++) {
//                if (x == target->node[i].key) {
//                    Node *parent = getleafparent(x);
//                    Node *sibling = parent->node[parent->node.size() - 2].next;
//                    if (sibling->node.size() == 2) {
//                        target->node.erase(target->node.begin() + i);
//                        merge(target, sibling, parent);
//                    } else {
//                        int temp = parent->node[parent->node.size() - 2].key;
//                        int temp2 = parent->node[parent->node.size() - 2].address;
//                        target->node.erase(target->node.begin() + i);
//                        del_key(filename, temp);
//                        insert(filename, temp, temp2);
//                    }
//                }
//            }
//        }
//    } else {
//        Node *leaf = getLeaf(x, target);
//        if (leaf->node.size() >= 3) {
//            deletenleaf(*target, x);
//        }
//        if (leaf->node.size() <= 2) {
//            for (int i = 0; i < target->node.size(); i++) {
//                if (x == target->node[i].key) {
//                    Node *parent = getParent(x, target->node[i].next);
//
//                    Node *sibling = parent->node[parent->node.size() - 2].next;
//                    if (sibling->node.size() == 2) {
//                        deletenleaf(*target, x);
//                        merge(leaf, sibling, parent);
//                    } else {
//                        int temp = parent->node[parent->node.size() - 2].key;
//                        int temp2 = parent->node[parent->node.size() - 2].address;
//                        deletenleaf(*target, x);
//                        del_key(filename, temp);
//                        insert(filename, temp, temp2);
//                    }
//                }
//            }
//
//        }
//    }
//}
//
//void BTree::merge(Node *current, Node *sibling, Node *parent) {
//    sibling->node.push_back(current->node[0]);
//    pair<int, int> x = {current->node[0].key, current->node[0].address};
//    current->node.pop_back();
//    parent->node.pop_back();
//    parent->node[parent->node.size() - 1].key = x.first;
//    parent->node[parent->node.size() - 1].address = x.second;
//    //update index file
//}
//
//Node *BTree::getParent(int key, Node *start) {
//    Node *parent = start;
//    Node *temp = start;
//    while (temp->isleaf == 1) {
//        int counter = 0;
//        for (auto i: temp->node) {
//            if (i.key == key) {
//                parent = temp;
//                temp = i.next;
//            }
//            counter++;
//        }
//    }
//    return parent;
//}
//
//Node *BTree::getLeaf(int key, Node *start) {
//    Node *temp = start;
//    while (temp->isleaf == 1) {
//        int counter = 0;
//        for (auto i: temp->node) {
//            if (i.key == key) {
//                temp = i.next;
//            }
//            counter++;
//        }
//    }
//    return temp;
//}
//
//int BTree::deletenleaf(Node &x, int key) {
//    if (x.isleaf) {
//        x.node.pop_back();
//        //update index file
//        return x.node[x.node.size() - 1].key;
//    }
//    if (!x.isleaf) {
//        for (auto &i: x.node) {
//            if (i.key == key) {
//                int replace = deletenleaf(*(i.next), key);
//                i.key = replace;
//                //update index file
//                return replace;
//            }
//        }
//    }
//}
//
//string BTree:: writeRecord(Node *node) {
//    string record = "";
//    int cnt = 0;
//    record += to_string(node->isleaf) + '|';
//
//    for (const auto &key: node->node) {
//
//        record += to_string(key.key) + '|' + to_string(key.address) + '|';
//        cnt+=2;
//    }
//
//    while (cnt < m*2) {
//        record += to_string(-1) + '|';
//        cnt++;
//    }
//    return record;
//}
//
//void BTree::writeBTree(string filename) {
//
//    vector<pair<int ,Node >>print;
//    int x = 1 ;
//    queue<Node>toprint;
//    toprint.push(*root);
//
//    while(!toprint.empty()){
//        Node temp2 = toprint.front();
//        print.emplace_back(x,temp2);
//        toprint.pop();
//        for(auto i : temp2.node){
//            if(i.next!=NULL)
//                toprint.push(*i.next);
//        }
//    }
//    sort(print.begin(), print.end(), [](const auto& a, const auto& b) {
//        return a.first < b.first;
//    });
//    for(auto i : print){
//        writeRecord(&(i.second));
//    }
//
//}
////
////    pair<int, int> splitLeaf(Node &current, Node &newnode, int RecordID, int ref);
////
////    void splitRootLeaf(Node &root, Node &node1, Node &node2, int place1, int place2, int id, int ref);
////
////    pair<int, vector<int>> getLeaf(const char *filename, Node &root, int recordID);
////
////    void sortNode(int *arr, int indx);
////
////    void splitRootNLeaf(Node &root, Node &node1, Node &node2, int place1, int place2,
////                        int max1, int max2, int oldMax, int max1place, int max2place);
////
////    pair<int, int>
////    splitParent(Node &currentparent, Node &newnode, int splitInindex, int max1, int max2, int oldMax, int max1place,
////                int max2place);
////
////    int InsertNewRecordAtIndex(char *filename, int RecordID, int Reference);
//
////
////pair<int, int> BTree::splitLeaf(Node &current, Node &newnode, int RecordID, int ref) {
////    newnode.nonLeaf = 0;
////    vector<pair<int, int>> v;
////    for (int x = 0; x < current.capacity; x += 2) {
////        v.emplace_back(current.valOfFreenode[x], current.valOfFreenode[x + 1]);
////    }
////    v.emplace_back(RecordID, ref);
////    sort(v.begin(), v.end());
////    int j = 0, i;
////    for (i = 0; i < (v.size() / 2); i++) {
////        current.valOfFreenode[j] = v[i].first;
////        current.valOfFreenode[j + 1] = v[i].second;
////        j += 2;
////    }
////    int maxnode1 = current.valOfFreenode[j - 2];
////    while (j < current.capacity) {
////        current.valOfFreenode[j] = -1;
////        current.valOfFreenode[++j] = -1;
////        ++j;
////    }
////    j = 0;
////    for (int i = v.size() / 2; i < v.size(); i++) {
////        newnode.valOfFreenode[j] = v[i].first;
////        newnode.valOfFreenode[j + 1] = v[i].second;
////        j += 2;
////    }
////    int maxnode2 = newnode.valOfFreenode[j - 2];
////    pair<int, int> splited;
////    splited = {maxnode1, maxnode2};
////    return splited;
////}
////
////void BTree::splitRootLeaf(Node &root, Node &node1, Node &node2, int place1, int place2, int id, int ref) {
////    int i;
////    root.nonLeaf = 1;
////    node1.nonLeaf = 0;
////    node2.nonLeaf = 0;
////    vector<pair<int, int>> v;
////    for (int x = 0; x < root.capacity; x += 2) {
////        v.emplace_back(root.valOfFreenode[x], root.valOfFreenode[x + 1]);
////    }
////    if (id != -1 && ref != -1)
////        v.emplace_back(id, ref);
////    sort(v.begin(), v.end());
////    int j = 0;
////    for (i = 0; i < (v.size() / 2); i++) {
////        node1.valOfFreenode[j] = v[i].first;
////        node1.valOfFreenode[j + 1] = v[i].second;
////        j += 2;
////    }
////    int max1 = node1.valOfFreenode[j - 2];
////    j = 0;
////    while (i < v.size()) {
////        node2.valOfFreenode[j] = v[i].first;
////        node2.valOfFreenode[j + 1] = v[i].second;
////        j += 2;
////        i++;
////    }
////    int max2 = node2.valOfFreenode[j - 2];
////    root.valOfFreenode[0] = max1;
////    root.valOfFreenode[1] = place1;
////    root.valOfFreenode[2] = max2;
////    root.valOfFreenode[3] = place2;
////    for (int k = 4; k < root.capacity; ++k) {
////        root.valOfFreenode[k] = -1;
////    }
////}
////
////pair<int, vector<int>> BTree::getLeaf(const char *filename, Node &root, int recordID) {
////    fstream Btree;
////    Btree.open(filename, ios::in);
////    vector<int> v;
////    int current = -1, i;// the position of the leaf node
////    bool f = false;// to check if the node with recordID founded
////    v.push_back(1);
////    for (i = 0; i < root.capacity and root.valOfFreenode[i] != -1; i += 2) {
////        if (root.valOfFreenode[i] >= recordID) {
////            f = true;
////            current = root.valOfFreenode[i + 1];
////            v.push_back(current);
////            Btree.seekg(current * sizeof(root), ios::beg);
////            Node n;
////            Btree.read((char *) &n, sizeof(root));
////            while (n.nonLeaf) {
////                for (int j = 0; j < n.capacity and n.valOfFreenode[j] != -1; j += 2) {
////                    if (n.valOfFreenode[j] >= recordID) {
////                        current = n.valOfFreenode[j + 1];
////                        Btree.seekg(current * sizeof(root), ios::beg);
////                        Btree.read((char *) &n, sizeof(root));
////                        break;
////                    }
////                }
////            }
////            break;
////        }
////    }
////    if (!f) {
////        current = root.valOfFreenode[--i];
////        v.push_back(current);
////        Node n;
////        Btree.seekg(current * sizeof(root), ios::beg);
////        Btree.read((char *) &n, sizeof(root));
////        while (n.nonLeaf) {
////            for (int j = 0; j < n.capacity and n.valOfFreenode[j] != -1; j += 2) {
////                current = n.valOfFreenode[j + 1];
////            }
////            v.push_back(current);
////            Btree.seekg(current * sizeof(root), ios::beg);
////            Btree.read((char *) &n, sizeof(root));
////        }
////    }
////    return {current, v};
////}
////
////void BTree::sortNode(int *arr, int indx) {
////    vector<pair<int, int>> v;
////    for (int i = 0; i <= indx; i += 2) {
////        v.emplace_back(arr[i], arr[i + 1]);
////    }
////    sort(v.begin(), v.end());
////    for (int i = 0, j = 0; i <= indx; i += 2, j++) {
////        arr[i] = v[j].first;
////        arr[i + 1] = v[j].second;
////    }
////}
////
////void BTree::splitRootNLeaf(Node &root, Node &node1, Node &node2, int place1, int place2, int max1, int max2, int oldMax,
////                           int max1place, int max2place) {
////    int i;
////    node1.nonLeaf = 1;
////    node2.nonLeaf = 1;
////    vector<pair<int, int>> v;
////    for (int x = 0; x < root.capacity; x += 2) {
////        if (root.valOfFreenode[x] != max1 and root.valOfFreenode[x] != max2 and root.valOfFreenode[x] != oldMax)
////            v.emplace_back(root.valOfFreenode[x], root.valOfFreenode[x + 1]);
////    }
////    v.emplace_back(max1, max1place);
////    v.emplace_back(max2, max2place);
////    sort(v.begin(), v.end());
////    int j = 0;
////    for (i = 0; i < (v.size() / 2); i++) {
////        node1.valOfFreenode[j] = v[i].first;
////        node1.valOfFreenode[j + 1] = v[i].second;
////        j += 2;
////    }
////    int maxroot1 = node1.valOfFreenode[j - 2];
////    j = 0;
////    while (i < v.size()) {
////        node2.valOfFreenode[j] = v[i].first;
////        node2.valOfFreenode[j + 1] = v[i].second;
////        j += 2;
////        i++;
////    }
////    int maxroot2 = node2.valOfFreenode[j - 2];
////    root.valOfFreenode[0] = maxroot1;
////    root.valOfFreenode[1] = place1;
////    root.valOfFreenode[2] = maxroot2;
////    root.valOfFreenode[3] = place2;
////    for (int k = 4; k < root.capacity; ++k) {
////        root.valOfFreenode[k] = -1;
////    }
////}
////
//
////
////pair<int, int>
////BTree::splitParent(Node &currentparent, Node &newnode, int splitInindex, int max1, int max2, int oldMax, int max1place,
////                   int max2place) {
////    newnode.nonLeaf = 1;
////    vector<pair<int, int>> v;
////    for (int i = 0; i < currentparent.capacity; i += 2) {
////        if (currentparent.valOfFreenode[i] != max1 and currentparent.valOfFreenode[i] != max2 and
////            currentparent.valOfFreenode[i] != oldMax)
////            v.emplace_back(currentparent.valOfFreenode[i], currentparent.valOfFreenode[i + 1]);
////    }
////    v.emplace_back(max1, max1place);
////    v.emplace_back(max2, max2place);
////    sort(v.begin(), v.end());
////    int j = 0, i;
////    for (i = 0; i < (v.size() / 2); i++) {
////        currentparent.valOfFreenode[j] = v[i].first;
////        currentparent.valOfFreenode[j + 1] = v[i].second;
////        j += 2;
////    }
////    max1 = currentparent.valOfFreenode[j - 2];
////    while (j < newnode.capacity) {
////        currentparent.valOfFreenode[j] = -1;
////        currentparent.valOfFreenode[++j] = -1;
////        ++j;
////    }
////    j = 0;
////    for (int i = v.size() / 2; i < v.size(); i++) {
////        newnode.valOfFreenode[j] = v[i].first;
////        newnode.valOfFreenode[j + 1] = v[i].second;
////        j += 2;
////    }
////    max2 = newnode.valOfFreenode[j - 2];
////    pair<int, int> split_result;
////    split_result = {max1, max2};
////    return split_result;
////}
//
//
//
////    void insertNew(int record, int reference);
////void splitNadd(Node *pNode, element element1);
////    Node *getbest(int key) {
////        if (this->root->isleaf) {
////            return root;
////        } else {
////            Node *temp = root;
////            while (!temp->isleaf) {
////                if (key > temp->node.back().key) {
////                    temp = temp->node.back().next;
////                }
////                for (int i = temp->node.size() - 1; i >= 0; i--) {
////                    if (temp->node[i].key < key) {
////                        temp = temp->node[i].next;
////                    }
////                }
////            }
////            return temp;
////        }
////
////    };
////void splitNupdate(Node *pNode, Node *pNode1, element element1);
//
////void BTree::splitNadd(Node *pNode, element element1) {
////    Node *one = new Node;
////    Node *two = new Node;
////    pNode->node[pNode->node.size()/2].next = one;
////    pNode->node.back().next = two;
////    int count = pNode->node.size();
////    for(int i = 0 ; i < (count/2)-1; i ++){
////        one->node.push_back(pNode->node.front());
////        pNode->node.erase(pNode->node.begin());
////    }
////    for(int i =0; i < pNode->node.size()-1 ; i ++ ){
////        two->node.push_back(pNode->node[1]);
////        pNode->node.erase(pNode->node.begin()+1);
////    }
////    if(pNode->node.front().key < element1.key){
////        if(pNode->node.back().key<element1.key){
////            int temp = pNode->node.back().key;
////            pNode->node.back().key = element1.key;
////
////            int temp2 = pNode->node.back().key;
////            pNode->node.back().address = element1.address;
////
////            two->addEle(element(temp, temp2));
////            //traverse up and update
////        }
////        else{
////            two->addEle(element1);
////        }
////    }
////    else{
////        one->addEle(element1);
////    }
////}
////
////void BTree::splitNupdate(Node *pNode, Node *pNode1, element element1) {
////    Node *one = new Node;
////    Node *two = new Node;
////
////    int count = pNode->node.size();
////    for(int i = 0 ; i < (count/2)-1; i ++){
////        one->node.push_back(pNode->node.front());
////    }
////    for(int i =0; i < pNode->node.size()-1 ; i ++ ){
////        two->node.push_back(pNode->node[1]);
////
////    }
////    if(pNode->node.front().key < element1.key){
////        if(pNode->node.back().key<element1.key){
////            int temp = pNode->node.back().key;
////            pNode->node.back().key = element1.key;
////
////            int temp2 = pNode->node.back().key;
////            pNode->node.back().address = element1.address;
////
////            two->addEle(element(temp, temp2));
////            //traverse up and update
////        }
////        else{
////            two->addEle(element1);
////        }
////    }
////    else{
////        one->addEle(element1);
////    }
////}
////void BTree::insertNew(int record, int reference) {
////    element x(record, reference);
////    if (this->root == nullptr) {
////        this->root = new Node;
////        root->addEle(x);
////    } else {
////        Node *best = getbest(x.key);
////        Node *parent = new Node;
////        //parent not full
////        splitNupdate(best, parent , x);
////        //parent is full
////        if (best->node.size() == m) {
////            splitNadd(best, x);
////        } else {
////            best->addEle(x);
////        }
////
////    }
////}
////
////int BTree::InsertNewRecordAtIndex(char *filename, int RecordID, int Reference) {
////    element toBeAdded(RecordID, Reference);
////    fstream treeFile;
////    treeFile.open(filename, ios::in | ios::out | ios::binary);
////    treeFile.seekg(0, ios::beg);
////    Node header;
////    treeFile.read((char *) &header, sizeof(header));
////    treeFile.seekg(sizeof(header), ios::beg);
////
////    Node root;
////
////    treeFile.read((char *) &root, sizeof(root));
////    //tree is empty-> no nodes
////    if (header.valOfFreenode[0] == 1) {
////        //->>>>>>>>>>>>>
////        //if root == Null
////        //update root
////        //this->root = new Node;
////        //this->root->addEle(toBeAdded);
////        //->>>>>>>>>>>>>
////
////        header.valOfFreenode[0]++;
////        root.nonLeaf = 0;
////        root.valOfFreenode[0] = RecordID;
////        root.valOfFreenode[1] = Reference;
////        treeFile.seekp(0, ios::beg);
////        treeFile.write((char *) &header, sizeof(header));
////        treeFile.write((char *) &root, sizeof(root));
////        treeFile.close();
////        return 1;
////    } else {
////        //level one that directly points to refrence the tree has root only
////        if (root.nonLeaf == 0) {
////            //is root size != maxmum
////            //inserting int root
////            //this->root->addEle(toBeAdded);
////            //insert_recort(node x, node place())
////            int i;
////            bool f = false;
////            for (i = 0; i < root.capacity; i += 2) {
////                if (root.valOfFreenode[i] == -1) {
////                    root.valOfFreenode[i] = RecordID;
////                    root.valOfFreenode[i + 1] = Reference;
////                    sortNode(root.valOfFreenode, i + 1);
////                    treeFile.seekp(sizeof(header), ios::beg);
////                    treeFile.write((char *) &root, sizeof(root));
////                    treeFile.close();
////                    f = true;
////                    return 1;
////                }
////            }
////            //level one is complete then we must split and add another level
////            if (!f) {
////                //if (root
////                //split_node(Node root)
////                //iterate throw root to find the place to add the x node
////                //insert_record(node x , node place)
////
////                int place1 = header.valOfFreenode[0];
////                if (place1 == -1)return -1;
////                treeFile.seekg(header.valOfFreenode[0] * sizeof(header), ios::beg);
////                Node node1;
////                treeFile.read((char *) &node1, sizeof(node1));
////                int place2 = node1.valOfFreenode[0];
////                if (place2 == -1)return -1;
////                treeFile.seekg(node1.valOfFreenode[0] * sizeof(node1), ios::beg);
////                Node node2;
////                treeFile.read((char *) &node2, sizeof(node2));
////                header.valOfFreenode[0] = node2.valOfFreenode[0];
////                int IndexOfNode = (root.valOfFreenode[root.capacity / 2 - 1] < RecordID) ? place2 : place1;
////
////                splitRootLeaf(root, node1, node2, place1, place2, RecordID, Reference);
////                treeFile.seekp(0, ios::beg);
////                treeFile.write((char *) &header, sizeof(root));
////                treeFile.seekp(sizeof(header), ios::beg);
////                treeFile.write((char *) &root, sizeof(root));
////                treeFile.seekp(sizeof(header) * place1, ios::beg);
////                treeFile.write((char *) &node1, sizeof(root));
////                treeFile.seekp(sizeof(header) * place2, ios::beg);
////                treeFile.write((char *) &node2, sizeof(root));
////                treeFile.close();
////                return IndexOfNode;
////            }
////        }
////            //not level one get the leaf to insert
////        else {
////            //root is non leaf
////
////            pair<int, vector<int>> visitedNodes = getLeaf(filename, root, RecordID);
////            int index = visitedNodes.first;
////            treeFile.seekg(index * sizeof(root), ios::beg);
////            Node current;
////            treeFile.read((char *) &current, sizeof(root));
////            int flag = 0;
////            for (int i = 0; i < current.capacity; i += 2) {
////                if (current.valOfFreenode[i] == -1) {
////                    flag = 1;
////                    current.valOfFreenode[i] = RecordID;
////                    current.valOfFreenode[i + 1] = Reference;
////                    sortNode(current.valOfFreenode, i + 1);
////                    treeFile.seekp(index * sizeof(root), ios::beg);
////                    treeFile.write((char *) &current, sizeof(root));
////                    break;
////                }
////            }
////            if (flag == 1) {
////                for (auto &it: visitedNodes.second) {
////                    treeFile.seekp(it * sizeof(root), ios::beg);
////                    treeFile.read((char *) &current, sizeof(root));
////                    if (current.nonLeaf) {
////                        for (int j = 0; j < current.capacity; j += 2) {
////                            if (current.valOfFreenode[j] == -1) {
////                                j -= 2;
////                                if (current.valOfFreenode[j] < RecordID) {
////                                    current.valOfFreenode[j] = RecordID;
////                                    current.valOfFreenode[j + 1] = index;
////                                }
////                                break;
////                            }
////                        }
////                    }
////                }
////                treeFile.close();
////                return index;
////                //split the leaf into two leaves
////            } else {
////                int newNode = header.valOfFreenode[0];
////                if (newNode == -1) return -1;
////                treeFile.seekg(newNode * sizeof(header), ios::beg);
////                Node node1;
////                treeFile.read((char *) &node1, sizeof(node1));
////                header.valOfFreenode[0] = node1.valOfFreenode[0];
////                // Split the nodes and determine nodeIndex
////                int oldMax = current.valOfFreenode[current.capacity - 2];
////                int nodeIndex = (current.valOfFreenode[current.capacity / 2 - 1] < RecordID) ? newNode : index;
////
////                pair<int, int> result = splitLeaf(current, node1, RecordID, Reference);
////
////                treeFile.seekp(newNode * sizeof(header), ios::beg);
////                treeFile.write((char *) &node1, sizeof(header));
////                vector<pair<int, int>> vector1;
////                vector1.emplace_back(result.first, index);
////                vector1.emplace_back(result.second, newNode);
////                //parent is root
////                if (visitedNodes.second.size() == 2) {
////                    //the root have place
////                    if (root.valOfFreenode[root.capacity - 1] == -1) {
////                        vector<pair<int, int>> v;
////                        for (int x = 0; x < root.capacity; x += 2) {
////                            if (root.valOfFreenode[x] != vector1[0].first and
////                                root.valOfFreenode[x] != vector1[1].first and
////                                root.valOfFreenode[x] != oldMax and root.valOfFreenode[x] != -1)
////                                v.emplace_back(root.valOfFreenode[x], root.valOfFreenode[x + 1]);
////                        }
////                        v.emplace_back(vector1[0].first, vector1[0].second);
////                        v.emplace_back(vector1[1].first, vector1[1].second);
////                        sort(v.begin(), v.end());
////                        int j = 0;
////                        for (int i = 0; i < v.size(); i++) {
////                            root.valOfFreenode[j] = v[i].first;
////                            root.valOfFreenode[j + 1] = v[i].second;
////                            j += 2;
////                        }
////                        while (j < root.capacity) {
////                            root.valOfFreenode[j] = -1;
////                            root.valOfFreenode[++j] = -1;
////                            ++j;
////                        }
////                    }
////                        // if root not empty split it
////                    else {
////                        int newplace = header.valOfFreenode[0];
////                        if (newplace == -1)return -1;
////                        treeFile.seekg(header.valOfFreenode[0] * sizeof(header), ios::beg);
////                        Node node4;
////                        treeFile.read((char *) &node4, sizeof(node4));
////                        header.valOfFreenode[0] = node4.valOfFreenode[0];
////                        int newplace2 = header.valOfFreenode[0];
////                        if (newplace2 == -1)return -1;
////                        treeFile.seekg(header.valOfFreenode[0] * sizeof(header), ios::beg);
////                        Node node2;
////                        treeFile.read((char *) &node2, sizeof(node4));
////                        header.valOfFreenode[0] = node2.valOfFreenode[0];
////
////                        splitRootNLeaf(root, node4, node2, newplace, newplace2, vector1[0].first, vector1[1].first,
////                                       oldMax,
////                                       vector1[0].second, vector1[1].second);
////
////                        treeFile.seekp(newplace2 * sizeof(header), ios::beg);
////                        treeFile.write((char *) &node2, sizeof(header));
////
////                        treeFile.seekp(newplace * sizeof(header), ios::beg);
////                        treeFile.write((char *) &node4, sizeof(header));
////                    }
////                    treeFile.close();
////                    return nodeIndex;
////                } else {
////                    int parentindx = visitedNodes.second[visitedNodes.second.size() - 1];
////                    treeFile.seekg(parentindx * sizeof(header), ios::beg);
////                    Node parent;
////                    treeFile.read((char *) &parent, sizeof(parent));
////                    // if parent is empty
////                    if (parent.valOfFreenode[parent.capacity - 1] == -1) {
////                        vector<pair<int, int>> v1;
////                        for (int x = 0; x < parent.capacity; x += 2) {
////                            if (parent.valOfFreenode[x] != vector1[0].first and
////                                parent.valOfFreenode[x] != vector1[1].first and
////                                parent.valOfFreenode[x] != oldMax and parent.valOfFreenode[x] != -1)
////                                v1.emplace_back(parent.valOfFreenode[x], parent.valOfFreenode[x + 1]);
////                        }
////                        v1.emplace_back(result.first, result.second);
////                        v1.emplace_back(result.first, result.second);
////                        sort(v1.begin(), v1.end());
////                        int j = 0;
////                        for (int i = 0; i < v1.size(); i++) {
////                            parent.valOfFreenode[j] = v1[i].first;
////                            parent.valOfFreenode[j + 1] = v1[i].second;
////                            j += 2;
////                        }
////                        while (j < parent.capacity) {
////                            parent.valOfFreenode[j] = -1;
////                            parent.valOfFreenode[++j] = -1;
////                            ++j;
////                        }
////                    } else {// if parent not empty split parent then put split leaves in
////                        bool flag = 0;
////                        for (int i = visitedNodes.second.size() - 2; i >= 0; i--) {
////                            treeFile.seekg(header.valOfFreenode[0] * sizeof(header), ios::beg);
////                            Node node;
////                            treeFile.read((char *) &node, sizeof(node));
////                            int newplace = header.valOfFreenode[0];
////                            if (newplace == -1)return -1;
////                            header.valOfFreenode[0] = node.valOfFreenode[0];
////                            int mParent = parent.valOfFreenode[parent.capacity - 2];
////                            pair<int, int> resSplitparent = splitParent(parent, node, newplace, vector1[0].first,
////                                                                        vector1[1].first,
////                                                                        oldMax, vector1[0].second,
////                                                                        vector1[1].second);
////                            treeFile.seekg(newplace * sizeof(header), ios::beg);
////                            treeFile.write((char *) &node, sizeof(node));
////                            vector1[0].first = resSplitparent.first;
////                            vector1[1].first = resSplitparent.second;
////                            vector1[0].second = visitedNodes.second[i + 1];
////                            vector1[1].second = newplace;
////                            oldMax = mParent;
////                            treeFile.seekg(visitedNodes.second[i] * sizeof(header), ios::beg);
////                            treeFile.read((char *) &parent, sizeof(parent));
////                            if (parent.valOfFreenode[parent.capacity - 1] == -1) {
////                                flag = 1;
////                                break;
////                            }
////                        }
////                        if (flag) {
////                            vector<pair<int, int>> v;
////                            for (int x = 0; x < parent.capacity; x += 2) {
////                                if (parent.valOfFreenode[x] != vector1[0].first and
////                                    parent.valOfFreenode[x] != vector1[1].first and
////                                    parent.valOfFreenode[x] != oldMax and parent.valOfFreenode[x] != -1)
////                                    v.emplace_back(parent.valOfFreenode[x], parent.valOfFreenode[x + 1]);
////                            }
////                            v.emplace_back(vector1[0].first, vector1[0].second);
////                            v.emplace_back(vector1[1].first, vector1[1].second);
////                            sort(v.begin(), v.end());
////                            int j = 0;
////                            for (auto &i: v) {
////                                parent.valOfFreenode[j] = i.first;
////                                parent.valOfFreenode[j + 1] = i.second;
////                                j += 2;
////                            }
////                            while (j < parent.capacity) {
////                                parent.valOfFreenode[j] = -1;
////                                parent.valOfFreenode[++j] = -1;
////                                ++j;
////                            }
////                            for (auto &it: visitedNodes.second) {
////                                treeFile.seekp(it * sizeof(root), ios::beg);
////                                treeFile.read((char *) &current, sizeof(root));
////                                if (current.nonLeaf) {
////                                    int j;
////                                    for (j = 0; j < current.capacity; j += 2) {
////                                        if (current.valOfFreenode[j] == -1) {
////                                            j -= 2;
////                                            if (current.valOfFreenode[j] < RecordID) {
////                                                current.valOfFreenode[j] = RecordID;
////                                                current.valOfFreenode[j + 1] = index;
////                                            }
////                                            break;
////                                        }
////                                    }
////                                }
////                            }
////                        } else {
////                            int place = header.valOfFreenode[0];
////                            if (place == -1)return -1;
////                            treeFile.seekg(header.valOfFreenode[0] * sizeof(header), ios::beg);
////                            Node node;
////                            treeFile.read((char *) &node, sizeof(node1));
////                            header.valOfFreenode[0] = node.valOfFreenode[0];
////
////                            int place3 = header.valOfFreenode[0];
////                            if (place3 == -1)return -1;
////                            treeFile.seekg(header.valOfFreenode[0] * sizeof(header), ios::beg);
////                            Node node1;
////                            treeFile.read((char *) &node1, sizeof(node1));
////                            header.valOfFreenode[0] = node1.valOfFreenode[0];
////                            splitRootNLeaf(parent, node, node1, place, place3, vector1[0].first, vector1[1].first,
////                                           oldMax,
////                                           vector1[0].second, vector1[1].second);
////                            treeFile.seekp(place3 * sizeof(header), ios::beg);
////                            treeFile.write((char *) &node1, sizeof(header));
////
////                            treeFile.seekp(place * sizeof(header), ios::beg);
////                            treeFile.write((char *) &node, sizeof(header));
////                        }
////                        treeFile.close();
////                        return nodeIndex;
////                    }
////                }
////            }
////        }
////    }
////    return -1;
////}