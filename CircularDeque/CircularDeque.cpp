#include <iostream>
#include <cstdio>
#include "../CircularQueue/CircularQueue.cpp"

using namespace std;

class CircularDeque : public CircularQueue {
public:
    CircularDeque() {}
    void addRear( int val ) { enqueue(val); }   // enqueue() 호출
    int deleteFront() { return dequeue(); }     // duqueue() 호출
    int getFront() { return peek(); }           // peek() 호출

    void display()                              // CircularQueue::display()를 재정의
    {
        printf("Dequeue: ");                    // 이부분만 다름
        int maxi = (front < rear) ? rear : rear + MAX_QUEUE_SIZE;
        for( int i = front+1; i<=maxi; i++)
            printf("[%2d] ", data[i%MAX_QUEUE_SIZE]);
        printf("\n");
    }

    int getRear()                               // 후단에서 peek
    {
        if(isEmpty())
            error(" Error: Deque is Empty\n");
        else return data[rear];
    }

    void addFront(int val)                      // 전단에 삽입
    {
        if( isFull() ) error(" error: Deque is Full\n");
        else
        {
            data[front] = val;
            front=(front-1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
        }
    }

    int deleteRear()                            // 후단에서 삭제
    {
        if( isEmpty() ) error(" Error: Deque is empty\n");
        else
        {
            int ret = data[rear];
            rear = (rear-1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
            return ret;
        }
    }
};

int main()
{
    CircularDeque deq;
    for(int i=1; i<10; i++)
    {
        if( i%2 ) deq.addFront(i);              // 앞에 삽입
        else deq.addRear(i);                    // 뒤에 삽입
    }
    deq.display();
    deq.deleteFront();
    deq.deleteRear();
    deq.deleteFront();
    deq.display();
}