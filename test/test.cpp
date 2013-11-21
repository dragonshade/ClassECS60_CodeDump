#include <iostream>
using namespace std;
int main(){
 unsigned int CityN=1234;
 unsigned int dist=8000;

  CityN = (CityN << 16);
  unsigned int Obj = (CityN | dist);

    cout<<"CityN:"<<  (Obj>>16) <<endl;
    cout<<"dist:"<< (unsigned short)Obj<<endl;



}
