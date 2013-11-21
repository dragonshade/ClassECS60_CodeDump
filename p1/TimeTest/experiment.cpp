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
using namespace std;

int main(void){
char* filename="File1.dat";
ifstream in(filename);
if(!in) {   //Error checking
    cout<<"Failed to open file.\n";
}

in.ignore(1000,'\n');
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
            if(!stL.pop())
               exit;
            break;
    }
   
}

in.close();

}
