/*#include <iostream>
#include "BTRE.h"

using namespace std;

int main() {
    const char *FileName;
    FileName = "tree.txt";
    fstream file;
    file.open(FileName, ios::out);
    file.close();
    BTree bTree(5, 10);
    bTree.CreateIndexFileFile(FileName, 10, 5);
    bTree.insert(3, 12);
    bTree.insert(7, 24);
    bTree.insert(10, 48);
    bTree.insert(24, 60);
    bTree.insert(14, 72);
    bTree.insert(19, 84);
    bTree.insert(30, 96);
    bTree.insert(15, 108);
    bTree.insert(1, 120);
    bTree.insert(5, 132);
    bTree.insert(2, 144);
    bTree.insert(8, 156);
    bTree.insert(9, 168);
    bTree.insert(6, 180);
    bTree.insert(11, 192);
    bTree.insert(12, 204);
    bTree.insert(17, 216);
    bTree.insert(18, 228);
    bTree.insert(32, 240);
    bTree.writeBTree(FileName);
    cout<<"\n\n";
    bTree.del_key(const_cast<char *>(FileName), 10);
    bTree.writeBTree(FileName);
    bTree.DisplayIndexFileContent(FileName);

}
*/
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
            bTree.del_key(FileName, DID);
            cout << endl;

        } else if (n == 3) {
            cout << "Enter the SearchKey to search: ";
            cin >> SearchKey;
            cout << endl;
            int Search = bTree.search(FileName, SearchKey);
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