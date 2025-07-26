#include <iostream>
using namespace std;

typedef struct word
{
  string en;
  string vi;
  int id;
} Word;

int increment = 0;

void inputWord(Word &w)
{
  cin.ignore();
  cout << "Nhap tu tieng Anh: ";
  getline(cin, w.en);
  cout << "Nhap nghia tieng Viet: ";
  getline(cin, w.vi);
  w.id = ++increment;
}

typedef struct node
{
  struct node *prev;
  Word data;
  struct node *next;
} Node;

typedef struct dlist
{
  Node *head;
  Node *tail;
  int size;
  dlist();
  Node *createNode(Word &x);
  void addWord(Word &x); // them rang buoc khi trung tu
  void search(string word);
  void display();
  void prevWord(Word &x);
  void sizeDict();
  void removeFirstWord();
  void removeLastWord();
  void removeWord(string word);
  void removeAllWords();
  void editWord(string word, Word &newWord);
  void swap(Node *&a, Node *&b);
  Node *getlastNode();
  Node *partition(Node *&low, Node *&high);
  Node *partition2(Node *&low, Node *&high);
  void quickSort(Node *&low, Node *&high);
  void quickSort2(Node *&low, Node *&high);

} Dlist;

dlist::dlist()
{
  head = tail = NULL;
  size = 0;
}

Node *dlist::createNode(Word &x)
{
  Node *p = new Node;
  p->data = x;
  p->prev = NULL;
  p->next = NULL;
  return p;
}

void dlist::addWord(Word &x)
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
      if (p == head) // Neu node da o dau danh sach
      {
        return; // Khong can di chuyen
      }
      q->next = p->next; // Xoa node da tim thay khoi danh sach
      p->next = head;    // Di chuyen node da tim thay ve dau
      p->prev = NULL;
      head = p;
      return;
    }
    q = p;
    p = p->next;
  }
  cout << "Khong tim thay tu" << endl;
  return;
}

void dlist::editWord(string word, Word &newWord)
{
  Node *p = head;
  while (p != NULL)
  {
    if (p->data.en == word)
    {
      p->data = newWord; // Cap nhat tu moi
      cout << "Da cap nhat tu: " << p->data.en << " - " << p->data.vi << endl;
      return;
    }
    p = p->next;
  }
  cout << "Khong tim thay tu de cap nhat" << endl;
}

void dlist::swap(Node *&a, Node *&b)
{
  Word temp = a->data;
  a->data = b->data;
  b->data = temp;
}

void dlist::removeFirstWord()
{
  if (head != NULL)
  {
    Node *a = head;
    head = head->next;
    head->prev = NULL;
    delete a;
    size--;
  }
  else
  {
    cout << "Danh sach rong, khong can xoa." << endl;
  }
}

void dlist::removeLastWord()
{
  if (head == NULL)
  {
    cout << "Danh sach rong, khong can xoa." << endl;
    return;
  }
  else if (head == tail)
  {
    delete head;
    head = tail = NULL;
    size = 0;
    return;
  }
  else
  {
    Node *temp = head;

    while (temp->next != tail)
    {
      temp = temp->next;
    }

    cout << "Tu ke cuoi: " << temp->data.en << endl;
    tail = temp;
    delete tail->next;
    tail->next = NULL;
    size--;
  }
}

void dlist::removeWord(string word)
{
  Node *p = head;
  while (p != NULL)
  {
    if (p->data.en == word)
    {
      if (p == head) // Neu node can xoa o dau danh sach
      {
        removeFirstWord();
      }
      else if (p == tail) // Neu node can xoa o cuoi danh sach
      {
        removeLastWord();
      }
      else // Neu node can xoa o giua danh sach
      {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        size--;
      }
      return;
    }
    p = p->next;
  }
  cout << "Khong tim thay tu de xoa" << endl;
}


Node *dlist::getlastNode()
{
  Node *p = head;
  while (head != NULL && p->next != NULL)
  {
    p = p->next;
  }
  return p;
}

Node *dlist::partition(Node *&low, Node *&high)
{
  Word pivot = high->data;
  Node *i = low->prev;

  for (Node *j = low; j != high; j = j->next)
  {
    if (j->data.en < pivot.en)
    {
      i = (i == NULL) ? low : i->next;
      swap(i, j);
    }
  }
  i = (i == NULL) ? low : i->next;
  swap(i, high);
  return i;
}

Node *dlist::partition2(Node *&low, Node *&high)
{
  Word pivot = high->data;
  Node *i = low->prev;

  for (Node *j = low; j != high; j = j->next)
  {
    if (j->data.en > pivot.en)
    {
      i = (i == NULL) ? low : i->next;
      swap(i, j);
    }
  }
  i = (i == NULL) ? low : i->next;
  swap(i, high);
  return i;
}

void dlist::quickSort(Node *&low, Node *&high)
{
  if (low != nullptr && high != nullptr && low != high && low != high->next)
  {

    Node *pivot = partition(low, high);

    quickSort(low, pivot->prev);

    quickSort(pivot->next, high);
  }
}

void dlist::quickSort2(Node *&low, Node *&high)
{
  if (low != nullptr && high != nullptr && low != high && low != high->next)
  {

    Node *pivot = partition2(low, high);

    quickSort2(low, pivot->prev);

    quickSort2(pivot->next, high);
  }
}

void dlist::display()
{
  for (Node *i = head; i != NULL; i = i->next)
  {
    cout << "(" << i->data.id << ") " << i->data.en << " - " << i->data.vi << " " << endl;
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
  for (int i = 0; i < n; i++)
  {
    inputWord(w);
    ds.addWord(w);
  }

  cout << "Danh sach tu dien:\n";
  Node *lastNode = ds.getlastNode();
  cout << "lastNode: " << lastNode->data.en << endl;
  // ds.quickSort2(ds.head, lastNode);
  ds.display();
  ds.removeWord("aple");
  cout << "Danh sach sau khi xoa tu :\n";
  ds.display();
  // cout << "Nhap tu can sua: ";
  // string word;
  // getline(cin, word);
  // Word newWord;
  // inputWord(newWord);
  // ds.editWord(word, newWord);
  // ds.display();
  return 0;
}