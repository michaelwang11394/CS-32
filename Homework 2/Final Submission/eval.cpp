#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include<cassert>
using namespace std;


bool infixToPostfix(string infix, string& postfix)
{
    postfix = "";
    
    stack<char> operators;
    
    for (int x = 0; x < infix.size(); x++)
    {
        char ch = infix[x];
        
        switch (ch)
        {
            case 'T':
                postfix += ch;
                break;
            case 'F':
                postfix += ch;
                break;
        
            case '(':
                operators.push(ch);
                break;
            case ')':
                while (operators.top() != '(')
                {
                    //append the stack top to postfix
                    postfix += operators.top();
                    
                    //pop the stack
                    operators.pop();
                }
                //pop '('
                operators.pop();
                break;
            case '!':
                while ((!operators.empty() && operators.top() != '(')
                       && (operators.top() != '&' && operators.top() != '|'))
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(ch);
                break;
            case '&':
                while ((!operators.empty() && operators.top() != '(')
                       && (operators.top() == '!' || operators.top() == '&'))
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(ch);
                break;
            case '|':
                while ((!operators.empty() && operators.top() != '(')
                       && (operators.top() == '!' || operators.top() =='&'
                           || operators.top() =='|'))
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(ch);
                break;
            default:
                break;
        }
        if (!operators.empty())
            cout << operators.top() << endl;
        cout << postfix << endl;
    }
    while (!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }
    return true;
}

int evaluate(string infix, string& postfix, bool& result)
{
//    stack<char> operators;
//     for (int x = 0; x < postfix.size(); x++)
//    if ( char ch= 'T' || char ch= 'F')
//        push the value that ch represents onto the operand stack
//        else // ch is a binary operator
//            set operand2 to the top of the operand stack
//            pop the stack
//            set operand1 to the top of the operand stack
//            pop the stack
//            apply the operation that ch represents to operand1 and
//            operand2, and push the result onto the stack
//            When the loop is finished, the operand stack will contain one item,
//            the result of evaluating the expressionr
    stack<bool> operands;
    bool temp;
    if(infixToPostfix(infix, postfix)== false)
        return -1;
    else if(infixToPostfix(infix, postfix)==true)
    {
    for (int y = 0; y < postfix.size(); y++)
    {
        char oper1, oper2;
        if (postfix[y] == 'T')
            operands.push(true);
        else if (postfix[y] == 'F')
            operands.push(false);
        else if (postfix[y] == '!')
        {
            temp = operands.top();
            operands.pop();
            operands.push(!temp);
        }
        else {
            oper1 = operands.top();
            operands.pop();
        
            if (operands.empty())
                return 1;
            oper2 = operands.top();
            operands.pop();
            if (postfix[y] == '|')
            {
                if (oper1 || oper2)
                    operands.push(true);
                else
                    operands.push(false);
            }
            else if (postfix[y] == '&')
            {
                if (oper1 && oper2)
                    operands.push(true);
                else
                    operands.push(false);
            }
        }}
    }
    result = operands.top();
    cout << endl;
    return 0;

}
int main()
{
    string pf;
    bool answer;
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    cout << "Passed all tests" << endl;
}
