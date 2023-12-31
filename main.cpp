#include <iostream>
#include<fstream>
#include "BTRE.h"

using namespace std;

int main() {
    char *FileName;
    FileName = "tree.txt";
    fstream file;
    file.open(FileName, ios::out);
    file.close();
    BTree bTree(5, 10);
    bTree.CreateIndexFileFile(FileName, 10, 5);
    bTree.insert(FileName, 3, 12);
    bTree.insert(FileName, 7, 24);
    bTree.insert(FileName, 10, 48);
    bTree.insert(FileName, 24, 60);
    bTree.insert(FileName, 14, 72);
    bTree.insert(FileName, 19, 84);
    bTree.insert(FileName, 30, 96);
    bTree.insert(FileName, 15, 108);
    bTree.insert(FileName, 1, 120);
    bTree.insert(FileName, 5, 132);
    bTree.insert(FileName, 2, 144);
    bTree.insert(FileName, 8, 156);
    bTree.insert(FileName, 9, 168);
    bTree.insert(FileName, 6, 180);
    bTree.insert(FileName, 11, 192);
    bTree.insert(FileName, 12, 204);
    bTree.insert(FileName, 17, 216);
    bTree.insert(FileName, 18, 228);
    bTree.insert(FileName, 32, 240);
    bTree.writeBTree(FileName);
    bTree.DisplayIndexFileContent(FileName);
}