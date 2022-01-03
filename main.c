/************************ladyjenkoMyronA3Main.c**************
Student Name: Myron Ladyjenko Email: mladyjen@uoguelph.ca Id: 1172255

Due Date: November 26 Course Name: CIS 1300

I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:

1) I have read and understood the University policy on academic integrity. 2) I
have completed the Computing with Integrity Tutorial on Moodle; and 3) I have
achieved at least 80% in the Computing with Integrity Self Test.

I assert that this work is my own. I have appropriately acknowledged any and
all material that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for
this course.

********************************************************/

/*********************************************************
Compiling the program
The program should be compiled using the following flags: -std=c99 -Wall

compiling:
gcc -std=c99 -Wall A3.c chaturvediRituA3Main.c

Running: ./a.out

OR

gcc -std=c99 -Wall ladyjenkoMyronA3.c ladyjenkoMyronA3Main.c -o assn3

Running the Program: ./assn3
*********************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "givenA3.h"

int main (int argc, char * argv[]) 
{ 
   int whichMedal;
   int choice;
   int indexMedal;
   int minOrMax;
   int totalNum;
   int checkCurr;
   
   char choiceStr[100];
   char whichMedalName[10];
   char indexMedalName[10];
   char countryNames [COUNTRIES][MAX_LENGTH_CNAME];
   char countryName [MAX_LENGTH_CNAME];

   int country [COUNTRIES][MEDALCAT];
   int totalAllCountries [COUNTRIES];
   int totalAllMedals [COUNTRIES];
   int indexOfCountries [COUNTRIES];
   
   choice = 0;
   totalNum = 0;
   checkCurr = 0;
   minOrMax = 0;
   indexMedal = 0;
   country [0][0] = -1;
   
   // checks if the user input two arguments 
   if( argc != 2 ) 
   {
      printf("Usage: main.exe inputFileName\n");
      return 1;  // mistake      
   }

   // reading from file and input the data into the appropariete arrays    
    readFromFile(argv[1], country, countryNames);

    if (country[0][0] == -999)
    {
       return -1; // error
    }
    else
    {
        // call this function before every other everything else because it fills up 
        // the array with the total number of medals won by each country. This data is // needed in other functions
        findTotalPerCountry(country, totalAllCountries);
        
        // do while-loop that promts the user for input of one of the categories 
        // provided in the menu unitl the user input 12 (breaks from the loop)
        do {
           // 
            printf ("\nHere is the menu \n\n");
            printf ("1. Display all country names read from file and the total number of medals won by each\n");
            printf ("2. Function 2 - Find total number of medals won by each country\n");
            printf ("3. Function 3 - Finds total number of medals in each category (Gold, Silver, Bronze)\n");
            printf ("4. Function 4 – Display horizontal histogram\n");
            printf ("5. Function 5 – Search for a country and return the total number of medals won by it\n");
            printf ("6. Function 6 – Rank and display top three countries in order of total medals won\n");
            printf ("7. Function 7 – Rank and display top three countries in order of total gold medals won\n");
            printf ("8. Function 8 – Find and display all countries that won no X medals, given X as either Gold, Silver or Bronze\n");
            printf ("9. Function 9 – Find and display all countries that won ONLY X medals, given X as either Gold, Silver or Bronze\n");
            printf ("10. Function 10 – Find and display name of the country that has minimum or maximum length among all countries read in option 1\n");
            
            printf ("11.   Function 11 – Display vertical histogram\n");
            
            printf ("12.   Exit\n");
            
            // user input for the options provided in the menu (chekcs for invalid type input
            while (checkCurr < 1) 
            {
               printf ("Enter your choice. Please choose from 1 to 12: ");
               fgets(choiceStr, 100, stdin);
             
               for (int i = 0; choiceStr[i] != '\n'; i++)
               {
                  
                  if ( isdigit(choiceStr[i]) ) 
                  {  
                    checkCurr = 1;
                  }
                  else
                  {
                     checkCurr = 0;
                     break;
                  }     
               }
            }
            checkCurr = 0;
            choice = atoi(choiceStr);
            
            // swithc statement for each of the options provided in the menu
            switch (choice) {
                // prints out all the data in the arrays after calling the function 
                // readFromFile using a for loop
                case 1:
                    printf("\n");    
                    for (int i = 0; i < COUNTRIES; i++)
                    {
                       printf("Country: %s, Gold = %d, Silver = %d, Bronze = %d\n", countryNames[i], country[i][0], country[i][1], country[i][2]);
                    }
                    break;
                // prints total number of medals for each country
                case 2:
                    printf("\n");   
                    for (int i = 0; i < COUNTRIES; i++)
                    {
                       printf("Country: %s = %d\n", countryNames[i], totalAllCountries[i]);
                    }
                    break;  
                // prints the number of medals in for each category and prints the max 
                case 3:
                    printf("\n");
                    findTotalPerMedal (country, totalAllMedals, &whichMedal); 
                    // based on the whichMedal category we need to print specific word // (Gold, Silver or Bronze). Use strcpy to copy the category into // the variable whichMedalName
                    
                    if (whichMedal == 0)
                    {
                       strcpy(whichMedalName, "Gold");
                    }
                    else
                    {
                       if (whichMedal == 1)
                       {
                          strcpy(whichMedalName, "Silver");
                       }
                       else
                       {
                          strcpy(whichMedalName, "Bronze");
                       }
                    }
                    
                    printf("Medal = Gold, Total = %d\n", totalAllMedals[0]);
                    printf("Medal = Silver, Total = %d\n", totalAllMedals[1]);
                    printf("Medal = Bronze, Total = %d\n", totalAllMedals[2]);
                    printf("Maximum number of medals = %d in category (%s)\n", totalAllMedals[whichMedal], whichMedalName);
                    break;
                
                // calls the function hHistogram
                case 4:
                    printf("\n");
                    hHistogram (countryNames, totalAllCountries);
                    break;
                
                // searches for the country in the array countryNames
                case 5:
                    printf("Searching for which country? ");
                    // promts the user to input a name of the country
                    fgets(countryName, 100, stdin);
                    countryName[strlen(countryName)-1] = '\0'; 
                    // based on whether the country was found or not prints the 
                    // appropariete message
                    if (searchCountry(countryName, countryNames, totalAllCountries) == -1)
                    {
                       printf("Country wasn't found\n");
                    }
                    else
                    {
                       printf("Found it - %s has a total of %d medals\n", countryName, searchCountry(countryName, countryNames, totalAllCountries));
                    }
                    
                    break;
                // calls function rankTopThreeByTotal
                case 6:
                    printf("\n");
                    printf("Rank top three Based on total number of medals\n");
                    rankTopThreeByTotal (totalAllCountries, countryNames);
   
                    break;

                // calls function rankTopThreeByMedal    
                case 7:
                    printf("\n");
                    printf("Rank top three Based on Gold medals\n");
                    rankTopThreeByMedal(country, countryNames);  
  
                    break;
                

                case 8:
                // user input for the indexMedal (1,2,3) (chekcs for invalid type input)
                    while ( !(indexMedal == 1 || indexMedal == 2 || indexMedal == 3) )
                    {
                        while (checkCurr < 1 ) 
                        {
                           printf ("Chose a category: 1-Gold, 2-Silver, 3-Bronze: ");
                          fgets(choiceStr, 100, stdin);
             
                          for (int i = 0; choiceStr[i] != '\n'; i++)
                          {
                  
                              if ( isdigit(choiceStr[i]) ) 
                              {  
                                 checkCurr = 1;
                              }
                              else
                              {
                                 checkCurr = 0;
                                 break;
                              }     
                           }
                          }

                        checkCurr = 0;
                        indexMedal = atoi(choiceStr);
                    }

                    // based on the indexMedal category we need to print specific word // (Gold, Silver or Bronze). Use strcpy to copy the category into // the variable whichMedalName 
                    if (indexMedal == 1)
                    {
                       strcpy(indexMedalName, "Gold");
                    }
                    else
                    {
                       if (indexMedal == 2)
                       {
                          strcpy(indexMedalName, "Silver");
                       }
                       else
                       {
                          strcpy(indexMedalName, "Bronze");
                       }
                    } 
                    
                    // calls function findAllWithNoXMedals and stores the result in 
                    // totalNum 
                    totalNum = findAllWithNoXMedals (country, indexMedal, indexOfCountries);

                    // based on the value of totalNum prints approparite message 
                    if (totalNum == 0)
                    {
                       printf("Number of countries with no %s medals = %d\n", indexMedalName, totalNum); 
                    }
                    else
                    {
                       printf("Number of countries with no %s medals = %d\n", indexMedalName, totalNum); 

                       // prints all the country names with this condition    
                       for (int i = 0; i < totalNum; i++)
                       {
                          printf("%s\n", countryNames[indexOfCountries[i]]);
                       }
                    }

                    indexMedal = 0;

                    break;

                case 9:
                    // user input for the indexMedal (1,2,3) (chekcs for invalid type input)
                    while ( !(indexMedal == 1 || indexMedal == 2 || indexMedal == 3) )
                    {
                        while (checkCurr < 1 ) 
                        {
                           printf ("Chose a category: 1-Gold, 2-Silver, 3-Bronze: ");
                          fgets(choiceStr, 100, stdin);
             
                          for (int i = 0; choiceStr[i] != '\n'; i++)
                          {
                  
                              if ( isdigit(choiceStr[i]) ) 
                              {  
                                 checkCurr = 1;
                              }
                              else
                              {
                                 checkCurr = 0;
                                 break;
                              }     
                           }
                          }

                        checkCurr = 0;
                        indexMedal = atoi(choiceStr);
                    }

                    // based on the indexMedal category we need to print specific word // (Gold, Silver or Bronze). Use strcpy to copy the category into // the variable whichMedalName 
                    if (indexMedal == 1)
                    {
                       strcpy(indexMedalName, "Gold");
                    }
                    else
                    {
                       if (indexMedal == 2)
                       {
                          strcpy(indexMedalName, "Silver");
                       }
                       else
                       {
                          strcpy(indexMedalName, "Bronze");
                       }
                    }

                    // calls function findAllWithNoXMedals and stores the result in 
                    // totalNum 
                    totalNum = findAllWithOnlyXMedals (country, indexMedal, indexOfCountries);
                    
                    // based on the value of totalNum prints approparite message
                    if (totalNum == 0)
                    {
                       printf("Number of countries with ONLY %s medals = %d\n", indexMedalName, totalNum); 
                    }
                    else
                    {
                       printf("Number of countries with ONLY %s medals = %d\n", indexMedalName, totalNum);
                       // prints all the country names with this condition
                       for (int i = 0; i < totalNum; i++)
                       {
                          printf("%s\n", countryNames[indexOfCountries[i]]);
                       }
                    }

                    indexMedal = 0;

                    break; 

                case 10:
                    // user input for the minOrMax (1,2) (chekcs for invalid type input) 
                    while ( !(minOrMax == 1 || minOrMax == 2) )
                    {
                        while (checkCurr < 1 ) 
                        {
                           printf ("Find the minimum or maximum length amoung all country names: type 1 to find Min, type 2 to find Max: ");
                           fgets(choiceStr, 100, stdin);
             
                          for (int i = 0; choiceStr[i] != '\n'; i++)
                          {
                  
                              if ( isdigit(choiceStr[i]) ) 
                              {  
                                 checkCurr = 1;
                              }
                              else
                              {
                                 checkCurr = 0;
                                 break;
                              }     
                           }
                          }

                        checkCurr = 0;
                        minOrMax = atoi(choiceStr);
                    }
                    
                    
                    // based on the user input print the appropariete message and call // the function
                    if (minOrMax == 1)
                    {
                       printf("The county name with minimum length = %s\n", countryNames[findCountryIndexWithMinOrMaxLength  (minOrMax, countryNames)] );
                    }
                    else
                    {
                       printf("The county name with maximum length = %s\n", countryNames[findCountryIndexWithMinOrMaxLength  (minOrMax, countryNames)] );
                    }

                    minOrMax = 0;      

                    break; 
                
                // printf vertical histogram by calling a function
                case 11:
                    printf("\n\n");
                    vHistogram (countryNames, totalAllCountries);
                    break; 

                // break from the while loop 
                case 12: 
                    break;  

               // validity check for the input for the choice variable 
               default: printf ("That is an invalid choice. Please choose from 1 to 12\n");
                    
            }
            
            checkCurr = 0;
        } while (choice != 12);
    }  
    
    return 0;
}

