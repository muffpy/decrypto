<h1> Decrypto </h1>

A decryption scheme for Subset-sum encrypted passwords

* Brute force method - 
Every single possible combination of subset sum that could work as a result of running the encrypted password through the symbol table. This is really ineffecient as there are (32^C) million different combinations for a C-character password that only uses the lowercase alphabet and the numbers 0-C.

* Efficient method -
Compute all subset sums generated by the first half, of every subset in the input file tables, using brute force and store the results in a hash table. For each of the N/2 first-half-sums, look up (in **expected** constant time) which stored second-half-sum adds with the first-half-sum to equal the encrypted key.

Complexity analysis:

P.S: C++ was used for the second one as unordered_map was readily available to implement a hash table - therefore, I converted key.c to key.hpp to experiment with splitting sums idea.
Hence, `decrypt.c` is still pending
