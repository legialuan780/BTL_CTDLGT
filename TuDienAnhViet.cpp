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

    if (sizeDict() < 4)
    {
        cout << "Tu dien can it nhat 4 tu de choi game trac nghiem." << endl;
        return;
    }

    srand(time(0)); //khoi tao seed rnd 

    int score = 0;
    int questions = 5; //so cau hoi 

    for (int i = 0; i < questions; ++i)
    {
        cout << "\n=== Cau hoi " << (i + 1) << "/" << questions << " ===" << endl;
        
        //chon ngau nhien 1 tu lm da an dung
        int correctIndex = rand() % sizeDict();
        Node *correctNode = head;
        for (int j = 0; j < correctIndex; ++j)
        {
            correctNode = correctNode->next;
        }

        cout << "Tu tieng Anh: " << correctNode->data.en << endl;
        cout << "Chon nghia dung:" << endl;

        //tao mang luu 4 dap an
        string answers[4];
        int correctPos = rand() % 4; //vi tri dap an dung
        
        //dat dap an dung vao vi tri ngau nhien
        answers[correctPos] = correctNode->data.vi;

        //tao dap an sai
        vector<string> wrongAnswers;
        Node *temp = head;
        while (temp != NULL && wrongAnswers.size() < 3)
        {
            if (temp->data.vi != correctNode->data.vi && temp->data.vi != "")
            {
                //check vi tri dap an co ch
                bool exists = false;
                for (const string& ans : wrongAnswers)
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

        //neu dap an sai k du, tao them dap an gia
        while (wrongAnswers.size() < 3)
        {
            wrongAnswers.push_back("Dap an gia " + to_string(wrongAnswers.size() + 1));
        }

        //dien cac dap an sai vao vi tri con lai
        int wrongIndex = 0;
        for (int k = 0; k < 4; k++)
        {
            if (k != correctPos)
            {
                answers[k] = wrongAnswers[wrongIndex++];
            }
        }

        //hien thi cac lua chon
        char options[] = {'A', 'B', 'C', 'D'};
        for (int k = 0; k < 4; k++)
        {
            cout << options[k] << ". " << answers[k] << endl;
        }

        //nhan dap an tu ng choi
        char userChoice;
        cout << "Nhap lua chon (A/B/C/D): ";
        cin >> userChoice;
        
        //chuyen ve chu hoa neu la chu thg
        if (userChoice >= 'a' && userChoice <= 'd')
        {
            userChoice = userChoice - 'a' + 'A';
        }

        //check dap an
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

void displayMenu()
{
    printf("\n\t+------------------------------------------------------------+\n");
    printf("\t|              CHUONG TRINH TU DIEN ANH - VIET               |\n");
    printf("\t+------------------------------------------------------------+\n");
    printf("\t|  1.  Them tu moi                                           |\n");
    printf("\t|  2.  Hien thi danh sach tu                                 |\n");
    printf("\t|  3.  Tim kiem tu                                           |\n");
    printf("\t|  4.  Sua tu                                                |\n");
    printf("\t|  5.  Xoa tu dau tien                                       |\n");
    printf("\t|  6.  Xoa tu cuoi cung                                      |\n");
    printf("\t|  7.  Xoa tu theo ten                                       |\n");
    printf("\t|  8.  Xoa tat ca tu                                         |\n");
    printf("\t|  9.  Xoa tu trung lap                                      |\n");
    printf("\t| 10.  Sap xep tang dan (A-Z)                                |\n");
    printf("\t| 11.  Sap xep giam dan (Z-A)                                |\n");
    printf("\t| 12.  Tim tu truoc do                                       |\n");
    printf("\t| 13.  Hien thi so luong tu                                  |\n");
    printf("\t| 14.  Choi game trac nghiem                                 |\n");
    printf("\t| 15.  Luu vao file                                          |\n");
    printf("\t|  0.  Thoat chuong trinh                                    |\n");
    printf("\t+------------------------------------------------------------+\n");
    printf("\n\t---> Nhap lua chon cua ban: ");
}

// Ham xu ly menu chinh
void mainMenu(Dlist &ds)
{
    Word w;
    int choice;
    string searchWord, editWord, removeWord;
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: {
                printf("\n--- THEM TU MOI ---\n");
                inputWord(w);
                ds.addLastWord(w);
                printf("Da them tu thanh cong!\n");
                break;
            }
            
            case 2: {
                printf("\n--- DANH SACH TU DIEN ---\n");
                ds.display();
                break;
            }
            
            case 3: {
                printf("\n--- TIM KIEM TU ---\n");
                cin.ignore();
                cout << "Nhap tu can tim: ";
                getline(cin, searchWord);
                ds.search(searchWord);
                break;
            }
            
            case 4: {
                printf("\n--- SUA TU ---\n");
                cin.ignore();
                cout << "Nhap tu can sua: ";
                getline(cin, editWord);
                printf("Nhap thong tin tu moi:\n");
                inputWord(w);
                ds.editWord(editWord, w);
                break;
            }
            
            case 5: {
                printf("\n--- XOA TU DAU TIEN ---\n");
                ds.removeFirstWord();
                printf("Da xoa tu dau tien!\n");
                break;
            }
            
            case 6: {
                printf("\n--- XOA TU CUOI CUNG ---\n");
                ds.removeLastWord();
                printf("Da xoa tu cuoi cung!\n");
                break;
            }
            
            case 7: {
                printf("\n--- XOA TU THEO TEN ---\n");
                cin.ignore();
                cout << "Nhap tu can xoa: ";
                getline(cin, removeWord);
                ds.removeWord(removeWord);
                break;
            }
            
            case 8: {
                printf("\n--- XOA TAT CA TU ---\n");
                printf("Ban co chac chan muon xoa tat ca tu? (y/n): ");
                char confirm;
                scanf(" %c", &confirm);
                if(confirm == 'y' || confirm == 'Y') {
                    ds.removeAllWords();
                    printf("Da xoa tat ca tu!\n");
                } else {
                    printf("Huy bo thao tac xoa!\n");
                }
                break;
            }
            
            case 9: {
                printf("\n--- XOA TU TRUNG LAP ---\n");
                ds.removeDuplicate();
                printf("Da xoa cac tu trung lap!\n");
                break;
            }
            
            case 10: {
                printf("\n--- SAP XEP TANG DAN (A-Z) ---\n");
                Node *lastNode = ds.getlastNode();
                if(lastNode != NULL) {
                    ds.quickSort(ds.head, lastNode);
                    printf("Da sap xep tu dien theo thu tu tang dan!\n");
                } else {
                    printf("Danh sach rong, khong the sap xep!\n");
                }
                break;
            }
            
            case 11: {
                printf("\n--- SAP XEP GIAM DAN (Z-A) ---\n");
                Node *lastNode = ds.getlastNode();
                if(lastNode != NULL) {
                    ds.quickSort2(ds.head, lastNode);
                    printf("Da sap xep tu dien theo thu tu giam dan!\n");
                } else {
                    printf("Danh sach rong, khong the sap xep!\n");
                }
                break;
            }
            
            case 12: {
                printf("\n--- TIM TU TRUOC DO ---\n");
                cin.ignore();
                ds.prevWord(w);
                break;
            }
            
            case 13: {
                printf("\n--- SO LUONG TU ---\n");
                printf("So luong tu trong tu dien: %d tu\n", ds.sizeDict());
                break;
            }
            
            case 14: {
                printf("\n--- GAME TRAC NGHIEM ---\n");
                ds.wordGame();
                break;
            }
            
            case 15: {
                printf("\n--- LUU VAO FILE ---\n");
                ds.saveToFile("data.txt");
                break;
            }
            
            case 0: {
                printf("\n--- THOAT CHUONG TRINH ---\n");
                printf("Ban co muon luu du lieu truoc khi thoat? (y/n): ");
                char saveChoice;
                scanf(" %c", &saveChoice);
                if(saveChoice == 'y' || saveChoice == 'Y') {
                    ds.saveToFile("data.txt");
                }
                printf("Cam on ban da su dung chuong trinh tu dien!\n");
                break;
            }
            
            default: {
                printf("\nLua chon khong hop le! Vui long nhap lai.\n");
                break;
            }
        }
        
        // Tam dung de nguoi dung xem ket qua
        if(choice != 0) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
            getchar();
        }
        
    } while(choice != 0);
}

int main()
{
    User s;
//    s.loginMenu();
    
    Dlist ds;
    
    // Doc du lieu tu file khi khoi dong
    ds.readFromFile("data.txt");
    printf("_Chuong trinh da co san danh sach mot so tu vung. Vui long chon (2) de xem._\n");
    mainMenu(ds);
    
    return 0;
}
