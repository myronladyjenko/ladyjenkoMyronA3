/************************ladyjenkoMyronA3.c**************
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
gcc -std=c99 -Wall ladyjenkoMyronA3.c ladyjenkoMyronA3Main.c

Running: ./a.out

OR

gcc -std=c99 -Wall ladyjenkoMyronA3.c ladyjenkoMyronA3Main.c -o assn3

Running the Program: ./assn3
*********************************************************/

#include <stdio.h>
#include <string.h>
#include "givenA3.h"

/******
 readFromFile: This function takes 3 parameters. The 1st parameter called fileWithMedals is a string that
stores the filename of a sequential data file. The 2nd and 3rd parameters are populated using data file
that stores the country names and medals won by each country.
 In: char fileWithMedals[30], int country [COUNTRIES][MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]
 Out: void
 Post: Nothing
*******/
void readFromFile (char fileWithMedals[30], int country [COUNTRIES][MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{ 
   int i;
   int j;

   i = 0;
   j = 0;
   
   // creating File variable
   FILE* inFile = NULL;
   
   // opening the file
   inFile = fopen(fileWithMedals, "r");                  
   
   // checking if the file opened
   if (inFile == NULL)
   {
      printf("Can't open the file\n");
      country[0][0] = -999;
   }
   else 
   {
      // copying names of the countries and the number of medals won by each into
      // the arrays  
      while (!feof(inFile))
      {  
         fscanf(inFile, "%s %d %d %d", countryNames[i], &country[i][j], &country[i][j+1], &country[i][j+2]);
         i = i + 1;
      }
      
      // closing the file
      fclose(inFile);
   }
}

/******
 findTotalPerCountry: Finds total medals for each country and stores it in array totalAllCountries.
 In: int country [COUNTRIES] [MEDALCAT], int totalAllCountries [COUNTRIES]
 Out: void
 Post: Nothing
*******/
void findTotalPerCountry (int country [COUNTRIES] [MEDALCAT], int totalAllCountries [COUNTRIES])
{
   // loop the goes through each country and sums up the medals in category (gold, 
   // silver and bronze)
   for (int i = 0; i < COUNTRIES; i++)
   {
      totalAllCountries[i] =  country[i][0] + country[i][1] + country[i][2];
   }
}

/******
 findTotalPerMedal: Finds total number of medals in each category (Gold/Silver/Bronze) and stores them in array
totalAllMedals. Returns the maximum value in totalAllMedals. Outputs (through call-by-reference parameter) the index of the category with maximum medals – category given in parameter whichMedal
 In: int country [COUNTRIES][MEDALCAT], int totalAllMedals [MEDALCAT], int * whichMedal
 Out: int
 Post: find max value in totalAllMedals and returns it, assigns whichMedal appropariete value (by reference)
*******/
int findTotalPerMedal (int country [COUNTRIES][MEDALCAT], int totalAllMedals [MEDALCAT], int * whichMedal)
{
   int maxVal;
   maxVal = -999;
   *whichMedal = 0;
   // outter loop that goes through categories of medals (gold, silver, bronze)
   for (int i = 0; i < MEDALCAT; i++)
   {
     totalAllMedals[i] = 0;
     // inner loop that loops the the chosen category for each country and sums the number of medals
     for (int j = 0; j < COUNTRIES; j++)
     {
        totalAllMedals[i] = totalAllMedals[i] + country[j][i]; 
     }
     
     // finds the max number in the array and passes the index to whichMedal
     if (totalAllMedals[i] > maxVal)
     {
        maxVal = totalAllMedals[i];
        *whichMedal = i;
     } 
   }
   return maxVal; 
}

/******
hHistogram: Displays a horizontal histogram of stars, where each star represents a medal. The total number of medals must be printed at the end of the line. For example (note that the medal counts may be
different for you).
 In: char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES]
 Out: void
 Post: printf horizontal histogram based of length of the country name and number of medals won by it.
*******/
void hHistogram (char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES])
{
   int maxLenName;
   maxLenName = strlen(countryNames[0]);

   // finds the longest country name in the array countryNames 
   for (int k = 1; k < COUNTRIES; k++)
   {
      if (strlen(countryNames[k]) > maxLenName)   
      {
         maxLenName = strlen(countryNames[k]);
      }
   }
     // loop that prints horizontal histogram
     for (int i = 0; i < COUNTRIES; i++)
     { 
        // -* is to align the text to the left with the fixed number of spaces
        // (maxLenName)
        printf("%-*s : ", maxLenName, countryNames[i]);
        
        // print the number of starts based on the number of medals won
        for (int j = 0; j < totalMedals[i]; j++)
        {
           printf("*");
        }
            
        printf(" (%d)\n", totalMedals[i]);
     }
}

/******
searchCountry: Returns the total number of medals won by a country, given its name (countryName). If countryName
does not exist in the given list of 10 countries, it returns -1.
 In: char countryName [MAX_LENGTH_CNAME], char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalAllCountries [COUNTRIES]
 Out: int
 Post: return the number of medals won a country that the user was searching for (else returns -1).
*******/
int searchCountry (char countryName [MAX_LENGTH_CNAME], char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalAllCountries [COUNTRIES])
{
  // loop that goes through through each country name in the array countryNames and compares it name given by the user using strcmp
   for (int i = 0; i < COUNTRIES; i++)
   {
      if (strcmp(countryName, countryNames[i]) == 0)
      {
          return totalAllCountries[i];   
      }
   }
   
   return -1;
}

/******
rankTopThreeByTotal: Displays the top three country names and the total medals won by each of them – the display must be in order of total medals won.
 In: int totalMedals[COUNTRIES], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]
 Out: void
 Post: Prints the top 3 country's name and the number of medals won by it from the largest to smallest based on totalMedals and countryNames.
*******/
void rankTopThreeByTotal (int totalMedals[COUNTRIES], char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{
   int maxVal1;
   int maxVal2;
   int maxVal3;
   int index1;
   int index2;
   int index3;
   int keepMax1;
   int keepMax2;
   int keepMax3;

   maxVal1 = -1;
   maxVal2 = -1;
   maxVal3 = -1;
   index1 = -1;
   index2 = -1;
   index3 = -1;
   keepMax1 = -1;
   keepMax2 = -1;
   keepMax3 = -1;
   
   // loop through the array of totalMedals to find top three countries
   for (int i = 0; i < COUNTRIES; i++)
   {
      // assign the value to the first variable (if its bigger) and shift all
       // others to second and third place
      if (totalMedals[i] > maxVal1)
      {
         maxVal3 = maxVal2;
         maxVal2 = maxVal1;
         maxVal1 = totalMedals[i]; 
      }
      else
      {
         // assign the value to the second variable (if its bigger) and shift 
         // second to the third
         if (totalMedals[i] > maxVal2)
         {
            maxVal3 = maxVal2;
            maxVal2 = totalMedals[i];
         }
         else
         {
            // assign the value to the third variable (if its bigger)
            if (totalMedals[i] > maxVal3)
            {
               maxVal3 = totalMedals[i];
            }
         }
      }  
   }
   
   keepMax1 = maxVal1;
   keepMax2 = maxVal2;
   keepMax3 = maxVal3;

   // loop through the totalMedals array already knowing the top three values to 
   // find the index of them (in order to use the index to print the country name)
   for (int j = 0; j < COUNTRIES; j++)
   {
      if (totalMedals[j] == maxVal1)
      {
         index1 = j;
         maxVal1 = -1;
      }
      else
      {
         if (totalMedals[j] == maxVal2)
         {
            index2 = j;
            maxVal2 = -1;
         }
         else
         {
            if (totalMedals[j] == maxVal3)
            {
              index3 = j;
              maxVal3 = -1;
            }
         }
      }
   }
   
   // printf the top three countries with the number of medals
   printf("%s (%d)\n", countryNames[index1], keepMax1);
   printf("%s (%d)\n", countryNames[index2], keepMax2);
   printf("%s (%d)\n", countryNames[index3], keepMax3);
}

/******
rankTopThreeByMedal: Displays the top three country names and the total gold medals won by each of them – the display must be in order of total gold medals won.
 In: int country [COUNTRIES] [MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]
 Out: void
 Post: Prints the top 3 country's name and the number of medals won by it in gold category from the largest to smallest based on country (stores number of medals in each category) and countryNames.
*******/
void rankTopThreeByMedal (int country [COUNTRIES] [MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{

   int maxVal1;
   int maxVal2;
   int maxVal3;
   int index1;
   int index2;
   int index3;
   int keepMax1;
   int keepMax2;
   int keepMax3;

   maxVal1 = -1;
   maxVal2 = -1;
   maxVal3 = -1;
   index1 = -1;
   index2 = -1;
   index3 = -1;
   keepMax1 = -1;
   keepMax2 = -1;
   keepMax3 = -1;
   
   // loop through the array of country array (gold medal category) to find top three countries
   for (int i = 0; i < COUNTRIES; i++)
   {
      // assign the value to the first variable (if its bigger) and shift all
      // others to second and third place
      if (country[i][0] > maxVal1)
      {
         maxVal3 = maxVal2;
         maxVal2 = maxVal1;
         maxVal1 = country[i][0]; 
      }
      else
      {
        // assign the value to the second variable (if its bigger) and shift 
         // second to the third
         if (country[i][0] > maxVal2)
         {
            maxVal3 = maxVal2;
            maxVal2 = country[i][0];
         }
         else
         {
            // assign the value to the third variable (if its bigger)
            if (country[i][0] > maxVal3)
            {
               maxVal3 = country[i][0];
            }
         }
      }  
   }
   
   keepMax1 = maxVal1;
   keepMax2 = maxVal2;
   keepMax3 = maxVal3;

   // loop through the totalMedals array already knowing the top three values to 
   // find the index of them (in order to use the index to print the country name)
   for (int j = 0; j < COUNTRIES; j++)
   {
      if (country[j][0] == maxVal1)
      {
         index1 = j;
         maxVal1 = -1;
      }
      else
      {
         if (country[j][0] == maxVal2)
         {
            index2 = j;
            maxVal2 = -1;
         }
         else
         {
            if (country[j][0] == maxVal3)
            {
              index3 = j;
              maxVal3 = -1;
            }
         }
      }
   }
   
   keepMax3 = -1;
   index3 = -1;
   // printf the top three countries with the number of medals
   printf("%s (%d)\n", countryNames[index1], keepMax1);
   printf("%s (%d)\n", countryNames[index2], keepMax2);
   printf("%s (%d)\n", countryNames[index3], keepMax3);
}

/******
findAllWithNoXMedals: Returns the total number of countries with no medal of a specific category, where category = indexMedal (1 for Gold, 2 for Silver, 3 for Bronze). Stores the indices of countries that do not have indexMedal in an array called indexOfCountries.
 In: int country [COUNTRIES] [MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES]
 Out: int
 Post: find and returns number of countries that have a category with no medals of that category.
*******/
int findAllWithNoXMedals (int country [COUNTRIES] [MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES])
{
    int total;
    total = 0;
    
    // loop through the array and compare the number of medals in the given
    // category to 0, if true store the index in the indexOfCountries array. Count 
    // number of times if-statement executed
    for (int j = 0; j < COUNTRIES; j++)
    {
       if (country[j][indexMedal-1] == 0)
       {
          indexOfCountries[total] = j;
          total++;
       }
    }

   return total; 
}

/******
findAllWithOnlyXMedals: Returns the total number of countries that have ONLY won medals of a specific category, where
category = indexMedal (1 for Gold, 2 for Silver, 3 for Bronze). Stores the indices of such countries in an array called indexOfCountries.
 In: int country [COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES]
 Out: int
 Post: find and returns number of countries that have a category with medals only in that category.
*******/
int findAllWithOnlyXMedals (int country [COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES])
{
   int total;
   int firstCat;
   int secondCat;

   total = 0;
   firstCat = 0;
   secondCat = 0;
   
  // since the user passes 1,2,3 and not 0,1,2 we need to know the other categories indexes (firstCat - firstCategory) (secondCat - secondCategory)
   if (indexMedal == 3)
   {
      firstCat = 0;
      secondCat = 1;
   }
   else
   {
      if (indexMedal == 2)
      {
         firstCat = 0;
         secondCat = 2;
      }
      else
      {
         if (indexMedal == 1)
         {
            firstCat = 1;
            secondCat = 2;
         }
      }
   }
    
    // loop through the array and compare the number of medals in the given
    // category is not zero and the rest categories are zero, if true store the
    // index in the indexOfCountries array. Count number of times if-statement 
    // executed
    for (int j = 0; j < COUNTRIES; j++)
    {
       if (country[j][indexMedal-1] != 0 && country[j][firstCat] == 0 && country[j][secondCat] == 0)
       {
          indexOfCountries[total] = j;
          total++;
       }
    }
  
   return total;
}

/******
findCountryIndexWithMinOrMaxLength: Returns the index of the countryName that has min or max length - use 1 for min and 2 for max. You must return only one index, even if there are more than 1 countryNames with a max or min length
 In: int minOrMax, char countryNames [COUNTRIES][MAX_LENGTH_CNAME]
 Out: int
 Post: find and returns the index of the country with min/max length based on minOrMax.
*******/
int findCountryIndexWithMinOrMaxLength (int minOrMax, char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{
   int minLen;
   int indexMax ;
   int maxLen;
   int indexMin;

   minLen = MAX_LENGTH_CNAME;
   indexMax = 0;
   maxLen = 0;
   indexMin = 0;
   
   // retunrs the index of the country with the minimum length by looping the array // countryNames and comaping the length of the strings using strlen
   if (minOrMax == 1)
   {
      for (int i = 0; i < COUNTRIES; i++)
      {
         if (strlen(countryNames[i]) < minLen)
         {
            minLen = strlen(countryNames[i]);
            indexMin = i;
         }
      }

      return indexMin;
   }
   else
   {  
      // retunrs the index of the country with the maximum length by looping the 
      // array countryNames and comaping the length of the strings using strlen
      for (int i = 0; i < COUNTRIES; i++)
      {
         if (strlen(countryNames[i]) > maxLen)
         {
            maxLen = strlen(countryNames[i]);
            indexMax = i;
         }
      }
   }

   return indexMax;
}

/******
vHistogram: Displays a vertical histogram. The top line of the histogram shows the total count of medals for each country. The last line displays the country names.
 In: char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES]
 Out: void
 Post: prints vertical histogram with stars representing the number of medals by a country.
*******/


void vHistogram (char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES])
{
  int maxMedals;
  int maxLenName;
  int currNumMedals;
  int numDigits;
  int lenSpaces;
  int numDigitsCountires[COUNTRIES];
  int lengthSpaces;
  int lengthSpacesNum;
  
  // finds the longest name among country names
  maxLenName = strlen(countryNames[findCountryIndexWithMinOrMaxLength(2, countryNames)]);
  maxMedals = totalMedals[0];
  numDigits = 0;
  lenSpaces = (strlen(countryNames[0]) - 1) / 2;
  lengthSpaces = 0;
  lengthSpacesNum = 0;
  
  // loop the countries length, if two names that are beside eahc other have maxLength, then add 2 psaces in order to make diagram more viewable
  for (int i = 0; i < COUNTRIES - 1; i++)
  {
     if (strlen(countryNames[i]) == maxLenName && strlen(countryNames[i]) - strlen(countryNames[i+1]) == 2)
     {
        maxLenName = maxLenName + 1;
        break;
     }
     else
     {
         if (strlen(countryNames[i]) == maxLenName && strlen(countryNames[i]) - strlen(countryNames[i+1]) == 1)
         {
            maxLenName = maxLenName + 2;
            break;
         }
         else
         {
            if (strlen(countryNames[i]) == maxLenName && (strlen(countryNames[i]) - strlen(countryNames[i+1])) == 0)
            {
               maxLenName = maxLenName + 2;
               break;
            }
         }
     }
  }
  
  for (int i = 0; i < COUNTRIES; i++)
     {
         currNumMedals = totalMedals[i];
         numDigits = 0;

         do 
         {
            currNumMedals = currNumMedals / 10;
            numDigits ++;

         } while (currNumMedals != 0);
          
         numDigitsCountires[i] = numDigits;
      }
  
  // calculating the longest number
  
  printf("%*s", lenSpaces, "");
  // number of spaces to print between lines for country names
  for (int i = 0; i < COUNTRIES - 1; i++)
  {
    
    if (numDigitsCountires[i] % 2 == 0 && numDigitsCountires[i+1] % 2 == 0 )
      {
         lengthSpacesNum = maxLenName - numDigitsCountires[i]/2 - numDigitsCountires[i+1]/2 ;
         printf("%d%*s", totalMedals[i], lengthSpacesNum, "");
      }
      else
      {
          if (numDigitsCountires[i] % 2 == 0 && numDigitsCountires[i+1] % 2 != 0 )
          {
             lengthSpacesNum = maxLenName - numDigitsCountires[i]/2 - (numDigitsCountires[i+1]+1)/2;
             printf("%d%*s", totalMedals[i], lengthSpacesNum, "");  
          }
          else
          {  
              lengthSpacesNum = maxLenName - numDigitsCountires[i]/2 - (numDigitsCountires[i+1]+1)/2;
              printf("%d%*s", totalMedals[i], lengthSpacesNum, "");
          }
      } 
  }

  printf("%d", totalMedals[COUNTRIES-1]);

  printf("\n");
  // loop that finds maximum number out of the number medals won by each country
  for (int i = 1; i < COUNTRIES; i++)
  {
     if (totalMedals[i] > maxMedals)
     {
        maxMedals = totalMedals[i];
     }
  }  

   // loop that prints spaces or stars horizontally
   for (int i = maxMedals; i > 0; i--)
   {
      for (int j = 0; j < COUNTRIES; j++)
      {   
          // prints a star if number of medals won a current country is bigger or equal // to the maxMedals
          // the spacing is determined by the longest country name and the spaces 
          // before the first symbol in the first column
          if (totalMedals[j] >= i)
          {
             if (j != 0)
             {
                printf("%*s*%*s", (maxLenName - 1) / 2, "", ((maxLenName - 1) / 2 + (maxLenName - 1) % 2), "");
             }
             else
             {
                printf("%*s*%*s", lenSpaces, "", ((maxLenName - 1) / 2 + (maxLenName - 1) % 2), "");
             }
             
          }
          else
          { 
             // prints a star if number of medals won a current country is less than 
             //  maxMedals
             // the spacing is determined by the longest country    
             if (j != 0)
             {
                printf("%*s %*s", (maxLenName - 1) / 2, "", ((maxLenName - 1) / 2 + (maxLenName - 1) % 2), "");
             }
             else
             {
                printf("%*s %*s", lenSpaces, "", ((maxLenName - 1) / 2 + (maxLenName - 1) % 2), "");
             } 
          }
      }
      printf("\n");
   }

   // loop that prints country names to print spaces between names based on maxLenNames and number of letters 
   for (int i = 0; i < COUNTRIES - 1; i++)
   {  
      
      if (strlen(countryNames[i]) % 2 == 0 && strlen(countryNames[i+1]) % 2 == 0 )
      {
         lengthSpaces = maxLenName - 1 -  (strlen(countryNames[i]) - 1) / 2 - (strlen(countryNames[i+1]) - 1) / 2 - 1;
         printf("%s%*s", countryNames[i], lengthSpaces, "");
      }
      else
      {
          if (strlen(countryNames[i]) % 2 == 0 && strlen(countryNames[i+1]) % 2 != 0 )
          {
             lengthSpaces = maxLenName - 1 -  (strlen(countryNames[i]) - 1) / 2 - (strlen(countryNames[i+1]) - 1) / 2 - 1;
             printf("%s%*s", countryNames[i], lengthSpaces, "");  
          }
          else
          {   
             lengthSpaces = maxLenName - 1 -  (strlen(countryNames[i]) - 1) / 2 - (strlen(countryNames[i+1]) - 1) / 2;
             printf("%s%*s", countryNames[i], lengthSpaces, "");
          }
      }
      
   }
   
   printf("%s", countryNames[COUNTRIES-1]);
   printf("\n");
} 