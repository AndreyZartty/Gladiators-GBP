#include "thread.h"
#include <iostream>

using namespace std;

Thread::Thread(QObject *parent)
    : QThread(parent)
{
    _finish = false;
}

void Thread::run(){
    bool finish = false;

    while(!finish) {

        emit boolFinish(finish);
        finish=getF();

    }

    cout<<"finish"<<endl;
}

bool Thread::getF(){
    return _finish;
}

void Thread::setF(bool finish){
    _finish=finish;
}
