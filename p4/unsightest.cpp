#include <iostream>

using namespace std;

int main(){

//unsigned char array[7]={'a','b','c','d','e','f','g'};

//cout<<"array[0]:"<<(unsigned int)array[0]<<endl;
//cout<<"array[1]:"<<(unsigned int)array[1]<<endl;
//cout<<"array[2]:"<<(unsigned int)array[2]<<endl;
//cout<<"array[3]:"<<(unsigned int)array[3]<<endl;
//cout<<"array[4]:"<<(unsigned int)array[4]<<endl;
//cout<<"array[5]:"<<(unsigned int)array[5]<<endl;
//cout<<"array[6]:"<<(unsigned int)array[6]<<endl;
//unsigned char* pt=array;
//(*(unsigned int*)(pt+2))=((*(unsigned int*)(pt+2))>>2);
//cout<<"(*(unsigned int*)pt):"<< (*(unsigned int*)pt)<<endl;
//cout<<"(unsigned int*)array[0]:"<<((unsigned int)array[0])<<endl;
//cout<<"(unsigned int*)array[1]:"<<((unsigned int)array[1])<<endl;
//cout<<"(unsigned int*)array[2]:"<<((unsigned int)array[2])<<endl;
//cout<<"(unsigned int*)array[3]:"<<((unsigned int)array[3])<<endl;
//cout<<"(unsigned int*)array[4]:"<<((unsigned int)array[4])<<endl;
//cout<<"(unsigned int*)array[5]:"<<((unsigned int)array[5])<<endl;
//cout<<"(unsigned int*)array[6]:"<<((unsigned int)array[6])<<endl;

//char k='1';
//cout<<(int)k<<endl;
//cout<<((unsigned int)k<<26);

////unsigned int puss=1;
////cout<<"puss >> 0:"<<puss<<endl;
//
//unsigned char array[10]={0};
//
////k has code 1001100011
//
//unsigned int code = 121 << 24;
//  
// *((unsigned int *)&array[0]) |= code;
//
//for(int i=0;i<5;i++)
//{
//cout<<"array["<<i<<"]:"<<array[i]<<endl;
//}
//
//}
unsigned int k =0x12345678;

for(int i=0;i<4;i++){
    cout<<hex;
cout<<((unsigned char *)&k)[i]<<" ";
}
cout<<endl;
cout<<(((unsigned char *)&k)[0] & 64);

k <<= 1 ;

for(int i=0;i<4;i++){
    cout<<hex;
cout<<((unsigned char *)&k)[i]<<" ";
}
cout<<endl;

}

