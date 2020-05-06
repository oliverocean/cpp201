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

// function prototypes
bool userMenu(std::string&);
std::string postfixFormer(std::string&);
int postfixCalculator(std::string&);

int main() {

    // update menu so it continue to ask for new expression until Quit is chosen.
    std::string userInput{};
    bool isValid = userMenu(userInput);

    if (!isValid) {
        std::cout << "\n---[ Output ]---\n";
        std::cout << "> Exiting...\n";
    } else {
        std::cout << "\n---[ Parse + Convert ]---\n";
        std::cout << "> Infix   [ " << userInput << " ]\n";
        std::string postfixInput = postfixFormer(userInput);
        std::cout << "> Postfix [ " << postfixInput << " ]\n";

        std::cout << "\n---[ Debug ]---\n";
        int calcResults = postfixCalculator(postfixInput);

        std::cout << "\n---[ Output ]---\n";
        std::cout << "> Result  [ " << calcResults << " ]\n";
    }

    return 0;
}

int postfixCalculator(std::string& postfixForm) {

    int result{0};
    std::string input = postfixForm;
    ArrayStack<int>operandStack;

    int leftOperand;
    int rightOperand;

    for (int c = 0; c < input.size(); ++c) {
        if (input[c] != '+' && input[c] != '-' && input[c] != '*' && input[c] != '/') {
            std::cout << "> push " << input[c] << "\n";
            operandStack.push(input[c] - '0'); // convert char to digit

        } else {
            std::cout << "> found " << input[c] << "\n";

            rightOperand = operandStack.peek();
            operandStack.pop();

            leftOperand = operandStack.peek();
            operandStack.pop();

            std::cout << "> eval [ " << leftOperand << " " << input[c] << " " << rightOperand << " ]\n";
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
            std::cout << ">    = [ " << result << " ]\n";
            operandStack.push(result);
        }
    }
    return result;
}

std::string postfixFormer(std::string& userInput) {

    ArrayStack<char>operatorStack;
    std::string postfixForm;

    for (const auto& c : userInput) {
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            operatorStack.push(c);
        } else {
            postfixForm += c;
        }
    }

    while (!operatorStack.isEmpty()) {
        postfixForm += operatorStack.peek();
        operatorStack.pop();
    }

    return postfixForm;
}

bool userMenu(std::string& userInput) {

    std::cout << "\n---[ Input ]---\n";
    std::cout << "> Enter an expression or 'q' to quit:\n";

    std::string rawInput;
    getline(std::cin, rawInput);
    if (rawInput == "q" || rawInput == "Q") {
        std::cout << "> You chose QUIT...\n";
        return (false);
    }

    std::string parsedInput;
    for (auto c: rawInput) {
        if (std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/') {
            parsedInput += c;
        } else {
            //std::cout << "> Invalid item (letter, space, etc); skipping" << "\n";
        }
    }

    if (parsedInput.empty()) {
        std::cout << "> No valid operands and/or operators found.\n";
        return false;
    } else {
        //std::cout << parsedInput << "\n";
        userInput = parsedInput;
        return true;
    }
}
