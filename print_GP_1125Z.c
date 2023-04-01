/*************************************************************************
                  ETIQUETAS PARA IMPRESORA GP-1125Z
*************************************************************************/
#include <math.h>

void printHeader(void){
   printf("^XA\r\n");
   printf("^SZ2^JMA\r\n");
   printf("^MCY^PMN\r\n");
   printf("^PW480\r\n");
   printf("^LL320\r\n");
   printf("~JSN\r\n");
   printf("^JZY\r\n");
   printf("^LH0,0^LRN\r\n");
   printf("^XZ\r\n");
   printf("^XA\r\n");
   printf("^FT131,77\r\n");
   printf("^CI0\r\n");
   printf("^A0N,51,71^FDTAUMM^FS\r\n");
}

void printFoot(void){
   printf("^PQ1,0,1,Y\r\n");
   printf("^XZ\r\n");
   printf("^XA\r\n");
   printf("^JUS\r\n");
   printf("^XZ\r\n");
}

void printLabel(char *peso, long bulto){
int i;
   printHeader();
   printf("^FT47,121\r\n");
   printf("^A0N,34,46^FDPESO : ^FS\r\n");
   printf("^FT47,220\r\n");
   printf("^A0N,34,46^FDHORA :^FS\r\n");
   printf("^FT47,277\r\n");
   printf("^A0N,34,37^FDFECHA :^FS\r\n");
   printf("^FT239,121\r\n");
   printf("^A0N,34,46^FD");
   
   for(i=0;i<7;i++) printf("%c",peso[i]);   
   
   printf(" kg");
               
   printf("^FS\r\n");
   printf("^FT262,220\r\n");
   printf("^A0N,34,46^FD");
   
      for(i=0;i<9;i++)
         printf("%c",frame.time[i]);   
   
   printf("^FS\r\n");
   printf("^FT213,277\r\n");
   printf("^A0N,34,38^FD");
   
      for(i=0;i<11;i++)
         printf("%c",frame.date[i]);   
         
   printf("^FS\r\n");
   printf("^FT47,168\r\n");
   
   printf("^A0N,34,46^FDBULTO No:^FS\r\n");
   printf("^FT307,168\r\n");
   
   printf("^A0N,34,53^FD%li^FS\r\n", bulto);
   printFoot();
}

void printTotalWeigth(char *peso, long bultos){
   int i;
   printHeader();
   printf("^FT118,125\r\n");
   printf("^A0N,34,46^FDPESO TOTAL ^FS\r\n");
   printf("^FT135,172\r\n");
   printf("^A0N,34,46^FD");
   
      for(i=0;i<7;i++)
         printf("%c",peso[i]);
   
   printf("Kg^FS\r\n");
   printf("^FT78,223\r\n");
   printf("^A0N,34,46^FDTOTAL DE BULTOS^FS\r\n");
   printf("^FT207,269\r\n"); 
   printf("^A0N,34,53^FD%li^FS\r\n", bultos);
   printFoot();
}

void printBultos(void){
long xPoint[20] = {26,89,26,89,26,89,26,89,26,89,244,306,244,306,244,306,244,306,244,306};
long yPoint[20] = {115,115,147,147,176,176,208,208,239,239,115,115,147,147,176,176,208,208,239,239};
long bultos = (long)(addressWrite/8);
signed long numBultos;
int etiquetas;
int x=0, y=0;
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
         printf("^FT%li,%li\r\n",xPoint[x],yPoint[y]);
         printf("^A0N,23,31^FDB%i: ^FS\r\n",(10*i + (j+1)));
         x++;
         y++;
         readArray(initMemory+1, &w, 7);
         clearMemory(initMemory);
         initMemory+=8;
         printf("^FT%li,%li\r\n",xPoint[x],yPoint[y]);
         printf("^A0N,23,31^FD%s Kg ^FS\r\n",w);
         x++;
         y++;
         pesoTotal += atof(w);
      }
      
      restoBultos -= 10;

      numBultos = (restoBultos >= 10) ? 10 : restoBultos;

      printFoot();   
      x=0;
      y=0;
      delay_ms(200);
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


