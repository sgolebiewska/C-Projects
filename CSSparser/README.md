Commands: <br/>
 <br/>
In the following commands, i and j are positive integers (fit within int), while n is a legal attribute name. <br/>
 <br/>
* ???? - beginning of the command section; <br/>
* **** - resume reading CSS; <br/>
* ? - print the number of CSS blocks; <br/>
* i,S,? - print the number of selectors for block number i (numbers starting from 1), skip if there is no such block; <br/>
* i,A,? - print the number of attributes for block number i, skip if there is no such block or block; <br/>
* i,S,j - print the j-th selector for the i-th block (block and attribute numbers start from 1), skip if there is no block or selector; <br/>
* i,A,n - print the value of the attribute with the name n for the i-th block, skip if there is none; <br/>
* n,A,? - print the total (for all blocks) number of occurrences of the attribute with the name n. (Duplicates within a single block should be removed during loading). It can be 0; <br/>
* z,S,? - print the total (for all blocks) number of occurrences of the selector z. It can be 0; <br/>
* z,E,n - print the value of the attribute with the name n for the selector z, taking the last occurrence if there are multiple occurrences of selector z. Skip if not present; <br/>
* i,D,* - remove the entire block number i (i.e., separators + attributes), print deleted after successful execution; <br/>
* i,D,n - remove the attribute with the name n from the i-th block, if the operation results in an empty block, it should also be removed (along with any selectors), print deleted after successful execution. <br/>
 <br/>
