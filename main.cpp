#include <iostream>
#include<fstream>
#include "BTree.cpp"

using namespace std;

int main() {
    char *FileName;
    FileName = "tree.txt";
    fstream file;
    file.open(FileName, ios::out);
    file.close();
    BTree bTree(5, 10);
    bTree.CreateIndexFileFile(FileName, 10, 5);
    bTree.InsertNewRecordAtIndex(FileName, 3, 12);
    bTree.InsertNewRecordAtIndex(FileName, 7, 24);
    bTree.InsertNewRecordAtIndex(FileName, 10, 48);
    bTree.InsertNewRecordAtIndex(FileName, 24, 60);
    bTree.InsertNewRecordAtIndex(FileName, 14, 72);
    bTree.InsertNewRecordAtIndex(FileName, 19, 84);
    bTree.InsertNewRecordAtIndex(FileName, 30, 96);
    bTree.InsertNewRecordAtIndex(FileName, 15, 108);
    bTree.InsertNewRecordAtIndex(FileName, 1, 120);
    bTree.InsertNewRecordAtIndex(FileName, 5, 132);
    bTree.InsertNewRecordAtIndex(FileName, 2, 144);
    bTree.InsertNewRecordAtIndex(FileName, 8, 156);
    bTree.InsertNewRecordAtIndex(FileName, 9, 168);
    bTree.InsertNewRecordAtIndex(FileName, 6, 180);
    bTree.InsertNewRecordAtIndex(FileName, 11, 192);
    bTree.InsertNewRecordAtIndex(FileName, 12, 204);
    bTree.InsertNewRecordAtIndex(FileName, 17, 216);
    bTree.InsertNewRecordAtIndex(FileName, 18, 228);
    bTree.InsertNewRecordAtIndex(FileName, 32, 240);
    bTree.DisplayIndexFileContent(FileName);
}