#include <iostream>
#include <stdio.h>
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
  void addLastWord(Word &x); // them rang buoc khi trung tu
  void search(string word);
  void display();
  void prevWord(Word &x);
  int sizeDict();
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
  // insert value in sorted order
  void sortID();
  void sortedInsert(Word &x);
  
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

void dlist::removeFirstWord(){
	if (head == NULL){
		printf("Danh sach rong, khong can xoa."); return;
	}
	
	Node *a = head;
	head = head->next;
	
	if (head) head->prev = NULL;	//k phai node cuoi 
	else tail = NULL;	//truong hop node cuoi ds 
  
	delete a;
	size--;
}

void dlist::removeLastWord(){
    if (head == NULL){
		printf("Danh sach rong, khong can xoa.\n"); return;
	}
    
    printf("Tu ke cuoi: %s\n", tail->prev); 
    Node* temp = tail;
    tail = tail->prev;
    
    if (tail) tail->next = NULL;	//k phai node cuoi 
    else head = NULL;	//xoa pt cuoi
    
    delete temp;
    size--;
    
    printf("Da xoa phan tu cuoi.\n"); 
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
  printf("Da xoa toan bo ds.\n");
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
        if(i->data.vi.empty())
    {
      cout << "(" << i->data.id << ") " << i->data.en << " - " << "NULL" << " " << endl;
    }
    else{

    
    cout << "(" << i->data.id << ") " << i->data.en << " - " << i->data.vi << " " << endl;
    }

  }
  if (head == NULL)
  {
    cout << "Khong co phan tu";
  }
  
}

// =================== FILE =======================

//sort ID
void dlist::sortID(){
    if (head == NULL || head->next == NULL) return;
    
    bool swapped;
    do{
        swapped = false;
        Node *current = head;
        
        while (current->next != NULL){
            if (current->data.id > current->next->data.id){
                swap(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
    } while(swapped);
} 

//luu file
void saveDictionaryToFile_C(Dlist *ds, const char *filename){
	ds->sortID(); 
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    
    Node *curr = ds->head;
    while (curr != NULL){
        fprintf(file, "%d\t%s\t%s\n", 
                curr->data.id, 
                curr->data.en.c_str(), 
                curr->data.vi.c_str());
        curr = curr->next;
    }
    
    fclose(file);
    printf("Da luu tu dien vao file %s\n", filename);
}

//doc file
void loadDictionaryFromFile_C(Dlist *ds, const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file de doc!\n");
        return;
    }
    
    //xoa ds hien tai(neu co)
    ds->removeAllWords();
    
    Word temp;
    char line[256];
    char en[100], vi[100];
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d\t%99[^\t]\t%99[^\n]", &temp.id, en, vi) == 3) {
            temp.en = en;
            temp.vi = vi;
            
            //update increment(neu can)
            if (temp.id > increment){
                increment = temp.id;
            }
            
            ds->addLastWord(temp);
        }
    }
    fclose(file);
    printf("Da doc tu dien tu file %s\n", filename);
}

void menu()
{
  cout << "=====Chuong trinh tu dien Anh-Viet=====\n";
  cout << "1. Them tu\n";
  cout << "2. Tim tu\n";
  cout << "3. Sua tu\n";
  cout << "4. Xoa tu\n";
  cout << "5. Hien thi danh sach tu dien\n";
  cout << "6. Sap xep tu tang dan\n";
  cout << "7. Sap xep tu giam dan\n";
  cout << "8. Xem tu truoc\n";
  cout << "0. Thoat\n";
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
    ds.addLastWord(w);
  }

  cout << "Danh sach tu dien:\n";
  Node *lastNode = ds.getlastNode();
  cout << "lastNode: " << lastNode->data.en << endl;
  ds.quickSort(ds.head, lastNode);
  inputWord(w);
  ds.sortedInsert(w);
  cout << "Danh sach sau khi them tu moi:\n";
  ds.display();
  ds.removeWord("aple");
  cout << "Danh sach sau khi xoa tu :\n";
  ds.display();
  saveDictionaryToFile_C(&ds, "dictionary_c.txt");
  Dlist ds2;
  loadDictionaryFromFile_C(&ds2, "dictionary_c.txt");
  cout << "Danh sach doc tu file (C):\n";
  ds2.display();
  // cout << "Nhap tu can sua: ";
  // string word;
  // getline(cin, word);
  // Word newWord;
  // inputWord(newWord);
  // ds.editWord(word, newWord);
  // ds.display();
  return 0;
}
