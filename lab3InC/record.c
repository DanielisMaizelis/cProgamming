#include "main.h"

void showPatientProfiles(healthRecords_t healthRecord[], int counter);
static void showPersonalDetails(healthRecords_t *healthRecord);
static void showVaccHistory(healthRecords_t *healthRecord);
static void showExtraDetails(healthRecords_t *healthRecord);


void addPersonalDetails(char* name, char* surname, char*birthDate, int gender, int height,float weight, char* city,
                        char* streetName, char*postcode, healthRecords_t *healthRecord);
static float calculateBmi(float height, float weight);
static void addExtraDetails(healthRecords_t *healthRecord);
static void addVaccHistory(char* diseaseName, healthRecords_t *healthRecord, int *counter);
static int checkIfChild(healthRecords_t *healthRecord);
static void listVaccinations(char* vaccName, healthRecords_t *healthRecord, int *index);

static void sortByBmi(healthRecords_t *healthRecords, int counter);

void showPatientProfiles(healthRecords_t healthRecord[], int counter)
{
    if(!counter)
        printf("The list is empty!\n");
    else
    {
        getchar();
        sortByBmi(healthRecord, counter);
        for (int i = 0; i < counter; ++i)
        {
            printf("\n---------------------------\n");
            printf("%d)\n",i+1);
            showPersonalDetails(&healthRecord[i]);
            showVaccHistory(&healthRecord[i]);
            showExtraDetails(&healthRecord[i]);
            if(i < counter-1) // End of users have not been reached
            {
                printf("Press [enter] to continue...\n"); // Asks to press enter for each user
                while (getchar() != '\n'); // Waits for a newline
            }
        }
    }
}

static void showPersonalDetails(healthRecords_t *healthRecord)
{
    // Set the age
    printf("Personal details:\n");
    printf("----\n");
    printf("%-12s%s\n", "First name:", healthRecord -> firstName);
    printf("%-12s%s\n", "Last name:", healthRecord -> lastName);
    printf("%-12s%s\n", "Birth date:", healthRecord-> birthdate.strDate);
    healthRecord -> gender ? printf("Gender:%-12s\n", "Female") : printf("Gender:%-12s\n", "Male");
    printf("%-12s%dcm\n", "Height:", healthRecord -> heightCm);
    printf("%-12s%.1fkg\n", "Weight:", healthRecord -> weightKg);
    printf("%-12s%.2f\n", "BMI:", healthRecord -> bmi);
    printf("%-12s%s, %s\n\n", "Address:",
           healthRecord -> address.streetName, healthRecord -> address.city);
}

static void showVaccHistory(healthRecords_t *healthRecord)
{
    int counter = 0;
    printf("Vaccination History:\n");
    printf("----\n");
    listVaccinations("Yellow fever", healthRecord, &counter);
    listVaccinations("Hepetitis", healthRecord, &counter);
    listVaccinations("Malaria", healthRecord, &counter);
    listVaccinations("Bird flu", healthRecord, &counter);
    listVaccinations("Polio", healthRecord, &counter);

}

static void listVaccinations(char* vaccName, healthRecords_t *healthRecord, int *index)
{
    printf("%-12s - ", vaccName);
    if(healthRecord -> vaccHistory[*index].hasVacc)
        printf("Vaccinated\n");
    else
        printf("Not vaccinated\n");
    *index+=1;
}

static void showExtraDetails(healthRecords_t *healthRecord) // Shows extra details, like school and pottasium sodium levels
{
    printf("\nExtra details:\n");
    printf("----\n");
    if(healthRecord -> isChild)
        printf("School name: %s\n", healthRecord -> specials.schoolName);
    else if(!healthRecord-> gender)
        printf("Potassium level: %d\n", healthRecord -> specials.potassiumLevel);
    else if(healthRecord -> gender)
        printf("Sodium level: %.1f\n", healthRecord -> specials.sodiumLevel);
    printf("---------------------------\n");
}


void addPersonalDetails(char* name, char* surname, char*birthDate, int gender, int height,float weight, char* city,
                        char* streetName, char*postcode, healthRecords_t *healthRecord)
{
    address_t addr;
    strcpy(healthRecord -> firstName, name);
    strcpy(healthRecord -> lastName, surname);
    healthRecord -> gender   = gender;
    healthRecord -> heightCm = height;
    healthRecord -> weightKg = weight;
    healthRecord -> bmi      = calculateBmi(((float)height)/100, weight);
    strcpy(addr.city , city);
    strcpy(addr.streetName , streetName);
    strcpy(addr.postCode , postcode);
    healthRecord -> address = addr;
    strcpy(healthRecord -> birthdate.strDate, birthDate);
    healthRecord -> isChild = checkIfChild(healthRecord);

    int counter = 0;
    // Iterates each vaccination
    addVaccHistory("Yellow fever", healthRecord, &counter);
    addVaccHistory("Hepetitis", healthRecord, &counter);
    addVaccHistory("Malaria", healthRecord, &counter);
    addVaccHistory("Bird flu", healthRecord, &counter);
    addVaccHistory("Polio", healthRecord, &counter);
    addExtraDetails(healthRecord);
}

static void sortByBmi(healthRecords_t *healthRecords, int counter) // Bubble sort w/ BMI
{
    healthRecords_t healthRecordsTemp;
    // Bubble sort used for sorting by bmi
    for (int i = 0; i < counter-1; ++i)
    {
        for (int j = i+1; j < counter; ++j)
        {
            if(healthRecords[i].bmi < healthRecords[j].bmi)
            {
                healthRecordsTemp = healthRecords[i];
                healthRecords[i] = healthRecords[j];
                healthRecords[j] = healthRecordsTemp;
            }
        }
    }
}

static int checkIfChild(healthRecords_t *healthRecord) // Checks if the person in under 16
{
    int isChild, age;
    time_t t = time(NULL);
    struct tm currDate = *localtime(&t); // Gets the local time
    int day   = healthRecord -> birthdate.day;
    int month = healthRecord -> birthdate.month;
    int year  = healthRecord -> birthdate.year;
    // Converts the received string from input into individual integers
    sscanf((char*)healthRecord -> birthdate.strDate, "%d-%d-%d",&day, &month,&year);
    // Subtracts the age
    age = currDate.tm_year + 1900-year;
    // Compares if the person has been born after the current month and day
    if(day < currDate.tm_mday && month < currDate.tm_mon+1)
        age--; // Decrements age
    isChild = age<16 ? 1:0; // Checks if the total age is less that 16, if so assign value 1
    return isChild;
}

static void addVaccHistory(char* diseaseName, healthRecords_t *healthRecord, int *counter) // Asks for vaccination of a particular disease
{
    vaccHistory_t vac;
    printf("Vaccinated with %s vaccine (1 for yes, 0 for no):\n",diseaseName);
    int hasVacc;
    scanf("%d", &hasVacc);
    vac.hasVacc = hasVacc;
    healthRecord -> vaccHistory[*counter] = vac;
    *counter+=1;
}

static void addExtraDetails(healthRecords_t *healthRecord) // Asks for extra details based on the user's info
{
    if(healthRecord -> isChild)
    {
        getchar(); // Gets a newline, so that it bypasses new line and won't skip the string
        printf("School name\n");
        scanf("%19[^\n]",healthRecord -> specials.schoolName);
    }
    else if(!healthRecord -> gender) // Male
    {
        printf("Potassium level (normal range is 135 - 145)\n");
        int potassiumLevel;
        scanf("%d",&potassiumLevel);
        healthRecord->specials.potassiumLevel = potassiumLevel;
        printf("%d %d",healthRecord->specials.potassiumLevel, potassiumLevel);
    }
    else if(healthRecord -> gender) // Female
    {
        printf("Sodium level (normal range is 2.5 - 3.5)\n");
        scanf("%f",&healthRecord -> specials.sodiumLevel);
    }
}

static float calculateBmi(float height, float weight)
{
    return weight/(height*height);
}