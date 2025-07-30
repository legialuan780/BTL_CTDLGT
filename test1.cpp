#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
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
  void addLastWord(Word &x); // them rang buoc khi trung tu
  void search(string word);
  void display();
  void prevWord(Word &x);
  int sizeDict();
  void removeFirstWord();
  void removeLastWord();
  void removeWord(string word);
  void removeAllWords();
  void removeDuplicate();
  void editWord(string word, Word &newWord);
  void swap(Node *&a, Node *&b);
  Node *getlastNode();
  Node *partition(Node *&low, Node *&high);
  Node *partition2(Node *&low, Node *&high);
  void quickSort(Node *&low, Node *&high);
  void quickSort2(Node *&low, Node *&high);
  void sortedInsert(Word &x);
  void readFromFile(const string &filename);
  void saveToFile(const string &filename);
  void wordGame();
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

void dlist::addLastWord(Word &x)
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

void dlist::prevWord(Word &x)
{
  cout << "Nhap tu tieng Anh: ";
  getline(cin, x.en);
  Node *a = head;
  while (a != NULL)
  {
    if (a->data.en == x.en)
    {
      if (a->prev != NULL)
      {
        cout << "Tu truoc: " << a->prev->data.en << endl;
      }
      else
      {
        cout << "Khong co tu truoc" << endl;
      }
      return;
    }
    a = a->next;
  }
  cout << "Khong tim thay tu" << endl;
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

void dlist::removeAllWords()
{
  Node *p = head;
  while (p != NULL)
  {
    Node *temp = p;
    p = p->next;
    delete temp;
  }
  head = tail = NULL;
  size = 0;
}

void dlist::removeDuplicate()
{
  Node *current = head;
  while (current != NULL)
  {
    Node *temp = current;
    while (temp->next != NULL)
    {
      if (temp->next->data.en == current->data.en)
      {
        Node *duplicate = temp->next;
        temp->next = temp->next->next;
        delete duplicate;
        size--;
      }
      else
      {
        temp = temp->next;
      }
    }
    current = current->next;
  }
}

int dlist::sizeDict()
{
  return size;
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

void dlist::sortedInsert(Word &x)
{
  Node *newNode = createNode(x);
  if (head == NULL)
  {
    head = tail = newNode;
    size++;
  }
  if (x.en <= head->data.en)
  {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    size++;
  }
  // traverse the list to find the correct position
  Node *curr = head;
  while (curr->next != NULL && curr->next->data.en < x.en)
  {
    curr = curr->next;
  }
  // insert the new node
  newNode->next = curr->next;
  if (curr->next != NULL)
  {
    curr->next->prev = newNode;
  }
  curr->next = newNode;
  newNode->prev = curr;
}

void dlist::display()
{
  for (Node *i = head; i != NULL; i = i->next)
  {
    if (i->data.vi.empty())
    {
      cout << "(" << i->data.id << ") " << i->data.en << " - " << "NULL" << " " << endl;
    }

    else
    {

      cout << "(" << i->data.id << ") " << "\t" << i->data.en << " - " << i->data.vi << " " << endl;
    }
  }
  if (head == NULL)
  {
    cout << "Danh sach hien dang rong";
  }
}

void dlist::readFromFile(const string &filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cout << "Khong mo duoc file." << endl;
    return;
  }

  string line;
  while (getline(file, line))
  {
    stringstream ss(line);
    string en, vi;

    if (getline(ss, en, '|') && getline(ss, vi))
    {
      Word w;
      w.en = en;
      w.vi = vi;
      w.id = ++increment;
      addLastWord(w);
    }
  }

  file.close();
}

void dlist::saveToFile(const string &filename)
{
  ofstream file(filename);
  if (!file.is_open())
  {
    cout << "Khong mo duoc file de ghi." << endl;
    return;
  }

  Node *current = head;
  while (current != nullptr)
  {
    file << current->data.en << "|" << current->data.vi << endl;
    current = current->next;
  }

  file.close();
  cout << "Da luu thao tac vao file " << filename << endl;
}

void dlist::wordGame()
{

  if (head == NULL)
  {
    cout << "Danh sach tu dien rong, khong the choi game." << endl;
    return;
  }

  srand(time(0)); // Khởi tạo seed cho random

  int score = 0;
  int questions = 5; // số câu hỏi

  for (int i = 0; i < questions; ++i)
  {
    // Chọn ngẫu nhiên 1 từ
    int index = rand() % sizeDict();
    Node *current = head;
    for (int j = 0; j < index; ++j)
    {
      current = current->next;
    }

    string userAnswer;
    cout << "Tu tieng Anh: " << current->data.en << "\nNghia tieng Viet la gi? ";
    getline(cin, userAnswer);

    if (userAnswer == current->data.vi)
    {
      cout << "Dung!\n";
      score++;
    }
    else
    {
      cout << "Sai. Dap an dung la: " << current->data.vi << "\n";
    }
  }

  cout << "\nDiem cua ban: " << score << "/" << questions << endl;
}

void menu()
{
  cout << "=====Chuong trinh tu dien Anh-Viet=====\n";
}

int main()
{
  Word w;
  Dlist ds;
  int choice;
  while(choice!=0)
  {









  }
  return 0;
}