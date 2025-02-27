# **CSE321 - Operating Systems Lab 02: Introducing C Programming**

## **Overview**
This repository contains solutions for Lab 02 of CSE321 (Operating Systems Lab), covering fundamental C programming concepts such as data types, pointers, arrays, strings, and structs.


2. Compile any C program using `gcc`:
   ```sh
   gcc filename.c -o output
   ./output
   ```

---

## **Basics of C**

### **1. Writing a Basic C Program**
A C program consists of functions and statements. Below is a simple "Hello, World!" program:

**File:** `hello_world.c`
```c
#include <stdio.h>
int main() {
    printf("Hello, World!\n");
    return 0;
}
```

### **2. Data Types in C**
C provides various data types such as:
- `int` - Integer type
- `float` - Floating point type
- `char` - Character type
- `double` - Double precision floating point type

Example:
```c
#include <stdio.h>
int main() {
    int a = 10;
    float b = 5.5;
    char c = 'A';
    printf("Integer: %d, Float: %.2f, Character: %c\n", a, b, c);
    return 0;
}
```

### **3. Taking User Input**
User input in C can be taken using `scanf`.

Example:
```c
#include <stdio.h>
int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("You entered: %d\n", num);
    return 0;
}
```

### **4. Conditional Statements**
C uses `if`, `else`, and `switch` statements for decision-making.

Example using `if-else`:
```c
#include <stdio.h>
int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (num > 0) {
        printf("Positive number\n");
    } else {
        printf("Non-positive number\n");
    }
    return 0;
}
```

### **5. Loops in C**
Loops allow repeated execution of a block of code.

Example using `for` loop:
```c
#include <stdio.h>
int main() {
    for (int i = 1; i <= 5; i++) {
        printf("Iteration %d\n", i);
    }
    return 0;
}
```

---

## **Topics Covered**
- Writing a basic C program
- Data types in C
- Taking inputs using `scanf`
- Arrays (1D & 2D)
- Pointers and memory addressing
- Strings and string manipulation
- Structures (`struct`) in C

---

## **Lab Tasks & Solutions**

### **1. Print Name, Date of Birth, and Mobile Number**
**File:** `print_info.c`
```c
#include <stdio.h>
int main() {
    printf("Name: John Doe\n");
    printf("Date of Birth: January 1, 2000\n");
    printf("Mobile Number: +123456789\n");
    return 0;
}
```

### **2. Compute Perimeter & Area of a Rectangle**
**File:** `rectangle_area.c`
```c
#include <stdio.h>
int main() {
    int height = 7, width = 5;
    int area = height * width;
    int perimeter = 2 * (height + width);
    printf("Area: %d\n", area);
    printf("Perimeter: %d\n", perimeter);
    return 0;
}
```

### **3. Compute Perimeter & Area of a Circle**
**File:** `circle_area.c`
```c
#include <stdio.h>
#define PI 3.1416
int main() {
    float radius;
    printf("Enter radius: ");
    scanf("%f", &radius);
    printf("Area: %.2f\n", PI * radius * radius);
    printf("Perimeter: %.2f\n", 2 * PI * radius);
    return 0;
}
```

### **4. Store and Print Array Elements**
**File:** `array_store.c`
```c
#include <stdio.h>
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    for(int i = 0; i < 5; i++) {
        printf("Element[%d] = %d\n", i, arr[i]);
    }
    return 0;
}
```

### **5. Display Array in Reverse Order**
**File:** `reverse_array.c`
```c
#include <stdio.h>
int main() {
    int n, arr[100];
    printf("Enter number of elements: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
    for(int i = n-1; i >= 0; i--) printf("%d ", arr[i]);
    return 0;
}
```

