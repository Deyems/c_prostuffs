    //#include <cs50.h>
    #include <math.h>
    #include <stdio.h>

    int main(void)
    {
        float dollar;
        
        do
        {
        dollar = get_float("Change: ");
        }while(dollar <= 0);

        int coin = round(dollar*100);
        int count=0; int remainder;
        int coins[] = {25,10,5,1};
        int arrloop = 0;
        while(arrloop < 4){
        count += floor(coin/coins[arrloop]);
            remainder = coin % coins[arrloop];
            if(remainder != 0){
                coin = remainder;
                arrloop++;
            }else{
                break;
            }
        }
            printf("%i\n",count);
    }