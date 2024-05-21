#include "../main.h"

int d1p1(void)
{
    char buffer[255];
    char numStr[20];
    char numStrResult[3];
    int  counter = 0;
    int  sum     = 0;
    int  intResult = 0;
    FILE* fp = fopen(NAME_OF_FILE,"r");

    if(!fp)
    {
        printf("File not found!\n");
        return 1;
    }
    while (fscanf(fp, "%s", buffer))
    {
        intResult = 0;
        counter = 0;
        memset(numStr, '\0', sizeof(numStr));
        memset(numStrResult, '\0', sizeof(numStrResult));

        for (int j = 0; j < sizeof(buffer); ++j)
        {
            if(buffer[j]>=48 && buffer[j]<=57)
            {
                numStr[counter] = buffer[j]; // array of chars that contains just numbers
                counter++;
            }
        }
        numStrResult[0] = numStr[0];
        numStrResult[1] = numStr[counter-1];
        numStrResult[2] = '\0';
        sscanf(numStrResult, "%d", &intResult);
        printf("%s\n",numStrResult);
        sum += intResult;
    }
    memset(buffer, '\0', sizeof(buffer));
    printf("Sum is: %d \n", sum);
    fclose(fp);
    return 0;
}
