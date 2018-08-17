#include "linkedL.cpp"

int nodeExists(node *, char[]);

void appendNode(node * head, Event * events){
  char type[500];
  cout << ">>What kind of activity is this?" << "\n\n";
  read(type);
  node * current = head;
  node * temp = head;
  /*
  if(nodeExists(head,type)){
    while(strcmp(head->activity,type)==0){
      current = current->next;
    }
    if(!head->chain){
      head->chain = events;
    }else{
      eventAppend(head->chain, events);
    }
  }
  else{
  */
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
  //}
}
int nodeExists(node * head, char test[]){
  //this is never finding a match
  int exists = 0;
  cerr << "---In node exists" << "\n\n";
  cout << "---head->act: " << head->activity << '\n';
  cout << "---test: " << test << '\n';

  if(!head)
    return exists;
  else if(strcmp(head->activity, test)==0){
    nodeExists(head->next,test);
    return n
  }
 return exists;
}
///////
bool find(node * head, char match[]) 
{
  if(head && head->activity == match)
    return 1;
  else if(head->next)
    find(head->next,match);
  else
    return 0;
}
//////
int remove_all(node * & head) 
{

  if(!head)
    return 0;
  int nodeCount = remove_all(head->next) +1; 

  delete head;
  head = NULL;
  return nodeCount;
}

