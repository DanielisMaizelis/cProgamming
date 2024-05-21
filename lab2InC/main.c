#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//------------------------------------------------------------------------------
#define PRACTICE  1
#define TEST      2
#define QUIT_GAME 3

#define PLUS           1
#define MINUS          2
#define PLUS_AND_MINUS 3

#define TEST_Q_AMOUNT     15
#define PRACTICE_Q_AMOUNT 10

#define PRACTICE_TYPE 0
#define TEST_TYPE     1

typedef struct testResult
{
    char  question[10];
    int   corrAns;
    int   yourAns;
}testResult_t;

void headMenu(char *name);
void choiceMenu(int *choice);
void getChoice(int *choice);
void practiceOrTestMenu();
void practiceQuiz(char sign, int i, testResult_t testResult[], int type);
void chooseCalculationMethod(int choice, int type, testResult_t testResult[]);
void showTestResult(testResult_t testResult[]);
void getResponse(int isCorrect);
//------------------------------------------------------------------------------

int main(){
    char username[10];
    int inputChoice;
    testResult_t testResult[15];              // Struct for keeping the result row
    srand(time(0));               // Initialise rand seed

    headMenu(username);                 // Menu for the beggining of the program
    choiceMenu(&inputChoice);          // Gets the user's choice
    switch (inputChoice){
        case PRACTICE:
            practiceOrTestMenu();               // Shows menu fro choosing practice or test
            getChoice(&inputChoice);     // Gets the inputChoice
            printf("Now, you will be given 10 questions to solve:\n");
            // Choose the type of the practice
            chooseCalculationMethod(inputChoice, PRACTICE_TYPE, testResult);
            break;
        case TEST:
            practiceOrTestMenu(); // Shows menu fro choosing practice or test
            getChoice(&inputChoice);   // Gets the inputChoice
            // Choose the type of the test
            chooseCalculationMethod(inputChoice, TEST_TYPE, testResult);
            showTestResult(testResult);
            break;
        case QUIT_GAME:
            break;
    }
    return 0;
}


void showTestResult(testResult_t testResult[]){
    int counter = 0;
    for (int i = 0; i < TEST_Q_AMOUNT; ++i)
        counter = (testResult[i].yourAns == testResult[i].corrAns) ? counter+1 : counter;
    printf("Result: %.2f percent\n", 100/(float)TEST_Q_AMOUNT*(float)counter);
    printf("%-20s %-20s %-20s %-20s\n", "No", "Question","Your answer","Correct answer");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < TEST_Q_AMOUNT; ++i)
        printf("%-20d %-20s %-20d %-20d\n", i+1, testResult[i].question,  testResult[i].yourAns, testResult[i].corrAns);
}

void chooseCalculationMethod(int choice, int type, testResult_t testResult[]){
    int questionAmount;
    if(type == PRACTICE_TYPE)
        questionAmount = PRACTICE_Q_AMOUNT;
    else if(type == TEST_TYPE)
        questionAmount = TEST_Q_AMOUNT;
    switch(choice){
        case PLUS:
            for (int i = 0; i < questionAmount; ++i)
                practiceQuiz('+', i, testResult, type);
            break;
        case MINUS:
            for (int i = 0; i < questionAmount; ++i)
                practiceQuiz('-', i, testResult,type);
            break;
        case PLUS_AND_MINUS:
            // Randomises the test
            for (int i = 0; i < questionAmount; ++i)
                rand() % 2 ? practiceQuiz('+', i, testResult,TEST_TYPE):practiceQuiz('-', i, testResult ,TEST_TYPE);
            break;
    }
}

void practiceQuiz(char sign, int i, testResult_t testResult[], int type){
    int r1, r2;
    int total, guess;
    if(sign == '+'){                        // Sum case
        r1 = rand()%99, r2 = rand()%99;
        total = r1+r2;
    }
    else{                                   // Subtraction case
        do r1 = rand()%99, r2 = rand()%99;
        while (r1 < r2);
        total = r1-r2;
    }
    printf("%d. %d %c %d\n",i+1,r1,sign,r2);
    if(type == TEST_TYPE){
        scanf("%d",&guess);
        sprintf(testResult[i].question, "%d %c %d",r1,sign,r2);
        testResult[i].corrAns = total;
        testResult[i].yourAns = guess;
    }
    else if(type == PRACTICE_TYPE){
        do{
            scanf("%d",&guess);
            guess != total ? getResponse(0):guess;
        }
        while(guess != total);
        getResponse(1);
    }
}

void getResponse(int isCorrect){
    // Add static
    char correctAnswers[][25] = {"Very good!","Excellent!","Nice work!","Well done!", "Great!", "Keep up the good work!"};
    char incorrectAnswers[][25] = {"No. Please try again.","Wrong. Try once again.", "Don't give up!", "No. Keep trying."};
    int cNum = rand()%((sizeof(correctAnswers)/25));
    int iNum = rand()%((sizeof(incorrectAnswers)/25));
    isCorrect ? printf("%s\n",correctAnswers[cNum]):printf("%s\n",incorrectAnswers[iNum]);
}

void practiceOrTestMenu(){
    printf("You can choose to do practices on:\n\n");
    printf("1. additions\n");
    printf("2. subtractions\n");
    printf("3. additions and subtractions\n");
}


void headMenu(char *name){
    printf("Enter your name:");
    scanf("%s", name);
    printf("Welcome, %s!\n\n", name);
}

void choiceMenu(int *choice){
    printf("You can choose:\n");
    printf("1. do a practice\n");
    printf("2. complete a test\n");
    printf("3. quit the program\n");
    getChoice(choice);
}

void getChoice(int *choice){
    printf("Enter your choice:");
    scanf("%d", choice);
}