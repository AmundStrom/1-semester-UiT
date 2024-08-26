#include <stdio.h>
#include <stdlib.h>

//nå går structen "stack" under navnet "stack_t"
typedef struct stack stack_t;

struct stack{
    //vi må ha en next slik at den kan peke på hva som er neste i stacken
    stack_t *next;
    //vi må ha en head slik at den første i stacken er definert som head
    stack_t *head;
    //verdien stakcen kan holde, altså en int verdi
    int verdi;
};

//vi lager en ny stack som ikke inneholder noe
stack_t *createstack(void)
{
    stack_t *NewStack = malloc(sizeof(stack_t)); //vi må allokere minne til stacken
        NewStack->head = NewStack; //dette er den første i stacken, derfor setter vi head er lik seg selv
        NewStack->next = NULL; //siden dette er den eneste i stacken må neste peke til NULL
        NewStack->verdi = 0; //den inneholder ingen verdi
}

//vi må kunne slette stacken fra minne hvis ønsket
void destroyStack(stack_t *stack)
{
    free(stack);
}

//legger til ett nytt heltatt i stacken
void PushStack(stack_t *stack, int verdi){
    stack_t *stackAdd = malloc(sizeof(stack_t)); //allokerer minne til den nye verdien
        stack->verdi = verdi; //setter verdien til stacken som man fikk som argument
        stack->next = stackAdd; //
        stack->head = stackAdd;
        stackAdd->next = NULL;
}

int main()
{
//vi lager stacken
int *stack;
stack = createstack();

//legger til verdi 5 i stacken
int leggtil = 5;
PushStack(stack, leggtil);

return 0;
}