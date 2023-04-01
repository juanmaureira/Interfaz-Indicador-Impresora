# use rs232(UART, disable_ints)

void clearBuffer(void){
   memset(buffer, 0, sizeof(buffer));
   next=0;
   data=0;
}

short validaDatos(void){
   frame = buffer;
   clearBuffer();
   return true;
}
/*

                                                         FORMATO DE TRANSMISION
                                          28-05-2020 15:48:02   12 W    1.40kg     0.00kg    1.40kg   24.54kg 
 2  8  -  0  5  -  2  0  2  0     1  5  :  4  8  :  0  2           1  2     W              1  .  4  0  k  g                 0  .  0  0  k  g              1  .  4  0  k  g           2  4  .  5  4  k  g 
------------11 byte-------------|---------9 byte-----------|-----7 byte--------|--------10 byte---------------|--------11 byte-----------------|--------10 byte--------------|--------10 byte--------------|-------------13 byte-----------------|
32 38 2D 30 35 2D 32 30 32 30 20 31 35 3A 34 38 3A 30 32 20 20 20 31 32 20 57 20 20 20 20 31 2E 34 30 6B 67 20 20 20 20 20 30 2E 30 30 6B 67 20 20 20 20 31 2E 34 30 6B 67 20 20 20 32 34 2E 35 34 6B 67 20 20 20 20 20 20 20 20 20 20 20 20 0D 0A
|---------DATE------------------|---------HORA-------------|-----No------------|-----------NET----------------|-----------TARE-----------------|----------GROSS--------------|---------TOTAL---------------|--------------FINAL DATA-------------|    
*/
#int_rda
void isrRda(void){
   data = getc();
   if(data!=0x0D && data!=0x0A){
      buffer[next++] = data;
   }else if(data ==0x0A){
      if(validaDatos())
         flagRcv = true;
      else{
         flagRcv = false;
         clearBuffer();
      }      
   }   
}

