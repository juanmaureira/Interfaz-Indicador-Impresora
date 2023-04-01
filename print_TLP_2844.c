/*************************************************************************
                  ETIQUETAS PARA IMPRESORA TLP-2844
*************************************************************************/
#include <math.h>

void printHeader(void){
   printf("I8,A\r\n");
   printf("q480\r\n");
   printf("O\r\n");
   printf("JF\r\n");
   printf("WN\r\n");
   printf("ZT\r\n");
   printf("Q320,25\r\n");
   printf("N\r\n");
   printf("A330,287,2,4,2,2,N,\"TAUMM\"\r\n");
}

void printFoot(void){
   printf("\"\r\n");
   printf("P1\r\n");
}

/*
I8,A
q480
O
JF
WN
ZT
Q320,25
N
A330,287,2,4,2,2,N,"TAUMM"
A400,227,2,4,1,1,N,"PESO:    12,54 Kg"
A400,187,2,4,1,1,N,"BULTO N:   1   "
A400,147,2,4,1,1,N,"HORA:   22:54:59"
A400,107,2,4,1,1,N,"FECHA: 18/06/2021"
P1

*/

void printLabel(char *peso, long bulto){
int i;

   printHeader();
   printf("A400,227,2,4,1,1,N,\"PESO:");

   for(i=0;i<7;i++) printf("%c",peso[i]);   

   printf("kg\"\r\n");
   printf("A400,187,2,4,1,1,N,\"BULTO N :%li\"\r\n", bulto);   
   printf("A400,147,2,4,1,1,N,\"HORA:");
   
   for(i=0;i<9;i++) printf("%c",frame.time[i]);   
   
   printf("\"\r\n");
   printf("A400,107,2,4,1,1,N,\"FECHA:");
   
   for(i=0;i<11;i++) printf("%c",frame.date[i]);   
         
   printFoot();

}

/*
I8,A
q480
O
JF
WN
ZT
Q320,25
N
A330,287,2,4,2,2,N,"TAUMM"
A330,227,2,4,1,1,N,"PESO TOTAL"
A300,187,2,4,1,1,N,"120,25 Kg"
A370,147,2,4,1,1,N,"TOTAL DE BULTOS"
A250,107,2,4,1,1,N,"10"
P1
*/

void printTotalWeigth(char *peso, long bultos){
   int i;
   printHeader();
   printf("A330,227,2,4,1,1,N,\"PESO TOTAL\"\r\n");
   printf("A300,187,2,4,1,1,N,\"");
   
   for(i=0;i<7;i++) printf("%c",peso[i]);

   printf("Kg\"\r\n");
   printf("A370,157,2,4,1,1,N,\"TOTAL DE BULTOS\"\r\n");
   printf("A250,107,2,4,1,1,N,\"%li\"\r\n", bultos);
   printf("P1\r\n");
}

/*

A340,242,2,1,1,1,N,"B1: 12,54 Kg"
A340,218,2,1,1,1,N,"B2: 12,54 Kg"
A340,194,2,1,1,1,N,"B3: 12,54 Kg"
A340,169,2,1,1,1,N,"B4: 12,54 Kg"
A340,146,2,1,1,1,N,"B5: 12,54 Kg"
A194,242,2,1,1,1,N,"B6: 12,54 Kg"
A194,217,2,1,1,1,N,"B7: 12,54 Kg"
A194,194,2,1,1,1,N,"B8: 12,54 Kg"
A194,169,2,1,1,1,N,"B9: 12,54 Kg"
A194,146,2,1,1,1,N,"B10: 12,54 Kg"
P1

*/

/*

A440,232,2,4,1,1,N,"B1:112,54 Kg"
A440,202,2,4,1,1,N,"B2:112,54 Kg"
A440,172,2,4,1,1,N,"B3:112,54 Kg"
A440,142,2,4,1,1,N,"B4:112,54 Kg"
A440,112,2,4,1,1,N,"B5:112,54 Kg"
A230,232,2,4,1,1,N,"B6:112,54 Kg"
A230,202,2,4,1,1,N,"B7:112,54 Kg"
A230,172,2,4,1,1,N,"B8:112,54 Kg"
A230,142,2,4,1,1,N,"B9:112,54 Kg"
A240,112,2,4,1,1,N,"B10:112,54 Kg"
P1
*/


void printBultos(void){
long xPoint[10] = {440,440,440,440,440,230,230,230,230,240};
long yPoint[10] = {232,202,172,142,112,232,202,172,142,112};
long bultos = (long)(addressWrite/8);
signed long numBultos;
int etiquetas;
long initMemory = 0;
char w[7];
char total[7];
float pesoTotal = 0.0;
long restoBultos = 0;

   memset(w, 0, sizeof(w));
   memset(total, 0, sizeof(total));

   #ifdef DEBUG 
		printf("bultos: %li\r\n", bultos);
   #endif

   etiquetas = (int)ceil((float)bultos/10);

   #ifdef DEBUG 
	   printf("Numero de etiquetas a imprimir: %i\r\n",etiquetas);
	   printf("Address: %li\r\n", addressWrite);
   #endif

   restoBultos = bultos;
   
   numBultos = 	(bultos>=10) ? 10 : bultos;
   
   for(int i=0; i<etiquetas; i++){ 
   
	  printHeader();
      
      for(int j=0; j<numBultos; j++){
         readArray(initMemory+1, &w, 7);
         clearMemory(initMemory);
         printf("A%li,%li,2,4,1,1,N,\"B%i:%sKg\"\r\n",xPoint[j],yPoint[j],(10*i + (j+1)),w);
         initMemory+=8;
         pesoTotal += atof(w);
      }
      
      restoBultos -= 10;

   	  numBultos = (restoBultos >= 10) ? 10 : restoBultos;

      printf("P1\r\n"); 
   }
      
   #ifdef DEBUG
      printf("peso total: %6.2f\r\n", pesoTotal);
   #endif
      sprintf(total,"%6.2f",pesoTotal);
      replaceDotForComma(total);

   #ifdef DEBUG
      printf("Peso total en string: %s\r\n", total);
   #endif
      printTotalWeigth(total, bultos);
      
}


