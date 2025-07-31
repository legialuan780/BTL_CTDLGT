#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

#include <stdio.h>
#include <string.h>
#include <conio.h>

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

typedef struct user{
	int checkLoginName(char *username);
	int checkPass(char *password);
	void hidePass(char *password);
	void saveAcc(char *username, char *password);
	int checkLogin(char *username, char *password);
	int reg();
	int login();
	void loginMenu();
}User;

int user::checkLoginName(char *username){
    if (strlen(username) >= 5) {
        return 1;
    }
    return 0;
}

int user::checkPass(char *password){
    int len = strlen(password);
    int coHoa = 0, coThuong = 0, coSo = 0;
    
    if (len < 8) {
        return 0;
    }
    
    for (int i = 0; i < len; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z'){
            coHoa = 1;
        }
        else if (password[i] >= 'a' && password[i] <= 'z'){
            coThuong = 1;
        }
        else if (password[i] >= '0' && password[i] <= '9'){
            coSo = 1;
        }
    }
    
    return (coHoa && coThuong && coSo);
}

void user::hidePass(char *password){
    int i = 0;
    char ch;
    
    while ((ch = getch()) != '\r' && i < 49) { //Enter = '\r', max 49 ky tu
        if (ch == '\b' && i > 0) { // Backspace
            printf("\b \b");
            i--;
        }
        else if (ch != '\b'){
            password[i] = ch;
            printf("*");
            i++;
        }
    }
    password[i] = '\0';
    printf("\n");
}

void user::saveAcc(char *username, char *password){
    FILE *file = fopen("accounts.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s|%s\n", username, password);
        fclose(file);
        printf("Tai khoan da duoc luu thanh cong!\n");
    }
    else {
        printf("Loi: Khong the luu tai khoan.\n");
    }
}

int user::checkLogin(char *username, char *password){
    FILE *file = fopen("accounts.txt", "r");
    char line[200];
    char fileUsername[50], filePassword[50];
    
    if (file == NULL) {
        printf("Chua co tai khoan nao duoc tao.\n");
        return 0;
    }
    
    while (fgets(line, sizeof(line), file)) {
        //Loai bo ky tu xuong dong
        line[strcspn(line, "\n")] = 0;
        
        // Tach username va password
        char *token = strtok(line, "|");
        if (token != NULL) {
            strcpy(fileUsername, token);
            token = strtok(NULL, "|");
            if (token != NULL) {
                strcpy(filePassword, token);
                
                //Kiem tra khop
                if (strcmp(username, fileUsername) == 0 && 
                    strcmp(password, filePassword) == 0) {
                    fclose(file);
                    return 1;
                }
            }
        }
    }
    
    fclose(file);
    return 0;
}

int user::reg(){
    char username[50], password[50], confirmPassword[50];
    
    printf("=== DANG KY TAI KHOAN ===\n");
    
    //Nhap ten dang nhap
    do {
        printf("Nhap ten dang nhap (it nhat 5 ky tu): ");
        scanf("%s", username);
        
        if (!checkLoginName(username)) {
            printf("Ten dang nhap phai co it nhat 5 ky tu!\n");
        }
    } while (!checkLoginName(username));
    
    //Nhap mat khau
    do{
        printf("Nhap mat khau (it nhat 8 ky tu, co chu hoa, chu thuong va so): ");
        hidePass(password);
        
        if (!checkPass(password)) {
            printf("Mat khau khong hop le! Phai co it nhat 8 ky tu, chu hoa, chu thuong va so.\n");
        }
    } while (!checkPass(password));
    
    //Xac nhan mat khau
    do {
        printf("Xac nhan lai mat khau: ");
        hidePass(confirmPassword);
        
        if (strcmp(password, confirmPassword) != 0){
            printf("Mat khau xac nhan khong khop!\n");
        }
    } while (strcmp(password, confirmPassword) != 0);
    
    saveAcc(username, password);
    return 1;
}

int user::login(){
    char username[50], password[50];
    int soLanThu = 0;
    
    printf("=== DANG NHAP ===\n");
    
    while (soLanThu < 3) {
        printf("Ten dang nhap: ");
        scanf("%s", username);
        
        printf("Mat khau: ");
        hidePass(password);
        
        if (checkLogin(username, password)) {
            printf("Dang nhap thanh cong! Chao mung %s!\n", username);
            return 1;
        }
        else {
            soLanThu++;
            printf("Sai ten dang nhap hoac mat khau! Con lai %d lan thu.\n", 3 - soLanThu);
        }
    }
    
    printf("Da het so lan thu. Chuong trinh se thoat.\n");
    return 0;
}

//Them ham menu dang nhap
void user::loginMenu(){
    int choice;
    
    while (1) {
        printf("=== HE THONG DANG NHAP UNG DUNG TU DIEN ===\n");
        printf("1. Dang ky tai khoan moi\n");
        printf("2. Dang nhap\n");
        printf("0. Thoat chuong trinh.\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        
        switch (choice){
            case 1:
                reg();
                // Sau khi dang ky, quay lai menu
                printf("\nNhan Enter de tiep tuc...\n");
                getchar(); // doc ky tu newline con lai
                getchar(); // cho nguoi dung nhan Enter
                break;
            case 2:
                if (login()){
                    return; // Dang nhap thanh cong, thoat khoi menu
                }
                else{
                    exit(1); // Het so lan thu, thoat chuong trinh
                }
                break;
            case 0:
            	printf("Dang thoat chuong trinh...\n");
            	exit(1);
            default:
                printf("Lua chon khong hop le!\n\n");
                break;
        }
    }
}

int main()
{
  User s;
  s.loginMenu();
  Word w;
  Dlist ds;
  // cout << "Nhap so luong tu: ";
  // int n;
  // cin >> n;

  // cout << "Nhap lan luot tu tieng Anh va nghia tieng Viet:\n";
  // for (int i = 0; i < n; i++)
  // {
  //   inputWord(w);
  //   ds.addLastWord(w);
  // }
  ds.readFromFile("data.txt");

  cout << "Danh sach tu dien:\n";
  Node *lastNode = ds.getlastNode();
  cout << "lastNode: " << lastNode->data.en << endl;
  ds.quickSort(ds.head, lastNode);
  ds.saveToFile("data2.txt");
  cout << "Nhap tu de tim tu truoc: " << endl;
  // inputWord(w);
  // ds.sortedInsert(w);
  cout << "Danh sach sau khi them tu moi:\n";
  ds.display();
  ds.wordGame();
  // ds.removeAllWords();
  // cout << "Danh sach sau khi xoa  :\n";
  // ds.prevWord(w);
  // ds.display();
  // // cout << "Nhap tu can sua: ";
  // string word;
  // getline(cin, word);
  // Word newWord;
  // inputWord(newWord);
  // ds.editWord(word, newWord);
  // ds.display();
  return 0;
}
