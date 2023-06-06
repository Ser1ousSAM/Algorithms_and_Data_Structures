#include <iostream>
#include <stack>
#include <queue>
#include <string>
 
using std::string;
using std::stack;
using std::queue;
 
class reversePolishNotation {
    //rotten code (int, NULL or NULL, char)
    queue <std::pair<int, char>> polishNotationQueue;
    stack <char> operationsStack;
 
    int getPriority(char c) {
        switch (c)
        {
        case '^':
            return 3;
        case '/':
            return 2;
        case '*':
            return 2;
        case '+':
            return 1;
        case '-':
            return 1;
        case '(':
            return 0;
        case ')':
            return 0;
        default:
            return -1;
        }
    }
    int resOfOperation(char c, int first, int second) {
        switch (c)
        {
        case '*' :
            return second * first;
        case '-':
            return second - first;
        case '+':
            return second + first;
        case '/':
            return second / first;
        case '^':
            return pow(second, first);
        default:
            return 0;
        }
    }
public:
    //11-2+3^2+2*(3-4*5^2-6)^2 = 21236
    //11 2 - 3 2 ^ + 2 3 4 5 2 ^ * - 6 - 2 ^ * +
    queue<std::pair<int, char>> TransleteToPolishNotaion(string expression) {
        string tempValue = "";
        for (int i = 0; i < expression.size(); i++) {
            if (i == 7)
                i = 7;
            if (48 <= int(expression[i]) && int(expression[i]) <= 57) {
                tempValue += expression[i];
                if(i==expression.size()-1)
                    polishNotationQueue.push(std::make_pair(stoi(tempValue), NULL));
            }
            else {
                if (tempValue!="")
                    polishNotationQueue.push(std::make_pair(stoi(tempValue), NULL));
                tempValue = "";
                if (expression[i] == '(')
                    operationsStack.push('(');
                else if(expression[i] == ')'){
                    while (operationsStack.top() != '(') {
                        polishNotationQueue.push(std::make_pair(NULL, operationsStack.top()));
                        operationsStack.pop();
                    }
                    operationsStack.pop();
                }
                else {
                    if (!operationsStack.empty()) {
                        while (getPriority(operationsStack.top()) > getPriority(expression[i]) || (getPriority(operationsStack.top()) == getPriority(expression[i]) && expression[i]!='^')) {
                            polishNotationQueue.push(std::make_pair(NULL, operationsStack.top()));
                            operationsStack.pop();
                            if (operationsStack.empty())
                                break;
                        }
                    }
                    operationsStack.push(expression[i]);
                }    
            }
        }
        while (!operationsStack.empty()) {
            polishNotationQueue.push(std::make_pair(NULL, operationsStack.top()));
            operationsStack.pop();
        }
        return polishNotationQueue;
    }
 
    void PresentAsPolishNotation(string expression) {
        TransleteToPolishNotaion(expression);
        queue <std::pair<int, char>> tempQueue = polishNotationQueue;
        while (!tempQueue.empty()) {
            if (tempQueue.front().first != NULL)
                std::cout << tempQueue.front().first << " ";
            else
                std::cout << tempQueue.front().second << " ";
            tempQueue.pop();
        }
        std::cout << '\n';
    }
 
    int CalculateExpression(string expression) {
        queue <std::pair<int, char>> tempQueue = polishNotationQueue;
        stack <int> tempStack;
        int firstTop, secondTop;
        while (!tempQueue.empty()) {
            if (tempQueue.front().first != NULL)
                tempStack.push(tempQueue.front().first);
            else {
                firstTop = tempStack.top();
                tempStack.pop();
                secondTop = tempStack.top();
                tempStack.pop();
                tempStack.push(resOfOperation(tempQueue.front().second, firstTop, secondTop));
            }
            tempQueue.pop();
        }
        return tempStack.top();
    }
};
 
int main()
{
    string input;
    std::cin >> input;
    reversePolishNotation p;
    p.PresentAsPolishNotation(input);
    std::cout << p.CalculateExpression(input);
}
