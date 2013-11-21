//Ran Xie
#include "TripsRunner.h"
#include "router.h"

////////////////////////////////////////////////////////////////
//        CONSTRUCTOR PARSING INFO FROM FLIGHTS ARRAY         //
////////////////////////////////////////////////////////////////
Router::Router(int numCities, int numFlights, Flight *flights)
{
      for(int k=0;k<5700;k++) {vArray[k]=0;}
      nCities=numCities;
      nFlights=numFlights;

    for(int i=0;i<numFlights;i++)
  {
      if(vArray[flights[i].originIndex]==0) //If the vertex has not been created
      { vArray[flights[i].originIndex]=new Vertex(flights[i].originIndex);}
      
      Edge* sV= new Edge(flights[i].destinationIndex,flights[i].departureTime,flights[i].duration,flights[i].originIndex,flights[i].flightNum);
      vArray[flights[i].originIndex]->insertAdj(sV);
  }
  
  //for(int i=0;i<5700;i++)
  //{
  //    if(vArray[i]!=0)
  //    {
  //      std::cout<<"Vertex Index: "<<vArray[i]->index<<std::endl;
  //      Edge* pt=vArray[i]->first;
  //      std::cout<<"Edge index(departure,duration,flightNum"<<std::endl;
  //      while(pt)
  //      {
  //        std::cout<<pt->index<<"("<<pt->departureTime<<","<<pt->duration<<","<<pt->edgeNum<<")"<<"->";
  //          pt=pt->next;
  //      }
  //      std::cout<<std::endl;
  //    }
  // }
  
} // Router()

////////////////////////////////////////////////////////////////
//FIND ROUTE FOR A TRIP AND STORE FLIGHT# IN ITINERARY ARRAY  //
////////////////////////////////////////////////////////////////
void Router::findRoute(const Trip* trip, Itinerary *itinerary)
{
   //SET TRIP STARTING VERTEX, SET STARTING TIME
    vArray[trip->originIndex]->known=true;
    vArray[trip->originIndex]->dist=0; //here dist means time duration of travel
    vArray[trip->originIndex]->clock=(unsigned int)trip->departureTime; //clock keep track of clock time
    //Run Dijkstra
    Dijkstra(vArray[trip->originIndex], vArray[trip->destinationIndex]);
    
    //Storing flight squence
    int flightSeq[20];
    int numFlights=0;
    int index=trip->destinationIndex;
    while(index!=trip->originIndex)
    {
      //std::cout<<index<<"("<<vArray[index]->dist<<")"<<"->";
      flightSeq[numFlights]=vArray[index]->pv; //set flight num (from last to first)
      index=vArray[index]->previous; //step backward
      numFlights++; //count flight numbers
      
    }
    //std::cout<<endl;
    //cout<<endl;
    //Dump data into Itinerary struct
    itinerary->numFlights = (short)numFlights;
    for(int k=0;k<numFlights;k++)
    {
      itinerary->flightNums[k]=flightSeq[numFlights-k-1];
    }
    
    reset();
   
}  // findRoute


////////////////////////////////////////////////////////////////
//    COMPUTER DIST TO ADJACENT VERTEX STARTING AT NON ORIGIN //
////////////////////////////////////////////////////////////////
unsigned int Router::calCost(Vertex* pivot, Edge* pt)
{
      int arrival_time=pivot->clock%1440;   //This gives arrival time at this pivot airport
          // depart-localtime <30 is late
           unsigned int gap=modularMinus(pt->departureTime,arrival_time);
             if(gap >30) //we don't miss the plane in this case
            {
                 //return pivot->dist+gap+1440+pt->duration; 
                 return pivot->dist+gap+pt->duration;  
            }
            else { //gap <30 means we can't make it
                  return pivot->dist+gap+1440+pt->duration; // 
            }

}

////////////////////////////////////////////////////////////////
//    COMPUTE DIST TO ADJACENT VERTEX STARTING AT ORIGIN      //
////////////////////////////////////////////////////////////////
unsigned int Router::calCostOrigin(Vertex* origin, Edge* pt)
{
       int arrival_time=origin->clock%1440;   //This gives arrival time at this pivot airport

            return modularMinus(pt->departureTime,arrival_time)+pt->duration;

}

////////////////////////////////////////////////////////////////
//    DIJKSTRA(START, GOAL) and TERMINATE WHEN GOAL IS KNOWN  //
////////////////////////////////////////////////////////////////
void Router::Dijkstra(Vertex* start, Vertex* goal){
      //Initialized Minheap
      BinaryHeap<HeapObj> heap(nFlights);
      //std::cout<<"RUNNING DIJKSTRA"<<start->index<<'\n';
      //std::cout<<"start:"<<start->index<<'\n';
      //handle the start first
      Edge* pt=start->first;
      unsigned int newCost;
      while(pt!=0)
      {
          newCost=calCostOrigin(start,pt);
          //we update the cost if it is smaller
         if(newCost< vArray[pt->index]->dist)
        {
          vArray[pt->index]->dist=newCost;
          vArray[pt->index]->pv = pt->edgeNum; //denote previous vertice using previous edge/flight num
          vArray[pt->index]->previous=start->index; //set previous vertice
          //Dump the (vertice, dist) pairs into the heap;
          /////////////////////////////////
          //
          //std::cout<<"index: "<<pt->index<<'\n';
          //std::cout<<"new dist:  "<<vArray[pt->index]->dist<<'\n';
          //std::cout<<"previous index:"<< vArray[pt->index]->previous<<'\n';
          //std::cout<<"previous index:"<< vArray[pt->index]->clock<<'\n';
          
          ////////////////////////////
          HeapObj temp(pt->index, newCost); //push each updated vertex dist pair into the heap
          heap.insert(temp);
        }
          
          pt=pt->next; //move to the next
      }
  
       
      // std::cout<<"finished handling origin!"<<std::endl;
       
  
  do{
       //FIND MINIMUM DISTANCE IN UNKNOWN VERTICES MARK AS KNOW
       HeapObj minUnknown=FindMinUnknown(heap);
       vArray[minUnknown.index]->known=true;
       //
       
       //clocktime at new pivot is equal to trip departuretime + the dist(duration of travel)
       vArray[minUnknown.index]->clock=start->clock+vArray[minUnknown.index]->dist;
          //std::cout<<std::endl;
          //std::cout<<"index: "<<vArray[minUnknown.index]->index<<'\n';
          //std::cout<<"new dist:  "<<vArray[minUnknown.index]->dist<<'\n';
          //std::cout<<"previous index:"<< vArray[minUnknown.index]->previous<<'\n';
          //std::cout<<"clock:"<< vArray[minUnknown.index]->clock<<'\n';
          
       
       pt=vArray[minUnknown.index]->first;
       while(pt!=0)
       {
            if(!vArray[pt->index]->known)  //do the following only to unknown vertex
           {
            newCost=calCost(vArray[minUnknown.index],pt);
            //if this Total_cost is less than the cost update
            if(newCost< vArray[pt->index]->dist)
            {
               vArray[pt->index]->dist=newCost;
               vArray[pt->index]->pv = pt->edgeNum; //denote previous vertice using previous edge/flight num
               vArray[pt->index]->previous=minUnknown.index; //Set previous vertice index
               HeapObj temp(pt->index, newCost); //push each updated vertex dist pair into the heap
               heap.insert(temp);
            }
           }
            pt=pt->next;
            
       }
    }while(!goal->known);
}


////////////////////////////////////////////////////////////////
//            FINDING MINIMUM UNKNOWN DISTANCE                //
////////////////////////////////////////////////////////////////
HeapObj Router::FindMinUnknown(BinaryHeap<HeapObj> &heap){

      while(vArray[(heap.findMin()).index]->known)
      {   //while the min vertex is unknown, we ignore it and keep popping
            heap.deleteMin();
      }      
      return heap.findMin();
}

//////////////////////////////////////////////////////////////////
//          RESET VERTEX BACK TO ORIGINAL STATE                 //
//////////////////////////////////////////////////////////////////
void Router::reset(){
      
      for(int i = 0 ; i<5700;i++)
      {
        if(vArray[i]!=0)
        {
            vArray[i]->known=0;
            vArray[i]->dist=-1;
            vArray[i]->pv=-1;
            vArray[i]->previous=-1;
            vArray[i]->clock=0;
        }   
      }
      
}


////////////////////////////////////////////////////////////////
//            MODULAR ARITHEMTIC FOR COMPUTING TIME           //
////////////////////////////////////////////////////////////////
unsigned int Router::modularMinus(int x, int y)
{
      if( x-y <0)
      {
            return 1440+x-y;
      }
      else return x-y;
}

unsigned int Router::modularAdd(unsigned int x, unsigned int y)
{
      if( x+y<1440)
      {
            return x+y;
      }
      else { return x+y-1440;}
}