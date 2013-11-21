#ifndef __ENCODING_MASK_H_INCLUDED__
#define __ENCODING_MASK_H_INCLUDED__

class Encoding{
 public:
    unsigned char key;
    int length;
    unsigned int code;
    int count;
};

class  Mask{
 public:
    unsigned int shifted_code;
};

#endif
