// Added library - cs50.h 
// #include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

    int get_digit_count(long num);
    string typeCard(int length, int *cardDetails, int sumOfDigits);
    int checkSum(long num);
    int* numToArr(long num);

//////Find the number of Digits on the Card
 int main(void){
    long card = get_long("Enter Card Number: ");
    int cardNum = get_digit_count(card);

    //TO FIND THE VALIDITY OF STARTING POINTS
    int* arrOfNumbers = numToArr(card);

    int luhn = checkSum(card);

    string isValid = typeCard(cardNum,arrOfNumbers,luhn);

    printf("%s",isValid);

    return 0;
 }

    int get_digit_count(long num){
        int size = 0;
        while(num != 0){
            num /= 10;
            size++;
        }
        return size;
    }

    int checkSum(long num){
        int len = get_digit_count(num);
        int sum = 0;
        int rem; int prodDigit; int lastDig; int firstDig;
        if(len%2 == 0 || len%2==2){
            for(int i = len-1; i >= 0; i--){
                rem = num % 10;
                if( (i%2 == 0) || (i%2 == 2) ){
                    prodDigit = rem * 2;
                    if(get_digit_count(prodDigit) > 1){
                        for(int j = 0; j < get_digit_count(prodDigit); j++){
                            lastDig = prodDigit % 10;
                            firstDig = floor(prodDigit/10);
                            // printf("Split digits: %i %i\n",firstDig,lastDig);
                        }
                        prodDigit = lastDig + firstDig;
                    }
                    sum = sum + prodDigit;
                    // printf("SumEven: %i\n",sum);
                }else{
                    sum += rem;
                    // printf("SumOdd: %i\n",sum);
                }
                num = floor(num/10);
            }
        }else{
            for(int i = len-1; i >= 0; i--){
                rem = num % 10;
                if( (i%2 == 0) || (i%2 == 2) ){
                    sum += rem;
                    // printf("SumEven: %i\n",sum);
                }else{
                    prodDigit = rem * 2;
                    if(get_digit_count(prodDigit) > 1){
                        for(int j = 0; j < get_digit_count(prodDigit); j++){
                            lastDig = prodDigit % 10;
                            firstDig = floor(prodDigit/10);
                            // printf("Split digits: %i %i\n",firstDig,lastDig);
                        }
                        prodDigit = lastDig + firstDig;
                    }
                    sum = sum + prodDigit;
                    // printf("SumOdd: %i\n",sum);
                }
                num = floor(num/10);
            }
        }
        return sum;
    }

    string typeCard(int length, int* cardDetails,int sumOfDigits){
        string cardType;

        if(length == 15 && (sumOfDigits%10 == 0) && ( (cardDetails[1] == 3 && cardDetails[2]== 4) || (cardDetails[1] == 3 && cardDetails[2]== 7) ) ){
            cardType = "AMEX\n";
        }else if( (length == 13 || length == 16) && cardDetails[1] == 4 && (sumOfDigits%10 == 0) ){
            cardType = "VISA\n";
        }else if(length == 16 && (sumOfDigits%10 == 0) && ( (cardDetails[1] == 5 && cardDetails[2]== 1) || (cardDetails[1] == 5 && cardDetails[2]== 2) || (cardDetails[1] == 5 && cardDetails[2]== 3) || (cardDetails[1] == 5 && cardDetails[2]== 4) || (cardDetails[1] == 5 && cardDetails[2]== 5)  ) ){
            cardType = "MASTERCARD\n";
        }else {
            cardType = "INVALID\n";
        }
        return cardType;
    }

    int* numToArr(long num){
        int size = get_digit_count(num);
        static int arr[] = {};
        int rem;
        for(int i = size; i>=0; i--){
            rem = num % 10;
            arr[i] = rem;
            num = floor(num/10);
        }
        return arr;
    }
