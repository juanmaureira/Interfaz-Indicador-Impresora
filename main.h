#include <18F2520.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOPBADEN                 //PORTB pins are configured as digital I/O on RESET
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES HS
#use delay(crystal=20000000)

#define INICIO    PIN_B0
#define IMPRESION PIN_B1
#define TERMINO   PIN_B2
#define LED       PIN_C0

#define IMPRESORA_GP_1125Z	true 
#define IMPRESORA_TLP_2844 	false 

#define INDICADOR_K7	false
#define INDICADOR_HC200	true 

// PARA DEBUGEAR, SETEAR ESTA VARIABLE EN TRUE
#define DEBUG_MODE false

#if (DEBUG_MODE)
	#define DEBUG 	 
#endif

#if (INDICADOR_HC200)

	#define MAXBUFFER 80

	typedef struct{
	   char    date[11];         
	   char    time[9];       
	   char    no[7];         
	   char    net[10];      
	   char    tare[11];         
	   char    gross[10];      
	   char    total[10];   
	   char    ref[13];      
	}Packet;

#endif

#if (INDICADOR_K7)

	#define MAXBUFFER 48

	typedef struct{
	   char    stx[2];
	   char    number[8];       
	   char    date[11];       
	   char    time[9];         
	   char    weigth[7];
	   char    unit[2];
	   char    etx[2];                
	}Packet;

#endif

Packet frame;
char buffer[MAXBUFFER];
int next=0;
char data;
boolean flagRcv = false;
boolean flagTotal = false;
boolean flagSumatoria = false;
boolean flagSumar = false;
long addressWrite;
long bulto;

#if (INDICADOR_HC200)
	#include <comunication_HC200.c>
#endif
#if (INDICADOR_K7)
	#include <comunication_K7.c>
#endif
#include "2432.c"
#include <write_i2c_eeprom.c>

#include "stringToFloat.c"

#if (IMPRESORA_GP_1125Z)
	#include <print_GP_1125Z.c>
#endif
#if (IMPRESORA_TLP_2844)
	#include <print_TLP_2844.c>
#endif

#include <utils.c>