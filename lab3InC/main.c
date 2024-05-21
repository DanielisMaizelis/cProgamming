#include "main.h"

void showPatientProfiles(healthRecords_t healthRecord[], int counter);
void addPersonalDetails(char* name, char* surname, char*birthDate, int gender, int height,float weight, char* city,
                        char* streetName, char*postcode, healthRecords_t *healthRecord);

static void showMenu();
static void getPatientProfile(healthRecords_t healthRecords[], int *counter);
static int savePatientProfile(char* fileName, healthRecords_t *healthRecords, int total);
static int readPatientProfile(char* fileName, healthRecords_t *healthRecords, int *total);


int main()
{
    int menuChoice, counterPeople = 0; // Counter people is the index of a struct
    healthRecords_t *healthRecords;
    healthRecords = malloc(10*sizeof(healthRecords_t)); // Allocates 10 spaces for 10 people
    choices_t       choices;                                 // Enum
    readPatientProfile(FILE_NAME,healthRecords,&counterPeople);
    printf("%llu bytes used\n",sizeof(healthRecords_t)); // Shows the size of the struct
    do {
        showMenu();
        scanf("%d",&menuChoice);
        choices = menuChoice;
        switch (choices){
            case SHOW_PROFILES: // Lists all the profiles
                showPatientProfiles(healthRecords, counterPeople);
                break;
            case INPUT_PROFILES: // Get the input from user
                getPatientProfile(healthRecords, &counterPeople);
                break;
            case QUIT: // Saves and quits the program
                if(!savePatientProfile(FILE_NAME, healthRecords, counterPeople))
                    printf("Unexpected error occured!\n");
                printf("Bye!");
                break;
            default:
                printf("Please enter the right number!");
        }
    }
    while (menuChoice != QUIT);
    return 0;
}


static int savePatientProfile(char* fileName, healthRecords_t *healthRecords, int total) // Save patient's data
{
    if(total) // Tries saving the file if some values were present from the begining
    {
        FILE* file;
        file = fopen(fileName, "wb");
        if(file == NULL) return 0; // File is empty
        if(!fwrite(&total, sizeof(int), 1, file)) return 0; // Unable to write the counter
        // Unable to write the user values
        if(!fwrite(healthRecords, sizeof(healthRecords_t), total, file)) return 0;
        if(fclose(file) == EOF) return 0; // End of file error
    }
    return 1;
}

static int readPatientProfile(char* fileName, healthRecords_t *healthRecords, int *total) // Reads all patient's data from file
{
    FILE* file;
    file = fopen(fileName, "rb");
    if(file == NULL) // File not found
    {
        printf("File %s not found", fileName);
        exit(1);
    }
    // Read the total value - the counter representing the amount of people registered in the file
    fread(total, sizeof(int),1, file);
    if(*total) // If the total counter value of data inside of the struct is bigger than 0
    {
        // Read the lines in the file the amount total values inside of the struct
        fread(healthRecords, sizeof(healthRecords_t),*total, file);
        fclose(file);
    }
    return 0;
}

static void getPatientProfile(healthRecords_t healthRecords[], int *counter) // Function for entering profiles for the user
{
    char name[20], surname[20], birthdate[15];
    int height, gender;
    float weight;
    char city[20], streetName[20], postcode[10];
    printf("Name:\n");
    scanf("%s", name);
    printf("Surname:\n");
    scanf("%s", surname);
    getchar(); // Gets a newline, so that it bypasses new line and won't skip the string
    printf("Birthdate (DD-MM-YYYY):\n");
    fgets(birthdate, sizeof(birthdate), stdin); // Read birthdate including newline character
    printf("Gender (Male 0, Female 1):\n");
    scanf("%d", &gender);
    printf("Height (in cm):\n");
    scanf("%d", &height);
    printf("Weight (in kg):\n");
    scanf("%f", &weight);
    printf("City:\n");
    scanf("%s", city);
    getchar(); // Gets a newline, so that it bypasses new line and won't skip the string
    printf("Street Name:\n");
    scanf("%19[^\n]", streetName);
    printf("Postcode:\n");
    scanf("%s", postcode);
    addPersonalDetails(name, surname, birthdate, gender, height, weight, city, streetName,
                       postcode, &healthRecords[*counter]); // Adds the details to structs from inputs
    *counter+=1;
}

static void showMenu() // Function for showing the head menu
{
    printf("--------\n");
    printf("Choose from these options:\n");
    printf("1. Show Profiles\n");
    printf("2. Input Profiles\n");
    printf("3. Save and Quit\n");
    printf("--------\n");
}