#include <iostream>
using namespace std;
#include "queueP.h"

PQueue::PQueue() : QueueI()
{}
PQueue::PQueue(PQueue* q) : QueueI(q)
{}

void PQueue::Enqueue(itemType newItem)
{
  node* Enq = new node;
  Enq->item = newItem;
  node* prev = PtrTo(newItem);
  Enq->next = prev ->next;
  prev->next = Enq;
}

node* PQueue::PtrTo(itemType newItem)
{
  node* cur = head;
  if(newItem < head->item)
    return head;
  while (cur->next != nullptr && cur->next->item <= newItem)
      cur = cur->next;
 return cur;
}

