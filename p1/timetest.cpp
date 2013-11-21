#include "CPUTimer.h"
#include "CursorList.h"
#include "LinkedList.h"
#include "StackAr.h"
#include "QueueAr.h"
#include "StackLi.h"
#include "vector.h"
#include "SkipList.h"
#include <iostream>
#include <fstream>
vector<CursorNode <int> > cursorSpace(250000);

using namespace std;

int Capacity=250001;

void RunList(char* filename);
void RunCursorList(char* filename);
void RunStackAr(char* filename);
void RunStackLi(char* filename);
void RunQueueAr(char* filename);
void RunSkipList(char* filename);
int getChoice(void);

int main(void){
   char filename[15];
   cout<<"Filename >> ";
   cin>>filename;
   cout<<endl;
   cout<<endl;

int choice;
CPUTimer ct;

  do
    {

        choice=getChoice();
        ct.reset();

        switch (choice)
        {
            case 1: RunList(filename); break;
            case 2: RunCursorList(filename); break;
            case 3: RunStackAr(filename); break;
            case 4: RunStackLi(filename); break;
            case 5: RunQueueAr(filename); break;
            case 6: RunSkipList(filename); break;

        }

     cout << "CPU time: " << ct.cur_CPUTime() << endl;

    }while(choice>0);

}

//********************************************
//********GETCHOICE***************************
//********************************************

int getChoice(void){
    int choice;
    cout<<"\t ADT Menu \n";
    cout<<"0. Quit\n";
    cout<<"1. LinkedList\n";
    cout<<"2. CursorList\n";
    cout<<"3. StackAr\n";
    cout<<"4. StackLi\n";
    cout<<"5. QueueAr\n";
    cout<<"6. SkipList\n";
    cout<<"Your choice >> ";
    cin>>choice;
    return choice;}

//********************************************
//********RUNLIST*****************************
//********************************************

void RunList(char* filename){

ifstream in(filename);
if(!in) {   //Error checking
    cout<<"Failed to open file.\n";
}

in.ignore(10000,'\n');
char CmdChar;
int integer;
List<int> LL;
ListItr<int> itr=LL.zeroth();

while(!in.eof())
{
  in>> CmdChar >> integer;
   switch(CmdChar)
   {
       case 'i':   //Insert
            LL.insert(integer,itr);
            break;
       case 'd':   //delete
            LL.remove(integer);
            break;
    }
}
in.close();
}

//********************************************
//***************RunCursorList****************
//********************************************
void RunCursorList(char* filename){
ifstream in(filename);
if(!in) {   //Error checking
    cout<<"Failed to open file.\n";
}

in.ignore(10000,'\n');
char CmdChar;
int integer;
CursorList<int> Clist(cursorSpace);
CursorListItr<int> Clitr=Clist.zeroth();

while(!in.eof())
{
  in>> CmdChar >> integer;
  switch(CmdChar)
   {
       case 'i':   //Insert
	    Clist.insert(integer,Clitr); 	
            break;
       case 'd':   //delete
	    Clist.remove(integer);	
            break;
    }

}

in.close();
}

//********************************************
//********RUNSTACKAR**************************
//********************************************
void RunStackAr(char* filename){
ifstream in(filename);
if(!in) {   //Error checking
    cout<<"Failed to open file.\n";
}

in.ignore(10000,'\n');
char CmdChar;
int integer;
StackAr<int> stA(Capacity);

while(!in.eof())
{
  in>> CmdChar >> integer;
  switch(CmdChar)
   {
       case 'i':   //Insert
            stA.push(integer);
            break;
       case 'd':   //delete
            if(!stA.isEmpty()) {stA.pop();}
            break;
    }

}
in.close();
}

//********************************************
//**************RUNSTACKLI********************
//********************************************
void RunStackLi(char* filename){
ifstream in(filename);
if(!in) {   //Error checking
    cout<<"Failed to open file.\n";
}

in.ignore(10000,'\n');
char CmdChar;
int integer;
StackLi<int> stL;

while(!in.eof())
{
  in>> CmdChar >> integer;
  switch(CmdChar)
   {
       case 'i':   //Insert
            stL.push(integer);
            break;
       case 'd':   //delete
            if(!stL.isEmpty()){stL.pop();}
            break;
    }

}

in.close();
}

//********************************************
//***************RUNQUEUEAR*******************
//********************************************
void RunQueueAr(char* filename){
ifstream in(filename);
if(!in) {   //Error checking
    cout<<"Failed to open file.\n";
}

in.ignore(10000,'\n');
char CmdChar;
int integer;
Queue<int> Q(Capacity);

while(!in.eof())
{
  in>> CmdChar >> integer;
  switch(CmdChar)
   {
       case 'i':   //Insert
            Q.enqueue(integer);
            break;
       case 'd':   //delete
            if(!Q.isEmpty()){Q.dequeue();}
            break;
    }

}
in.close();
}

//********************************************
//****************RunSkipList*****************
//********************************************
void RunSkipList(char* filename){
ifstream in(filename);
if(!in) {   //Error checking
    cout<<"Failed to open file.\n";
}

in.ignore(10000,'\n');
char CmdChar;
int integer;
SkipList<int> Slist(0,250000);

while(!in.eof())
{
  in>> CmdChar >> integer;
  switch(CmdChar)
   {
       case 'i':   //Insert
	    Slist.insert(integer);
            break;
       case 'd':   //delete
	bool temp;
	 temp=Slist.deleteNode(integer);
            break;
    }

}
in.close();
}
