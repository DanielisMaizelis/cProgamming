#ifndef LAB3INC_MAIN_H
#define LAB3INC_MAIN_H

// Includes:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// defines
#define FILE_NAME           "../healthrecord.dat"
#define VACCINATIONS_AMOUNT 5

// enums
typedef enum choices{
    SHOW_PROFILES = 1,
    INPUT_PROFILES,
    QUIT
}choices_t;

// Structs:
typedef struct
{
    char city[20];
    char streetName[20];
    char postCode[20];
}address_t;

typedef struct
{
    int day  :5;
    int month:4;
    int year :12;
    char strDate[20];
}birthdate_t;

typedef union // To int array
{
    int hasVacc:1;
}vaccHistory_t;

typedef union
{
    float sodiumLevel;
    // For men
    int potassiumLevel:9;
    // For Children
    char schoolName[20];
}specials_t;

typedef struct
{
    char          firstName[20];
    char          lastName[20];
    birthdate_t   birthdate;
    int           gender:1;
    int           heightCm:9;
    float         weightKg;
    float         bmi;
    address_t     address;
    vaccHistory_t vaccHistory[VACCINATIONS_AMOUNT];
    int           isChild:1;
    specials_t    specials;

}healthRecords_t;

#endif //LAB3INC_MAIN_H
