#include <iostream>
#include<fstream>
//#include "BTree.h"
#include "insert.cpp"

using namespace std;

int main() {
   char *FileName;
    FileName = "tree.txt";
    fstream file;
    file.open(FileName,ios::in);
    if ((file.fail()))
    {
        cout<<"fail "<<endl;
    }
    file.close();
    BTree bTree(5,10);
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

  //bTree.root->displayKey();
 //   bTree.CreateIndexFileFile(FileName, 10, 5);
 // bTree.InsertNewRecordAtIndex(FileName, 3, 12);
/*//    bTree.InsertNewRecordAtIndex(FileName, 7, 24);
//    bTree.InsertNewRecordAtIndex(FileName, 10, 48);
//    bTree.InsertNewRecordAtIndex(FileName, 24, 60);
//    bTree.InsertNewRecordAtIndex(FileName, 14, 72);
//
//
//    bTree.InsertNewRecordAtIndex(FileName, 19, 84);
//
//
//    bTree.InsertNewRecordAtIndex(FileName, 30, 96);
//    bTree.InsertNewRecordAtIndex(FileName, 15, 108);
//    bTree.InsertNewRecordAtIndex(FileName, 1, 120);
//    bTree.InsertNewRecordAtIndex(FileName, 5, 132);
//
//
//    bTree.InsertNewRecordAtIndex(FileName, 2, 144);
//
//    bTree.InsertNewRecordAtIndex(FileName, 8, 156);
//    bTree.InsertNewRecordAtIndex(FileName, 9, 168);
//    bTree.InsertNewRecordAtIndex(FileName, 6, 180);
//    bTree.InsertNewRecordAtIndex(FileName, 11, 192);
//    bTree.InsertNewRecordAtIndex(FileName, 12, 204);
//    bTree.InsertNewRecordAtIndex(FileName, 17, 216);
//    bTree.InsertNewRecordAtIndex(FileName, 18, 228);
//
//
//    bTree.InsertNewRecordAtIndex(FileName, 32, 240);
    
    int n,DID,SearchKey;
    while(true) {
        cout << "1- Display Index File\n";
        cout << "2- Delete Record\n";
        cout << "3- Search Record\n";
        cout << "4- Exit\n";
        cout << "\nEnter Choice: ";
        cin >> n;

        if (n == 1) {
            cout << endl;
            bTree.DisplayIndexFileContent(FileName);
            cout << endl;
        } else if (n == 2) {
            cout << "Enter Element to delete: ";
            cin >> DID;
            bTree.DeleteRecordFromIndex(FileName, DID);
            cout << endl;

        } else if (n == 3) {
            cout << "Enter the SearchKey to search: ";
            cin >> SearchKey;
            cout << endl;
            int Search = bTree.SearchARecord(FileName, SearchKey);
            if (Search == -1) {
                cout << Search << endl << "not found" << endl;
            } else if (Search == 0) {
                cout << "File Is Empty .. " << endl;
            }

        } else if (n == 4) {
            break;
        }
    }*/
   /* Node n;
    n.add(3,12);
    n.add(7,24);
    n.add(2,23);
    n.add(0,72);
    n.add(5,0);
    n.sort();
    n.displayKey();*/
    return 0;
}
