#include <iostream>
using namespace std;

#include "queueP.h"


int main()
{

 PQueue* que = new PQueue;
 for (int i = 5; i >= 1; i--)
  que->PutItemH(i);
 que->Enqueue(2);
 que->Enqueue(1);
 que->Enqueue(4);
 que->Enqueue(3);
 que->Enqueue(2);
 que->Enqueue(6);
 que->Enqueue(5);
 que->Enqueue(2);
 que->Print();


 delete que;
}
