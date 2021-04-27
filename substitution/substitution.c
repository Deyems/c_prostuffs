#include <stdio.h>
#include <math.h>
#include <cs50.h>
#include <string.h>

bool checkKey(string key);
bool isAlpha(string key);

int main(int argc, string argv[]){
    while(argc != 2){
        printf("Usage: ./substitution *key: 26 Non-repeated Alphabets*\n");
        return 1;
    }

    while(checkKey(argv[1]) == 0){
        printf("Usage: ./substitution *key: 26 Non-repeated Alphabets*\n");
        return 1;
    }

    if(checkKey(argv[1]) == 1){
        string key = argv[1];
        printf("Successful: %s\n",key);

        string plaintext = get_string("Enter plaintext: ");
        // printf("plaintext: %s\n",plaintext);

        string alphabets = "abcdefghijklmnopqrstuvwxyz";
        // int position;
        // char ciphertext[40];
        // char keyEquiv[40] = key;

        string keyAndAlpha[2];
        keyAndAlpha[0] = key;
        keyAndAlpha[1] = alphabets;
        char ciphertext;

        printf("Ciphertext: ");
        for(int i = 0, n = strlen(plaintext); i < n; i++){
            for(int j = 0, m = strlen(alphabets); j < m; j++){
                if(plaintext[i] == keyAndAlpha[1][j]){
                    ciphertext = keyAndAlpha[0][j];
                }
                // else{
                //     ciphertext = plaintext[i];
                // }

            } // End of Alphabets LookUp
            printf("%c",ciphertext);
        } //End of Plaintext Loop through
            printf("\n");

        //SEARCHING THROUGH ALPHABETS AND ASSIGNING THEM
        //CORRESPONDING LETTERS
        // for(int i = 0, n = strlen(plaintext); i < n; i++ ){
        //     for(int j = 0, n = strlen(plaintext); j < n; j++){
        //         if(plaintext[i] == alphabets[j]){
        //             position = j;
        //             strcat(ciphertext,keyEquiv);
        //             break;
        //         }
        //     }
        // }


    }


}// end of Main program

bool checkKey(string key){
    if(strlen(key) != 26){
        return false;
    }else{
        for(int i = 0, n = strlen(key); i < n; i++){
        for(int j = i+1, len = strlen(key); j < len; j++ ){
            if(key[i] == key[j] || isAlpha(key) == 0 ){
                return false;
                }
            }
        }
        return true;
    } // end of For-Loop

} //end of function

bool isAlpha(string key){
    for(int i = 0, n=strlen(key); i < n; i++){
        int keyAscii = (int) key[i];
        if( (keyAscii >= 0 && keyAscii <= 64) || (keyAscii >= 91 && keyAscii <= 96) || (keyAscii > 122) ) {
            return false;
        }
    }
    return true;
}// end of 2nd Function