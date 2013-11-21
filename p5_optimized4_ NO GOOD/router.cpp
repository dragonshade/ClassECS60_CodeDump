//Ran Xie
#include "TripsRunner.h"
#include "router.h"

////////////////////////////////////////////////////////////////
//        CONSTRUCTOR PARSING INFO FROM FLIGHTS ARRAY         //
////////////////////////////////////////////////////////////////
Router::Router(int numCities, int numFlights, Flight *flights)
{
      for(int k=0;k<5701;k++) {vArray[k]=0;}
      int eArraySize=4*numFlights/numCities;
      nCities=numCities;
      nFlights=numFlights;
      arrayOfCities=new int[nCities];  //initialize tally of cities
     // for(int i=0;i<numCities;i++){arrayOfCities[i]=5700;}
      //vArray[5700]=new Vertex(5700);
      
    for(int i=0;i<numFlights;i++)
  {
      
      if(vArray[flights[i].originIndex]==0) //If the vertex has not been created
      { vArray[flights[i].originIndex]=new Vertex(flights[i].originIndex,eArraySize);
        arrayOfCities[i]=flights[i].originIndex; //keep tally of cities
      }
      
      vArray[flights[i].originIndex]->eArray[vArray[flights[i].originIndex]->eArrayIndex]= new Edge(flights[i].destinationIndex,flights[i].departureTime,flights[i].duration,flights[i].originIndex,flights[i].flightNum);
      //vArray[flights[i].originIndex]->insertAdj(sV);
      vArray[flights[i].originIndex]->eArrayIndex++;
       }
 
 
  
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
    int flightSeq[50];
    int numFlights=0;
    int index=trip->destinationIndex;
    while(index!=trip->originIndex)
    {
      //std::cout<<index<<"("<<vArray[index]->dist<<")"<<"->";
      flightSeq[numFlights]=vArray[index]->pv; //set flight num (from last to first)
      index=vArray[index]->previous; //step backward
      numFlights++; //count flight numbers
      
    }
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
inline unsigned int Router::calCost(Vertex* pivot, Edge* pt)
{
      int arrival_time=pivot->clock%1440;   //This gives arrival time at this pivot airport
          int gap=pt->departureTime-arrival_time;
          if(gap <0) {gap=(1440+gap);}
  
             if(gap >=30) //we don't miss the plane in this case
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
inline unsigned int Router::calCostOrigin(Vertex* origin, Edge* pt)
{

       int gap=pt->departureTime-(origin->clock%1440);
          if(gap <0) {gap=(unsigned int)(1440+gap);}
      //return modularMinus(pt->departureTime,origin->clock%1440)+pt->duration;
      return gap+pt->duration;
}

////////////////////////////////////////////////////////////////
//    DIJKSTRA(START, GOAL) and TERMINATE WHEN GOAL IS KNOWN  //
////////////////////////////////////////////////////////////////
void Router::Dijkstra(Vertex* start, Vertex* goal){
      //Initialized Minheap
      BinaryHeap heap(nFlights);
      unsigned int newCost;
      for(int k=0;k<start->eArrayIndex;k++)
      {
          newCost=calCostOrigin(start,start->eArray[k]);
          //we update the cost if it is smaller
         if(newCost< vArray[start->eArray[k]->index]->dist)
        {
          vArray[start->eArray[k]->index]->dist=newCost;
          vArray[start->eArray[k]->index]->pv = start->eArray[k]->edgeNum; //denote previous vertice using previous edge/flight num
          vArray[start->eArray[k]->index]->previous=start->index; //set previous vertice
          //Dump the (vertice, dist) pairs into the heap;
    
          HeapObj* temp= new HeapObj(start->eArray[k]->index, newCost); //push each updated vertex dist pair into the heap
          heap.insert(temp);
        }
          
      }
       
  
  do{
       //FIND MINIMUM DISTANCE IN UNKNOWN VERTICES MARK AS KNOW
       HeapObj* minUnknown=FindMinUnknown(heap);
       vArray[minUnknown->index]->known=true;
       
       
       //
       
       //clocktime at new pivot is equal to trip departuretime + the dist(duration of travel)
       vArray[minUnknown->index]->clock=start->clock+vArray[minUnknown->index]->dist;

       
        for(int k=0;k<vArray[minUnknown->index]->eArrayIndex;k++)
       {
            if(!vArray[vArray[minUnknown->index]->eArray[k]->index]->known)  //do the following only to unknown adjacent vertex
           {
            newCost=calCost(vArray[minUnknown->index],vArray[minUnknown->index]->eArray[k]);
            //if this Total_cost is less than the cost update
            if(newCost< vArray[vArray[minUnknown->index]->eArray[k]->index]->dist)
            {
               vArray[vArray[minUnknown->index]->eArray[k]->index]->dist=newCost;
               vArray[vArray[minUnknown->index]->eArray[k]->index]->pv = vArray[minUnknown->index]->eArray[k]->edgeNum; //denote previous vertice using previous edge/flight num
               vArray[vArray[minUnknown->index]->eArray[k]->index]->previous=minUnknown->index; //Set previous vertice index
               HeapObj* temp= new HeapObj(vArray[minUnknown->index]->eArray[k]->index, newCost); //push each updated vertex dist pair into the heap
               heap.insert(temp);
            }
           }
            
       }
    }while(!goal->known);
}


////////////////////////////////////////////////////////////////
//            FINDING MINIMUM UNKNOWN DISTANCE                //
////////////////////////////////////////////////////////////////
inline HeapObj* Router::FindMinUnknown(BinaryHeap &heap){

      while(vArray[(heap.findMin())->index]->known)
      {   //while the min vertex is unknown, we ignore it and keep popping
            heap.deleteMin();
      }      
      return heap.findMin();
}

//////////////////////////////////////////////////////////////////
//          RESET VERTEX BACK TO ORIGINAL STATE                 //
//////////////////////////////////////////////////////////////////
inline void Router::reset(){
      
      for(int i = 0 ; i<nCities;i++)
      {
  
            vArray[arrayOfCities[i]]->known=0;
            vArray[arrayOfCities[i]]->dist=-1;
            //vArray[i]->pv=-1;
            //vArray[i]->previous=-1;
            //vArray[i]->clock=0;
  
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