#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Stack {
    int data[MAX];
    int count; // Starts from 0
};

// Global stack variable
struct Stack s = { .count = 0 };

void push(int value) {
    if (s.count >= MAX) {
        return;  // Prevent overflow
    }
    
    s.data[s.count] = value;  // Store value in stack
    s.count++;  // Increase stack count
}

void pop(int *value) {
    if (s.count == 0) {
        *value = 0;  // Handle underflow gracefully
        return;
    }

    s.count--;  // Reduce stack count
    *value = s.data[s.count];  // Store the popped value
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infix_to_rpn(const char *infix, char *rpn_out) {
    s.count = 0;  // Reset global stack
    int rpnIndex = 0;

    for (int i = 0; infix[i]; i++) {
        if (infix[i] >= '0' && infix[i] <= '9') {  // Check if it's a digit
            rpn_out[rpnIndex] = infix[i];
            rpnIndex++;
        } else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {  // Check for operators
            while (s.count > 0 && precedence(s.data[s.count - 1]) >= precedence(infix[i])) {
                int poppedValue;
                pop(&poppedValue);
                rpn_out[rpnIndex] = poppedValue;
                rpnIndex++;
            }
            push(infix[i]);
        }
    }

    while (s.count > 0) {
        int poppedValue;
        pop(&poppedValue);
        rpn_out[rpnIndex] = poppedValue;
        rpnIndex++;
    }
    rpn_out[rpnIndex] = '\0';
}

int evaluate_rpn(const char *expression) {
    s.count = 0;  // Reset global stack
    for (int i = 0; expression[i]; i++) {
        if (expression[i] >= '0' && expression[i] <= '9') {  // Check if it's a digit
            push(expression[i] - '0');
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {  // Check for operators
            int a, b;
            pop(&b);
            pop(&a);
            switch (expression[i]) {
                case '+': push(a + b); break;
                case '-': push(a - b); break;
                case '*': push(a * b); break;
                case '/': push(a / b); break;
            }
        }
    }
    int result;
    pop(&result);
    return result;
}

int main() {
    char infix[] = "3 + 4 * 5";
    char rpn_out[MAX];

    infix_to_rpn(infix, rpn_out);
    printf("RPN: %s\n", rpn_out);
    printf("Result: %d\n", evaluate_rpn(rpn_out));

    return 0;
}
