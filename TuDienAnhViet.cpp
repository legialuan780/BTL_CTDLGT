#include <iostream>
using namespace std;

typedef struct word {
    string en;
    string vi;
    int id;
} Word;

int currentID = 0; 

void inputWord(Word &w) {
    cin.ignore(); 
    cout << "Nhap tu tieng Anh: ";
    getline(cin, w.en);
    cout << "Nhap nghia tieng Viet: ";
    getline(cin, w.vi);
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
    void addLast(Word &x);
    void search(string word);
    void remove(int p);
    void display();
    // sua tu
    // sort tu
    // kiem tra tu dien rong
    // xoa tu trung lap
    
} Dlist;

dlist::dlist() {
    head = tail = NULL;
    size = 0;
}

Node *dlist::createNode(Word &x) {
    Node *p = new Node;
    p->data = x;
    p->prev = NULL;
    p->next = NULL;
    return p;
}


void dlist::addLast(Word &x)
{
   Node *a = createNode(x);
  if (a == NULL)
  {
    cout << "het bo nho";
  }
  else if (head == NULL)
  {
    head = tail = a;
    size++;
  }
  else
  {
    tail->next = a;
    a->prev = tail;
    tail = a;
    size++;
  }

}

void dlist::search(string word)
{
  Node *p = head;
  Node *q;
  while (p != NULL)
  {
    if (p->data.en == word)
    {
      cout << "Tim thay tu: " << p->data.en << " - " << p->data.vi << " - id " << p->data.id << endl;
      if(p == head) // Neu node da o dau danh sach
      {
        return; // Khong can di chuyen
      }
      q->next = p->next; // Xoa node da tim thay khoi danh sach
      p->next=head; // Di chuyen node da tim thay ve dau
      p->prev=NULL;
      head=p;
      return;
    }
    q=p;
    p = p->next;
  }
  cout << "Khong tim thay tu" << endl;
  return;
}

void dlist::display()
{
  for (Node *i = head; i != NULL; i = i->next)
  {
    cout << "(" << i->data.id << ") " << i->data.en << " - " << i->data.vi << " "<<endl;
  }
  if (head == NULL)
  {
    cout << "Khong co phan tu";
  }
}

int main()
{
    Word w;
    Dlist ds;
    cout << "Nhap so luong tu: ";
    int n;
    cin >> n;
    cout << "Nhap lan luot tu tieng Anh va nghia tieng Viet:\n";
    for (int i = 0; i < n; i++) {
        inputWord(w);
        ds.addLast(w);
    }
    cout << "Danh sach tu dien:\n";
    ds.display();
    cout << "Nhap tu can tim: ";
    string word;
    getline(cin, word);
    ds.search(word);
     ds.display();
      cout << "Nhap tu can tim: ";
    string word2;
    getline(cin, word2);
    ds.search(word2);
    return 0;
}