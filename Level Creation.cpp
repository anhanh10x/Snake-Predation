#include<iostream>
#include<conio.h>
#include<cstdlib>
using namespace std;
int main()
{
    system("cls");
    short a[100];
    int count=1;
    int i=61;
    int j=5;
    while(true){
        if(count>11)
            break;
        cout<<"a["<<i<<"]="<<30<<";"<<endl;
        cout<<"a["<<i+1<<"]="<<j<<";"<<endl;     
        i=i+2;
        j++;
        count++;
    }
}