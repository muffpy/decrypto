#include <stdlib.h>
#include <stdio.h>
#include <math.h> // includes power function
#include "key.h"

void bruteForce(Key *, Key T[N]);
int main(int argc, char *argv[]){

   unsigned char buffer[C+1];     // temporary string buffer 
   Key encrypted;                  // the encrypted password
   Key decrypted;                 // the decrypted result (user password)
   Key T[N];                      // the table T

   if (argc != 2) exit(EXIT_FAILURE);

   encrypted = KEYinit((unsigned char *) argv[1]);
   
   // print out input password
   printf("   ");
   KEYshow(encrypted);
   printf("\n");

   // read in table T
   for (int i = 0; i < N; i++) {
      scanf("%s", buffer);
      T[i] = KEYinit(buffer);
   }

   bruteForce(&encrypted,T);

}

void bruteForce(Key * encrypted, Key T[N]){
   Key sum_count;
   Key subset_sum; // subset sum of sum_count

   // Generate one and zero keys
   Key one, zero; // representation of 000......0001 in binary
   char res[C];
   char first = 'a';
   char second = 'b';

   for (int i = 0; i < C; i++){
      res[i] = first;
   }

   zero = KEYinit((unsigned char *) res);
   res[C - 1] = second;
   one = KEYinit((unsigned char *) res);

   long long int len = pow(32, C); int i = 0;
   sum_count = zero;
   while (i < len){
      if (equalKeys(*encrypted, KEYsubsetsum(sum_count,T))){
         printf("\n");
         printf("User password:  ");
         KEYshow(sum_count);
      }
      // KEYshow(sum_count); // debugging
      sum_count = KEYadd(sum_count,one);
      subset_sum = KEYsubsetsum(sum_count,T);
      i++;
   }

}
