#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t is_ascii(char string[]) {
	int length = strlen(string);
	
	for (int i = 0; i < length; i++){
		if ((string[i] >> 7) != 0){
			return 0;
		}
	}
	return 1;
}





int main(int argc, char** argv) {
	char buffer[100];
	uint8_t result;

	printf("Valid ASCII: ");
	if ((fgets(buffer, 99, stdin) == NULL)){
		printf("Error");
		return 1;
	}
	result = is_ascii(buffer);
	printf("%s\n", result ? "true" : "false");
	return 0;
}
