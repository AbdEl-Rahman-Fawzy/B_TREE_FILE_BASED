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
    }
}
