#include <iostream>
#include "BTRE.h"

using namespace std;
void prepare(BTree * bTree ) {
    bTree->insert(3, 12);
    bTree->insert(7, 24);
    bTree->insert(10, 48);
    bTree->insert(24, 60);
    bTree->insert(14, 72);
    bTree->insert(19, 84);
    bTree->insert(30, 96);
    bTree->insert(15, 108);
    bTree->insert(1, 120);
    bTree->insert(5, 132);
    bTree->insert(2, 144);
    bTree->insert(8, 156);
    bTree->insert(9, 168);
    bTree->insert(6, 180);
    bTree->insert(11, 192);
    bTree->insert(12, 204);
    bTree->insert(17, 216);
    bTree->insert(18, 228);
    bTree->insert(32, 240);
}
int main() {
    const char *FileName;
    FileName = "tree.txt";
    fstream file;
    file.open(FileName, ios::out);
    file.close();

    char filename[50];
    int choice, RecordID, Reference, m, numberOfRecords, result;

    cout << "Enter the filename: ";
    std::cin >> filename;

    cout << "Enter the value of m: ";
    cin >> m;

    cout << "Enter the number of records: ";

    cin >> numberOfRecords;

    BTree bTree(m, numberOfRecords);
    bTree.CreateIndexFileFile(filename, numberOfRecords, m);

    prepare(&bTree);
    bTree.writeBTree(FileName);
    cout << "\n\n";
    bTree.writeBTree(FileName);
    bTree.DisplayIndexFileContent(FileName);

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Insert New Record\n";
        std::cout << "2. Delete Record\n";
        std::cout << "3. Display Index File Content\n";
        std::cout << "4. Search a Record\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter RecordID and Reference to insert: ";
                cin >> RecordID >> Reference;
                bTree.insert(RecordID, Reference);
                bTree.writeBTree(FileName);
                break;

            case 2:
                cout << "Enter RecordID to delete: ";
                cin >> RecordID;
                bTree.del_key(filename, RecordID);
                cout << "Record deleted.\n";
                bTree.writeBTree(FileName);
                break;

            case 3:
                cout << "Index File Content:\n";
                bTree.DisplayIndexFileContent(filename);
                bTree.writeBTree(FileName);
                break;

            case 4:
                std::cout << "Enter RecordID to search: ";
                std::cin >> RecordID;
                result = bTree.search(filename, RecordID);
                if (result == -1) {
                    std::cout << "Record not found in the index.\n";
                } else {
                    std::cout << "Record found at index " << result << ".\n";
                }
                break;

            case 5:
                std::cout << "Exiting program.\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}


