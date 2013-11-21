#ifndef _HEAPOBJ_H_INCLUDED
#define _HEAPOBJ_H_INCLUDED

class HeapObj{
    public:
    HeapObj(unsigned int i, unsigned int d);
    HeapObj();
    unsigned int index;
    unsigned int dist;
};

#endif