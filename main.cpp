#include <iostream>
#include <thread>
#include <vector>
#include"semaphore.h"

std::vector<int> buffor;
int max = 10;
int min = 0;
bool val = true; // not necessary - CLion has annoying warring about while true
bool flagAC = false, flagB = false;
Condition cMax,cMin,cAC,cB,c3;

Monitor m = Monitor();

void produce() {
    int product = 1;
    while (val) {
        m.enter();

        if (max <= 0) {
            std::cout << "P: sleepin" << std::endl;
            m.wait(cMax);
        }
        max--;
        buffor.push_back(product);
        std::cout << "P: put " << product <<" into  fifo, size: "<<buffor.size()<< std::endl;

        if (min > 0) {
            min++;
            m.signal(cMin);
        } else {
            min++;
        }
        if(buffor.size()>3)
            m.signal(c3);
        m.leave();
        sleep(5);
        product++;
    }
}

void consumAC(std::string id) {
    while (val) {

        m.enter();
        if (min <= 0) {
            std::cout<<id << ": sleepin,nothin to read" << std::endl;
            m.wait(cMin);
        }
        if (flagAC == true) {
            m.wait(cAC);
        }
        flagAC=true;

        std::cout << id << ": readin: " << buffor.front() << std::endl;
        if(flagB==true){
            if(buffor.size()<=3){
                std::cout<<id << ": cannot delete - go to sleep" << std::endl;
                m.wait(c3);
            }

            std::cout<<id<<": deleting: "<<buffor.front()<<", fifo size:"<<buffor.size()<<std::endl;
            buffor.erase(buffor.begin());
            flagB=false;
            flagAC=false;
            m.signal(cB);
            m.signal(cAC);
            min--;
        }

        if (max == 0) {
            max++;
            m.signal(cMax);
        }
        else{
            max++;
        }

        m.leave();
        sleep(2);

    }

}

void consumB() {
    while (val){
        m.enter();

        if (min <= 0) {
            std::cout<<"B: sleepin,nothin to read" << std::endl;
            m.wait(cMin);
            std::cout<<"B: wake up" << std::endl;
        }
        if(flagB==true)
            m.wait(cB);
        flagB=true;


        std::cout<< "B: readin: " << buffor.front() << std::endl;
        if(flagAC==true){
            if(buffor.size()<=3){
                std::cout<< "B: cannot delete - go to sleep" << std::endl;
                m.wait(c3);
            }

            std::cout<<"B: deleting: "<<buffor.front()<<", fifo size: " <<buffor.size()<<std::endl;
            buffor.erase(buffor.begin());
            flagB=false;
            flagAC=false;
            m.signal(cB);
            m.signal(cAC);
            min--;
        }

        if (max == 0) {
            max++;
            m.signal(cMax);
        }
        else{
            max++;
        }

        m.leave();
        sleep(2);

    }
}


int main() {

    std::thread producer(produce);
    std::thread cons1(consumAC, "A");
    std::thread cons2(consumB);
    std::thread cons3(consumAC,"C");

    producer.join();
    cons1.join();
    cons2.join();
    cons3.join();

    std::cout << "never reach it" << std::endl;


    return 0;
}

