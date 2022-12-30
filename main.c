
/*Abeer Muhammad
 * Student Number: 251143649
 * Date : November 11, 2022
 * Function: This code Takes inputs based on the world cup,
 * it allows the user to input up to 32 teams, update the teams, search for teams.
 */
#include <stdio.h>
#include <stdbool.h>
#include "readline.h"
#include <string.h>
// setting constant variables using define
#define NAME_LEN 25
#define MAX  32
#define SEED 2
struct worldCup {

    int code; // team code variable
    char name[NAME_LEN+1]; //creating a string in c is an array of characters
    char seeds[SEED+1]; // group seeding
    char colour[7]; // coulour
} teams[MAX]; // to call variables in structure you would use this first

int num_teams = 0; /* number of parts currently stored */

// intizializing all functions
int find_team(int code);
void insert(void);
void search(void);
void update(void);
void print(void);

int main() {
    char ans;
    bool func = true;

    // this section runs an infintie loop until the user asks to quit the program
    while (func == true) {
        printf("\nWhich operation would you like to complete:");
        scanf(" %c", &ans);
        switch (ans) { // takse input: i,s,u,p,q

            case 'i':
                insert(); // goes to insert function
                break;
            case 's':
                search(); // goes to search function
                break;
            case 'u':
                 update(); // goes to update function
                break;
            case 'p':
                print(); // goes to print functionn
                break;
            case 'q':
                printf("Goodbye."); // if quit is entered then goodbye is output
                func = false; // ends the loop
                break;
            default:
                printf("Invalid input, try again.\n"); // if a letter which is not permissable is entered
                break;
        }
    }
    return 0;
}
// this function (find_team) will take the user inputed team code and check if it is being used or not, because each has to be unique, if found will tell user that and to try again
int find_team(int code)
{
    int i;
    for (i = 0; i < num_teams; i++)
            if (teams[i].code == code)
                return i;
    return -1;
}
// this will check if the name is already existent, if it does then it will inform the user
char find_name(char team[26]){
    int j;
    int i;
    for ( i = 0; i < num_teams;i++) {
        j = strcmp(teams[i].name, team);
        if (j == 0) {
            return i;
        }
        }

    return -1;
}

// this checks if the group seeding is unique, and it checks if the group seeding has already been inputted
int find_seed(char seed, char seed2)
{
    int i;
    for (i = 0; i < num_teams; i++)
        if (teams[i].seeds[0] == seed && teams[i].seeds[1] == seed2)
            return i;
    return -1;
}
// this checks if the group seeding falls between a-h and 1-4, if not then it tells the user to try again
int check_seed(char answer, char numc){
    if (answer =='A' || answer =='B' || answer =='C' || answer =='D' || answer =='E' || answer =='F' || answer =='G' || answer =='H') {
        if (numc == '1' || numc == '2' || numc == '3' || numc == '4' ) {
        }
        else{
            printf("\nPlease try again. Input has to be 1-4.");

            return -1;
        }
    }
    else{
        printf("\nPlease try again. Input has to be A-H.");
        return -1;
    }
}
// this function checks if the colour is part of ROYGBIV and it also converts the letter input into Word output
int check_colour(char colour, int i){
    int count;
    int check = 0;
    char colours [7] ={'R','O','Y','G','B','I','V'};
    char arcfull [][10] ={"Red", "Orange","Yellow","Green","Blue","Indigo","Violet"};
    // this converts the letter input to full name input
    for (int count1 = 0;count1<7;count1++){
        if (colour == colours[count1]) {
            check = 1;
            for (count = 0; count < 7; count++) {
                if (colour == colours[count]) {
                    strcpy(teams[i].colour, arcfull[count]);
                }
            }
        }
    }
    // if its not found then it says its an invalid colour and not part of ROYGBIV
    if (check == 0){
        printf("\nThis is invalid colour. Must be ROYGBIV.");
        return -1;
    }
    else{
        return 0;
    }
}
// THIS ALLOWS THE USER TO INPUT ALL THE REQUIRED PARTS OF THE TEAM
void insert(void) {
    int code_num;

    // FIRST CHECKS IF THE DATABASE IS FULLL, IF IT IS THEN IT TELLS THE USER.
    if (num_teams == MAX) {
        printf("Database is full; can't add more teams.\n");
        return;
    }
    // IF THE DATABASE IS NOT FULL THEN ENTER THE TEAM CODE
    printf("Enter team code:");
    scanf("%d", &code_num);
    // checks if the code is within the appropriate range
    if(code_num > 31 || code_num < 0){
        printf("Your code number has to be through 0 and 31.\n");
        return;
    }
    // check if the code already exists, every code has to be unique so sends to find team
    if (find_team(code_num) >= 0) {
        printf("code already exists.\n");

        return;
    }
    teams[num_teams].code = code_num; // if all checks are passed then it is assigned

    // ASKS FOR TEAM NAME//
    printf("Enter team name:");
    read_line(teams[num_teams].name, NAME_LEN); // ONLY ACCEPTS 25 CHARACTERS
    if (find_name(teams[num_teams].name) >= 0){ // CHECKS IF THE TEAM NAME ALREADY EXISTS
        printf("This team name already exists.\n");
        return;
    }


    // GETS GROUP SEEDING FROM USER
    printf("Enter group seeding:");
    read_line(teams[num_teams].seeds, 2); // ACCEPTS ONLY 2 CHARACTERS

    char answer = teams[num_teams].seeds[0];
    char numc = teams[num_teams].seeds[1];
    if(check_seed(answer,numc) < 0 ){ //CHECKS IF SEED ENTERED CORRECTLY
        return;
    }

    if (find_seed(answer, numc) >= 0) { // ALSO CHECKS IF SEED ALREADY EXISTS
        printf("Seed already exists.\n");

        return;
    }

    // ASKS FOR TEAM COLOUR
    printf("Enter a team colour:");
    read_line(teams[num_teams].colour, 2);

    char colour = teams[num_teams].colour[0];
    if (check_colour(colour,num_teams) < 0){ // CHECKS IF COLOUR IS ROYGBIV AND CONVERTS TO WORD
        return;
    }

    num_teams++;
}

// THIS SEARCH FUNCTION ONLY PRESENTS THE TEAM CODE THAT IS BEING LOOKED FOR AND PRINTS OUT THOSE VALUES
void search(void)
{
    int i, number;
    printf("Enter the team code:");
    scanf("%d", &number);
    i = find_team(number); // finds the team in team code and if it doesnt exist it tells the user
    if (i >= 0) {
        printf("Team Code\tTeam Name\tGroup Seeding\tColour\n");
            printf("%d\t%18s\t%14s\t%7s\n", teams[i].code,
                   teams[i].name, teams[i].seeds, teams[i].colour);
    } else
        printf("Team not found.\n");
}

// UPDATE FUNCTION ASKS THE USER FOR THE TEAM CODE THEYD LIKE TO UPDATE AND UPDATES EVERY VALUE OF THE CHART
void update(void)
{
    int i, number;
    char newname[25];
    char newgroup[3];
    char newcol[2];


    printf("Enter team code:");
    scanf("%d", &number);
    i = find_team(number);

    if (i >= 0) { // IF THE TEAM EXISTS
        printf("Enter new team name:"); // ENTER NAME
        scanf("%25s", &newname);
        char country [26];
        strcpy( country, teams[i].name);
        strcpy(teams[i].name,"E"); // EMPTIES THE VALUE FIRST THIS ALLOWS THE USER TO INPUT THE SAME COUNTRY NAME AGAIN IF THEY DO NOT WANT TO CHANGE THAT
        if (find_name(newname) >= 0) { // CHECKS IF NAME EXISTS BUT AVOIDS THE ISSUE IF FOR EXAMPLE THEY WANT TO KEEP NAME CANADA, THEY CAN INPUT IT AGAIN WITHOUT ERROR
            printf("This team name already exists.\n");
            strcpy( teams[i].name,country);
            return;
        }


        // ENTERS THE GROUP SEEDING
        printf("Enter group seeding:");
        scanf("%2s", &newgroup);
        char answer = newgroup[0];
        char numc = newgroup[1];
        char group [3];
        strcpy(group, teams[i].seeds);
        strcpy(teams[i].seeds,"E"); // EMPTIES IT BEFORE USER PUTS IT IN TO ALLOW THEM TO ENTER THE SAME GROUP SEEIDNG IF REQUIRED
        if (check_seed(answer, numc) < 0) { // CHECKS ranges  WITHOUT INCLUDING THE ONE FROM BEFORE
            strcpy( teams[i].seeds,group );
            strcpy( teams[i].name,country);
            return;
        }
        if (find_seed(answer, numc) >= 0) { // checks if the seed already exists
            printf("Seed already exists.\n");
            strcpy( teams[i].seeds,group );
            strcpy( teams[i].name,country);
            return;

        }

        // TAKES THE COLOUR CHANGE
        printf("Enter change in colour:");
        scanf("%2s", &newcol);
        char colour = newcol[0];
        char colours [7];
        strcpy(colours, teams[i].colour);
        strcpy( teams[i].seeds,group);
        printf("%s",teams[i].seeds);
        strcpy(teams[i].colour, "E"); // EMPTIES IF NECESSARY
        if (check_colour(colour, i) < 0) { // CHECKS IF COLOUR IS ROYGBIV
            // if the input is not complete due to a mistake by user it reverts back to original input to try again
            strcpy( teams[i].colour,colours);
            strcpy( teams[i].seeds,group);
            strcpy( teams[i].name,country);
            return;
        }

        strcpy(teams[i].seeds, newgroup);
        strcpy(teams[i].name, newname);


    }
    else
        printf("team not found.\n");
    return;
}



// PRINTS OUT ALL THE VALUES WITHIN THE STRUCTURE
void print(void) {
    int i;
    printf("Team Code\tTeam Name\tGroup Seeding\t   Colour\n");
    for (i = 0; i < num_teams; i++)
        printf("%d\t%14s\t%18s\t%3s\n", teams[i].code,
               teams[i].name, teams[i].seeds, teams[i].colour);
}
