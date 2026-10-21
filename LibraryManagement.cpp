#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Book {
public:
    int id;
    string title, author;
    bool issued;
    int memberId;
    Book(int i=0, string t="", string a="", bool s=false, int m=0)
        : id(i), title(t), author(a), issued(s), memberId(m) {}
};

class Member {
public:
    int id;
    string name;
    Member(int i=0, string n="") : id(i), name(n) {}
};

vector<Book> books;
vector<Member> members;

void loadData() {
    books.clear(); members.clear();
    ifstream bf("books.txt");
    Book b;
    while (bf >> b.id) {
        bf.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(bf, b.title); getline(bf, b.author);
        bf >> b.issued >> b.memberId;
        bf.ignore(numeric_limits<streamsize>::max(), '\n');
        books.push_back(b);
    }
    ifstream mf("members.txt");
    Member m;
    while (mf >> m.id) {
        mf.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(mf, m.name);
        members.push_back(m);
    }
}
void saveBooks() {
    ofstream f("books.txt");
    for (const Book &b : books)
        f << b.id << '\n' << b.title << '\n' << b.author << '\n'
          << b.issued << '\n' << b.memberId << '\n';
}
void saveMembers() {
    ofstream f("members.txt");
    for (const Member &m : members) f << m.id << '\n' << m.name << '\n';
}
int findBook(int id) {
    for (int i=0; i<(int)books.size(); i++) if (books[i].id==id) return i;
    return -1;
}
int findMember(int id) {
    for (int i=0; i<(int)members.size(); i++) if (members[i].id==id) return i;
    return -1;
}
void addBook() {
    int id; string title, author;
    cout << "Enter book ID: "; cin >> id;
    if (findBook(id)!=-1) { cout << "Book ID already exists!\n"; return; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter title: "; getline(cin,title);
    cout << "Enter author: "; getline(cin,author);
    books.push_back(Book(id,title,author)); saveBooks();
    cout << "Book added successfully!\n";
}
void addMember() {
    int id; string name;
    cout << "Enter member ID: "; cin >> id;
    if (findMember(id)!=-1) { cout << "Member ID already exists!\n"; return; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter member name: "; getline(cin,name);
    members.push_back(Member(id,name)); saveMembers();
    cout << "Member added successfully!\n";
}
void displayBooks() {
    if (books.empty()) { cout << "No books found.\n"; return; }
    cout << "\n--- BOOK LIST ---\n";
    for (const Book &b : books)
        cout << "ID: " << b.id << " | Title: " << b.title
             << " | Author: " << b.author << " | Status: "
             << (b.issued ? "Issued to member " + to_string(b.memberId) : "Available") << '\n';
}
void displayMembers() {
    if (members.empty()) { cout << "No members found.\n"; return; }
    cout << "\n--- MEMBER LIST ---\n";
    for (const Member &m : members) cout << "ID: " << m.id << " | Name: " << m.name << '\n';
}
void searchBook() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string key; cout << "Enter book title or author to search: "; getline(cin,key);
    bool found=false;
    for (const Book &b : books)
        if (b.title.find(key)!=string::npos || b.author.find(key)!=string::npos) {
            cout << "ID: " << b.id << " | Title: " << b.title << " | Author: " << b.author
                 << " | Status: " << (b.issued ? "Issued" : "Available") << '\n';
            found=true;
        }
    if (!found) cout << "No matching book found.\n";
}
void issueBook() {
    int bid, mid; cout << "Enter book ID: "; cin >> bid;
    int i=findBook(bid);
    if (i==-1) { cout << "Book not found!\n"; return; }
    if (books[i].issued) { cout << "Book is already issued.\n"; return; }
    cout << "Enter member ID: "; cin >> mid;
    if (findMember(mid)==-1) { cout << "Member not found! Add the member first.\n"; return; }
    books[i].issued=true; books[i].memberId=mid; saveBooks();
    cout << "Book issued successfully!\n";
}
void returnBook() {
    int id; cout << "Enter book ID to return: "; cin >> id;
    int i=findBook(id);
    if (i==-1) { cout << "Book not found!\n"; return; }
    if (!books[i].issued) { cout << "This book is not currently issued.\n"; return; }
    books[i].issued=false; books[i].memberId=0; saveBooks();
    cout << "Book returned successfully!\n";
}
int main() {
    loadData();
    int choice;
    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n"
             << "1. Add Book\n2. Add Member\n3. Display Books\n4. Display Members\n"
             << "5. Search Book by Title/Author\n6. Issue Book\n7. Return Book\n8. Exit\n"
             << "Enter choice: ";
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
        }
        switch(choice) {
            case 1: addBook(); break;
            case 2: addMember(); break;
            case 3: displayBooks(); break;
            case 4: displayMembers(); break;
            case 5: searchBook(); break;
            case 6: issueBook(); break;
            case 7: returnBook(); break;
            case 8: cout << "Thank you for using the library system!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while(choice!=8);
    return 0;
}
