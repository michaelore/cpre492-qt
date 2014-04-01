#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <cmath>

int examplefunction()
{
    double j = 0.0;
    for(int i = 0; i < 100000000; i++) {
        j += pow(1.0, i);
    }
    //std::cerr << "Hello World!";
    return j;
}

void spin(int &iteration)
{
    const int work = 1000 * 1000 * 40;
    volatile int v = 0;
    for (int j = 0; j < work; ++j)
        ++v;

    qDebug() << "iteration" << iteration << "in thread" << QThread::currentThreadId();
}
