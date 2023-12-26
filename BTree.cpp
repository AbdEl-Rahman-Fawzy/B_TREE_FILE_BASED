#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include<cstddef>
#include<cmath>



using namespace std;

class Node;

class element
{
    public:
    int key ;
    int address;
    Node * next;
    element(int k,int a =-1)
    {
        key=k;
        address=a;
        next=nullptr;
    }

};
struct SortByKey
{
    bool operator() (element const &l,element  const& r)
    {
        return (l.key)<(r.key) ;
    }

};
//#define nullptr NULL
class Node
{
    public:
    //m
    int capacity;
   /* vector<pair<int,Node*>> key;
    //vector<Node*> pointers;
    vector<int> address;*/
    //int capacity;
    vector<element> node;
    bool isleaf=true;
   
    void setCapacity(int s)
    {
        capacity=s;
    }
    int getKey(int i)
    {
        return node[i].key;
    }
    void changeKeyAt(int index, int value)
    {
        node[index].key=value;
    }
    bool is_full()
    {
        int size=node.size();
        if(size==capacity)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int getSize()
    {
        return node.size();
    }
    //sort the vector according to the key 
    void sort()
    {
        std::sort(node.begin(),node.end(),SortByKey());
    }
    //to create and add element to node
    void add(int id,int ref)
    {
       element e(id,ref);
       node.push_back(e);
       this->sort();
    }
    //add element to node

    void addEle(element e)
    {
        node.push_back(e);
       this->sort();
    }
    void displayKey()
    {
        for(int i=0;i<node.size();i++)
        {
            cout<<" key :"<<this->getKey(i)<<" --> ref:"<<node[i].address<<endl;
        }
    }
    element getfront()
    {
        return node.front();
    }
    void popFront()
    {
        node.erase(node.begin());

    }
    int getMaxKey()
    {
        return node.back().key;
    }
    //returns the next node of an element
    Node* getNext(int i)
    {
        return node[i].next;

    }
};

/*
class Node{
public:
    char key[5] ;
    char address [5];
    Node* pointers[5] ;
    Node(){
        strncpy(key , "-1" , sizeof(key) -1);
        strncpy(address , "-1" , sizeof(address) -1);

    }
    Node(int key , int address){
        setKey(key);
        setAddress(address);
    }
    void setKey(int _key){
        strncpy(this->key , std::to_string(_key).c_str() , sizeof(key) - 1);
    }
    int getKey(){
        return atoi(key);
    }
    void setAddress(int _address){
        strncpy(this->address , std::to_string(_address).c_str() , sizeof(address) - 1);
    }
    int getAddress(){
        return atoi(address);
    }
};*/
class Block{
public:
    char leaf[5] ;
    Node keys[5] ;
    Block(){
        strncpy(leaf , "-1" , sizeof (leaf) - 1);
    }
    void setLeaf(int leaf){
        strncpy(this->leaf , to_string(leaf).c_str() , sizeof(leaf) -1);
    }
    int getLeaf(){
        return atoi(leaf);
    }
};
class BTree{
public:
    fstream BTreeFile;
    Node* root=nullptr;
    bool level1=true;
    int m , numberOfRecords;
    BTree(int m , int numberOfRecords){
        this->m = m;
        this->numberOfRecords = numberOfRecords;
    }
    void split(Node* l,Node* r)
    {

    }
  pair<Node*,int > findPlace( int ref)
    {
        Node* ptr=new Node();
        Node* prev=new Node();
        //postion of the element that holds the pointer to the position
        int pos;
        bool found=false;
        ptr=root;

        // while a leaf position is not found
        while(!found&&!(ptr->isleaf))
        {
            for(int i=0;i<ptr->getSize();i++)
            {
                //ref smaller than element
                if(ref<(ptr->getKey(i)))
                {
                    pos=i;
                    found=true;
                    prev=ptr;
                    ptr=ptr->getNext(i);
                    break;
                }
                // if the element is not smaller than the last key in the node then it is our position
                else if(!found &&( i= (ptr->getSize())-1))
                {
                    pos=i;
                    found=true;
                    prev=ptr;
                    ptr=ptr->getNext(i);
                    break;
                }
            }
        }
        //return the node that points to node where we can insert the new element and is  a leaf node 
        return {prev,pos};
    }
    /*
    void CreateIndexFileFile (char * filename, int _numberOfRecords, int _m){
        this->numberOfRecords = _numberOfRecords;
        this->m = _m;

        BTreeFile.open(filename , ios::out);
        if(BTreeFile.fail())
        {
            cout<<"fail in f"<<endl;
        }
        BTreeFile.seekg(0 , ios ::end);

        if(BTreeFile.tellg() <= 0){
            for (int i = 0; i < numberOfRecords; i++) {
                Block block;
                block.setLeaf(-1);
                for (int j = 0; j < m; j++) {
                    if(j == 0 && i < numberOfRecords -1){
                        block.keys[j].setKey(i+1);
                    } else{
                        block.keys[j].setKey(-1);
                    }
                    block.keys[j].setAddress(-1);
                }
                BTreeFile.seekg(i* sizeof block , ios::beg);
                BTreeFile.write((char *) &block , sizeof block);
            }
            BTreeFile.close();
        }
    }*/
    void DisplayIndexFileContent(char *fileName ){
        
        BTreeFile.close();
        BTreeFile.open(fileName , ios::in);
        Block block ;
        int rrn = 0;
        while (numberOfRecords--){
            BTreeFile.seekg(rrn * sizeof block , ios::beg);
            BTreeFile.read((char *) &block , sizeof block);
            cout<<block.getLeaf()<<"   ";
            for (int i = 0; i < m; ++i) {
             //   cout<<block.keys[i].getKey()<<"\t" <<block.keys->getAddress()<<"\t";
            }
            cout<< endl;
            rrn++;
        }
        BTreeFile.close();
    }
    int InsertNewRecordAtIndex (char * filename, int RecordID, int Reference)
    {
        // index is empty
        if(root==nullptr)
        {
            cout<<"index is empty"<<endl;
            Node* newNode= new Node();
            newNode->setCapacity(m);
            newNode->add(RecordID,Reference);
            cout<<"d 1:";
            this->root=newNode;
            newNode=nullptr;
            delete newNode;
        }
        //level one that directly points to refrence
        else if(level1)
        {
            //level one is complete then we must split and add another level
            if(root->is_full())
            {
                cout<<"yes it is full"<<endl;
                level1=false;
                root->add(RecordID,Reference);
                //split
                Node* newNode= new Node();
                Node* newNode2=new Node();
                newNode->setCapacity(m);
                newNode2->setCapacity(m);
                int mid= ceil((this->root->getSize())/2);
                cout<<"mid ==>"<<mid<<endl;
                for(int i=0;i< mid;i++)
                {
                    newNode->addEle(root->getfront());
                    root->popFront();
                }
                cout<<"left node =====>"<<endl;
                newNode->displayKey();
                 for(int i=mid;i< m+1;i++)
                {
                    newNode2->addEle(root->getfront());
                    root->popFront();
                }
                cout<<"Right node =====>"<<endl;
                newNode2->displayKey();
                //create a new level
                Node* newpar=new Node();
                int max1=newNode->getMaxKey();
                int max2=newNode2->getMaxKey();
                element e1(max1);
                e1.next=newNode;
                newpar->addEle(e1);
                element e2(max2);
                e2.next=newNode2;
                newpar->addEle(e2);
                newpar->isleaf=false;
                root=newpar;
                newpar=nullptr;
                newNode=nullptr;
                newNode2=nullptr;
                delete newpar;
                delete newNode;
                delete newNode2;
                cout<<"===========test=============="<<endl;
                this->root->displayKey();
                cout<<"left child =====>"<<endl;
                this->root->getfront().next->displayKey();

            }
            else
            {
               root->add(RecordID,Reference);
            }

        }
        else
        {
            Node* ptr= new Node();
            int pos;
            ptr=findPlace(RecordID).first;
            pos=findPlace(RecordID).second;
            Node* place=new Node();
            place=ptr->getNext(pos);
            if(place->isleaf)
            {
                cout<<" the found place is a leaf"<<endl;
            }
            if(place->is_full())
            {
                //split
            }
            else
            {
                place->add(RecordID,Reference);
                //if the new inserted value greater than the pointer then change the value of the key
                if(RecordID>ptr->getKey(pos))
                {
                    ptr->changeKeyAt(pos,RecordID);
                }
                cout<<"parent :"<<endl;
                ptr->displayKey();
                cout<<"child : "<<endl;
                ptr->getNext(pos)->displayKey();
                cout<<"child  again: "<<endl;
                place->displayKey();

            }

        }
        cout<<"========================="<<endl;
        this->root->displayKey();
        return -1;
    }
    void DeleteRecordFromIndex (char* filename, int RecordID){}
    int SearchARecord (char* filename, int RecordID){
        return 0;
    }

};
