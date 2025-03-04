#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255
// MACROS LIST:
#define ALLOC_ERROR_RETURN() \
    printf("Allocation error\n"); \
    return 0;

#define IF_NOT_NULL_FREE(pObj) \
    if(pObj != NULL) \
        free(pObj);

#define PRINT_ERROR_STR_RETURN_0(str) \
    printf("Error: %s\n", str); \
    return 0;

char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size, FILE* source);
char* getDynStr(char* str);
char** splitCharsToWords(char* str, int* pCount, int* pTotalLength);

void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));
int getRandomInt(int min, int max);

#endif