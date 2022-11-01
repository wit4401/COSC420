# Program 2: Finding Mutual Friends in a Social Network with MapReduce
Identify threesomes of users that are mutual friends in a social network, i.e. A friends with B, B 
friends with C, and C friends with A. The output should enumerate the mutual friends for each 
user and avoid duplicate entries, i.e. the trio of users A, B, and C will contribute output:

<A,B,C> to A's list  
<B,A,C> to B's list   
<C,A,B> to C's list 

This needs to be implemented in the Map/Reduce paradigm. The input to the Map/Reduce 
program is set of friend lists. Each file in the input contains the id of the user followed by a list of 
her/his friends. All identifiers are integer values separated by spaces and all friends in the list 
appear on a single line. For example, the file: 

117 2149 84 57 6048

is the list of user 117's friend, consisting of users 2149, 84, 57, and 6048. You may assume that 
the input has two properties:

* Symmetry: If A is a friend of B then B is a friend of A 
* No Duplicates: Each friend appears in a list at most once. 

All of the triples for a single user should appear contiguously in the output.
