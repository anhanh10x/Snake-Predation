#include<conio.h>
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include"snakePredation.h"
using namespace std;

int main()
{
    //set up man hinh 
    system("cls");
    SetWindowSize(120,40);
    srand((int)time(0));
    font(22);
	ShowCur(0);
    //khai bao bien
    queue q;
    char heart=(char)3;
    short Xheart=0,Yheart=0,Xhead,Yhead,Xtail,Ytail;
    int point=0;
    short level=1;
    int state=1,stateBefore=1;
    short CheDo;
    short a[200];
	int count=-1;
    bool success=true;
    bool End=false;
    //ham chuong trinh
    ManHinhChinh(CheDo);
    while(true)
    {
        system("cls");
        //ve mot hinh chu nhat dai 60 rong 20
        rectangle(60,20);
        //ham dieu huong chu ran nho cua minh
        khoiTaoQueue(q);
        GoTo(1,9);
        cout<<"0";
        GoTo(1,9);
        Xtail=Xhead=1;
        Ytail=Yhead=9;
        if(CheDo==1)
        {
            GoTo(61,9);
            cout<<" Diem: ";
            while(true)
            {
                if(success==true)
                {
                    Xheart=random(1,58);
                    Yheart=random(1,18);
                    if(checkTouch(q,Xheart,Yheart)==true)
                        continue;
                    count++;
                    GoTo(67,9);
                    cout<<point;
                    if(count==5)
                    {
                        GoTo(Xheart,Yheart);
                        SetColor(0,11);
                        cout<<(char)2;
                        count=1;
                        point=point+2;
                    }
                    else
                    {
                        GoTo(Xheart,Yheart);
                        SetColor(0,4);
                        cout<<heart;
                        point++;
                    }
                    GoTo(Xhead,Yhead);
                    success=false;
                    SetColor(0,7);
                }
        
                if(state==1 && stateBefore==2 || state==2 && stateBefore==1 || state==3 && stateBefore==4 || state==4 && stateBefore==3)
                    state=stateBefore;
                if(state==1)
                {
                    runHorizontalAhead(Xhead,Yhead);
                }
                else if(state==2)
                {
                    runHorizontalBack(Xhead,Yhead);
                }
                else if(state==3)
                {
                    runVerticalUp(Xhead,Yhead);
                }
                else
                {
                    runVerticalDown(Xhead,Yhead);
                }
                push(q);
                q.top->State=state;
                q.top->x=Xhead;
                q.top->y=Yhead;
                if(checkTouch(q,Xhead,Yhead)==true)
                {
                    End=true;
                    break;
                }
                if(checkWall(Xhead,Yhead,state)==true)
                {
                    End=true;
                    break;
                }
                if(Xhead==Xheart && Yhead==Yheart)
                {
                    success=true;
                    continue;
                }
        
                if(q.bottom->State==1)
                {
                    deleteHorizontalAhead(Xtail,Ytail);
                    pop(q);
                }
                else if(q.bottom->State==2)
                {
                    deleteHorizontalBack(Xtail,Ytail);
                    pop(q);
                }
                else if(q.bottom->State==3)
                {
                deleteVerticalUp(Xtail,Ytail);
                pop(q);
                }
                else
                {
                    deleteVerticalDown(Xtail,Ytail);
                    pop(q);
                }
                stateBefore=state;
                if(kbhit()){
                    Direction(state);
                }
        
                Sleep(50);
            }
            if(End==true)
                break;
        }
        if(CheDo==2)
        {
            ManChoiHienDai(a);
            GoTo(62,9);
            cout<<" Can dat: ";
            point=a[a[0]*2-1]+1;
            state=1;
            while(true)
            {
                if(success==true)
                {
                    Xheart=random(1,58);
                    Yheart=random(1,18);
                    if(checkTouch(q,Xheart,Yheart)==true || ChuongNgaiVat(a,Xheart,Yheart)==true)
                        continue;
                    GoTo(Xheart,Yheart);
                    SetColor(0,4);
                    cout<<heart;
        	        GoTo(72,9);
                    point--;
                    if(point==0)
                    {
                        break;
                    }
                    cout<<" ";
                    GoTo(71,9);
        	        cout<<point;
                    GoTo(Xhead,Yhead);
                    success=false;
                    SetColor(0,7);
                }
                if(state==1 && stateBefore==2 || state==2 && stateBefore==1 || state==3 && stateBefore==4 || state==4 && stateBefore==3)
                    state=stateBefore;
                if(state==1)
                {
                    runHorizontalAhead(Xhead,Yhead);
                }
                else if(state==2)
                {
                    runHorizontalBack(Xhead,Yhead);
                }
                else if(state==3)
                {
                    runVerticalUp(Xhead,Yhead);
                }
                else
                {
                    runVerticalDown(Xhead,Yhead);
                }
                push(q);
                q.top->State=state;
                q.top->x=Xhead;
                q.top->y=Yhead;
                if(checkTouch(q,Xhead,Yhead)==true)
                {
                    End=true;
                    break;
                }
                if(ChuongNgaiVat(a,Xhead,Yhead)==true)
			    {
                    End=true;
                    break;
        	    }
                if(Xhead==Xheart && Yhead==Yheart)
                {
                    success=true;
                    continue;
                }
                if(q.bottom->State==1)
                {
                    deleteHorizontalAhead(Xtail,Ytail);
                    pop(q);
                }
                else if(q.bottom->State==2)
                {
                    deleteHorizontalBack(Xtail,Ytail);
                    pop(q);
                }
                else if(q.bottom->State==3)
                {
                    deleteVerticalUp(Xtail,Ytail);
                    pop(q);
                }
                else
                {
                    deleteVerticalDown(Xtail,Ytail);
                    pop(q);
                }
                stateBefore=state;
                if(kbhit()){
                    Direction(state);
                }
                Sleep(a[a[0]*2]);
            }
            level++;
            if(level==8)
            {
                End=true;
                break;
            }
            if(End==true)
                break;
            ChuyenMan(level);   
        }
        giaiPhong(q);
    }
    end();
    giaiPhong(q);
}
