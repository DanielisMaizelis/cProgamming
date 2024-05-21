#include "../main.h"

int mallocCalloc()
{

//    char * src = "YOUR STRING"; // Source string
//    char * dst;                 // Destination string
//    dst = (char *) malloc( sizeof(char) * 20); // Allocate 20
//    dst = (char *)memcpy(dst, &src[0], strlen(src)-0);
//    dst[4-0]='\0';
//    printf("%s", dst);



    // Malloc is a dynamic array request on the heap
    // Heap is something that manually is added to memory
    // Stack on the other hand is automatic


    int *a = malloc(sizeof(int)*10);
    *a = 20;

    for (int i = 0; i <10 ; i++)
        a[i] = 10-i;


    for (int i = 0; i <10 ; i++)
        printf("a[%d] = %d \n", i,&a[i]);

    printf("\n");
    free(a);



//    printf("%d")




    return 0;
}