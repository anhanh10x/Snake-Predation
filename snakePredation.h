#include<iostream>
#include <stdio.h>
#include <conio.h>
#include<ctime>
#include<windows.h>
using namespace std;
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
void GoTo(SHORT posX, SHORT posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;
	SetConsoleCursorPosition(hStdout, Position);
}

void SetColor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

// chinh font chu
void font(short x)
{   
    HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
    PCONSOLE_FONT_INFOEX font = new CONSOLE_FONT_INFOEX() ;
    font->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(cons,0,font);
    font->dwFontSize.X = x;
    font->dwFontSize.Y = x;
    //font->FontWeight = 22;
    //font->FontFamily = FF_DECORATIVE;
    SetCurrentConsoleFontEx(cons,0,font); 
}
//ham random
int random(int minN, int maxN){
    return minN + rand() % (maxN + 1 - minN);
}
//Ham ve hinh chu nhat
void rectangle(int length, int width)
{
    SetColor(0,5);
    GoTo(1,0);
    for(int i=0;i<length-1; i++)
    {
        cout<<(char)30;
    }
    SetColor(0,2);
    GoTo(0,0);
    for(int i=0;i<width;i++)
    {
        cout<<(char)17;
        GoTo(0,whereY()+1);
    }
    SetColor(0,5);
    GoTo(1,width-1);
    for(int i=0;i<length-1;i++)
    {
        cout<<(char)31;
    }
    GoTo(length-1,0);
    SetColor(0,2);
    for(int i=0;i<width;i++)
    {
        cout<<(char)16;
        GoTo(length-1,whereY()+1);
    }
    SetColor(0,7);
}
//ham cho ran chay ngang tu trai qua phai
void runHorizontalAhead(short &Xhead, short &Yhead)
{
    GoTo(Xhead+1,Yhead);
    //xu ly gap bien phai
    if(whereX()==59)
        GoTo(1,whereY());
    cout<<"O";
    Xhead=whereX()-1;
    Yhead=whereY();
}
void deleteHorizontalAhead(short &Xtail, short &Ytail)
{
    GoTo(Xtail,Ytail);
    cout<<" ";
    //xu ly gap bien phai
    if(whereX()==59)
        GoTo(1,whereY());
    Xtail=whereX();
    Ytail=whereY();
}
//ham cho ran chay ngang tu phai qua trai
void runHorizontalBack(short &Xhead, short &Yhead)
{
    GoTo(Xhead-1,Yhead);
    //xu ly gap bien phai
    if(whereX()==0)
        GoTo(58,Yhead);
    cout<<"O";
    Xhead=whereX()-1;
    Yhead=whereY();
}
void deleteHorizontalBack(short &Xtail, short &Ytail)
{
    GoTo(Xtail,Ytail);
    cout<<" ";
    GoTo(whereX()-2,whereY());
    //xu ly gap bien phai
    if(whereX()==0)
        GoTo(58,Ytail);
    Xtail=whereX();
    Ytail=whereY();
}
//chay doc theo toa do tu tren xuong duoi
void runVerticalDown(short &Xhead, short &Yhead)
{
    GoTo(Xhead,Yhead+1);
    //xu ly gap bien phai
    if(whereY()==19)
        GoTo(Xhead,1);
    cout<<"O";
    Xhead=whereX()-1;
    Yhead=whereY();
}
void deleteVerticalDown(short &Xtail, short &Ytail)
{
    GoTo(Xtail,Ytail);
    cout<<" ";
    GoTo(whereX()-1,whereY()+1);
    //xu ly gap bien phai
    if(whereY()==19)
        GoTo(whereX(),1);
    Xtail=whereX();
    Ytail=whereY();
}
//chay doc theo toa do len tren
void runVerticalUp(short &Xhead, short &Yhead)
{
    GoTo(Xhead,Yhead-1);
    //xu ly gap bien phai
    if(whereY()==0)
        GoTo(Xhead,18);
    cout<<"O";
    Xhead=whereX()-1;
    Yhead=whereY();
}
void deleteVerticalUp(short &Xtail, short &Ytail)
{
    GoTo(Xtail,Ytail);
    cout<<" ";
    GoTo(whereX()-1,whereY()-1);
    //xu ly gap bien phai
    if(whereY()==0)
        GoTo(whereX(),18);
    Xtail=whereX();
    Ytail=whereY();
}
void Direction(int &state)
{
    char c[3];
    c[0]=getch();
    c[1]=getch();
    //neu ma nhan mui ten len
    if(c[1]=='H')
    {
        state=3;
    }
    //neu ma nhan mui ten xuong
    if(c[1]=='P')
    {
        state=4;
    }
    //neu an mui ten sang phai
    if(c[1]=='M')
    {
        state=1;
    }
    //neu an mui ten sang trai
    if(c[1]=='K')
    {
        state=2;
    }
}
struct node
{
    int State;
    short x;
    short y;
    struct node *next;
};
typedef struct node node;

struct queue
{
    node *bottom;
    node *top;
};
typedef struct queue queue;

bool isEmpty(queue q)
{
    if(q.bottom==NULL)
        return true;
    else 
        return false;
}

node* creatNode()
{
    node *p = new node;
    p->State=0;
    p->x=0;
    p->y=0;
    p->next=NULL;
        return p;
}
void push(queue &q)
{
    node *p = creatNode();
    if(isEmpty(q)==true)
        q.bottom=q.top=p;
    else   
    {
        q.top->next=p;
        q.top=p;
    }
}

void pop(queue &q)
{
    node *h=q.bottom;
    q.bottom=q.bottom->next;
    delete h;
}
void khoiTaoQueue(queue &q)
{
    q.bottom=NULL;
    q.top=NULL;
}

void giaiPhong(queue &q)
{
    while(true)
    {
        if(isEmpty(q)==false)
        {
            node *h=q.bottom;
            q.bottom = q.bottom->next;
            delete h;
        } 
        else 
        {
            cout<<"I am free!! <3";
            return;
        }
    }
}
bool checkTouch(queue q, short Xhead, short Yhead)
{
    bool Check=false;
    for(node *i=q.bottom; i!=q.top; i=i->next)
    {
        if(i->x==Xhead && i->y==Yhead)
        {
            Check=true;
            break;
        }
    }
    if(Check==true)
        return true;
    else
        return false;
}

bool checkWall(short Xhead, short Yhead, int state)
{
    bool check;
    if(Xhead==1 && state==1 || Xhead==58 && state==2 || Yhead==1 && state==4 || Yhead==18 && state==3)
        check=true;
    else    
        check=false;
    return check;
}
void RanNguSac(short Xhead, short Yhead)
{
    static short color=1;
    GoTo(Xhead-4,Yhead);
    SetColor(0,color);
    cout<<"OOOOO";
    GoTo(Xhead,Yhead);
    color++;
    if(color==7)
        color=1;
}
void XoaRanNguSac(short Xhead, short Yhead)
{
    GoTo(Xhead-4,Yhead);
    SetColor(0,7);
    cout<<"     ";
    GoTo(Xhead,Yhead);
}
void XoaChuRanNho(short Xhead, short Yhead, int length)
{
    static short color=1;
    short Xtail=Xhead-4;
    short Ytail=Yhead;
    for(int i=1; i<=length; i++)
    {
        SetColor(0,color);
        runHorizontalAhead(Xhead,Yhead);
        deleteHorizontalAhead(Xtail,Ytail);
        Sleep(100);
        color++;
        if(color==12)
            color=1;

    }
}
void ManHinhChinh(short &CheDo)
{
    int state;
    SetColor(0,9);
    GoTo(18,3);
    cout<<"HUONG DAN CHOI";
    SetColor(0,7);
    GoTo(15,5);
    cout<<" - Che do choi co dien se thua khi cham tuong.";
    GoTo(15,6);
    cout<<" - Che do choi hien dai co the di xuyen tuong. Co 7 level. ";
    GoTo(15,7);
    cout<<" - Che do co dien an qua thuong +1 diem, qua To cong +2 diem.";
    GoTo(15,8);
    cout<<" - Dung phim "<<(char)30<<" hoac phim "<<(char)31<<" de chon che do.";

    //xet up chon che do;
    RanNguSac(15,10);
    GoTo(17,10);
    SetColor(15,10);
    cout<<" 1.CHE DO CO DIEN";
    SetColor(0,7);
    GoTo(17,12);
    SetColor(0,11);
    cout<<" 2.CHE DO HIEN DAI";
    SetColor(0,7);
    GoTo(17,10);
    while(true){
        char c[3];
        c[0]=getch();
        if((int)c[0]==13)
        {
            XoaChuRanNho(15,whereY(),22);
            if(whereY()==10)
                CheDo=1;
            else
                CheDo=2;
            SetColor(0,7);
            system("cls");
            return;
        }
        c[1]=getch();
        //neu ma nhan mui ten len
        if(c[1]=='H')
        {
            state=3;
        }
        //neu ma nhan mui ten xuong
        if(c[1]=='P')
        {
            state=4;
        }
        //neu an mui ten sang phai
        if(c[1]=='M')
        {
            state=1;
        }
        //neu an mui ten sang trai
        if(c[1]=='K')
        {
            state=2;
        }
        if(state==3 || state==1)
        {
            XoaRanNguSac(15,12);
            RanNguSac(15,10);
            GoTo(17,10);
            SetColor(15,10);
            cout<<" 1.CHE DO CO DIEN";
            SetColor(0,7);
            GoTo(17,12);
            SetColor(0,11);
            cout<<" 2.CHE DO HIEN DAI";
            GoTo(17,10);
            SetColor(0,7);
        }
        if(state==4 || state==2)
        {
            XoaRanNguSac(15,10);
            RanNguSac(15,12);
            GoTo(17,10);
            SetColor(0,11);
            cout<<" 1.CHE DO CO DIEN";
            SetColor(0,7);
            GoTo(17,12);
            SetColor(15,10);
            cout<<" 2.CHE DO HIEN DAI";
            SetColor(0,7);
        }    
    }
}

void SinhMan(short a[])
{
    static short level=0;
    if(level==0)
    {
        a[0]=2;
        //mau sac
        a[1]=14;
        a[2]=14;
        //so diem can dat;
        a[3]=10;
        //toc do
        a[4]=25;
    }
    if(level==1)
    {
        a[0]=12;
        a[1]=20;
        a[2]=1;
        a[3]=20;
        a[4]=2;
        a[5]=20;
        a[6]=3;
        a[1]=20;
        a[2]=1; 
        a[3]=20;
        a[4]=2; 
        a[5]=20;
        a[6]=3; 
        a[7]=20;
        a[8]=4; 
        a[9]=20;
        a[10]=5; 
        a[11]=20;
        a[12]=6; 
        a[13]=20;
        a[14]=7; 
        a[15]=20;
        a[16]=8; 
        a[17]=20;
        a[18]=9;
        a[19]=20;
        a[20]=10;
        //mau sac
        a[21]=11;
        a[22]=11;
        //so diem can dat;
        a[23]=10;
        //toc do
        a[24]=40;
    }
    if(level==2)
    {
        a[0]=32;
        a[1]=1;  
        a[2]=12; 
        a[3]=2;  
        a[4]=12; 
        a[5]=3;  
        a[6]=12; 
        a[7]=4;  
        a[8]=12; 
        a[9]=5;  
        a[10]=12;
        a[11]=6; 
        a[12]=12;
        a[13]=7; 
        a[14]=12;
        a[15]=8; 
        a[16]=12;
        a[17]=9;
        a[18]=12;
        a[19]=10;
        a[20]=12;
        a[21]=11;
        a[22]=12;
        a[23]=12;
        a[24]=12;
        a[25]=13;
        a[26]=12;
        a[27]=14;
        a[28]=12;
        a[29]=15;
        a[30]=12;
        a[31]=16;
        a[32]=12;
        a[33]=17;
        a[34]=12;
        a[35]=18;
        a[36]=12;
        a[37]=19;
        a[38]=12;
        a[39]=20;
        a[40]=12;
        a[41]=21;
        a[42]=12;
        a[43]=22;
        a[44]=12;
        a[45]=23;
        a[46]=12;
        a[47]=24;
        a[48]=12;
        a[49]=25;
        a[50]=12;
        a[51]=26;
        a[52]=12;
        a[53]=27;
        a[54]=12;
        a[55]=28;
        a[56]=12;
        a[57]=29;
        a[58]=12;
        a[59]=30;
        a[60]=12;
        //mau sac
        a[61]=1;
        a[62]=1;
        //so diem can dat;
        a[63]=10;
        //toc do
        a[64]=40;
    }
    if(level==3)
    {
        a[0]=40;
        a[1]=1;  
        a[2]=12; 
        a[3]=2;  
        a[4]=12; 
        a[5]=3;  
        a[6]=12; 
        a[7]=4;  
        a[8]=12; 
        a[9]=5;  
        a[10]=12;
        a[11]=6; 
        a[12]=12;
        a[13]=7; 
        a[14]=12;
        a[15]=8; 
        a[16]=12;
        a[17]=9;
        a[18]=12;
        a[19]=10;
        a[20]=12;
        a[21]=11;
        a[22]=12;
        a[23]=12;
        a[24]=12;
        a[25]=13;
        a[26]=12;
        a[27]=14;
        a[28]=12;
        a[29]=15;
        a[30]=12;
        a[31]=16;
        a[32]=12;
        a[33]=17;
        a[34]=12;
        a[35]=18;
        a[36]=12;
        a[37]=19;
        a[38]=12;
        a[39]=20;
        a[40]=12;
        a[41]=21;
        a[42]=12;
        a[43]=22;
        a[44]=12;
        a[45]=23;
        a[46]=12;
        a[47]=24;
        a[48]=12;
        a[49]=25;
        a[50]=12;
        a[51]=26;
        a[52]=12;
        a[53]=27;
        a[54]=12;
        a[55]=28;
        a[56]=12;
        a[57]=29;
        a[58]=12;
        a[59]=30;
        a[60]=12;
        a[61]=37;
        a[62]=1; 
        a[63]=37;
        a[64]=2; 
        a[65]=37;
        a[66]=3; 
        a[67]=37;
        a[68]=4; 
        a[69]=37;
        a[70]=5; 
        a[71]=37;
        a[72]=6; 
        a[73]=37;
        a[74]=7; 
        a[75]=37;
        a[76]=8; 
        //mau sac
        a[77]=7;
        a[78]=7;
        //so diem can dat;
        a[79]=10;
        //toc do
        a[80]=50;
    }
    if(level==4)
    {
        a[0]=53;
        a[1]=1;  
        a[2]=12; 
        a[3]=2;  
        a[4]=12; 
        a[5]=3;  
        a[6]=12; 
        a[7]=4;  
        a[8]=12; 
        a[9]=5;  
        a[10]=12;
        a[11]=6; 
        a[12]=12;
        a[13]=7; 
        a[14]=12;
        a[15]=8; 
        a[16]=12;
        a[17]=9;
        a[18]=12;
        a[19]=10;
        a[20]=12;
        a[21]=11;
        a[22]=12;
        a[23]=12;
        a[24]=12;
        a[25]=13;
        a[26]=12;
        a[27]=14;
        a[28]=12;
        a[29]=15;
        a[30]=12;
        a[31]=16;
        a[32]=12;
        a[33]=17;
        a[34]=12;
        a[35]=18;
        a[36]=12;
        a[37]=19;
        a[38]=12;
        a[39]=20;
        a[40]=12;
        a[41]=21;
        a[42]=12;
        a[43]=22;
        a[44]=12;
        a[45]=23;
        a[46]=12;
        a[47]=24;
        a[48]=12;
        a[49]=25;
        a[50]=12;
        a[51]=26;
        a[52]=12;
        a[53]=27;
        a[54]=12;
        a[55]=28;
        a[56]=12;
        a[57]=29;
        a[58]=12;
        a[59]=30;
        a[60]=12;
        a[61]=37;
        a[62]=1; 
        a[63]=37;
        a[64]=2; 
        a[65]=37;
        a[66]=3; 
        a[67]=37;
        a[68]=4; 
        a[69]=37;
        a[70]=5; 
        a[71]=37;
        a[72]=6; 
        a[73]=37;
        a[74]=7; 
        a[75]=37;
        a[76]=8; 
        a[77]=58;
        a[78]=15;
        a[79]=57;
        a[80]=15;
        a[81]=56;
        a[82]=15;
        a[83]=55;
        a[84]=15;
        a[85]=54;
        a[86]=15;
        a[87]=53;
        a[88]=15;
        a[89]=52;
        a[90]=15;
        a[91]=51;
        a[92]=15;
        a[93]=50;
        a[94]=15;
        a[95]=49;
        a[96]=15;
        a[97]=48;
        a[98]=15;
        a[99]=47;
        a[100]=15;
        a[101]=46;
        a[102]=15;
        //mau sac
        a[103]=13;
        a[104]=13;
        //so diem can dat;
        a[105]=10;
        //toc do
        a[106]=60;
    }
    if(level==5)
    {
        a[0]=62;
        a[1]=15; 
        a[2]=7;  
        a[3]=16; 
        a[4]=7;  
        a[5]=17; 
        a[6]=7;  
        a[7]=18; 
        a[8]=7;  
        a[9]=19; 
        a[10]=7; 
        a[11]=20;
        a[12]=7; 
        a[13]=21;
        a[14]=7; 
        a[15]=22;
        a[16]=7; 
        a[17]=23;
        a[18]=7;
        a[19]=24;
        a[20]=7;
        a[21]=25;
        a[22]=7;
        a[23]=26;
        a[24]=7;
        a[25]=27;
        a[26]=7;
        a[27]=28;
        a[28]=7;
        a[29]=29;
        a[30]=7;
        a[31]=30;
        a[32]=7;
        a[33]=31;
        a[34]=7;
        a[35]=32;
        a[36]=7;
        a[37]=33;
        a[38]=7;
        a[39]=34;
        a[40]=7;
        a[41]=35;
        a[42]=7;
        a[43]=36;
        a[44]=7;
        a[45]=37;
        a[46]=7;
        a[47]=38;
        a[48]=7;
        a[49]=39;
        a[50]=7;
        a[51]=40;
        a[52]=7;
        a[53]=41;
        a[54]=7;
        a[55]=42;
        a[56]=7;
        a[57]=43;
        a[58]=7;
        a[59]=44;
        a[60]=7;
        a[61]=15;
        a[62]=14;
        a[63]=16;
        a[64]=14;
        a[65]=17;
        a[66]=14;
        a[67]=18;
        a[68]=14;
        a[69]=19;
        a[70]=14;
        a[71]=20;
        a[72]=14;
        a[73]=21;
        a[74]=14;
        a[75]=22;
        a[76]=14;
        a[77]=23;
        a[78]=14;
        a[79]=24;
        a[80]=14;
        a[81]=25;
        a[82]=14;
        a[83]=26;
        a[84]=14;
        a[85]=27;
        a[86]=14;
        a[87]=28;
        a[88]=14;
        a[89]=29;
        a[90]=14;
        a[91]=30;
        a[92]=14;
        a[93]=31;
        a[94]=14;
        a[95]=32;
        a[96]=14;
        a[97]=33;
        a[98]=14;
        a[99]=34;
        a[100]=14;
        a[101]=35;
        a[102]=14;
        a[103]=36;
        a[104]=14;
        a[105]=37;
        a[106]=14;
        a[107]=38;
        a[108]=14;
        a[109]=39;
        a[110]=14;
        a[111]=40;
        a[112]=14;
        a[113]=41;
        a[114]=14;
        a[115]=42;
        a[116]=14;
        a[117]=43;
        a[118]=14;
        a[119]=44;
        a[120]=14;
        //mau sac
        a[121]=12;
        a[122]=12;
        //so diem can dat;
        a[123]=10;
        //toc do
        a[124]=50;
    }
    if(level==6)
    {
        a[0]=43;
        a[1]=15; 
        a[2]=5;  
        a[3]=16; 
        a[4]=5;  
        a[5]=17; 
        a[6]=5;  
        a[7]=18; 
        a[8]=5;  
        a[9]=19; 
        a[10]=5; 
        a[11]=20;
        a[12]=5; 
        a[13]=21;
        a[14]=5; 
        a[15]=22;
        a[16]=5; 
        a[17]=23;
        a[18]=5;
        a[19]=24;
        a[20]=5;
        a[21]=25;
        a[22]=5;
        a[23]=26;
        a[24]=5;
        a[25]=27;
        a[26]=5;
        a[27]=28;
        a[28]=5;
        a[29]=29;
        a[30]=5;
        a[31]=30;
        a[32]=5;
        a[33]=31;
        a[34]=5;
        a[35]=32;
        a[36]=5;
        a[37]=33;
        a[38]=5;
        a[39]=34;
        a[40]=5;
        a[41]=35;
        a[42]=5;
        a[43]=36;
        a[44]=5;
        a[45]=37;
        a[46]=5;
        a[47]=38;
        a[48]=5;
        a[49]=39;
        a[50]=5;
        a[51]=40;
        a[52]=5;
        a[53]=41;
        a[54]=5;
        a[55]=42;
        a[56]=5;
        a[57]=43;
        a[58]=5;
        a[59]=44;
        a[60]=5;
        a[61]=30;
        a[62]=5; 
        a[63]=30;
        a[64]=6; 
        a[65]=30;
        a[66]=7; 
        a[67]=30;
        a[68]=8; 
        a[69]=30;
        a[70]=9; 
        a[71]=30;
        a[72]=10;
        a[73]=30;
        a[74]=11;
        a[75]=30;
        a[76]=12;
        a[77]=30;
        a[78]=13;
        a[79]=30;
        a[80]=14;
        a[81]=30;
        a[82]=15;
        //mau sac
        a[83]=11;
        a[84]=11;
        //so diem can dat;
        a[85]=10;
        //toc do
        a[86]=50;
    }
    level++;
}
void ManChoiHienDai(short a[])
{   
    SinhMan(a);
    int i=1;
    int count=a[0]-2;
    SetColor(a[a[0]*2-3],a[a[0]*2-2]);
    while(true)
    {
        if(count==0){
            SetColor(0,7);
            return;
    }     
        GoTo(a[i],a[i+1]);
        cout<<" ";
        i=i+2;
        count--;
    }
}
bool ChuongNgaiVat(short a[], short Xhead, short Yhead)
{
    int count=a[0]-2;
    int i=1;
    bool check=false;
    while(true)
    {
        if(count==0)
            break;
        if(Xhead==a[i] && Yhead==a[i+1])
        {
            check=true;
            break;
        }
        i=i+2;
        count--;
    }
    if(check==true)
        return true;
    else
        return false;
}

void ChuyenMan(short level)
{
    system("cls");
    rectangle(60,20);
    GoTo(25,8);
    cout<<"Man "<<level<<">>>";
    RanNguSac(23,8);
    Sleep(350);
    XoaChuRanNho(23,8,8);
}
void end()
{
	for(int i=0; i<20; i++)
	{
		system("cls");
		GoTo(40,5);
		SetColor(0,6);
		cout<<" Game Over "<<endl;
		Sleep(50);
		GoTo(40,5);
		SetColor(0,1);
    	cout<<" Game Over "<<endl;
		SetColor(0,2);
		GoTo(32,6);
		Sleep(50);
		cout<<" Thank to play my game!!! "<<endl;
		SetColor(0,5);
		Sleep(50);
		GoTo(32,6);
		cout<<" Thank to play my game!!! "<<endl;
		Sleep(50);
	}
    return;
}
