#include <stdio.h>
#include <string.h>

int main() {
    while (1) {
        char myString[50];

        // Input a string (without spaces)
        printf("Enter a string (no spaces): ");
        scanf("%s", myString);

        printf("You entered: %s\n", myString);   
    }
    return 0;
}