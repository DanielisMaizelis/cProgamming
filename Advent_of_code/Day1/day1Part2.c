#include "../main.h"


struct foundInts
{
    char nums[5];
    int locations[5];
};

struct foundStr
{
    char foundStr[20];
    char numbersStr[5];
    int  locations[5];
};

void resetSearch(char *result, int *k2, int *k, int *j);
void findInts(int i, char buffer[], struct foundInts fi, int *counter);



int d1p2(void)
{
    char numbers[10][10] = {"one","two","three","four","five","six","seven","eight","nine"};
    int  num[10] = {1,2,3,4,5,6,7,8,9};
    char buffer[255];
    char numStr[255];
    int counter;


    int counterStr = 0;
    int counterRow = 0;

    FILE* fp = fopen(NAME_OF_FILE,"r");



    if(!fp)
    {
        printf("File not found!\n");
        return 1;
    }

    struct foundInts fi;
    struct foundStr fs;


    while (fscanf(fp, "%s", buffer) == 1)
    {
        counter = 0;
        int counter1 = 0;
        int counter2 = 0;
        int k = 0;
        int k2 = 0;
        int l =0 ;
        char result[20];
        int matchFound = 0;
        char * found;

        if(counterRow == 1)
        {
            break;
        }

        int i = 0;
        while(buffer[i] != '\0')
        {
            if(buffer[i]>=48 && buffer[i]<=57)
            {
                fi.nums[counter1]      = buffer[i];
                fi.locations[counter1] = i;
                counter1++;
            }
            else
            {
                fs.foundStr[counter2] = buffer[i];
//                fs.locations[counter2] = i;
//                printf("Char: %c - ", fs.foundStr[counter2]);
//                printf("Loc: %d\n", fs.locations[counter2]);
                counter2++;
            }
            i++;
        }
        int j = 0;
        char *a;
        a = malloc(20);
        int temp = 0;
        char *locNum;

        while(numbers[j][0] != '\0')
        {
            // one is searched in 5oneone1
            found = strstr(fs.foundStr, numbers[j]); // Find a sub-string within a string
            if (found)
            {
                // mem of last element 2000- mem of the found element 1994
                locNum = found - sizeof(numbers[j]);
                printf("%s", locNum);
            j++;
        }
        ++counterRow;
    }
    return 0;
}




void findStrings()
{

}





//
//void findInts(int i, char buffer[], struct foundInts fi, int *counter)
//{
//    int result;
//    if(buffer[i]>=48 && buffer[i]<=57)
//    {
////        printf("%c ",buffer[i]);
//        sscanf(&result, "%d",&buffer[i]);
//
//
//        printf("%d ", result);
//        fi.numbers[*counter] = result;
//        fi.locations[*counter] = i;
//        *counter++;
//    }
//}

