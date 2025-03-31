#include <stdio.h>

int count_leading_0s(const char *num) {
    int count = 0;
    if (num == NULL || *num == '\0') return 0;
    while (num[count] == '0') count++;
    return count;
}

int compare_with_0(const char *str) {
    
	if (str == NULL) return 0;
	while (*str) {
        if (*str != '0') {
            return 0;
        }
        str++;
    }
    return 1;
}

int arrlen(const char *str) {
    int length = 0;
    while (str[length] != '\0')
		length++;
    return length;
}

void divide_by_2(char *inp, char *outp) {
	int inplen = arrlen(inp);
	char result[inplen];
	int bitarrlen = (int)(inplen * 3.32193 - 1)+2;
	char bits[bitarrlen];
	int kek = bitarrlen;
	int loopcount = 0;
	int temp;
	int cnt;
	char *res;
	char *inp0;
	int started;
	
	for (int i = 0; i < bitarrlen; i++) bits[i] = '0';
	
	while (loopcount < bitarrlen+10) {
		loopcount++;
		if (loopcount > bitarrlen+5)
			printf("!!! WE HAVE A PROBLEM !!!");
		temp = 0;
		res = result;
		inp0 = inp;
		started = 0;
		
		while (*inp != '\0') {
			temp = temp * 10 + (*inp - '0');
			if (temp >= 2) { 
				cnt = temp / 2; 
				temp = temp % 2; 
				*res++ = cnt + '0'; 
				started = 1; 
			} else if (started) { 
				*res++ = '0'; 
			}       
			inp++; 
		}
		inp--;
		kek--;
		
		if (kek==bitarrlen-1){
			bits[kek]=*inp%2+'0';
			kek--;
		}
		if (!started) { 
			*res++ = '0'; 
			*res = '\0';
			break;
		}
		
		*res = '\0'; 
		*res--;
		bits[kek]=*res%2+'0';
		inp = result;
	}
	bits[bitarrlen] = '\0'; 
	int leadings = 0;
	for (int i = 0; bits[i] != '\0'; i++) {
        if (bits[i] == '1') break;
		leadings++;
        bits[i] = '0';
    }
	char *out = bits+leadings;
	
	for (;*out!='\0';*out++,*outp++) *outp = *out;
	*outp='.';
}

void multiply_by_2(char *num, char *result, int prec, char *buf) {
	while (*buf!='.') buf++;
	if (*num == '\0') {
		*buf = '\0';
		return;
	}
	
	while (prec){
		buf++;
		int length = arrlen(num);
		int carry = 0;
    
		result[length] = '\0';
		for (int i = length - 1; i >= 0; i--) {
			int digit = num[i] - '0';
			int product = digit * 2 + carry;
			carry = product / 10;
			result[i] = (product % 10) + '0';
		}
    
		if (carry) *buf='1';
		else *buf='0';
		
		if (compare_with_0(result)) break;
		num = result;
		prec--;
	}
	buf++;
	*buf = '\0';
}

int check_1(char *arr) {
	int i = 0;
	char flag = 0;
    while (arr[i] != '\0') {
        if ((arr[i] >= '0' && arr[i] <= '9') || arr[i] == '.'){
            if (arr[i] == '.') {
				arr[i] = '\0';
				if (flag) return 0;
				flag = i+1;
			}
		} else return 0;
		i++;
    }
	if (!flag) flag = i;
    return flag;
}

void main() {
	
	printf("Welcome! This program is aimed to convert decimal numbers to binary.\nUse \"exit\" to finish.\n");

	int maxlen;
	int dot;
    
	printf("\n(int) Max input length: ");
	scanf("%d", &maxlen);
	char teststr[maxlen]; 
	
	int prec;
	printf("\n(int) Binary places: ");
	scanf("%d", &prec);
	char result[prec];
	char neg;
	char *rem;
	
	const int buflen = maxlen + prec;
	char buffer[buflen];
	
	
	while (1){
		for(int i = 0; i<buflen ;i++)buffer[i]= '0';
		neg = 0;
		printf("\n\n-----------------------\nInput: ");
		scanf("%s", teststr);
	
		if (*teststr == 'e') return;
		
		if (*teststr == '-'){
			*teststr = '0';
			neg = 1;
		}
		
		dot=check_1(teststr);
	
		rem = teststr+dot;
	
		if (dot) {
			
			if (neg) buffer[0] = '-';
			divide_by_2(teststr + count_leading_0s(teststr),buffer+neg);
			multiply_by_2(rem, result, prec, buffer+neg);
			
			printf("\nResult: %s",buffer);
			
			//printf("\n\n"); // to print all of the buffer
			//for (int i = 0;i < buflen;i++) printf("%c",buffer[i]);
		
		} else {
			printf("Invalid array.\n");
		}
	}
}