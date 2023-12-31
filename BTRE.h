//
// Created by mamom on 12/31/2023.
//
#include <bits/stdc++.h>

#ifndef B_TREE_FILE_BASED_BTRE_H
#define B_TREE_FILE_BASED_BTRE_H

using namespace std;
class BTRE {

};

class Node;

class element {
public:
    int key;
    int address;
    Node *next;

    element(int k, int a = -1) {
        key = k;
        address = a;
        next = nullptr;
    }

};

struct SortByKey {
    bool operator()(element const &l, element const &r) {
        return (l.key) < (r.key);
    }

};

//#define nullptr NULL
class Node {
public:
    //m
    int capacity;
    int nonLeaf;
    int *valOfFreenode;
    vector<element> node;
    bool isleaf = true;

    Node() {};

    Node(int m, int next) {
        this->capacity = m * 2;
        this->nonLeaf = -1;
        valOfFreenode = new int[(m * 2)];
        valOfFreenode[0] = next;
        for (int i = 1; i < (m * 2); ++i) {
            valOfFreenode[i] = -1;
        }
    }


    void setCapacity(int s) {
        capacity = s;
    }

    int getKey(int i) {
        return node[i].key;
    }

    void changeKeyAt(int index, int value) {
        node[index].key = value;
    }

    bool is_full() {
        int size = node.size();
        if (size == capacity) {
            return true;
        } else {
            return false;
        }
    }

    int getSize() {
        return node.size();
    }

    //sort the vector according to the key
    void sort() {
        std::sort(node.begin(), node.end(), SortByKey());
    }

    //to create and add element to Node
    void add(int id, int ref) {
        element e(id, ref);
        node.push_back(e);
        this->sort();
    }
    //add element to Node

    void addEle(element e) {
        node.push_back(e);
        this->sort();
    }

    element getfront() {
        return node.front();
    }

    void popFront() {
        node.erase(node.begin());

    }

    int getMaxKey() {
        return node.back().key;
    }

    //returns the next Node of an element
    Node *getNext(int i) {
        return node[i].next;

    }

    void sortNode(int *arr, int indx) {
        vector<pair<int, int>> v;
        for (int i = 0; i <= indx; i += 2) {
            v.emplace_back(arr[i], arr[i + 1]);
        }
        ::sort(v.begin(), v.end());
        for (int i = 0, j = 0; i <= indx; i += 2, j++) {
            arr[i] = v[j].first;
            arr[i + 1] = v[j].second;
        }
    }
};

class BTree {
public:
    fstream BTreeFile;
    int line = 1;
    Node *root = nullptr;
    int m, numberOfRecords;

    BTree(int m, int numberOfRecords) {
        this->m = m;
        this->numberOfRecords = numberOfRecords;
    }

    void CreateIndexFileFile(const char *filename, int numberOfRecords, int m);

    void DisplayIndexFileContent(const char *filename);

    Node search(int k) {
        Node x(0, 1);
        return x;
    }

    Node *getNode(int key);

    Node *getleafparent(int key);

    void del_key(char *filename, int x);


    void merge(Node *current, Node *sibling, Node *parent);

    Node *getParent(int key, Node *start);

    Node *getLeaf(int key, Node *start);

    int deletenleaf(Node &x, int key);

    Node *getParent(Node *node, Node *child) {
        if (node->isleaf) {
            return NULL;
        }
        for (int i = 0; i < m; i++) {
            if (node->node[i].next == child) {
                return node;
            }
            Node *parent = getParent(node->node[i].next, child);
            if (parent != nullptr) {
                return parent;
            }
        }
        return NULL;
    }

    void insert(char *filename, int key, int offset) {
        if (root == nullptr) {
            root = new Node;
            root->isleaf = true;
            root->addEle(element(key, offset));
            return;
        }

        Node *node = root;
        Node *parent = nullptr;

        while (!node->isleaf) {
            parent = node;

            int i = 0;
            while (i < node->node.size() - 1 && key > node->node[i].key) {
                i++;
            }

            if (i < node->node.size() && node->node[i].next != nullptr) {
                node = node->node[i].next;
            } else {// No more child nodes to traverse
                break;
            }
        }

        node->addEle(element(key, offset));

        if (parent != nullptr) {
            // Update parent node with the maximum value from the child
            int maxKeyIndex = parent->node.size() - 1;
            if (parent->node[maxKeyIndex].key < node->node[node->node.size() - 1].key) {
                parent->node[maxKeyIndex] = node->node[node->node.size() - 1];
            }
        }

        if (node->node.size() > m) {
            split(node);
        }
    }


    void split(Node *node) {
        Node *left = new Node;
        left->isleaf = true;
        Node *right = new Node;
        right->isleaf = true;
        int mid = node->node.size() / 2;
        for (int i = 0; i < mid; i++) {
            left->addEle(element(node->node[i].key, node->node[i].address));
        }

        for (int i = mid; i < node->node.size(); i++) {
            right->addEle(element(node->node[i].key, node->node[i].address));
        }

        if (!node->isleaf) {
            for (int i = 0; i < mid; i++) {
                left->node[i].next = node->node[i].next;
            }
            for (int i = mid; i < node->node.size(); i++) {
                right->node[i - mid].next = node->node[i].next;
            }
        }

        if (node == root) {
            root = new Node;
            root->isleaf = true;
            root->addEle(element(node->node[mid - 1].key, node->node[mid - 1].address));
            root->addEle(element(node->node[node->node.size() - 1].key, node->node[node->node.size() - 1].address));
            root->node[0].next = left;
            root->node[1].next = right;

        } else {
            Node *parent = getParent(root, node);
            int i = 0;
            while (i < parent->node.size() - 1 && node->node[mid].key > parent->node[i].key) {
                i++;
            }
            parent->addEle(element(node->node[mid - 1].key, node->node[mid - 1].address));
            // shift children to the right
            for (int j = parent->node.size() - 1; j > i; j--) {
                parent->node[j + 1].next = parent->node[j].next;
            }
            parent->node[i].next = left;
            parent->node[i + 1].next = right;
            if (parent->node.size() > m) {
                split(parent);
            }
        }
    }


    void writeBTree(string filename, int maxKeys, Node *root);

    string writeRecord(Node *node);

    void writeBTree(string filename);
};


void BTree::CreateIndexFileFile(const char *filename, int numberOfRecords, int m) {
    fstream Btree;
    Btree.open(filename, ios::in | ios::out | ios::binary | ios::app);
    for (int i = 0; i < numberOfRecords - 1; i++) {
        Node write(m, i + 1);
        Btree.write((char *) &write, sizeof(write));

    }
    Node write(m, -1);
    Btree.write((char *) &write, sizeof(write));
    Btree.close();
}

void BTree::DisplayIndexFileContent(const char *filename) {
    fstream Btree;
    Btree.open(filename, ios::in | ios::out | ios::binary | ios::app);
    Btree.seekg(0, ios::beg);
    Node read;
    while (Btree.read((char *) &read, sizeof(read))) {
        cout << read.nonLeaf << " ";
        for (int i = 0; i < read.capacity; ++i) {
            cout << read.valOfFreenode[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
    Btree.close();
}

Node *BTree::getNode(int key) {
    if (root == nullptr) {
        return nullptr;
    }

    Node *temp = root;
    int count = 0;
    while (count < numberOfRecords) {
        for (auto i: temp->node) {
            if (i.key == key) {
                return temp;
            }
        }
        int counter = 0;
        for (auto i: temp->node) {
            if (i.key > key) {
                temp = i.next;
                break;
            }
            counter++;
        }
        count++;

    }
    return nullptr;
}

Node *BTree::getleafparent(int key) {
    if (root == nullptr) {
        return nullptr;
    }
    Node *pre = root;
    Node *temp = root;
    int count = 0;
    while (count < numberOfRecords) {
        for (auto i: temp->node) {
            if (i.key == key) {
                return pre;
            }
        }
        int counter = 0;
        for (auto i: temp->node) {
            if (i.key > key) {
                pre = temp;
                temp = i.next;
                break;
            }
            counter++;
        }
        count++;

    }
    return nullptr;
}

void BTree::del_key(char *filename, int x) {
    Node *target = getNode(x);
    if (target == nullptr) {
        cout << "key not found \n";
        return;
    }
    if (target->isleaf) {
        if (target->node.size() > 2) {
            for (int i = 0; i < target->node.size(); i++) {
                if (x == target->node[i].key) {
                    target->node.erase(target->node.begin() + i);
                }
            }
        } else {
            for (int i = 0; i < target->node.size(); i++) {
                if (x == target->node[i].key) {
                    Node *parent = getleafparent(x);
                    Node *sibling = parent->node[parent->node.size() - 2].next;
                    if (sibling->node.size() == 2) {
                        target->node.erase(target->node.begin() + i);
                        merge(target, sibling, parent);
                    } else {
                        int temp = parent->node[parent->node.size() - 2].key;
                        int temp2 = parent->node[parent->node.size() - 2].address;
                        target->node.erase(target->node.begin() + i);
                        del_key(filename, temp);
                        insert(filename, temp, temp2);
                    }
                }
            }
        }
    } else {
        Node *leaf = getLeaf(x, target);
        if (leaf->node.size() >= 3) {
            deletenleaf(*target, x);
        }
        if (leaf->node.size() <= 2) {
            for (int i = 0; i < target->node.size(); i++) {
                if (x == target->node[i].key) {
                    Node *parent = getParent(x, target->node[i].next);

                    Node *sibling = parent->node[parent->node.size() - 2].next;
                    if (sibling->node.size() == 2) {
                        deletenleaf(*target, x);
                        merge(leaf, sibling, parent);
                    } else {
                        int temp = parent->node[parent->node.size() - 2].key;
                        int temp2 = parent->node[parent->node.size() - 2].address;
                        deletenleaf(*target, x);
                        del_key(filename, temp);
                        insert(filename, temp, temp2);
                    }
                }
            }

        }
    }
}

void BTree::merge(Node *current, Node *sibling, Node *parent) {
    sibling->node.push_back(current->node[0]);
    pair<int, int> x = {current->node[0].key, current->node[0].address};
    current->node.pop_back();
    parent->node.pop_back();
    parent->node[parent->node.size() - 1].key = x.first;
    parent->node[parent->node.size() - 1].address = x.second;
    //update index file
}

Node *BTree::getParent(int key, Node *start) {
    Node *parent = start;
    Node *temp = start;
    while (temp->isleaf == 1) {
        int counter = 0;
        for (auto i: temp->node) {
            if (i.key == key) {
                parent = temp;
                temp = i.next;
            }
            counter++;
        }
    }
    return parent;
}

Node *BTree::getLeaf(int key, Node *start) {
    Node *temp = start;
    while (temp->isleaf == 1) {
        int counter = 0;
        for (auto i: temp->node) {
            if (i.key == key) {
                temp = i.next;
            }
            counter++;
        }
    }
    return temp;
}

int BTree::deletenleaf(Node &x, int key) {
    if (x.isleaf) {
        x.node.pop_back();
        //update index file
        return x.node[x.node.size() - 1].key;
    }
    if (!x.isleaf) {
        for (auto &i: x.node) {
            if (i.key == key) {
                int replace = deletenleaf(*(i.next), key);
                i.key = replace;
                //update index file
                return replace;
            }
        }
    }
}

string BTree:: writeRecord(Node *node) {
    string record = "";
    int cnt = 0;
    record += to_string(node->isleaf) + '|';

    for (const auto &key: node->node) {

        record += to_string(key.key) + '|' + to_string(key.address) + '|';
        cnt+=2;
    }

    while (cnt < m*2) {
        record += to_string(-1) + '|';
        cnt++;
    }
    return record;
}

void BTree::writeBTree(string filename) {

    vector<pair<int ,Node >>print;
    int x = 1 ;
    queue<Node>toprint;
    toprint.push(*root);

    while(!toprint.empty()){
        Node temp2 = toprint.front();
        print.emplace_back(x,temp2);
        toprint.pop();
        for(auto i : temp2.node){
            if(i.next!=NULL)
                toprint.push(*i.next);
        }
    }
    sort(print.begin(), print.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });
    for(auto i : print){
        this->BTreeFile.open(filename, ios::out);
        string val = writeRecord(&(i.second));
        BTreeFile.write(val.data(),val.size());
        BTreeFile.put('\n');
    }

    this->BTreeFile.close();
}

#endif //B_TREE_FILE_BASED_BTRE_H
