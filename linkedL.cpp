#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

//what to do:
//things not working as expected with !head
//get display all working
//get nodeExists working

//flow:
//enter an event,
//return a pointer
//take pointer as arg into main Ll
//set event->next to the arg

struct Event{
   char * name;
   char * season;
   char * desc;
   char * bring;
   Event * advance;
};

struct node{
    node * next;
    char * activity;
    Event * chain;
};

bool again();
void read(char[]);
void eventAppend(Event *, Event *);
bool nodeExists(node *, char[]);
int clean(node * &);
int cleanChain(Event * &);
int displayChain(Event * );

Event * createEvent(){
   char tempN[500];
   cout << ">>Enter activity name!" << "\n\n";
   read(tempN);
   Event * ptr = new Event;
   ptr->name= new char(strlen(tempN));
   strcpy(ptr->name,tempN);
   ptr->advance = NULL;

   return ptr;
};
void read(char input[]){
   cin.get(input,500,'\n');
   cin.ignore(500,'\n');
};

bool nodeExists(node * head, char match[]){
  cerr << "---activ: " << head->activity << '\n';
  cerr << "---match: " << match << '\n';
  if(head && strcmp(head->activity,match) == 0)
    return 1;
  else if(head->next)
    nodeExists(head->next,match);
  return 0;
}

void appendNode(node * head, Event * events){
  char type[500];
  cout << ">>What kind of activity is this?" << "\n\n";
  read(type);
  node * current = head;
  node * temp = head;
  if(nodeExists(current,type)){
    while(strcmp(current->activity,type)==0){
      current = current->next;
    }
    if(!head->chain){
      head->chain = events;
    }else{
      eventAppend(head->chain, events);
    }
  }
  else{
    while(current){
      temp = current;
      current = current->next;
    }
    current = new node;
    current->next = NULL;
    if(!current->chain)
      current->chain = events;
    else{
      eventAppend(current->chain,events);
    }
    current->activity = new char[strlen(type)];
    strcpy(current->activity, type);
    temp->next = current;
  }
}

void eventAppend(Event * head, Event * append){
    Event * current = head;
    while(current->advance){
      current = current->advance;
    }
    current->advance = append;
}

void displayAll(node * head){
  if(!head){
    cout << ">>END OF DATA" << "\n\n";
  }else{
    cout << "DATA EXISTS: " << head->activity << "\n\n";
    if(head->chain) cout << ">>CHAIN LINKED: "<< head->activity <<"\n\n";
    displayChain(head->chain);
    displayAll(head->next);
  }
}
int displayChain(Event * head){
  cerr << "--- in disp chain" << '\n';
    if(!head)
      return 0;
    else{
      displayChain(head->advance);
      cout << ">>output: " << head->name <<'\n';
      return 1;
    }
}
int clean(node * & head){
  if(!head){
    return 0;
  }else{
    cleanChain(head->chain);
    clean(head->next);
    delete [] head->activity;
    head->chain = NULL;
    head = NULL;
    return 1;
  }
}
int cleanChain(Event * & head){
  if(!head){
    return 0;
  }else{
    cleanChain(head->advance);
    delete[] head->name;
    delete[] head->season;
    delete[] head->desc;
    delete[] head->bring;
    head = NULL;
    return 1;
  }
}


int nodeAttacher(){
   node * head = new node();
   head->next=NULL;
   head->activity=NULL;
   do{
      appendNode(head,createEvent());
   }while(again());
   displayAll(head->next);
   clean(head);
   cout << ">>Post clean: ";
   displayAll(head);
   delete head;
   return 0;
}

bool again(){
    char option = ' ';
    cout << ">>again?" << '\n';
    cin >> option;
    cin.ignore(100,'\n');
    if(tolower(option)=='n') return false;
    return true;
}

int main(){
  nodeAttacher();
  return 0;
}
/*
void recursiveAppend(node * head,int & data  need to bring in a pointer to obj, int data is tes){
    if(!head){//if head doesn't exist make it
        head = new node;
        head->next = NULL;
        head->data = data;
        data = 0;
    }else{
        addNodeEnd(head->next, data);
    }
}
*/

   /*
      if(head==NULL){//if head doesn't exist make it
      displayText("In null head",true);
      head->next = NULL;
      head->data = data;
      }else{
      */


