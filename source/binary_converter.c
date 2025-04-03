#include <stdio.h>
#include "binary_converter_base.h"

void main() {
	const int maxlen;
	printf("\n(int) Max input length: ");
	scanf("%d", &maxlen); 
	
	const int prec;
	printf("\n(int) Binary places: ");
	scanf("%d", &prec);
	
	const int buflen = maxlen + prec;
	char buffer[buflen];
	
	for (char inpstr[maxlen]; *inpstr != 'e';){
		printf("\n\n-----------------------\nInput: "); 
		scanf("%s", inpstr);
		
		for(int i = 0; i < buflen; i++)
			buffer[i] = '0';
		
		char neg = 0;
		
		if (*inpstr == '-'){
			*inpstr = '0';
			neg = 1;
		}
		
		int dot = check(inpstr, maxlen);
	
		char *rem = inpstr + dot;
	
		if (dot) {
			if (neg) buffer[0] = '-';
			divide_by_2(inpstr + count_leading_0s(inpstr), buffer + neg);
			multiply_by_2(rem, prec, buffer + neg);
			printf("\nResult: %s",buffer);
			
			//printf("\n\n"); // to print all of the buffer
			//for (int i = 0;i < buflen;i++) printf("%c",buffer[i]);
		
		} else printf("\nInvalid number format!");
	}
}