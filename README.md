<h1> Decrypto </h1>

A decryption scheme for Subset-sum encrypted passwords

Subset-sum encryption - User-input password is encoded to 5-bit  using a 32-char alphabet: `abcdefghijklmnopqrstuvwxyz012345` where `a` represents `00000`, `b` represnts `00001` etc. Thus, N = 5 * C where C is the number of characters in the password. The program reads in the table T, then uses the bits of the password to select the words from the table to add together, and prints out the encrypted version.

## Decryption solutions:##
* Brute force method - 
Every single possible combination of subset sum that could work as a result of running the encrypted password through the symbol table. This is really ineffecient as there are (32^C) million different combinations for a C-character password that only uses the lowercase alphabet and the numbers 0-C

* Efficient method -
  1. Compute all subset sums generated by the first half from digit 0 to N/2, of every subset in the input file tables, using brute force. For example, a C-digit password would produce 2^(N/2) first-half-sums `00000...[00000...00000]` to `00000...[11111...11111]` 
    
  2. Store the results in a hash table
  3. Check if the first-half-sum equals the user input encrypted password using constant lookup and print matches
  3. Compute encryption key of every second-half-sum `00000...[11111...11111]` to `11111...[11111...11111]`
  4. For each of the 2^(N/2) second-half-sums, look up (in **expected** constant time) which stored first-half-sum adds with the second-half-sum to equal the encrypted key and print matches.

[complexity.txt](complexity.txt) - time complexity analysis for the decryption of each C-char password

P.S: C++ was used for the second one as unordered_map was readily available to implement a hash table - therefore, I converted key.c to key.hpp to experiment with the splitting sums idea.
Hence, `decrypt.c` is still pending
