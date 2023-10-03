#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Node {
    char info[80];
    Node* next;
};

typedef Node NODE;

NODE* start = nullptr;
NODE* copy = nullptr;

char fn[80];

void insert();
void delet();
void show();
void copyy();
void paste();
void save();
void openn();

int main() {
    int ch;

    do {
        cout << "\n\t******LINE EDITOR MENU******";
        cout << "\n\n\t\t1. Insert\n\t\t2. Delete\n\t\t3. Show\n\t\t4. Copy\n\t\t";
        cout << "5. Paste\n\t\t6. Save\n\t\t7. Open\n\t\t0. Exit";
        cout << "\n\n\tENTER YOUR CHOICE:- ";
        cin >> ch;

        switch (ch) {
            case 0:
                exit(0);
            case 1:
                insert();
                break;
            case 2:
                delet();
                break;
            case 3:
                show();
                break;
            case 4:
                copyy();
                break;
            case 5:
                paste();
                break;
            case 6:
                save();
                break;
            case 7:
                openn();
                break;
            default:
                cout << "\n\t!!!! Invalid Choice !!!!\n";
        }
    } while (1);

    return 0;
}

void insert() {
    char data[80];
    cout << "\nEnter text to insert: ";
    cin.ignore();
    cin.getline(data, sizeof(data));
    data[strcspn(data, "\n")] = '\0';  // Remove trailing newline if any

    NODE* new_node = new NODE;
    strcpy(new_node->info, data);
    new_node->next = nullptr;

    if (!start) {
        start = new_node;
    } else {
        NODE* current = start;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void delet() {
    if (!start) {
        cout << "\nNO DATA FOUND TO DELETE";
        return;
    }

    int line_number;
    cout << "\nEnter line number to delete: ";
    cin >> line_number;

    if (line_number == 1) {
        NODE* temp = start;
        start = start->next;
        delete temp;
    } else {
        NODE* current = start;
        for (int i = 1; i < line_number - 1 && current->next; ++i) {
            current = current->next;
        }
        if (current->next) {
            NODE* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
}

void show() {
    if (!start) {
        cout << "\nNo lines to show.\n";
        return;
    }

    NODE* current = start;
    while (current) {
        cout << "\t" << current->info << endl;
        current = current->next;
    }
}

void copyy() {
    if (!start) {
        cout << "\nNO DATA FOUND TO COPY";
        return;
    }

    int line_number;
    cout << "\nEnter line number to copy: ";
    cin >> line_number;

    NODE* current = start;
    for (int i = 1; i < line_number && current; ++i) {
        current = current->next;
    }

    copy = new NODE;
    strcpy(copy->info, current->info);
    copy->next = nullptr;
}

void paste() {
    if (!copy) {
        cout << "\nNO DATA FOUND TO PASTE";
        return;
    }

    int line_number;
    cout << "\nEnter line number to paste after: ";
    cin >> line_number;

    NODE* current = start;
    for (int i = 1; i < line_number && current; ++i) {
        current = current->next;
    }

    NODE* temp = current->next;
    current->next = copy;
    copy->next = temp;
}

void save() {
    if (!start) {
        cout << "\nNO DATA FOUND TO SAVE";
        return;
    }

    cout << "\nEnter the file name: ";
    cin >> fn;

    ofstream fp(fn);
    if (!fp) {
        cout << "\nCannot open file for writing.";
        return;
    }

    NODE* current = start;
    int i = 1;

    while (current) {
        fp << i << " " << current->info << "\n";
        current = current->next;
        i++;
    }

    fp.close();
    cout << "\nCurrent content is saved in " << fn << endl;
}

void openn() {
    cout << "\nEnter the file name to open: ";
    cin >> fn;

    ifstream fp(fn);
    if (!fp) {
        cout << "\nCannot open file for reading.\n";
        return;
    }

    char line[80];
    while (fp.getline(line, sizeof(line))) {
        NODE* new_node = new NODE;
        strcpy(new_node->info, line);
        new_node->next = nullptr;

        if (!start) {
            start = new_node;
        } else {
            NODE* current = start;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    cout << "\nFile contents have been loaded into the editor.\n";
    fp.close();
}
