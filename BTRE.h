//
// Created by mamom on 12/31/2023.
//
#include <bits/stdc++.h>

#ifndef B_TREE_FILE_BASED_BTRE_H
#define B_TREE_FILE_BASED_BTRE_H

using namespace std;

class Node;

class element {
public:
    int key;
    int address;
    Node *next;
    element(int k, int a) {
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
    Node() = default;
    int capacity{};
    int nonLeaf{};
    int *valOfFreenode{};
    vector<element> node;
    bool isleaf = true;

    //constructor
    Node(int m, int next) {
        this->capacity = m * 2;
        this->nonLeaf = -1;
        valOfFreenode = new int[(m * 2)];
        valOfFreenode[0] = next;
        for (int i = 1; i < (m * 2); ++i) {
            valOfFreenode[i] = -1;
        }
    }

    //sort the vector according to the key
    void sort() {
        std::sort(node.begin(), node.end(), SortByKey());
    }

    //add element to Node
    void addEle(element e) {
        node.push_back(e);
        this->sort();
    }

};


class BTree {
public:
    fstream BTreeFile;
    int line = 1;
    Node *root = nullptr;
    int m, numberOfRecords;

    BTree(int m, int numberOfRecords);

    static void CreateIndexFileFile(const char *filename, int numberOfRecords, int m);

    static void DisplayIndexFileContent(const char *filename);

    Node search(int k) {
        Node x(0, 1);
        return x;
    }

    //search for first occurrence for a key
    Node *getNode(int key) const;

    //utility function for del-key
    Node *getleafparent(int key) const;

    //handle cases of deletion
    void del_key(char *filename, int x);

    //merge two nodes
    static void merge(Node *current, Node *sibling, Node *parent);

    //returns last parent to a non-leaf node
    static Node *getParent(int key, Node *start);

    //return leaf node for a non leaf element
    static Node *getLeaf(int key, Node *start);

    //delete a non leaf key and update all occurrences
    // of non leaf node with the new replacement
    int deletenleaf(Node &x, int key);

    //return pointer the
    Node *getParent(Node *node, Node *child);

    //handle cases of insertion with splitting and re splitting
    void insert(int key, int offset);

    //splits node and passing its children to the new children
    void split(Node *node);

    //takes node return to_string to that node
    string writeRecord(Node *node) const;

    //takes file name and update index file
    void writeBTree(const string &filename);

    int search(char *filename, int RecordID);
};

///------search function--------->>>>>>

int BTree ::search (char* filename, int RecordID){
    fstream treeFile;Node read;
    treeFile.open(filename, ios::in | ios::out | ios::binary);
    treeFile.seekg( 0,ios::beg);
    treeFile.read(reinterpret_cast<char *>(&read), sizeof (Node));
    int norecords;
    if(read.valOfFreenode[0]==-1){
        norecords=m;
    }else{
        norecords=read.valOfFreenode[0];
    }
    int i=0;
    while(i<norecords-1){
        treeFile.read(reinterpret_cast<char *>(&read), sizeof (Node));
        if(read.nonLeaf){
            i++;
            continue;
        }
        i++;
        int j=0;bool found=false;
        while(read.valOfFreenode[j]!=-1){
            if(read.valOfFreenode[j]>RecordID){
                break;
            }
            if(read.valOfFreenode[j]==RecordID){
                //cout<<"Found "<<read.valOfFreenode[j++]<<" Reference "<<read.valOfFreenode[j++]<<endl;
                found=true;
                j++;
                return read.valOfFreenode[j];
            }
            //cout<<read.valOfFreenode[j++]<<" "<<read.valOfFreenode[j++]<<endl;
            j+=2;
        }

    }
    treeFile.close();
    return -1;

}
///--------------------->>>>

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
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

Node *BTree::getNode(int key) const {
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

Node *BTree::getleafparent(int key) const {
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
                        insert(temp, temp2);
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
                        insert(temp, temp2);
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
    } else {
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

string BTree::writeRecord(Node *node) const {
    string record;
    int cnt = 0;
    record += to_string(!node->isleaf) + '|';

    for (const auto &key: node->node) {
        record += to_string(key.key) + '|' + to_string(key.address) + '|';
        cnt += 2;
    }

    while (cnt < m * 2) {
        record += to_string(-1) + '|';
        cnt++;
    }
    return record;
}

void BTree::writeBTree(const string &filename) {
    vector<pair<int, Node>> print;
    int x = 1;
    queue<Node> toprint;
    toprint.push(*root);

    // Open the file outside the loop
    this->BTreeFile.open(filename, ios::out);

    while (!toprint.empty()) {
        Node temp2 = toprint.front();
        print.emplace_back(++x, temp2);
        toprint.pop();
        for (auto i: temp2.node) {
            if (i.next != nullptr)
                toprint.push(*i.next);
        }
    }

    // Sort the vector after the loop
    sort(print.begin(), print.end(), [](const auto &a, const auto &b) {
        return a.first < b.first;
    });

    stringstream val;
    for (auto i: print) {
        val << writeRecord(&(i.second));
        val << '\n';
    }

    // Write to the file and then close it
    BTreeFile << val.str();
    this->BTreeFile.close();
}

Node *BTree::getParent(Node *node, Node *child) {
    if (node->isleaf) {
        return nullptr;
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
    return nullptr;
}

void BTree::insert(int key, int offset) {
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
            parent->node[maxKeyIndex].key = node->node[node->node.size() - 1].key;
        }
    }

    if (node->node.size() > m) {
        split(node);
    }
}

void BTree::split(Node *node) {
    Node *left = new Node;
    left->isleaf = node->isleaf;
    Node *right = new Node;
    right->isleaf = node->isleaf;
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
        root->isleaf = false;
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
        parent->node[i].next = left;
        parent->node[i + 1].next = right;
        if (parent->node.size() > m) {
            split(parent);
        }
    }
}

BTree::BTree(int m, int numberOfRecords) {
    this->m = m;
    this->numberOfRecords = numberOfRecords;
}

#endif //B_TREE_FILE_BASED_BTRE_H

///code ends here
///------------------->>
///-Z-A-W-A-R-U-D-O-O-0
///-I-S-_-U-R-_-B-O-S-S
///------------------->>

