/*
                              37 caracteres utilies
0D 0A 4E 6F 2E 30 30 30 32 20 31 33 2D 30 35 2D 32 30 32 31 20 31 35 3A 35 31 3A 31 36 20 20 31 31 32 2E 34 35 6B 67 0D 0A
      N  o  .  0  0  0  2     1  3  -  0  5  -  2  0  2  1     1  5  :  5  1  :  1  6        1  1  2  .  4  5  k  g
*/

#use rs232(UART, disable_ints)


void clearBuffer(void){
   memset(buffer, 0, sizeof(buffer));
   next = 0;
}

void receiveData(void){
   if(buffer[0] == 0x0D && buffer[1] == 0x0A && buffer[39] == 0x0D && buffer[40] == 0x0A){
      frame = buffer;
   }else{
		frame = 0;	
		flagRcv = false;
   }
   clearBuffer();   
}

#INT_RDA
void isrRda(void){

 buffer[next++] = getc();

 if(next==41){
	flagRcv = true;
	receiveData();
 }

 if(next>41 || buffer[0] != 0x0D) clearBuffer();

}
