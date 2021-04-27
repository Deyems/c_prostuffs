#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

int letterCount(string word);
int sentenceCount(string word);
int wordCount(string word);

int main(void){
    string str = get_string("Text: ");
    string readingLevel = "";

    //printf("We have %i letter(s) present\n", letterCount(str));
    //printf("We have %i sentence(s) present\n", sentenceCount(str));
    //printf("We have %i word(s) present\n", wordCount(str));
    float L = (letterCount(str) * 100) / wordCount(str);
    float S = (sentenceCount(str) * 100) / wordCount(str);

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if(index < 1) {
        readingLevel = "Before Grade 1";
        printf("%s\n",readingLevel);
    }else if(index > 16){
        readingLevel = "Grade 16+";
        printf("%s\n",readingLevel);
    }else{
        readingLevel = "Grade";
        printf("%s %i\n",readingLevel,index);
    }


}

int letterCount(string word){
    int length = 0;
    for(int i = 0, n = strlen(word); i < n; i++){
        int ansciiEquiv = (int) word[i];
        if((ansciiEquiv >= 97 && ansciiEquiv <= 122) ||(ansciiEquiv >= 65 && ansciiEquiv <= 90)){
            length += 1;
        }
    }
    return length;
}

int sentenceCount(string word){
    int sentenceLength = 0;
    for(int i = 0, n = strlen(word); i < n; i++){
        if(word[i] == '.' || word[i] == '!' || word[i] == '?' ){
            sentenceLength += 1;
        }
    }
    return sentenceLength;
}

int wordCount(string word){
    int wordCounter = 0;
    for(int i = 0, n = strlen(word); i <= n; i++){
        if(word[i] == ' '){
            wordCounter += 1;
        }
    }
    return wordCounter+1;
}
