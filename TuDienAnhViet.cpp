#include <iostream>
using namespace std;

typedef struct word {
    string en;
    string vi;
    int id;
} Word;

int currentID = 0; 

void inputWord(Word &w) {
    cout << "Nhap tu tieng Anh: ";
    cin >> w.en;
    cout << "Nhap nghia tieng Viet: ";
    cin >> w.vi;
    w.id = ++currentID;
}

typedef struct node {
    struct node *prev;
    Word data;
    struct node *next;
} Node;

typedef struct dlist {
    Node* head;
    Node* tail;
    int size;
    // khoi tao danhsach
     dlist();
  // ham tao Node
    Node *createNode(Word &x);
    void addFirst(Word &x);
    void addLast(Word &x);
    void insert(Word &x, int p);
    void search(Word &x);
    void remove(int p);
    void display();
} Dlist;

