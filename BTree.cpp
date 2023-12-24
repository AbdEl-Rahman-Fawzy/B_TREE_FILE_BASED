#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
class Node{
public:
    char key[5] ;
    char address [5];
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
};
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
    int m , numberOfRecords;
    BTree(int m , int numberOfRecords){
        this->m = m;
        this->numberOfRecords = numberOfRecords;
    }
    void CreateIndexFileFile (char * filename, int _numberOfRecords, int _m){
        this->numberOfRecords = _numberOfRecords;
        this->m = _m;

        BTreeFile.open(filename , ios::out);
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
    }
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
                cout<<block.keys[i].getKey()<<"\t" <<block.keys->getAddress()<<"\t";
            }
            cout<< endl;
            rrn++;
        }
        BTreeFile.close();
    }
    int InsertNewRecordAtIndex (char * filename, int RecordID, int Reference){}
    void DeleteRecordFromIndex (char* filename, int RecordID){}
    int SearchARecord (char* filename, int RecordID){}

};
