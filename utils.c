boolean isSummationActive(void){
	return (read_eeprom(0x00)==0xEE) ? true : false;
}   

long initPositionMemory(void){
   return searchForMemorySpace();
}
  
void initMicro(void){
   set_tris_b(0xFF);
   port_B_pullups(0xFF); 

   init_ext_eeprom();
   delay_ms(10);
   
   if(!isFormatEeprom()) {

	#ifdef DEBUG
      printf("Formateando eeprom\r\n");
	#endif

      formatEeprom();
   }

   if(isSummationActive()) flagSumar=true;  

      addressWrite = initPositionMemory();
      
   if(addressWrite>0x0FF8)	printf("No hay espacio en memoria\r\n");

	#ifdef DEBUG
    	printf("La posicion de memoria actual es: %li\r\n",addressWrite);
	#endif		
   
   clearBuffer();
   enable_interrupts(INT_EXT_H2L);
   enable_interrupts(INT_EXT1_H2L);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
}

short isThereData(void){
	return (read_eeprom(0xFF)!=0xFF) ? true : false;
}

void sumatoria(){
	if(!isSummationActive()) write_eeprom(0x00,0xEE);
	flagSumar=true;
	flagSumatoria=false;
}

void proccessReceive(){

		 #if (INDICADOR_K7)
         	replaceDotForComma(frame.weigth);
		 #endif
		
		 #if (INDICADOR_HC200)
			replaceDotForComma(frame.net);
		 #endif

         if(flagSumar){
			#if (INDICADOR_HC200)
            	if(addressWrite<=0x0FF0) writeArray((++addressWrite), frame.net, 7);
            	else printf("No hay espacio en memoria!!!\r\n");
			#endif

			#if (INDICADOR_K7)
            	if(addressWrite<=0x0FF0) writeArray((++addressWrite), frame.weigth, 7);
            	else printf("No hay espacio en memoria!!!\r\n");
			#endif
         }
         
         bulto = (long)(addressWrite/8);
         
		if(bulto == 0) bulto = 1;

		 #ifdef DEBUG
         	printf("Bulto: %li  -  addressWrite: %li\r\n", bulto, addressWrite);
 		 #endif

		 #if (INDICADOR_HC200)
         	printLabel(frame.net, bulto);
         #endif

		 #if (INDICADOR_K7)
			printLabel(frame.weigth, bulto);
		 #endif
		 
         flagRcv=false;
}

void printTotal(){
         printBultos();
         flagTotal = false;
         flagSumar = false;
         addressWrite = initPositionMemory();
         write_eeprom(0x00,0xFF);
}

void runInterfaz(){
output_low(LED);
initMicro();
   while(TRUE){
     
      if(flagSumatoria)sumatoria();

      if(flagRcv) proccessReceive();
      
      if(flagTotal) printTotal();

   }
}

#INT_EXT
void  iniciaSumatoria(void){
   flagSumatoria = true;
}

#INT_EXT1
void  imprimeTotalEtiquetas(void) {
   flagTotal = true;
}