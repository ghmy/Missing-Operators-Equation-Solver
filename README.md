# Missing Operators Equation Solver
Using 123456789 string and putting +, -, * and / operations between the digits, algorithm tries to find all the solutions to given number. 
Concatenation is also a valid operation. However, paranthesis is not considered in this algorithm. 

I ran the algorithm on Linux Mint 19 with QtCreator environment, and its fast enough (seemingly immediate) to show results, but there is still a room for optimization. Though slightly more complex algorithm would be required. 

One can hold the result for up to last + or - sign in the solve function and calculate for the rest of
the string. 
For example, let's say we have calculated:
12 * 34 + 5 - 6*7 + 8 - 9
and the next operand would be * instead of - between 8 and 9 so the algorithm will calculate
12 * 34 + 5 - 6*7 + 8 * 9

However, instead of calculating whole string again, we can hold the result for up to last + and - operators 
which would be 12 * 34 + 5 - 67 and calculate the rest of the string as 8 * 9 and add the results. 

As of 21.11.2018, v2 is added to the repository which is implemented with this optimization idea. 
According to the tests, the main implementation takes about 0.081 seconds while v2 takes around 0.06 seconds to run solve function. 
