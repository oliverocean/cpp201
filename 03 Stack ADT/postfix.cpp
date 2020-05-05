// @file: postfix.cpp
// @author: Oliver Ocean

/*
Infix Calculator:
Convert an infix expression to postfix form and evaluate the resulting postfix expression.
Ch. 6, #5 (p 219)

Infix expressions include:
   - single-digit operands
   - operators:  + - * /
   - parentheses: ( )

Assume:
   - unary operators are illegal
   - expression contains no embedded spaces
Notes:
  - review 6.3.1
  - C has an atoi function but it may be easier to subtract the char '0' from the char digit
*/

#include <iostream>
#include "Array_Stack.h"
#include "Linked_Stack.h"
#include "Deque_Stack.h"

// function prototypes
bool userMenu(std::string&, std::string&);
int postfixCalculator(std::string&, std::string&);

int main() {

    std::string userInput{};
    std::string stackType{"A"}; // default is ArrayStack, note maxSize = 30 in implementation file (.h)

    if (!userMenu(userInput, stackType)) {
        std::cout << "\n---[ Output ]---\n";
        std::cout << "> Exiting...\n";
    } else {
        std::cout << "\n---[ Debug ]---\n";
        std::cout << "> eval [ " << userInput << " ]\n";
        std::cout << "> stack [ " << stackType << " ]\n";
        int calcResults = postfixCalculator(userInput, stackType);

        std::cout << "\n---[ Output ]---\n";

        std::cout << "> Stack type [ ";
        if (stackType == "L" || stackType == "l") {
            std::cout << "Linked List ]\n";
        } else if (stackType == "D" || stackType == "d") {
            std::cout << "Deque ]\n";
        } else {
            std::cout << "Array (default) ]\n";
        }
        std::cout << "> Result  [ " << calcResults << " ]\n";
    }

    return 0;
}

int postfixCalculator(std::string& postfixForm, std::string& stackType) {

    int result{0};
    std::string input = postfixForm;
    StackInterface<int>* operandStack = nullptr;

    if (stackType == "D") {
        operandStack = new DequeStack<int>();
    } else if (stackType == "L") {
        operandStack = new LinkedStack<int>();
    } else {
        operandStack = new ArrayStack<int>();
    }

    int leftOperand;
    int rightOperand;

    for (int c = 0; c < input.size(); ++c) {
        if (input[c] != '+' && input[c] != '-' && input[c] != '*' && input[c] != '/') {
            std::cout << "> push " << input[c] << "\n";
            operandStack->push(input[c] - '0'); // convert char to digit

        } else {
            std::cout << "> operator '" << input[c] << "'\n";

            rightOperand = operandStack->peek();
            operandStack->pop();

            leftOperand = operandStack->peek();
            operandStack->pop();

            std::cout << "> eval [ " << leftOperand << " " << input[c] << " " << rightOperand << " ]";
            switch (input[c]) {
                case '+':
                    result = leftOperand + rightOperand;
                    break;
                case '-':
                    result = leftOperand - rightOperand;
                    break;
                case '*':
                    result = leftOperand * rightOperand;
                    break;
                case '/':
                    result = leftOperand / rightOperand;
                    break;
            }
            std::cout << " = [ " << result << " ]\n";
            std::cout << "> push " << result << "\n";
            operandStack->push(result);
        }
    }
    return result;
}

bool userMenu(std::string& userInput, std::string& stackType) {

    std::cout << "\n---[ Input ]---\n";
    std::cout << "> Enter an expression or 'q' to quit:\n";

    std::string rawInput;
    getline(std::cin, rawInput);
    if (rawInput == "q" || rawInput == "Q") {
        std::cout << "> You chose QUIT...\n";
        return (false);
    }

    std::cout << "> Choose a stack type:\n" <<
              "  'A' for Array (default)\n" <<
              "  'L' for Linked List\n" <<
              "  'D' for Deque\n" <<
              "? ";

    std::string stackSelection;
    getline(std::cin, stackSelection);

    if (stackSelection == "L" || stackSelection == "l") {
        stackType = "L";
    } else if (stackSelection == "D" || stackSelection == "d") {
        stackType = "D";
    } else {
        // array is default
    }

    std::string parsedInput;
    for (auto c: rawInput) {
        if (std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/') {
            parsedInput += c;
        } else if (std::isspace(c)) {
            // future improvement -> parse spaces for digits larger than 0-9;
        } else {
            //std::cout << "> Invalid item (letter, etc); skipping" << "\n";
        }
    }

    if (parsedInput.empty()) {
        std::cout << "> No valid operands and/or operators found.\n";
        return false;
    } else {
        userInput = parsedInput;
        return true;
    }
}