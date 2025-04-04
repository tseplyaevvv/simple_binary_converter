# simple_binary_converter

This program is a simple C99 console app to convert numbers from decimal form (like 123.1415) to binary 
without using C data types to store the value, making it easy to convert big numbers like 52!. 
The program allows to set the precision in binary places.

Here is an examle of using the program.
```
Welcome! This program is aimed to convert decimal numbers to binary.
Commands: "exit", "history".

(int) Max input length: 120

(int) Binary places: 12


-----------------------
Input: 3.1415

Result: 11.001001000011

-----------------------
Input: 2423523239123121

Result: 1000100111000010111001111001110001011101100010110001

-----------------------
Input: 213u99

Invalid number format!

-----------------------
Input: -1231

Result: -10011001111

-----------------------
Input: 3.1415
(has been entered before)

Result: 11.001001000011

-----------------------
Input: history

3.1415
11.001001000011

2423523239123121
1000100111000010111001111001110001011101100010110001

213u99
Invalid number format!

-1231
-10011001111



-----------------------
Input: exit
```
