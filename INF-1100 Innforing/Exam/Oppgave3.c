#include <stdio.h>


/* Oppgave 3a */
int lengste(char **A, int n)
{
    int tekststreng = 0;
    int lengste_tekststreng = 0;
    int posisjon = 0;

    //itererer gjennom hele arreyet
    for(int i = 0; i < n; i++)
    {
        //forteller størrelsen på et array
        //den funker slik at den skjekker hvor mye plass i minnet helle arrayet tar
        //så skjekker den hvor mye første element i arrayet tar i minnet
        //og deler disse to verdiene.
        //vi tar minus 1 fordi alle array ender med en '\0' og den vil vi ikke telle med
        //Dette kan man gjør siden man vet at et array bare har 1 type variabler, i vårt tilfelle er det char 
        tekststreng = (sizeof(A[i])/sizeof(A[i][0])) - 1;

        //hvis det nyligste skjekket arreyet er større eller lik den forrige største
        if (tekststreng >= lengste_tekststreng)
        {
            //lagrer verdien slik at if-statementet funker igjennom hele iterasjonen
            lengste_tekststreng = tekststreng;
            //lagrer verdien til posisjon til den største arrayet
            posisjon = i;
        }    
    }
    return posisjon;
}

/* Oppgave 3b */
int *finn(char **A, char *substreng)
{
    //det første man må gjør er å allokere minne til det nye arrayet med alle substrengene
    //den blir nå lagret på "heapen" og med å ta vare på adressen mister vi ikke veriden etter funksjonen har returnert arrayet
    //dette blir dobbelpointer siden vi vil ta vare på adressen til substrengene
    char *alleSubstrenger[] = malloc(sizeof(char));

    //lengden på A og Substreng, ville egentlig gitt den som et argument i funksjonen
    int lengdeA = 10;
    int lengdePaSubstreng = 20;

    int substrengCounter = 0;
    int lengdePaArray;

    //her starter man med å iterere gjennom pointerne inni arrayet A
    for(int i = 0; i < lengdeA; i++)
    {
        //finner størrelsen av Arrayet man skal skjekke om har en substreng
        lengdePaArray = (sizeof(A[i])/sizeof(A[i][0])) - 1;

        //itererer igjennom en tekststreng inni arrayet A
        for(int j = 0; j < lengdePaArray; j++)
        {
            //skjekker hvis en bokstav er lik en i substrengen
            if(A[i][j] == substreng[substrengCounter])
            {
                //hvis en bokstav er lik, så øker vi med 1 slik at substrengen går videre til neste bokstav
                substrengCounter++;
                //hvis en bokstav er lik, starter vi på nytt å iterere i tekststrengen inni arrayet A
                j=0;

                //skjekker hvis substrengCounter er lik lengden på substrengen
                if(substrengCounter == lengdePaSubstreng)
                {
                    //hvis substrengCounter og lengden på substrengen er like vet vi at tekststrengen inni arrayet A er en substreng
                    //vi vet tekststrengene er like fordi substrengCounter øker bare hvis de har matchende bokstaver,
                    //og den har økt helt opp til lengden av Substrengen, altså alle bokstavene matcher.
                    //vi legger den derfor inni arrayet som tar vare på alle substrengene
                    alleSubstrenger[i] = A[i];
                    //setter j som lengden av det nåværende arrayet slik at den kan gå videre til neste
                    j = lengdePaArray;
                }
            }
        }
    }
    return alleSubstrenger;
}

int main()
{
    /* Oppgave 3a */
    //vi har fra før av en dobbelpointer som inneholder et array med pointere, som peker til egne tekststrenger
    char *dobbelpointer[] = {/* pointere til tekststrenger */};
    int lengde = 10; //lengden på dobbelpointer

    int posisjon;
    posisjon = lengste(dobbelpointer, lengde);

    /* Oppgave 3b */
    //vi bruker samme dobbelpointer som i forrige oppgave, og antar at den er full av pointere med tekststrenger
    char substreng[] = "Dette er substrengen";

    //vi bruker denne til å ta vare på adressen til det nye arrayet med alle substrengene
    char *alleStrenger;
    alleStrenger = finn(dobbelpointer, substreng);

return 0;
}