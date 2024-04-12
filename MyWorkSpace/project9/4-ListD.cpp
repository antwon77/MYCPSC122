#include <iostream>
#include <climits>
using namespace std;

#include "4-ListD.h"

ListD::ListD()
{
 InitializeVars();
}

ListD::ListD(ListD* lst)
{
 InitializeVars();
 //returns a pointer to the first node, which is what we want here
 doubleNode* cur = lst->FindPosition(2);
 for (int i = 1; i <= lst->length; i++)
 {
  cout << cur->item << endl;
  Insert(cur->item,i);
  cur = cur->next;
 }
}

void ListD::InitializeVars()
{
 length = 0;

//create dummy nodes;
 head = new doubleNode;
 tail = new doubleNode;

 //set values for head dummy node;
 head->prev = NULL;
 head->item = INT_MIN;
 head->next = tail;

 //set values for tail dummy node;
 tail->prev = head; 
 tail->item = INT_MAX;
 tail->next = NULL;
}

//how would you do this?
ListD::~ListD()
{
  doubleNode* cur = head -> next;
  while (cur != tail)
    {
      doubleNode* nextNode = cur -> next;
      delete cur;
      cur = nextNode;
    }
  delete head;
  delete tail;
}
void ListD::Insert(itemType item, int pos)
{
 //new node goes between these two nodes
 doubleNode* insertPtA = FindPosition(pos);  
 doubleNode* insertPtB = insertPtA->next; 

 //create new node and set its values
 doubleNode* tmp = new doubleNode; 
 tmp->prev = insertPtA;
 tmp->item = item;
 tmp->next = insertPtB;

 //set pointers for nodes before and after the insertion point
 insertPtA->next = tmp;
 insertPtB->prev = tmp;

 length++;
}

void ListD::PrintForward()
{
 doubleNode*  cur = head->next;

 int i = 0;
 while (i < length)
 {
  cout << cur->item << endl;
  cur = cur->next;
  i++;
 }
}
void ListD::PrintBackward()
{
  doubleNode* cur = tail->prev;
  int i = 0;
  while (i < length)
    {
      cout << cur->item << endl;
      cur = cur->prev;
      i++;
    }
}

  void ListD::Delete(int pos)  
    {
    doubleNode* cur = head->next;
    int nodesDeleted = 0; // Counter for deleted nodes
    int currentPosition = 1;

    while (cur != tail && currentPosition != pos) {
        cur = cur->next;
        currentPosition++;
    }

    if (currentPosition == pos) {
        cout << "found item to delete: " << cur->item << endl;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
        length--;
        nodesDeleted++; // Increment counter
    } else {
        cout << "Position not found in the list." << endl;
    }

    return;
  }
int ListD::DeleteAll(itemType item) {
    doubleNode* cur = head->next;
    int nodesDeleted = 0; // Counter for deleted nodes

    while(cur != tail) {
        if (cur->item == item) {
            cout << "found item to delete: " << cur->item << endl;
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;
            length--;
            nodesDeleted++; // Increment counter
            return nodesDeleted;
        }
        cur = cur->next;
    }
    cout << "Item not found in the list." << endl;
    cout << cur->item << endl;
    return nodesDeleted;
}

doubleNode* ListD::FindPosition(int pos) {
    doubleNode* cur = head;
    int currentPosition = 0;

    while (cur != nullptr && currentPosition < pos - 1) {
        cur = cur->next;
        currentPosition++;
    }

    if (cur == nullptr || currentPosition != pos - 1) {
        cout << "Error finding insertion point." << endl;
        return nullptr;
    }

    return cur;
}
void ListD::Sort() {
    for (doubleNode* i = head->next; i != tail; i = i->next) {
        for (doubleNode* j = i->next; j != tail; j = j->next) {
            if (i->item > j->item) {
                // Swap the values
                int temp = i->item;
                i->item = j->item;
                j->item = temp;
            }
        }
    }
}