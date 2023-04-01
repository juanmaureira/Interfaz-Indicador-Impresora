#define atof(s)   strtof(s, 0)
#define isdigit(x)  isamong(x,"0123456789")

float strtof(char *s, char *endptr){
   float pow10 = 1.0, result = 0.0;
   int1 skip = 1, sign = 0, point = 0;
   char c;
   unsigned int8 ptr = 0;

   if (!s)
      return 0;

   for(c=s[ptr++]; c!=0; c=s[ptr++]){
      if (skip && c != 0x20){
         skip = 0;
         if (c == '+'){
            sign = 0;
            continue;
         }            
         else if (c == '-'){
            sign = 1;
            continue;
         }
      }
      if (!skip && (c == ',') && !point)
            point = 1;
      else if (!skip && isdigit(c)){
         c -= '0';
         if (point){
            pow10 = pow10 * 10.0;
            result += (float)c / pow10;   
         }
         else{
            result = 10.0 * result + (float)c;
         }
      }
      else if (!skip)
         break;
   }

   if (sign)
      result = -1*result;

   return(result);
}

void replaceDotForComma(char *ptr){
   for(int i=0; i<7; i++){
      if(*(ptr+i) == '.') *(ptr+i) = ',';
   }
}