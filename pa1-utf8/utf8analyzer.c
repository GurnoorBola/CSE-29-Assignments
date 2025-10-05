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

int8_t codepoint_size(unsigned char c){
		if ((c >> 7) == 0){
			return 1;
    } else if ((c >> 5) == 0b110){
			return 2;
    } else if ((c >> 4) == 0b1110){
			return 3;
    } else if ((c >> 3) == 0b11110){
    	return 4;
    }	
    return -1;
}

void utf8_substring(const char str[], int start, int end) {
    int length = strlen(str);
    int idx = -1;
    char res[length];
    res[0] = '\0';
    for (int i=0; i < length; i++){
	  if (((unsigned char)str[i] >> 6) != 0b10){
		 idx += 1;
	  }
	  if (idx < start){
		 continue;
	  }
	  if (idx == end){
		 printf("%s\n", res);
		 return;
	  }
	  char temp[2] = {str[i], '\0'};
	  strcat(res, temp); 
    }
    printf("%s\n", res);
    return;
}

int32_t codepoint_at(char str[], int32_t byte_index) {
    int32_t byte = (unsigned char)str[byte_index];

    if (byte >> 6 == 0b10){
	    return -1;
    } else if ((byte >> 5) == 0b110){
	    int32_t res = byte & 0b00011111;
	    for (int i = 1; i < 2; i++){
		    res = (res << 6) | (str[byte_index+i] & 0b00111111);
	    }
	    return res;
    } else if ((byte >> 4) == 0b1110){
	    int32_t res = byte & 0b00001111;
	    for (int i = 1; i < 3; i++){
		    res = (res << 6) | (str[byte_index+i] & 0b00111111);
	    }
	    return res;
    } else if ((byte >> 3) == 0b11110){
	    int32_t res = byte & 0b00000111;
	    for (int i = 1; i < 4; i++){
		    res = (res << 6) | (str[byte_index+i] & 0b00111111);
	    }
	    return res;
    } else {
	    return byte;
    }
}

int is_animal_emoji_at(char str[], int byte_index, size_t l){
	size_t length = l;	
	int32_t cdpt = codepoint_at(str, byte_index);
	if (cdpt == -1){
		return 0;
	}
	if (((0x1F400 <= cdpt) && (0x1F43F >= cdpt)) || ((0x1F980 <= cdpt) && (0x1F9AE >= cdpt))){
		return 1;
	}
	return 0;
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
	
	printf("Bytes per code point: ");
	for (int i=0; i < length; i++){
		int8_t size = codepoint_size(buffer[i]);
		if (size != -1){
			printf("%d ", size);
		}
	}
	printf("\n");	
	
	printf("Substring of the first 6 code points: ");
	utf8_substring(buffer, 0, 6);
	
	printf("Code points as decimal numbers: ");
	for (int i=0; i < length; i++){
		int32_t num = codepoint_at(buffer, i);
		if (num != -1){
			printf("%d ", num);
		}
	}
	printf("\n");	
	

	//if there is an animal emoji starting at current byte, get the number of
	//bytes it has and concatonate that many bytes starting from start to
	//start+num_bytes then print
	printf("Animal Emojis: ");
	for (int i=0; i < length; i++){
		if (is_animal_emoji_at(buffer, i, length)){
			int8_t num_bytes = codepoint_size(buffer[i]);
			printf("%.*s ", num_bytes, &buffer[i]);
		}
	}
	printf("\n");	
	return 0;
}
