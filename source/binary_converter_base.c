#include <stdio.h>
#include "binary_converter_base.h"

int custom_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int already_there(char *array, int num_strings, int string_length, const char *target) {
    for (int i = 0; i < num_strings; i++) {
        char *current_string = array + (i * string_length);
        if (custom_strcmp(current_string, target) == 0) {
            return 1;
        }
    }
    return 0;
}

int count_leading_0s(const char *num) {
    int count = 0;
    if (num == NULL || *num == '\0') return 0;
    while (num[count] == '0') count++;
    return count;
}

int it_is_0(const char *str) {
	if (str == NULL) return 0;
	for (; *str; str++)
        if (*str != '0') return 0;
    return 1;
}

int arrlen(const char *str) {
    int length = 0;
    while (str[length] != '\0')
		length++;
    return length;
}

void divide_by_2(char *inp, char *outp) {
	char result[arrlen(inp)];
	const int bitarrlen = (int)(arrlen(inp) * 3.32193 - 1) + 2;
	char bits[bitarrlen];
	int kek = bitarrlen;
	
	for (int i = 0; i < bitarrlen; i++) bits[i] = '0';
	
	// This for should exit through break!
	for (int i = 0; i < bitarrlen + 10; i++) {
		char *res = result;
		int started = 0;
		
		for (int temp = 0; *inp != '\0'; inp++) {
			temp = temp * 10 + (*inp - '0');
			if (temp >= 2) {
				int cnt = temp / 2;
				temp = temp % 2;
				*res++ = cnt + '0'; 
				started = 1;
			} else
				if (started)
					*res++ = '0';
		}
		inp--;
		kek--;
		if (kek == bitarrlen - 1){
			bits[kek] = *inp % 2 + '0';
			kek--;
		}
		if (!started) { 
			*res++ = '0'; 
			*res = '\0';
			break;
		}
		*res-- = '\0';
		bits[kek] = *res % 2 + '0';
		inp = result;
	}
	bits[bitarrlen] = '\0'; 
	int leadings = 0;
	for (int i = 0; bits[i] != '\0'; i++) {
        if (bits[i] == '1') break;
		leadings++;
        bits[i] = '0';
    }
	char *out = bits + leadings;
	for (; *out != '\0'; *out++, *outp++)
		*outp = *out;
	*outp = '.';
}

void multiply_by_2(char *num, int prec, char *buf) {
	char result[prec];
	while (*buf != '.') buf++;
	if (*num == '\0') {
		*buf = '\0';
		return;
	}
	for (; prec; prec--){
		buf++;
		int carry = 0;
    
		result[arrlen(num)] = '\0';
		for (int i = arrlen(num) - 1; i >= 0; i--) {
			int digit = num[i] - '0';
			int product = digit * 2 + carry;
			carry = product / 10;
			result[i] = (product % 10) + '0';
		}
    
		if (carry) *buf = '1';
		else *buf = '0';
		
		if (it_is_0(result)) break;
		num = result;
	}
	*++buf = '\0';
}

int check(char *arr, int maxlen) {
	int i = 0;
	char flag = 0;
    for (; arr[i] != '\0'; i++) {
        if ((arr[i] >= '0' && arr[i] <= '9') || arr[i] == '.'){
			if (i >= maxlen) return 0;
            if (arr[i] == '.') {
				arr[i] = '\0';
				if (flag) return 0;
				flag = i + 1;
			}
		} else return 0;
    }
	if (!flag) flag = i;
    return flag;
}