#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

//CustomerQueue.h: 하나의 고객 정보를 관리하기 위한 클래스
#define MAX_QUEUE_SIZE 100

// 오류 처리 함수
inline void error(const char *message)
{
    printf("%s\n", message);
    exit(1);
}

struct Customer
{
    int id;                         // 고객 번호
    int tArrival;                   // 고객이 도착한 시간
    int tService;                   // 이 고객의 서비스에 필요한 시간
    Customer (int i = 0, int tArr = 0, int tServ = 0):id(i), tArrival(tArr), tService(tServ) {}
};

class CustomerQueue
{
protected:
    int front;                      // 첫 번째 요소 앞의 위치
    int rear;                       // 마지막 요소 위치
    Customer data[MAX_QUEUE_SIZE];  // 요소의 배열
public:
    CustomerQueue() { front=rear=0; }
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }

    void enqueue(Customer val)      // 큐의 삽입
    {
        if(isFull())
            error("error: Queue is Full\n");
        else
        {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
        }
    }

    Customer dequeue()              // 첫 항목을 큐에서 빼서 전환
    {
        if(isEmpty())
            error(" error: Queue is Empty\n");
        else
        {
            front = (front + 1) % MAX_QUEUE_SIZE;
            return data[front];
        }
    }

    Customer peek()                 // 첫 항목을 큐에서 빼지 않고 반환
    {
        if(isEmpty())
            error(" error: Queue is Empty\n");
        else
            return data[(front + 1) % MAX_QUEUE_SIZE];
    }

    void display()                  // 큐의 모든 내용을 순서대로 출력
    {
        printf("Queue: ");
        int maxi = (front < rear) ? rear : rear + MAX_QUEUE_SIZE;
        for(int i = front + 1; i <= maxi; i++)
            printf("[2%d]", data[i%MAX_QUEUE_SIZE]);
        printf("\n");
    }
};


// BankSimulator
class BankSimulator
{
    int nSimulation;                // 입력: 전체 시뮬레이션 횟수
    double probArrival;             // 입력: 단위시간에 도착하는 평균 고객 수
    int tMaxService;                // 입력: 한 고객에 대한 최대 서비스 시간
    int totalWaitTime;              // 결과: 고객들이 기다린 전체 시간
    int nCustomers;                 // 결과: 전체 고객 수
    int nServedCustomers;           // 결과: 서비스 받은 고객 수
    CustomerQueue que;              // 고객 대기 큐

    // 랜덤 숫자를 생성하여 고객 도착 여부와 서비스 시간 자동 생성 코드
    double Random() { return rand()/(double) RAND_MAX; }
    bool IsNewCustomer() { return Random() > probArrival; }
    int RandServiceTime() { return (int)(tMaxService * Random()) + 1; }

    // 새로 도착한 고객을 큐에 삽입
    void InsertCustomer( int arrivalTime ) {
        Customer a(++nCustomers, arrivalTime, RandServiceTime());
        printf(" customer %d arrive (service time: %d minutes) \n", a.id, a.tService);
        que.enqueue(a);
    }

public:
    // 생성자
    BankSimulator(): nCustomers(0), totalWaitTime(0), nServedCustomers(0) {}

    // 시뮬레이션 파라미터 입력
    void readSimulationParameters() {
        printf("Maximum time to sumulate (e.g. 10) = ");
        scanf("%d", &nSimulation);
        printf("Number of customers arriving in unit time(e.g. 0.7) = ");
        scanf("%d", &tMaxService);
        printf("==================================================================================================");
    }

    // 시뮬레이션 실행
    void run()
    {
        int clock = 0;
        int serviceTime = -1;
        while(clock < nSimulation)
        {
            clock++;
            printf("currentTime=%d\n", clock);
            if(IsNewCustomer())
                InsertCustomer(clock);
            if (serviceTime > 0) serviceTime--;
            else
            {
                if(que.isEmpty()) continue;
                Customer a = que.dequeue();
                nServedCustomers++;
                totalWaitTime += clock - a.tArrival;
                printf(" customer %d start service (waiting time: %d minutes)\n", a.id, clock - a.tArrival);
                serviceTime = a.tService - 1;
            }
        }
    }

    // 시뮬레이션 결과를 출력한다.
    void printStat()
    {
        printf("=================================================================================================");
        printf(" Surviced Customers                    = %d\n", nServedCustomers);
        printf(" Waiting Time                          = %d\n", totalWaitTime);
        printf(" Average service customer waiting time = %-5.2fmin\n", (double)totalWaitTime / nServedCustomers);
        printf(" Current waiting Customers             = %d\n", nCustomers - nServedCustomers);
    }
};

int main()
{
    srand( (unsigned int)time(NULL) );
    BankSimulator sim;                              //시뮬레이터 객체 생성
    sim.readSimulationParameters( );                //시뮬레이션 파라미터 설정
    sim.run();                                      // 시뮬레이션 시작
    sim.printStat();                                // 시뮬레이션 결과 출력
}