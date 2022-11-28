#include "../RLEList.h"
#include "AsciiArtTool.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

RLEList asciiArtRead(FILE* in_stream)
{
    if(in_stream == NULL)
    {
        return NULL;
    }

    RLEList list = RLEListCreate();
    if(list == NULL)
        return NULL;
    char c;
    while( fscanf(in_stream,"%c",&c)!=EOF )
    {
        RLEListAppend( list, c);
    }
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(list==NULL || out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }else
    {
        int size= RLEListSize(list);
        for (int i = 0; i <size ; ++i)
        {
            char character=RLEListGet( list, i, NULL);
            fprintf(out_stream,"%c",character);
        }
    }
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if (list==NULL||out_stream==NULL)
        return RLE_LIST_NULL_ARGUMENT;

    RLEListResult result;
    char* s = RLEListExportToString(list, &result);
    if(s == NULL)
        return result;
    fprintf(out_stream, "%s", s);
    free(s);
    return RLE_LIST_SUCCESS;

}