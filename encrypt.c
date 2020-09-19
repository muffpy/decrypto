/**********************************************************************
 *  Encrypt a file using subset-sum algorithm.
 *
 *  Compiliation:   % gcc226 encrypt.c key.c -o encrypt
 *  Execution:      % encrypt password < rand8.txt
 *                  vbskbezp
 *
 *  Note: need to set C = 8 in key.h before compiling and executing
 *        with rand8.txt.
 *
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "key.h"
#include "keysize.h"

// Key createNumKey(int);
// unsigned char * makeCopy(unsigned char *, char *, int);
// void append(char* s, char c);
int main(int argc, char *argv[]) {
   int i;
   unsigned char buffer[C+1];     // temporary string buffer 
   Key password;                  // the user supplied password
   Key encrypted;                 // the encrypted password
   Key T[N];                      // the table T

   if (argc != 2) exit(EXIT_FAILURE);

   password = KEYinit((unsigned char *) argv[1]);
   // print out input password
   printf("   ");
   KEYshow(password);
   printf("\n");

   // read in table T
   for (i = 0; i < N; i++) {
      scanf("%s", buffer);
      T[i] = KEYinit(buffer);
   }
   // Key one, zero; // representation of 000......0001 in binary

   // zero = KEYinit((unsigned char *) "aaaaa");
   // one = KEYinit((unsigned char *) "aaaab");
   // int result = equalKeys(one,one);
   // printf("Equality : %d", result);
   // printf("\n");
   
   // compute subset sum
   encrypted = KEYsubsetsum(password, T);

   // print results
   printf("\n   ");
   KEYshow(encrypted);
   
   return 0;
}

// Key createNumKey(int num){
//    Key a; // key to return
//    unsigned char * n[C];
//    char letter[N];

//    if (num < 33){
//       char t = ALPHABET[num];
//       append(letter, t);
//       printf("%c", t);
//       for(int loop = 0; loop < 40; loop++)
//       // printf("%u", letter[loop]);

//       *n = makeCopy(*n, letter, C);
//    }
// }

// unsigned char * makeCopy(unsigned char * arr, char * letter, int c){
//    int len = strlen(letter);
//    printf("%d", len);
//    for (int i = 0; i<=len; i++){
//       arr[i] = 'a';
//       printf("%c", arr[i]);
//    }
//    return arr;
// }

// void append(char* s, char c) {
//         int len = strlen(s);
//         printf("%d", len);
//         s[0] = c;
//         s[len+1] = '\0';
// }