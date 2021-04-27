#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc == 1 || argc >2)
    {
        printf("Usage: ./recover [filename] \n");
        return 1;
    }

    FILE *file = fopen(argv[1],"r");

    if(file == NULL){
        printf("Cannot open file %s\n",argv[1]);
        return 1;
    }

    BYTE fileOndisk[512];
    int counter = 0;
    char titleOfJpegFile[8];
    FILE *jpegImg = NULL;

    while(true){
        // if(file == feof(file)) break;
        size_t size = fread(fileOndisk,1,512,file);
        // check for condition to stop loop with eof and size of 0
        if(size == 0 && feof(file)) break;

        if(fileOndisk[0] == 0xff &&
        fileOndisk[1] == 0xd8 && fileOndisk[2] == 0xff &&
        (fileOndisk[3] & 0xf0) == 0xe0 && jpegImg != NULL ){
            fclose(jpegImg);
            counter++;
        }

        if(fileOndisk[0] == 0xff &&
            fileOndisk[1] == 0xd8 && fileOndisk[2] == 0xff &&
            (fileOndisk[3] & 0xf0) == 0xe0 ){

            sprintf(titleOfJpegFile,"%03i.jpg",counter);
            jpegImg = fopen(titleOfJpegFile,"w");
        }

            // while(size != 512){
        if(jpegImg != NULL){
            fwrite(fileOndisk,1,512,jpegImg);
        }
            // counter++;


            // }
    }
    fclose(jpegImg);
    fclose(file);

    return 0;
}
