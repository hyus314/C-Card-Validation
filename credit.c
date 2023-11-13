#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "cs50.h"

long get_card_number(void);
string get_card_validity(long);

int main(void)
{
    //The cs50 library is an online library created by Harvard's CS50 Computer Science course. It implements basic input in the language of C
    long cardNumber = get_card_number();
    string validity = get_card_validity(cardNumber);
    printf("%s", validity);
}

long get_card_number()
{
    //Input card's number
    long number;
    do
    {
        //This method comes from the CS50 library.
        number = get_long("Number: ");
    }

    while(number < 1);

    return number;
}

string get_card_validity(long cardNumber)
{
    //Get the length of the card number in order to turn it into a char array
    int cardNumberLength = (int)(ceil(log10(cardNumber)));

    //Allocating memory for the new char array of the card
    char *cardNumberInCharArrayUnreversed = (char *)malloc(cardNumberLength * sizeof(char)); // <-- Initial array

    sprintf(cardNumberInCharArrayUnreversed, "%ld", cardNumber);

    //Creating a new char array instance in order to get the reversed version of the char array
    char *cardNumberInCharArray = (char *)malloc(cardNumberLength * sizeof(char)); // <-- Array we will be operating with

    //Reversing the array and saving the elements into the new array
    int counter = 0;
    for(int i = cardNumberLength - 1; i >= 0; i--)
    {
        cardNumberInCharArray[counter++] = cardNumberInCharArrayUnreversed[i];
    }

    //Saving the first two elements of the UNREVERSED array, because that is how the brand type will be checked
    char firstDigitOfCard = cardNumberInCharArrayUnreversed[0];
    char secondDigitOfCard = cardNumberInCharArrayUnreversed[1];

    //Disposing the first array to result in memory optimization

    free(cardNumberInCharArrayUnreversed);

    //Beginning of Luhn's Algorithm
    int sumOfSecondToLast = 0;
    int sumOfNOTSecondToLast = 0;
    for(int index = 0; index < cardNumberLength; index++)
    {
        //Converting the elements one by one to integer in order to apply Luhn's algorithm, since they are saved in a char array
        int currentNumber = 0;
        currentNumber = cardNumberInCharArray[index] - '0';

        //Separating the odd and even indexes in order to calculate the sum of both
        if(index % 2 != 0)
        {
            int numberForSum = currentNumber * 2;
            if(numberForSum >= 10)
            {
                //Separating digits if the sum will be a two-digit number

                int lengthOfTwoDecimalNumberArray = 2;
                char *twoDecimalNumber = (char *)malloc(lengthOfTwoDecimalNumberArray * sizeof(char));


                sprintf(twoDecimalNumber, "%d", numberForSum);
                sumOfSecondToLast += (twoDecimalNumber[0] - '0') + (twoDecimalNumber[1] - '0');

                free(twoDecimalNumber);
            }
            else
            {
                sumOfSecondToLast += numberForSum;
            }
        }
        else
        {
            sumOfNOTSecondToLast += currentNumber;
        }
    }

    //Assuming the input data is false
    bool isCardValid = false;

    //Getting the sum of elements in even and odd position
    int totalSum = (int)sumOfSecondToLast + (int)sumOfNOTSecondToLast;


    //Getting the last number of the sum
    char totalSumArrayLastCharacter = totalSum % 10;

    //If the last digit of the sum was not zero, our assumption was correct
    //And we return the INVALID message
    if(totalSumArrayLastCharacter == 0)
    {
        isCardValid = true;
    }
    else
    {
        isCardValid = false;
        return "INVALID\n";
    }

    free(cardNumberInCharArray);

    //These conditional statements were created as a result of applying CS50's instructions regarding the assignment
    if(cardNumberLength == 15 && firstDigitOfCard == '3' && (secondDigitOfCard == '4' || secondDigitOfCard == '7') )
    {
        return "AMEX\n";
    }
    else if(cardNumberLength == 16 && firstDigitOfCard == '5' && (secondDigitOfCard == '1' || secondDigitOfCard == '2' || secondDigitOfCard == '3' || secondDigitOfCard == '4' || secondDigitOfCard == '5'))
    {
        return "MASTERCARD\n";
    }
    else if((cardNumberLength == 16 || cardNumberLength == 13) && firstDigitOfCard == '4')
    {
        return "VISA\n";
    }
    else
    {
        return "INVALID\n";
    }
}
