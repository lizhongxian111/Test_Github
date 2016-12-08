# include <stdio.h>

int main(int argc, char* argv[])
{
  printf("Hello world!\n");
  return 1;
}
=====================================================================================================================================
//@brief evaluate the log2 of the integer value, rounding to the highest 1 bit
static inline uint32_t UTIL_Log2(uint32_t wVal)
{    
  static const uint32_t pos[32] = {0, 1, 28, 2, 29, 14, 24, 3,             
                                   30, 22, 20, 15, 25, 17, 4, 8, 31, 27, 13, 23, 21, 19,             
                                   16, 7, 26, 12, 18, 6, 11, 5, 10, 9};      
  wVal |= wVal >> 1;      
  wVal |= wVal >> 2;       
  wVal |= wVal >> 4;       
  wVal |= wVal >> 8;       
  wVal |= wVal >> 16;       
  wVal = (wVal >> 1) + 1;         
  return pos[(wVal * 0x077CB531UL) >> 27]; 
}
====================================================================================================================================
//Search the least significate bit which has been set in bitmap, no matter the input bitmap is Uint32, Uint16 or Uint8. 
uint8_t DM_LSB(uint32_t bitmap, uint8_t typeWidth)
{    
  FTL_ASSERT(8 == typeWidth || 16 == typeWidth || 32 == typeWidth);    
  if (0 == bitmap)    
  {        
    Gprint("bitmap is 0\n");        
    return UINT8_MAX;    
  }    
  bitmap <<= (32 - typeWidth);   
  uint8_t middlePosition = typeWidth >> 1;    
  uint8_t bitPosition = 0;   
  //LSB    
  while(middlePosition)   
  {        
    if ( 0 == (bitmap << middlePosition))        
    {             
      bitPosition += middlePosition;        
    }        
    else        
    {            
      bitmap <<= middlePosition;        
    }            
    middlePosition >>= 1;       
  }   
  return bitPosition;
}
====================================================================================================================================





