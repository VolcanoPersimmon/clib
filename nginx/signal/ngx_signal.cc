#include <stdio.h>
#include <unistd.h>
#include <iostream>
void mysignal()
{
    cout << "执行了mysignal函数" << endl;
    return;
}