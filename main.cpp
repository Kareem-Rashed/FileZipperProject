#include <iostream>
#include "PriorityQueue.h"
using namespace std;



int main()
{

    Node<char>* first = new Node('a', 12);
    Node<char>* second = new Node('b', 3);

    Node<char>* third = new Node('c', 90);

    PriorityQueue<char> pq;

    pq.insert(first);
    pq.insert(second);
    pq.insert(third);

    pq.display();

    pq.dequeue();

    pq.display();


    pq.dequeue();

    pq.display();

    pq.dequeue();

    pq.display();




    return 0;
}