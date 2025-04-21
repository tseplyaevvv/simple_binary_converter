#include <stdio.h>
#include "binary_converter_base.h"

void main() {
	
	printf("Welcome! This program is aimed to convert decimal numbers to binary.\nCommands: \"exit\", \"history\".\n");
	
	const int histlen = 20;
	//Uncomment for user input.
	//printf("\n(int) History length: ");
	//scanf("%d", &histlen);
	
	const int maxlen;
	printf("\n(int) Max input length: ");
	scanf("%d", &maxlen); 
	
	const int prec;
	printf("\n(int) Binary places: ");
	scanf("%d", &prec);
	
	const int buflen = maxlen * 3 + prec;
	char buffer[buflen];
	char set_dec[histlen][maxlen];
	char set_bin[histlen][buflen];
	int a = 0;
	
	for (char inpstr[maxlen]; *inpstr != 'e'; a++){
		printf("\n\n-----------------------\nInput: "); 
		scanf("%s", inpstr);
		
		int do_not_write = 0;
		char *dec_1 = *set_dec;
		
		if(*inpstr == 'h'){
			printf("\n");
			getchar();
			for(int i = 0; i < a;i++){
				printf(set_dec[i]);
				printf("\n");
				printf(set_bin[i]);
				printf("\n\n");
				if (i % 4 == 0 && i){
					printf("\nPress ENTER ...");
					getchar();
				}
			};
			continue;
		}
		
		if (already_there(dec_1, histlen, maxlen, inpstr)){
			printf("(has been entered before)\n");
			a--;
			do_not_write = 1;
		}else snprintf(set_dec[a], maxlen, inpstr);
		
		
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
			if (!do_not_write)
				snprintf(set_bin[a], buflen, buffer);
		
		} else {
			printf("\nInvalid number format!");
			if (!do_not_write)
				snprintf(set_bin[a], 23, "Invalid number format!");
		};
	}
}