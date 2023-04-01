void writeArray(long int dir, char *data, int size){
long i, address = dir;
     
   for(i=0;i<size;i++,dir++){
      write_ext_eeprom(dir,*(data+i));
      delay_ms(10);
   }
   delay_ms(10);
   write_ext_eeprom(--address,0x01);
   addressWrite+=7;
	#ifdef DEBUG
		printf("La nueva posicion de memoria es: %li\r\n",addressWrite );
	#endif
   delay_ms(10);
}

void readArray(long int dir,char *array1, int size){
int i;
   for(i=0;i<size;i++,dir++){
      *(array1+i)=read_ext_eeprom(dir);
       delay_ms(10);   
   }   
}

boolean isFormatEeprom(void){
	return (read_ext_eeprom(0x0FF8)==0xAA) ? true : false;
}

void formatEeprom(void){
   for(long i=0; i<0x0FF1;i=i+8){
      write_ext_eeprom(i,0x00);
      delay_ms(10);
   }
   write_ext_eeprom(0x0FF8,0xAA);  
}

void clearMemory(long int dir){
    write_ext_eeprom(dir,0x00);
    delay_ms(10);
    
       for(int i=0; i<7; i++){
         write_ext_eeprom(dir+i+1, 0xFF);
         delay_ms(10);
       }
}

long searchForMemorySpace(void){

   for(long i=0; i<0x0FF1; i=i+8){
      if(read_ext_eeprom(i)==0x00) return i;
      delay_ms(10);
   }

   return 0x0FF8;
}

void readAllEeprom(void){
int j=0;
   for(long i=0x0000; i<=0x0FFF; i++){
      printf("%lx ", read_ext_eeprom(i));
      j++;
      if(j==8){
         printf("   --%li-- \r\n",(long)(i/8));
         j=0;
      }  
   }
}
