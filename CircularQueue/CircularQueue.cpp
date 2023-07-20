#include <iostream>
#include <cstdio>
using namespace std;

inline void error(char *message) {
    printf("%s\n", message);
    exit(1);
}

#define MAX_QUEUE_SIZE 100
class CircularQueue {
protected:
    int front;                  // 첫 번째 요소 앞에 위치
    int rear;                   // 마지막 요소 앞에 위치
    int data[MAX_QUEUE_SIZE];   // (정수)요소의 배열

public:
    CircularQueue() { front = rear = 0; }
    bool isEmpty()  { return front == rear; }
    bool isFull()   { return (rear + 1) % MAX_QUEUE_SIZE == front; }

    void enqueue( int val )     // 큐에 삽입
    {  
        if( isFull() )
            error(" error: Queue is Full");
        else
        {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
        }
    }

    int dequeue()               // 첫 항목을 큐에서 빼서 반환
    {
        if( isEmpty() ) error(" Error: Queue is Empty\n");
        else
        {
            front = (front + 1) % MAX_QUEUE_SIZE;
            return data[front];
        }
    }

    int peek()                  // 첫 항목을 큐에서 빼지 않고 반환
    {
        if( isEmpty() ) error( " Error: Queue is Empty\n");
        else
            return data[(front+1) % MAX_QUEUE_SIZE];
    }

    void display()              // 큐의 모든 내용을 순서대로 출력
    {
        printf( "Queue: ");
        int maxi = (front < rear) ? rear : rear + MAX_QUEUE_SIZE;
        for(int i = front + 1; i <= maxi; i++)
            printf( "[%2d] ", data[i%MAX_QUEUE_SIZE]);
        printf( "\n" );
    }
};

int main() {
    CircularQueue que;
    for( int i=1; i<10; i++ )
        que.enqueue( i );
    que.display();
    que.dequeue();
    que.dequeue();
    que.dequeue();
    que.display();
}