//Ran Xie
#ifndef ROUTER_H
#define	ROUTER_H

#include "TripsRunner.h"
#include "BinaryHeap.h"
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//   Vertex1->Edge11->Edge12-> Edge13-> .....
//   Vertex2->Edge22->Edge23->.......
//
//   Vertex->pv = previous edge (flight number connecting previous vertice)
//
//////////////////////////////////////////////////////////////////////////////


class Edge{
    public:
    Edge(unsigned in, unsigned int de, unsigned int du,unsigned int ori,unsigned int flightNum)
    {
        index = in;
        departureTime=de;
        duration=du;
        //dv=-1;
        origin=ori;
        next=0;
        edgeNum=flightNum;
    }
    unsigned int index;
    unsigned int origin;
    unsigned int departureTime;
    unsigned int duration;
   // unsigned int dv;
    unsigned int edgeNum;
    Edge* next;
};


class Vertex{
    public:
    Vertex(unsigned int in)
    {
       index=in;
       known=0;
       dist=-1;
       first=0;
       pv=-1;
       previous=-1;
       clock=0;
    }
        
    void insertAdj(Edge* obj)
    {
      // if(!findDuplicate(obj)) //If no duplicate insert.
      // {
         obj->next=first;
         first=obj;
      // }
    }
    
    bool findDuplicate(Edge* obj)  //True if duplicate is found
    {
        Edge* pt;
        pt=first;
        if(pt!=0)
      {
        while(pt->next!=0)
        {
            if(pt->index==obj->index) //same index implies duplicate
            {return true;}
            pt=pt->next;
        }
      }
        return false;
    }
    
    unsigned int index;
    Edge* first;
    bool known;
    unsigned int dist;
    unsigned int pv; //previous flight/edge num (flight num)
    unsigned int previous;
    unsigned int clock;
};



class Router
{
public:
    Router(int numCities, int numFlights, Flight *flights) ;
    void findRoute(const Trip* trip, Itinerary *itinerary);
    void Dijkstra(Vertex* start, Vertex* goal);
   inline unsigned int calCost(Vertex* pivot, Edge* pt);
   inline unsigned int calCostOrigin(Vertex* origin, Edge* pt);
    HeapObj* FindMinUnknown(BinaryHeap &heap);
    unsigned int modularMinus(int x, int y);
    unsigned int modularAdd(unsigned int x, unsigned int y);
    void reset();
    ~Router()
    {
         for(int i = 0 ; i<nCities;i++)
      {
  
            Edge* pt = vArray[arrayOfCities[i]]->first;
            while(pt!=0)
            {
                Edge* next= pt->next;
                delete pt;
                pt= next;
            }
        delete vArray[arrayOfCities[i]];
  
      }
        
    }
  
    int nCities;
    int nFlights;
    Vertex* vArray[5700];  //the last one is safe guard
    int* arrayOfCities;

};

#endif	/* ROUTER_H */

