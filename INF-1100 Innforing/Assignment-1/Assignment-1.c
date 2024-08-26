#include <stdio.h>
#include <string.h>

//Task 1 declared
    void compare_value(int x, int y);

//Task 2 declared
    void myTriangles(int numlines);

//Task 3 declared
    int myPrimeFactor(int number, int primeFactor);

//Task 4 declared
    void myNumbers(int startnum, int endnum);

//Task 5 declared
    int myLog2(unsigned int n);

//Task 6 declared
    void reverseString(char string[]);

int main() {

//Task 1 main
    int number_x = 13;
    int number_y = 12;

    compare_value(number_x, number_y);
        printf("\n"); //to make it easier to read in termianl

//Task 2 main
    int trianglesLength = 4;

    myTriangles(trianglesLength);
        printf("\n"); //to make it easier to read in termianl

//Task 3 main
    int myPrimeFactorNumber = 10;
    int myPrimeFactorPirmeFactor = 5;

    printf("this is the myPrimeFactor result %i\n",myPrimeFactor(myPrimeFactorNumber,myPrimeFactorPirmeFactor));
        printf("\n"); //to make it easier to read in termianl

//Task 4 main
    int startnumber = 10;
    int endnumber = 15;

    myNumbers(startnumber, endnumber);
        printf("\n"); //to make it easier to read in termianl

//Task 5 main
    unsigned int myLog2number = 50;

    printf("This is myLog2 result %i\n", myLog2(myLog2number));
        printf("\n"); //to make it easier to read in termianl

//Task 6 main
    char reverse[] = "Hello World!";

    reverseString(reverse);
        printf("\n"); //to make it easier to read in termianl
return 0;
}

//Task 1 execution
    void compare_value(int x, int y) {

        if(x == y){ //checking if numbers are equal
            printf("Numbers are equal\n");
        } else {
            if (x > y) { //checking what is bigger
                printf("%i is the biggest number\n", x);
            }else{
                printf("%i is the biggest number\n", y);
            }
        }
    }

//Task 2 execution
    void myTriangles(int numlines) {

        int j = 0;
        int i = 0;

        while (numlines > 0)//while numlines is larger than 0, repeat
        {
            while (j < i)//while j is smaller than i, repeat
            {
                printf("*");
                j++;
            }
            printf("*\n");
            j = 0;//set this to 0 so that it can print longer lines of "*", since "i" increases
            numlines--;//decrease the value by 1, so that when it reaches 0, the triangle is done
            i++;//increase the value by 1, so that it can print longer lines of "*"
        }
    }

//Task 3 execution
    int myPrimeFactor(int number, int primeFactor) {

        if ((number == 0) || (primeFactor == 0)) //checking if number OR primefactor is 0
        {
            return 0; //is not a prime factor
        }

        int myPrimeFactorResult = 0;
        myPrimeFactorResult = number % primeFactor; 

        if(myPrimeFactorResult == 0){//checking if myPrimeFactroResult is 0
            return 1; //is a prime factor
        }else{//if myPrimeFactroResult is not 0
            return 0; //is not a prime factor
        }
    }

//Task 4 execution
    void myNumbers(int startnum, int endnum){

        for (int i = startnum; i <= endnum; i++)//for loop, starts and ends from the already defined variabels (startnum, endnum)
        {
            if(i % 2 == 0){//checking if i is even
                if (myPrimeFactor(i,5) == 1)//checking if 5 is a primefactor
                {
                    printf("%i is even \t and 5 is a prime factor\n", i);//using \t to make it easier to read in terminal
                }else{
                    printf("%i is even \t and 5 is not a prime factor\n", i);
                }
            }else{//if i is not even, it is odd
                if (myPrimeFactor(i,5) == 1)//checking if 5 is a primefactor
                {
                    printf("%i is odd \t and 5 is a prime factor\n", i);
                }else{
                    printf("%i is odd \t and 5 is not a prime factor\n", i);
                }
            }
        }
    }

//Task 5 execution
    int myLog2(unsigned int n){

        if(n == 0){//checking if user inputs 0, if so, answer is 0
            return 0;
        }

        int shiftcounter = 0;

        while(n != 1){//while n is NOT equal to 1, repeat. Since every number will eventualy end up as 1
            n = n >> 1;//shifting the bitnumber 1 time to the right
            shiftcounter++ ;//counting how many shifts, and this is the position of the most significant set bit
        }

        return shiftcounter;
    }

//Task 6 execution
    void reverseString(char string[]){

        char copyString[strlen(string)];//new string, haveing the same length as the original string
        strcpy(copyString, string);//copying the content from "string" to "copyString", so both has the same content
        int end = strlen(string) - 1;//this is the length of the string, but we reduce it by 1 since the string starts at 0

        printf("this is the original string: %s\n", string);
        
        for(int start = 0; start < strlen(string); start++){

            string[start] = copyString[end];//the first letter in "string" is now the last letter in "copyString", this will eventually reverse the string as "start" increases and "end" decreases
            end--;
        }

        printf("this is the reversed string: %s\n", string);
    }