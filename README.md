<h1> Decrypto </h1>

A decryption scheme for Subset-sum encrypted passwords.

Brute force solution - Every single possible combination of subset sum that could work as a result of running the encrypted password through the symbol table. This is really ineffecient as there are (32^C) million different combinations for a C-character password that only uses the lowercase alphabet and the numbers 0-C.

Efficient solution -
