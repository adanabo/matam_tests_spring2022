#include <string.h>
#include "../RLEList.h"
#include "AsciiArtTool.h"

#define FIRST_FLAG "-i"
#define SECOND_FLAG "-e"
#define FIRST_ARGUMENT 1
#define SECOND_ARGUMENT 2
#define THIRD_ARGUMENT 3
#define TOTAL_ARGUMENTS 4
#define SPACE ' '
#define AT '@'

char swappingSymbols(char symbol)
{
    if(symbol==AT)
    {
        return SPACE;

    }
    if(symbol==SPACE)
    {
        return AT;

    }
    return 0;

}
int main(int argc , char** argv) {
    if(argc != TOTAL_ARGUMENTS)
    {
        return 0;

    }
    FILE* source = fopen(argv[SECOND_ARGUMENT] , "r");
    if(!source)
    {
        return 0;
    }

    FILE* target = fopen(argv[THIRD_ARGUMENT] , "w");
    if(!target)
    {
        return 0;
    }

    if(strcmp(argv[FIRST_ARGUMENT] , SECOND_FLAG)==0)
    {
        RLEList list = asciiArtRead(source);
        if(list != NULL)
        {
            asciiArtPrintEncoded(list,target);
        }
        RLEListDestroy(list);
    }
    if(strcmp(argv[FIRST_ARGUMENT], FIRST_FLAG)==0){
        RLEList list = asciiArtRead(source);
        if(list!=NULL)
        {
            RLEListMap(list,swappingSymbols);
            asciiArtPrint(list,target);
        }
        RLEListDestroy(list);
    }
    fclose(source);
    fclose(target);
    return 0;
}