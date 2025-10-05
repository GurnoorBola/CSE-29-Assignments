#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t is_ascii(char string[], size_t l) {
	size_t length = l; 
	
	for (int i = 0; i < length; i++){
		if ((string[i] >> 7) != 0){
			return 0;
		}
	}
	return 1;
}

int32_t capitalize_ascii(char str[], size_t l) {
	int32_t res = 0;
	size_t length = l;
	for (int i=0; i < length; i++){
		if (str[i] >= 97 && str[i] <= 122){
			res += 1;
			str[i] -= 32;
		}
	}
	return res;
}

int32_t utf8_strlen(char str[], size_t l) {
    size_t length = l;
    int32_t res = 0;

    for (int i=0; i < length; i++){
			unsigned char c = (unsigned char)str[i];
			if ((c>>6) != 0b10){
				res += 1;
			}
    }
    return res;
}

int main(int argc, char** argv) {
	char buffer[100];
	uint8_t valid_ascii;
	
	printf("Enter a UTF-8 encoded string: ");
	if ((fgets(buffer, 99, stdin) == NULL)){
		printf("Error");
		return 1;
	}

	//strip new line
	size_t length = strcspn(buffer, "\n");
	if (buffer[length] == '\n'){
		buffer[length] = '\0';
	}


	valid_ascii = is_ascii(buffer, length);
	printf("Valid ASCII: %s\n", valid_ascii ? "true" : "false");

	char caps[100];
	strcpy(caps, buffer);
	capitalize_ascii(caps, length);
	printf("Upercased ASCII: %s\n", caps);

	printf("Length in bytes: %ld\n", length);
	
	
	int32_t utf_len = utf8_strlen(buffer,length);
	printf("Number of code points: %d\n", utf_len);
	return 0;
}
