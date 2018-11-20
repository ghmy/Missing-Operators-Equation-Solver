# Missing Operators Equation Solver
Using 123456789 string and putting +, -, * and / operations between the digits, algorithm tries to find all the solutions to given number. 
Concatenation is also a valid operation. However, paranthesis is not considered in this algorithm. 

I ran the algorithm and its fast enough to show results (on Linux Mint 19 with QtCreator), but there is still a room for optimization. Though slightly more complex algorithm would be required. 

One can hold the result for up to last + or - sign in the solve function and calculate for the rest of
the string. 

For example, let's say we have calculated:
12 * 34 + 5 - 6*7 + 8 - 9
and the next operand would be * instead of - between 8 and 9 so the algorithm will calculate
12 * 34 + 5 - 6*7 + 8 * 9

However, instead of calculating whole string again, we can hold the result for up to last + and - operators 
which would be 12 * 34 + 5 - 67 and calculate the rest of the string as 8 * 9 and add the results. 
