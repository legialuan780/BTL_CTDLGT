#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
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
  void reverseDisplay();
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
  Node *a = head;
  while (a != NULL)
  {
    if (a->data.en == x.en)
    {
      if (a->prev != NULL)
      {
        cout << endl
             << "Tu truoc cua: " << x.en << " la: " << a->prev->data.id << " " << a->prev->data.en << endl;
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
      head->prev = p; 
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
  else if (head == tail)
  {
    delete head;
    head = tail = NULL;
    size = 0;
    return;
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
    return;
  }

  if (x.en <= head->data.en)
  {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    size++;
    return;
  }

  Node *curr = head;
  while (curr->next != NULL && curr->next->data.en < x.en)
  {
    curr = curr->next;
  }

  newNode->next = curr->next;
  newNode->prev = curr;

  if (curr->next != NULL)
  {
    curr->next->prev = newNode;
  }
  else
  {

    tail = newNode;
  }

  curr->next = newNode;
  size++;
}

void dlist::display()
{
  cout << "+------------------------------------------------------------+" << endl;
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
  cout << "+------------------------------------------------------------+" << endl;
}

void dlist::reverseDisplay()
{
  cout << "+------------------------------------------------------------+" << endl;
  for (Node *i = tail; i != NULL; i = i->prev)
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
  cout << "+------------------------------------------------------------+" << endl;
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
  cout << endl
       << "Da luu thao tac vao file " << filename << endl;
}

void menu()
{
  cout << endl
       << "=====Chuong trinh tu dien Anh-Viet=====" << endl;
  cout << "***Them tu dien***" << endl;
  cout << "1. Nhap bo tu dien co san" << endl;
  cout << "2. Nhap thu cong" << endl;
  cout << "***Cac thao tac voi bo tu dien ap dung Doubly Linked List***" << endl;
  cout << "3. Hien thi tu dien tu dau" << endl;
  cout << "4. Hien thi tu dien tu cuoi" << endl;
  cout << "5. Tim tu bat ky" << endl;
  cout << "6. Sua tu bat ky" << endl;
  cout << "7. Xoa tu dau tien" << endl;
  cout << "8. Xoa tu cuoi cung" << endl;
  cout << "9. Xoa tu bat ky" << endl;
  cout << "10. Xoa tat ca tu trung lap" << endl;
  cout << "11. Xoa toan bo tu dien" << endl;
  cout << "***Ap dung thuat toan Quick Sort va Insertion Sort***" << endl;
  cout << "12. Sap xep tu tang dan theo bang chu cai" << endl;
  cout << "13. Sap xep tu giam dan theo bang chu cai" << endl;
  cout << "14. Them tu moi vao bo tu dien voi dung thu tu" << endl;
  cout << "15. Tro choi on tap tu vung" << endl;
  cout << "0. Thoat chuong trinh" << endl;
}

void menu2()
{
  cout << "1. Nhap bo tu dien co san" << endl;
  cout << "2. Nhap thu cong" << endl;
  cout << "3. Hien thi tu dien" << endl;
  cout << "4. Tim tu bat ky" << endl;
  cout << "5. Sua tu bat ky" << endl;
  cout << "6. Xoa tu dau tien" << endl;
  cout << "7. Xoa tu cuoi cung" << endl;
  cout << "8. Xoa tu bat ky" << endl;
  cout << "9. Xoa tat ca tu trung lap" << endl;
  cout << "10. Xoa toan bo tu dien" << endl;
  cout << "11. Sap xep tu tang dan theo bang chu cai" << endl;
  cout << "12. Sap xep tu giam dan theo bang chu cai" << endl;
  cout << "13. Them tu moi vao bo tu dien voi dung thu tu" << endl;
  cout << "14. Tro choi on tap tu vung" << endl;
  cout << "0. Thoat chuong trinh" << endl;
}

typedef struct user
{
  int checkLoginName(char *username);
  int checkPass(char *password);
  void hidePass(char *password);
  void saveAcc(char *username, char *password);
  int checkLogin(char *username, char *password);
  int reg();
  int login();
  void loginMenu();
} User;

int user::checkLoginName(char *username)
{
  if (strlen(username) >= 5)
  {
    return 1;
  }
  return 0;
}

int user::checkPass(char *password)
{
  int len = strlen(password);
  int coHoa = 0, coThuong = 0, coSo = 0;

  if (len < 8)
  {
    return 0;
  }

  for (int i = 0; i < len; i++)
  {
    if (password[i] >= 'A' && password[i] <= 'Z')
    {
      coHoa = 1;
    }
    else if (password[i] >= 'a' && password[i] <= 'z')
    {
      coThuong = 1;
    }
    else if (password[i] >= '0' && password[i] <= '9')
    {
      coSo = 1;
    }
  }

  return (coHoa && coThuong && coSo);
}

void user::hidePass(char *password)
{
  int i = 0;
  char ch;

  while ((ch = getch()) != '\r' && i < 49)
  { // Enter = '\r', max 49 ky tu
    if (ch == '\b' && i > 0)
    { // Backspace
      printf("\b \b");
      i--;
    }
    else if (ch != '\b')
    {
      password[i] = ch;
      printf("*");
      i++;
    }
  }
  password[i] = '\0';
  printf("\n");
}

void user::saveAcc(char *username, char *password)
{
  FILE *file = fopen("accounts.txt", "a");
  if (file != NULL)
  {
    fprintf(file, "%s|%s\n", username, password);
    fclose(file);
    printf("Tai khoan da duoc luu thanh cong!\n");
  }
  else
  {
    printf("Loi: Khong the luu tai khoan.\n");
  }
}

int user::checkLogin(char *username, char *password)
{
  FILE *file = fopen("accounts.txt", "r");
  char line[200];
  char fileUsername[50], filePassword[50];

  if (file == NULL)
  {
    printf("Chua co tai khoan nao duoc tao.\n");
    return 0;
  }

  while (fgets(line, sizeof(line), file))
  {
    // Loai bo ky tu xuong dong
    line[strcspn(line, "\n")] = 0;

    // Tach username va password
    char *token = strtok(line, "|");
    if (token != NULL)
    {
      strcpy(fileUsername, token);
      token = strtok(NULL, "|");
      if (token != NULL)
      {
        strcpy(filePassword, token);

        // Kiem tra khop
        if (strcmp(username, fileUsername) == 0 &&
            strcmp(password, filePassword) == 0)
        {
          fclose(file);
          return 1;
        }
      }
    }
  }

  fclose(file);
  return 0;
}

int user::reg()
{
  char username[50], password[50], confirmPassword[50];

  printf("=== DANG KY TAI KHOAN ===\n");

  // Nhap ten dang nhap
  do
  {
    printf("Nhap ten dang nhap (it nhat 5 ky tu): ");
    scanf("%s", username);

    if (!checkLoginName(username))
    {
      printf("Ten dang nhap phai co it nhat 5 ky tu!\n");
    }
  } while (!checkLoginName(username));

  // Nhap mat khau
  do
  {
    printf("Nhap mat khau (it nhat 8 ky tu, co chu hoa, chu thuong va so): ");
    hidePass(password);

    if (!checkPass(password))
    {
      printf("Mat khau khong hop le! Phai co it nhat 8 ky tu, chu hoa, chu thuong va so.\n");
    }
  } while (!checkPass(password));

  // Xac nhan mat khau
  do
  {
    printf("Xac nhan lai mat khau: ");
    hidePass(confirmPassword);

    if (strcmp(password, confirmPassword) != 0)
    {
      printf("Mat khau xac nhan khong khop!\n");
    }
  } while (strcmp(password, confirmPassword) != 0);

  saveAcc(username, password);
  return 1;
}

int user::login()
{
  char username[50], password[50];
  int soLanThu = 0;

  printf("=== DANG NHAP ===\n");

  while (soLanThu < 3)
  {
    printf("Ten dang nhap: ");
    scanf("%s", username);

    printf("Mat khau: ");
    hidePass(password);

    if (checkLogin(username, password))
    {
      printf("Dang nhap thanh cong! Chao mung %s!\n", username);
      return 1;
    }
    else
    {
      soLanThu++;
      printf("Sai ten dang nhap hoac mat khau! Con lai %d lan thu.\n", 3 - soLanThu);
    }
  }

  printf("Da het so lan thu. Chuong trinh se thoat.\n");
  return 0;
}

// Them ham menu dang nhap
void user::loginMenu()
{
  int choice;

  while (1)
  {
    printf("=== DANG NHAP UNG DUNG TU DIEN ===\n");
    printf("1. Dang ky tai khoan moi\n");
    printf("2. Dang nhap\n");
    printf("0. Thoat chuong trinh.\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      reg();
      // Sau khi dang ky, quay lai menu
      printf("\nNhan Enter de tiep tuc...\n");
      getchar(); // doc ky tu newline con lai
      getchar(); // cho nguoi dung nhan Enter
      break;
    case 2:
      if (login())
      {
        return; // Dang nhap thanh cong, thoat khoi menu
      }
      else
      {
        exit(1); // Het so lan thu, thoat chuong trinh
      }
      break;
    case 0:
      printf("Da thoat chuong trinh\n");
      exit(1);
    default:
      printf("Lua chon khong hop le!\n\n");
      break;
    }
  }
}

void dlist::wordGame()
{
  if (head == NULL)
  {
    cout << "Danh sach tu dien rong, khong the choi game." << endl;
    return;
  }

  if (sizeDict() < 4)
  {
    cout << "Tu dien can it nhat 4 tu de choi game trac nghiem." << endl;
    return;
  }

  srand(time(0)); // Khởi tạo seed cho random

  int score = 0;
  int questions = 5; // số câu hỏi

  for (int i = 0; i < questions; ++i)
  {
    cout << "\n=== Cau hoi " << (i + 1) << "/" << questions << " ===" << endl;

    // Chọn ngẫu nhiên 1 từ làm đáp án đúng
    int correctIndex = rand() % sizeDict();
    Node *correctNode = head;
    for (int j = 0; j < correctIndex; ++j)
    {
      correctNode = correctNode->next;
    }

    cout << "Tu tieng Anh: " << correctNode->data.en << endl;
    cout << "Chon nghia dung:" << endl;

    // Tạo mảng lưu 4 đáp án
    string answers[4];
    int correctPos = rand() % 4; // Vị trí của đáp án đúng (0-3)

    // Đặt đáp án đúng vào vị trí ngẫu nhiên
    answers[correctPos] = correctNode->data.vi;

    // Tạo 3 đáp án sai
    vector<string> wrongAnswers;
    Node *temp = head;
    while (temp != NULL && wrongAnswers.size() < 3)
    {
      if (temp->data.vi != correctNode->data.vi && temp->data.vi != "")
      {
        // Kiểm tra xem đáp án này đã có chưa
        bool exists = false;
        for (const string &ans : wrongAnswers)
        {
          if (ans == temp->data.vi)
          {
            exists = true;
            break;
          }
        }
        if (!exists)
        {
          wrongAnswers.push_back(temp->data.vi);
        }
      }
      temp = temp->next;
    }

    // Nếu không đủ đáp án sai, tạo thêm đáp án giả
    while (wrongAnswers.size() < 3)
    {
      wrongAnswers.push_back("Dap an gia " + to_string(wrongAnswers.size() + 1));
    }

    // Điền các đáp án sai vào các vị trí còn lại
    int wrongIndex = 0;
    for (int k = 0; k < 4; k++)
    {
      if (k != correctPos)
      {
        answers[k] = wrongAnswers[wrongIndex++];
      }
    }

    // Hiển thị các lựa chọn
    char options[] = {'A', 'B', 'C', 'D'};
    for (int k = 0; k < 4; k++)
    {
      cout << options[k] << ". " << answers[k] << endl;
    }

    // Nhận đáp án từ người chơi
    char userChoice;
    cout << "Nhap lua chon (A/B/C/D): ";
    cin >> userChoice;

    // Lặp cho đến khi nhận được đáp án hợp lệ
    bool validChoice = false;
    while (!validChoice)
    {
      // Chuyển về chữ hoa nếu là chữ thường
      if (userChoice >= 'a' && userChoice <= 'd')
      {
        userChoice = userChoice - 'a' + 'A';
      }

      // Check if input is valid
      if (userChoice >= 'A' && userChoice <= 'D')
      {
        validChoice = true;
      }
      else
      {
        cout << "Lua chon khong hop le! Vui long nhap lai (A/B/C/D): ";
        cin >> userChoice;
      }
    }

    // Kiểm tra đáp án
    char correctChoice = options[correctPos];
    if (userChoice == correctChoice)
    {
      cout << "Dung! +1 diem" << endl;
      score++;
    }
    else
    {
      cout << "Sai! Dap an dung la: " << correctChoice << ". " << correctNode->data.vi << endl;
    }
  }

  cout << "\n=== KET QUA GAME ===" << endl;
  cout << "Diem cua ban: " << score << "/" << questions << endl;

  if (score == questions)
  {
    cout << "Xuat sac! Ban da tra loi dung tat ca!" << endl;
  }
  else if (score >= questions * 0.8)
  {
    cout << "Rat tot! Ban da lam duoc " << (score * 100 / questions) << "%!" << endl;
  }
  else if (score >= questions * 0.6)
  {
    cout << "Kha on! Hay co gang hon nhe!" << endl;
  }
  else
  {
    cout << "Can co gang them! Hay hoc them tu vung nhe!" << endl;
  }
}

void runProgram()
{
  menu();
  Word w;
  Dlist ds;
  int choice1 = -1;
  string findWord;
  string editWord;
  string removeWord;
  Word newWord;
  Word sortedWord;

  while (choice1 != 0)
  {
    menu();
    cout << endl
         << "Moi nhap lua chon: " << endl;
    cin >> choice1;
    cin.ignore();
    Node *lastNode = ds.getlastNode();
    switch (choice1)
    {
    case 1:
      ds.readFromFile("data.txt");
      cout << endl
           << "---Nhap file thanh cong---";
      cout << endl
           << "So luong tu hien tai: " << ds.sizeDict();
      break;
    case 2:
      cout << endl
           << "---Moi ban nhap tu dien---(Nhan Enter de nhap)" << endl;
      inputWord(w);
      ds.addLastWord(w);
      ds.saveToFile("data2.txt");
      cout << endl
           << "So luong tu hien tai: " << ds.sizeDict();
      break;
    case 3:
      ds.display();
      cout << endl
           << "So luong tu hien tai: " << ds.sizeDict();
      break;
    case 4:
      ds.reverseDisplay();
      cout << endl
           << "So luong tu hien tai: " << ds.sizeDict();
      break;
    case 5:
      cout << endl
           << "---Nhap tu can tim: " << endl;
      getline(cin, findWord);
      ds.search(findWord);
      break;
    case 6:
      cout << endl
           << "---Nhap tu can sua: " << endl;
      getline(cin, editWord);
      ds.search(editWord);

      cout << endl
           << "---Nhap tu moi--(Nhan Enter de nhap)" << endl;
      inputWord(newWord);
      ds.editWord(editWord, newWord);
      ds.saveToFile("data2.txt");
      break;
    case 7:
      ds.removeFirstWord();
      cout << endl
           << "Da xoa tu dau tien";
      ds.saveToFile("data2.txt");
      cout << endl
           << "So luong tu hien tai: " << ds.sizeDict();
      break;
    case 8:
      ds.removeLastWord();
      cout << endl
           << "Da xoa tu cuoi cung";
      ds.saveToFile("data2.txt");
      cout << endl
           << "So luong tu hien tai: " << ds.sizeDict();
      break;
    case 9:
      cout << endl
           << "---Nhap tu can xoa--" << endl;
      getline(cin, removeWord);
      ds.removeWord(removeWord);
      cout << endl
           << "Da xoa tu " << removeWord;
      ds.saveToFile("data2.txt");
      cout << endl
           << "So luong tu hien tai: " << ds.sizeDict();
      break;
    case 10:
      ds.removeDuplicate();
      cout << endl
           << "Da xoa tat ca tu trung lap";
      ds.saveToFile("data2.txt");
      cout << endl
           << "So luong tu hien tai: " << ds.sizeDict();
      break;
    case 11:
      ds.removeAllWords();
      cout << endl
           << "Da xoa toan bo tu dien";
      ds.saveToFile("data2.txt");
      cout << endl
           << "So luong tu hien tai: " << ds.sizeDict();
      break;
    case 12:
      ds.quickSort(ds.head, lastNode);
      cout << endl
           << "Tu dien da duoc sap xep tang dan";
      ds.saveToFile("data2.txt");
      break;
    case 13:
      ds.quickSort2(ds.head, lastNode);
      cout << endl
           << "Tu dien da duoc sap xep giam dan";
      ds.saveToFile("data2.txt");
      break;
    case 14:
      cout << endl
           << "---Nhap tu moi---(Nhan Enter de nhap)" << endl;
      inputWord(sortedWord);
      ds.sortedInsert(sortedWord);
      ds.saveToFile("data2.txt");
      cout << endl
           << "Da them tu voi thu tu dung";
      ds.prevWord(sortedWord);
      cout << "Tu da them: " << sortedWord.id << " " << sortedWord.en << " " << sortedWord.vi;
      cout << endl
           << "So luong tu hien tai: " << ds.sizeDict();
      break;
    case 15:
      ds.wordGame();
    case 0:
      choice1 = 0;
      cout << "Da thoat chuong trinh";
      break;
    }
  }
}

int main()
{
  // User s;
  // s.loginMenu();
  runProgram();
}
