#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;

template<typename t>
class notepad
{
   struct node {
       t data;
       node* next;
       node* prev;
       node(t val = t(), node* nptr = nullptr, node* pptr = nullptr)
           : data(val), next(nptr), prev(pptr) {}
   };

   node* head, * tail, * cursor;
   int size;

public:
   notepad() {
       head = new node();  // dummy head 
       tail = new node();   
       head->next = tail;
       tail->prev = head;
       cursor = tail;
       size = 0;
   }


   void print() {
       system("cls");
       node* temp = head->next;
       cout << "\r";
       while (temp != tail) {
           if (temp == cursor) {
               cout << "|";
           }
           cout << temp->data;
           temp = temp->next;
       }
       if (cursor == tail) {
           cout << "|";
       }
       cout << "\t\t  cursor position: " << size;  // show cursor position

   }

   ~notepad() {
       node* curr = head;
       node* next;
       while (curr != nullptr) {
           next = curr->next;
           delete curr;
           curr = next;
       }
   }

   void movecursorleft() {
       if (cursor->prev != head) {
           cursor = cursor->prev;
           size--;
       }
   }

   void movecursorright() {
       if (cursor->next != nullptr && cursor != tail) {
           cursor = cursor->next;
           size++;
       }
   }

   void deletebeforecursor() {
       if (cursor->prev == head) {  // no characters before the cursor (khali list)
           return;
       }
       node* temp = cursor->prev;
       temp->prev->next = cursor;
       cursor->prev = temp->prev;
       delete temp;
       size--;
   }

   void insertbeforecursor(t v) {
       node* newnode = new node(v, cursor, cursor->prev);
       cursor->prev->next = newnode;
       cursor->prev = newnode;
       size++;
   }

   void writetofile(const string& filename) {
       ofstream outfile(filename);
       if (!outfile) {
           cerr << "error: unable to open file for writing.\n";
           return;
       }

       node* temp = head;
       while (temp != nullptr) {
           outfile << temp->data;
           temp = temp->next;
       }

       outfile.close();
   }
   void writefromfile(const string& filename) {
       ifstream infile(filename);
       if (!infile) {
           cerr << "error: file could not be opened!" << endl;
       }
       char ch;
       while (infile.get(ch)) {
           insertbeforecursor(ch);
       }
       infile.close();
   }

};

int main()
{
   notepad<char> n1;
   n1.print();

   while (true) {
       char ch = _getch();

       if (ch == 27)   // esc key
           break;

       if (ch == 13) 
           n1.insertbeforecursor('\n');    // enter key

       if (ch == '\b' || ch == 127)   // backspace key
           n1.deletebeforecursor();
       
       else if (ch == -32) { // arrow keys
           ch = _getch();

           if (ch == 75)   // left arrow key
               n1.movecursorleft();
           
           else if (ch == 77)   // right arrow key
               n1.movecursorright();
           
       }
       else if (ch >= 32 && ch <= 126)   // printable characters
           n1.insertbeforecursor(ch);
       
       else if (ch == 19)      // ctrl + s
           n1.writetofile("notes.txt");
       
       else if (ch == 15)      //ctrl + o
           n1.writefromfile("notes.txt");  
      
       n1.print();
   }

   n1.print();
   cout << endl;

   return 0;
}
