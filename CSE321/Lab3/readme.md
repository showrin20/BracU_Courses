# CSE321 - Operating Systems Lab 03: Introducing C Programming (02)

## Overview
This lab introduces fundamental C programming concepts such as flow control, loops, functions, file I/O, and command-line arguments. Below are brief explanations and solutions to the given lab tasks.


## **Concepts Covered**
- **Flow Statements**: `if-else` for decision making.
- **Loops**: `for`, `while`, and nested loops for iteration.
- **Functions**: Call by value and call by reference.
- **File I/O**: Reading and writing files in C.
- **Command Line Arguments**: Passing arguments to a C program.

---
## **Lab Tasks and Solutions**

### **1. Check if a Character is a Vowel or Consonant**
```c
#include <stdio.h>

int main() {
    char ch;
    printf("Enter a character: ");
    scanf("%c", &ch);
    
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
        ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
        printf("%c is a vowel.\n", ch);
    } else {
        printf("%c is a consonant.\n", ch);
    }
    return 0;
}
```

### **2. Check if a Triangle is Valid**
```c
#include <stdio.h>

int main() {
    int a, b, c;
    printf("Enter three angles: ");
    scanf("%d %d %d", &a, &b, &c);
    
    if (a + b + c == 180)
        printf("Valid Triangle\n");
    else
        printf("Invalid Triangle\n");
    
    return 0;
}
```

### **3. Sum of Even Numbers from 1 to n**
```c
#include <stdio.h>

int main() {
    int n, sum = 0;
    printf("Enter n: ");
    scanf("%d", &n);
    
    for (int i = 2; i <= n; i += 2) {
        sum += i;
    }
    printf("Sum of even numbers: %d\n", sum);
    return 0;
}
```

### **4. Reverse an Array**
```c
#include <stdio.h>

void reverse(int arr[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    reverse(arr, size);
    return 0;
}
```

### **5. Circle Properties using Functions**
```c
#include <stdio.h>
#define PI 3.1416

void circleProperties(float r) {
    printf("Diameter: %.2f\n", 2 * r);
    printf("Circumference: %.2f\n", 2 * PI * r);
    printf("Area: %.2f\n", PI * r * r);
}

int main() {
    float r;
    printf("Enter radius: ");
    scanf("%f", &r);
    circleProperties(r);
    return 0;
}
```

### **6. Swap Two Numbers using Call by Reference**
```c
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    printf("Before Swap: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("After Swap: x=%d, y=%d\n", x, y);
    return 0;
}
```

### **7. Read a File and Print Alphabet Characters Only**
```c
#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *file = fopen("input.txt", "r");
    char ch;
    if (file == NULL) {
        printf("File cannot be opened\n");
        return 1;
    }
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch))
            putchar(ch);
    }
    fclose(file);
    return 0;
}
```

### **8. Sort Numbers using Command Line Arguments**
```c
#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./a.out num1 num2 ...\n");
        return 1;
    }
    
    int n = argc - 1;
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }
    
    bubbleSort(arr, n);
    printf("Sorted numbers: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
```

---
## **How to Compile and Run**
- **Compile**: `gcc program.c -o program`
- **Run with arguments**: `./program arg1 arg2 ...`

