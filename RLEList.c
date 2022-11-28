#include "RLEList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node_t{
    char character;
    int occurencies;
    struct node_t*  next;
}*nodePtr;

struct RLEList_t{
    nodePtr head;
    nodePtr tail;
    int size;
};


RLEList RLEListCreate(){
    RLEList ptr = malloc (sizeof (*ptr));
    if(!ptr)
    {
        return NULL;
    }
    ptr->head=NULL;
    ptr->tail=NULL;
    ptr->size=0;
    return ptr;
}
nodePtr createNode(char value) {
    nodePtr ptr = malloc(sizeof(*ptr));
    if(!ptr) {
        free(ptr);
        return NULL;
    }
    ptr->character = value;
    ptr->occurencies=1;
    ptr->next = NULL;
    return ptr;
}

void RLEListDestroy(RLEList list){
    if (!list || list->size==0) {
        return;
    }
    nodePtr current = list->head;
    nodePtr next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    list->head=NULL;
    list->tail=NULL;
    list->size=0;
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value){
    //CHECK IF THE VALUES ARE NULL
    if(!list || !value)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->tail==NULL)
    {
        nodePtr initialNode= createNode(value);
        if(!initialNode)
        {
            free(initialNode);
            return RLE_LIST_OUT_OF_MEMORY;
        }
        //initialNode->occurencies++;
        list->tail=initialNode;
        list->size++;
        list->head=initialNode;

    }
    else
    {
        if(list->tail->character==value)
        {
            list->tail->occurencies++;
        }
        else
        {
            nodePtr newNode= createNode(value);
            if(!newNode)
            {
                return RLE_LIST_OUT_OF_MEMORY;
            }
            list->tail->next=newNode;
            list->tail=newNode;
            list->size++;
        }
    }
    return RLE_LIST_SUCCESS;
}
int RLEListSize(RLEList list)
{
    int size=0;
    if(!list)
    {
        return -1;
    }
    nodePtr current = list->head;
    while(current){
        size+=current->occurencies;
        current = current->next;
    }
    return size;
}
int sumOfoccurencies(nodePtr from , nodePtr to)
{
    nodePtr current=from;
    int sum=0;
    if(from==NULL || to==NULL) {
        return -1;
    }
    while(current != to && current !=NULL)
    {
        sum+=current->occurencies;
        current=current->next;
    }
    sum+= to->occurencies;
    return sum;

}
//nodePtr getPrevious(nodePtr currentNode , RLEList list){
//
//    nodePtr previous=list->head;
//
////    if(previous ==NULL || previous->next==NULL) {
////        previous = NULL;
////        return previous;
////    }
//    while(previous->next != currentNode)
//    {
//        previous=previous->next;
//    }
//    return previous;
//}


RLEListResult RLEListRemove(RLEList list, int index) {
    index++;
    //if the list is null
    if (!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int totalChars = RLEListSize(list);
    if (index > totalChars || index <= 0) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    nodePtr current = list->head;
    nodePtr helper = NULL;
    nodePtr previousNode = NULL;
    nodePtr nextNode = current->next;
    while(current)
    {
        int result= sumOfoccurencies(list->head , current);
        if(result==-1)
        {
            return RLE_LIST_NULL_ARGUMENT;
        }
        if (index<=result)
        {
            helper=current;
            break;
        }
        previousNode=current;
        current=current->next;


    }

    if (helper->occurencies ==1)
    {
        if(helper == list->tail)
        {
            if ( list->size != 1) {
                free(list->tail);
                list->size--;
                nodePtr temp = list->head;
                for (int i = 0; i < (list->size) - 1; ++i) {
                    temp = temp->next;
                }
                list->tail = temp;
                temp->next = NULL;
                return RLE_LIST_SUCCESS;
            }else if (list->size == 1)
            {
                list->head=NULL;
                list->tail=NULL;
                list->size=0;
                free(current);
                return RLE_LIST_SUCCESS;
            }
        }

        if(helper == list->head)
        {
            if(list->size ==1)
            {
                list->head=NULL;
                list->tail=NULL;
                list->size=0;
                free(current);
                return RLE_LIST_SUCCESS;

            }
            if(list->size!=1)
            {
                list->head=current->next;
                previousNode=current->next;
                free(current);
                list->size--;
                nextNode=nextNode->next;
                return RLE_LIST_SUCCESS;
            }

        } else
            nextNode=current->next;
        if (previousNode->character == nextNode->character)
        {
            previousNode->occurencies += nextNode->occurencies;
            if(nextNode->next !=NULL) {
                previousNode->next = nextNode->next;
                free(current);
                free(nextNode);
                list->size -= 2;
                return RLE_LIST_SUCCESS;
            }if(nextNode->next ==NULL)
            {
                list->tail=previousNode;
                previousNode->next=NULL;
                free(current);
                free(nextNode);
                list->size -= 2;
                return RLE_LIST_SUCCESS;
            }
        } else if (previousNode->character != nextNode->character)
        {

            previousNode->next = current->next;
            free(current);
            list->size--;
            return RLE_LIST_SUCCESS;
        }

    }
    if (current->occurencies != 1) {
        current->occurencies--;
        return RLE_LIST_SUCCESS;
    }
    return RLE_LIST_SUCCESS;
}



char RLEListGet(RLEList list, int index, RLEListResult *result) {
    int counter = 0;
    if (!list) {
        if (result != NULL) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    int totalChars = RLEListSize(list);

    if (index > totalChars - 1 || index < 0) {
        if (result != NULL) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    if(index <= totalChars-1 && index >= totalChars-(list->tail->occurencies))
    {
        if (result != NULL) {
            *result = RLE_LIST_SUCCESS;
        }
        return list->tail->character;

    }
    else
    {
        nodePtr current = list->head;
        while(current) {
            if (index <= current->occurencies + counter - 1) {
                if (result != NULL) {
                    *result = RLE_LIST_SUCCESS;
                }
                return current->character;
            }
            counter += current->occurencies;
            current = current->next;
        }
        return 0;

    }


}

//RLEListResult RLEListMap(RLEList list, MapFunction map_function)
//{
//    if(!map_function || !list)
//    {
//        return RLE_LIST_NULL_ARGUMENT;
//    }
//    if(RLEListSize(list)==0)
//    {
//        return RLE_LIST_SUCCESS;
//    }
//    nodePtr current=list->head;
//    while(current)
//    {
//        char letter =map_function(current->character);
//        current->character=letter;
//        current=current->next;
//    }
//    nodePtr currentNode=list->head;
//    nodePtr nextNode =list->head->next;
//    while(nextNode->next!=NULL)
//    {
//        if(currentNode->character!=nextNode->character)
//        {
//            currentNode=currentNode->next;
//            nextNode=nextNode->next;
//        }
//        else
//        {
//           nextNode->occurencies+=currentNode->occurencies;
//            free(currentNode);
//            currentNode=nextNode;
//            nextNode=nextNode->next;
//            list->size--;
//          }
//    }
//    return RLE_LIST_SUCCESS;
//}
//convert a number to char pointer

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(map_function==NULL || list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    nodePtr current=list->head;
    while(current!=NULL)
    {
        current->character =map_function(current->character);
        current=current->next;
        if(list->size ==1)
            return RLE_LIST_SUCCESS;
    }
    if(list->size==0)
    {
        return RLE_LIST_SUCCESS;
    }

    current=list->head;
    nodePtr nextNode = current->next;

    while(current->next!=NULL && nextNode->next!=NULL)
    {
        if(current->character == nextNode->character)
        {
            current->occurencies += nextNode->occurencies;
            nodePtr delete = nextNode;
            nextNode=delete->next;
            current->next=nextNode;
            free(delete);
            list->size--;
        }else{
            current = current->next;
            nextNode=nextNode->next;

        }
    }
    if(current->character == current->next->character)
    {
        current->occurencies += nextNode->occurencies;
        nodePtr delete = nextNode;
        nextNode=delete->next;
        free(delete);
        current->next=NULL;
        list->tail=current;
        list->size--;
    }
    return RLE_LIST_SUCCESS;

}





char *convert(int number , char *buffer)
{
    int currentNum=number;
    int j;
    int length=0;
    while(currentNum!=0)
    {
        length++;
        currentNum/=10;
    }
    for (int i = 0; i < length; ++i)
    {
        j=number%10;
        number/=10;
        buffer[length-i-1]= j +'0';
    }
    buffer[length]='\0';
    return buffer;
}
//function that return the number of digits
int numberOfDigits(long long number)
{
    if (number == 0)
        return 1;
    int count = 0;
    while (number != 0) {
        number/= 10;
        ++count;
    }
    return count-1;
}
char* RLEListExportToString(RLEList list, RLEListResult* result) {

    if(!list)
    {
        if(result!=NULL)
        {
            *result=RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    int totalSize= 3*(list->size);
    int i=0;
    nodePtr first= list->head;
    if(first==NULL)
    {
        char *nullString= malloc(sizeof (char));
        if(!nullString)
        {
            free(nullString);
            return NULL;

        }
        nullString[0]='\0';
        return nullString;
    }
    while(first != NULL){
        totalSize+= numberOfDigits(first->occurencies);
        first=first->next;
    }
    //totalSize+=1;
    char *str = malloc(sizeof (char) * totalSize+1);
    if(!str)
    {
        if(result!=NULL)
            *result=RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    while(i<totalSize)
    {
        str[i]=0;
        i++;
    }

    int currentCell,j=0;
    nodePtr current=list->head;
    while(j<totalSize)
    {
        str[j]=current->character;
        int len = numberOfDigits(current->occurencies);
        char *buffer= malloc(sizeof (buffer)*(len+1));
        if(!buffer)
        {
            *result=RLE_LIST_NULL_ARGUMENT;
            free(buffer);
            return NULL;
        }
        currentCell=j+2+len;
        convert(current->occurencies,buffer);
        strcat(str,buffer);
        str[currentCell]='\n';
        current=current->next;
        j=currentCell+1;
        currentCell=0;
        free(buffer);
    }
    if(result!=NULL)
        *result=RLE_LIST_SUCCESS;
    str[j]='\0';
    return str;
}