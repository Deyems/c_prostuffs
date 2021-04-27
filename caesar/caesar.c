#include <stdio.h>
#include <string.h>
#include <cs50.h>

bool checkKey(string arr);
//int positionOfLetter(char letters[],char plaintextChar);

int main(int argc, string argv[]){
    while(argc != 2){
        printf("Usage: ./caesar *key*\n");
        return 1;
    }

    while(checkKey(argv[1]) == 0 ){
        printf("Usage: ./caesar *key*\n");
        return 1;
    }

    if(checkKey(argv[1]) == 1 ){
        char* valInStr = argv[1];
        int key;

        sscanf(valInStr, "%i", &key);
//      printf("Success: %i\n", key);

        string plaintext = get_string("plaintext: ");
        //printf("%s\n",plaintext);

        //SEARCH FOR THE PLAINTEXT INPUT
        char ciphertext;
        int cipherInt;

        printf("ciphertext: ");
        // char dest = "ciphertext";

        for(int i = 0, len = strlen(plaintext); i <= len; i++){
            int plaintextInt = (int) plaintext[i];
            cipherInt = (int) plaintext[i]+key;

            if((plaintextInt >= 97 && plaintextInt <= 122) || (plaintextInt >= 65 && plaintextInt <= 90) ){
                ciphertext = (char) cipherInt;
            }else{
                ciphertext = plaintext[i];
            }

            if(cipherInt>122){
                cipherInt = ((cipherInt % 122) + 96);
                ciphertext = (char) cipherInt;
            }

            if(cipherInt>90 && cipherInt<97){
                cipherInt = ((cipherInt % 90) + 64);
                ciphertext = (char) cipherInt;
            }

            printf("%c", ciphertext);
        }

        printf("\n");
    }

}


bool checkKey(string arr){
    for(int i = 0, n = strlen(arr); i < n; i++){
        int numEquiv = (int) arr[i];
        if(!(numEquiv >= 48 && numEquiv <= 57)){
            return false;
        }
    }
    return true;
}


