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

//new Event creator, returns pointer
Event * createEvent(){
   char tempN[500];
   cout << ">>Enter activity name!" << "\n\n";
   read(tempN);
   char tempS[500];
   cout << ">>Enter the best season for your activity!" << "\n\n";
   read(tempS);
   char tempD[500];
   cout << ">>Enter activity description!" << "\n\n";
   read(tempD);
   char tempB[500];
   cout << ">>Enter what you should bring!" << "\n\n";
   read(tempB);
   Event * ptr = new Event;
   ptr->name= new char[(strlen(tempN)+1)];
   ptr->season= new char[(strlen(tempS)+1)];
   ptr->desc= new char[(strlen(tempD)+1)];
   ptr->bring= new char[(strlen(tempB)+1)];
   strcpy(ptr->name,tempN);
   strcpy(ptr->season,tempS);
   strcpy(ptr->desc,tempD);
   strcpy(ptr->bring,tempB); 
   ptr->advance = NULL;

   return ptr;
};
//reads in values to temps
void read(char input[]){
   cin.get(input,500,'\n');
   cin.ignore(500,'\n');
};
/*
int nodeExists(node * head, char match[]){
  if(head->activity){
    if(strcmp(head->activity, match))
      return 1;
    else if(head->next)
      nodeExists(head->next,match);
  }
  return 0;
}
*/
bool nodeExists(node * head, char type[]){
  node * current = head;
  while(current){
    if(current->activity){
      cerr << "current exists" << "\n\n";
     if(strcmp(current->activity,type)==0){
      cerr << "current strcmp" << "\n\n";
       return true;
     }
    }
  current = current->next;
  }
  return false;
}
//main show, takes event creator as arg
//attaches that to secondary linked list
//assigns takes in name for secondary linked list
//compares input name to existing names
//if name exists appends new event node to end of secondary LL
//if not, creates new node and attaches event node to secondary LL
//should probably split it up
void appendNode(node * head, Event * events){
  char type[500];
  cout << ">>What kind of activity is this?" << "\n\n";
  read(type);
  node * current = head;
  node * temp = head;
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
//traverses and appends
void eventAppend(Event * head, Event * append){
    Event * current = head;
    while(current->advance){
      current = current->advance;
    }
    current->advance = append;
}
//recursive, moves through the lists, di
void displayAll(node * head){
  if(!head){
    cout << ">>END OF DATA" << "\n\n";
  }else{
    if(head->chain) cout << ">>Activity type: "<< head->activity <<"\n\n";
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
      cout << ">>name: " << head->name <<'\n';
      cout << ">>season: " << head->season <<'\n';
      cout << ">>description: " << head->desc <<'\n';
      cout << ">>to bring: " << head->bring <<"\n\n";
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
