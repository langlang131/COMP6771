#include <stdio.h>

int main(void) {
    int i = 0;
    int j = 0;

    printf("Please enter two numbers: ");

    if (scanf("%d %d", &i, &j) != 2) {
        printf("Something went wrong while reading an integer, bailing...\n");
        return -1;
    }

    int sum = i + j;
    printf("Sum: %d\n", sum);

    return 0;
}
