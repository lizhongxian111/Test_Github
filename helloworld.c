# include <stdio.h>

int main(int argc, char* argv[])
{
  printf("Hello world!\n");
  return 1;
}
==========================================================================================
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
==========================================================================================
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
==========================================================================================
//@brief evaluate the log2 of the integer value, rounding to the highest 1 bit
static inline u32 UTIL_Log2(u32 wVal)
{
    static const u32 pos[32] = {0, 1, 28, 2, 29, 14, 24, 3,     
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
==========================================================================================
//use "-wrap" when compiling,then when calling func(). It will call __wrap_func() if __wrap_func() is defined, OW will call __real_func() if not.
#define FUNC_REDEFINE(func)                                  \
extern void __real_##func(void* param);                   \
void __wrap_##func(void* param)                           \
{																		\
	assert(is_safe_to_call_func());										\	
	__real_##func(param);												\
}	
==========================================================================================
const int MultiplyDeBruijnBitPosition[32] = 
{
  0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
  8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
};
/*******************************************************************************
                            Local Function Prototypes
 ******************************************************************************/
//Utility function that use the DeBrujin Algorithm to find the first bit set into a word
static INLINE uint8_t GetFirstValidBit(uint32_t numberToExamine)
{
	uint32_t result;      // result goes here

    numberToExamine |= numberToExamine >> 1; // first round down to one less than a power of 2
    numberToExamine |= numberToExamine >> 2;
    numberToExamine |= numberToExamine >> 4;
    numberToExamine |= numberToExamine >> 8;
    numberToExamine |= numberToExamine >> 16;

    result = MultiplyDeBruijnBitPosition[(uint32_t)(numberToExamine * 0x07C4ACDDU) >> 27];
    return (uint8_t) (31 - result);
}
==========================================================================================
// round up
#define ROUND_UP(a,b)               (((a) + (b) - 1) / (b))
#define ROUND_UP_2_POW(a, b, logb)  (((a) + (b) - 1) >> (logb))
// mod2 bitwise
#define MOD2(x)             ((x) - 1)
==========================================================================================
#define LOG2_NUM  (NUM >> 1)  //it's OK when NUM=1,2,4
==========================================================================================
#define LOG_MK_VALUE(x)            # x

#define LOG_WARN(format, args...)     if(LOG_LVL<=LOG_LVL_ERROR) {LOG_PRINTTIMESTAMP();LOG_PRINTF("[" LOG_MK_VALUE(LOG_MODULE_NAME) "][WARN] "  format, ##args);}
//LOG_PRINTF() will be defined to use the standard lib func.
==========================================================================================
//analyze test result using windows cmd.
TEST_RESULT=`find TestLog/*.csv | xargs grep FAIL`
TIME_OUT_CHECK=`find TestLog/*.csv | xargs grep TIMEOUT`

if [ "$TEST_RESULT" == "" -a "$TIME_OUT_CHECK" == "" ]
then
    echo -e "\033[30;42mBCI Test cases pass!\033[0m"
    exit 0
else
    echo -e "\033[31mBCI Test cases fail!\033[0m"
    echo -e "\033[31m$TEST_RESULT\033[0m"
    echo -e "\033[31m$TIME_OUT_CHECK\033[0m"
    exit 1
fi
==========================================================================================
typedef uint16_t Index_t;
typedef uint16_t ListID_t;

typedef struct _DListPointer_t
{
    Index_t hPrev; // Used also as Tail
    Index_t hNext; // Used also as Head
}  DListPointer_t;

typedef struct tSListHeader
{
    void*          pArray;
    tSListPointer* psListHeads;
    ListID_t        hNumLists;
    Index_t         hNumElements;
} tSListHeader;

void SList_Init( tSListHeader* ptListHeader , void* pArray, tSListPointer* psListHeads,
                        Index_t hNumElements, ListID_t hNumLists, ListID_t hListID)
{
    ptListHeader->pArray       = pArray;
    ptListHeader->psListHeads  = psListHeads;
    ptListHeader->hNumLists    = hNumLists; 
    ptListHeader->hNumElements = hNumElements; 

    SList_Reset(ptListHeader, hListID);
} 
void SList_Reset( tSListHeader* ptListHeader, ListID_t hListID)
{
    uint16_t hNdx;

    // Clear all the lists
    Gmemset((void*) ptListHeader->psListHeads, 0xFF, ptListHeader->hNumLists * sizeof(tSListPointer));

    if (NO_LIST == hListID)
    {
        // All elements are out of a list

        for  (hNdx = 0; hNdx < ptListHeader->hNumElements; hNdx++)
        {
            SList_ClearPointer(ptListHeader, hNdx);
        }
    }
    else
    {
        // All elements are in a list

        // Set the starting list with head and tail to the 1st and last element, respectively
        ptListHeader->psListHeads[hListID] = 0;

        // Push all the elements in the list one by one
        for  (hNdx = 0; hNdx <= ptListHeader->hNumElements-2; hNdx++)
        {
            SList_SetPointer(ptListHeader, hNdx, hNdx+1);
        }

        /* Tail Pointer */
        SList_SetPointer(ptListHeader, ptListHeader->hNumElements-1, NO_ELEMENT);
    }
}

void SList_SetPointer(tSListHeader* ptListHeader, Index_t hIndex, Index_t hNext)
{
    ((tSListPointer*) ptListHeader->pArray )[ hIndex ] = hNext;
}

void SList_ClearPointer(tSListHeader* ptListHeader, Index_t hIndex)
{
    SList_SetPointer(ptListHeader, hIndex, FREE_ELEMENT);
}
==========================================================================================


