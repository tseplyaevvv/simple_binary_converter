# simple_binary_converter

This program is a simple C99 console app to convert numbers from decimal form (like 123.1415) to binary 
without using C data types to store the value, making it easy to convert big numbers like 52!. 
The program allows to set the precision in binary places.

Here is an examle of using the program.
```
Welcome! This program is aimed to convert decimal numbers to binary.
Use "exit" to finish.

(int) Max input length: 120

(int) Binary places: 12


-----------------------
Input: 3.1415

Result: 11.001001000011

-----------------------
Input: 2423523239

Result: 10010000011101000000011110100111

-----------------------
Input: 12312u3
Invalid array.


-----------------------
Input: 80658175170943878571660636856403766975289505440883277824000000000000

Result: 1011111101111001010010100110100011001001110100110001100100100111001111111010110100101100011000000010101101101101011100101110010110000000101010100111100000011000111000101010110010000000000000000000000000000000000000000000000000

-----------------------
Input: exit
```
