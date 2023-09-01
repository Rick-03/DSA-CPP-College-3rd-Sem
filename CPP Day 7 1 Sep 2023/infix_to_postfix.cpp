#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

// infix to postfix

using namespace std;
#define SIZE 100

char stack[SIZE];
int top = -1;
void push(char item)
{
    if (top >= SIZE - 1)
        cout << "Stack overflow" << endl;
    else
    {
        top++;
        stack[top] = item;
    }
}
char pop()
{
    char item;
    if (top < 0)
    {
        cout << "Stack underflow" << endl;
        // getchar();
        exit(1);
    }
    else
    {
        item = stack[top];
        top = top - 1;
        return (item);
    }
}
int isoperator(char symbol)
{
    if (symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-')
        return 1;
    else
        return 0;
}
int precedence(char symbol)
{
    if (symbol == '^')
        return 3;
    else if (symbol == '*' || symbol == '/')
        return 2;
    else if (symbol == '+' || symbol == '-')
        return 1;
    else
        return 0;
}
void inf_pos(char infix_exp[], char postfix_exp[])
{
    int i, j;
    char x, item;
    push('(');
    strcat(infix_exp, ")");
    i = 0;
    j = 0;
    item = infix_exp[i];
    while (item != '\0')
    {
        if (item == '(')
            push(item);
        else if (isdigit(item) || isalpha(item))
        {
            postfix_exp[j] = item;
            j++;
        }
        else if (isoperator(item) == 1)
        {
            x = pop();
            while (isoperator(x) == 1 && precedence(x) >= precedence(item))
            {
                postfix_exp[j] = x;
                j++;
                x = pop();
            }
            push(x);
            push(item);
        }
        else if (item == ')')
        {
            x = pop();
            while (x != '(')
            {
                postfix_exp[j] = x;
                j++;
                x = pop();
            }
        }
        else
        {
            cout << "Invalid expression" << endl;
            exit(1);
        }
        i++;
        item = infix_exp[i];
    }
    if (top > 0)
    {
        cout << "Invalid expression" << endl;
        exit(1);
    }
    postfix_exp[j] = '\0';
}
int main()
{
    char infix[SIZE], postfix[SIZE];
    int i;
    // clrscr();
    cout << "Enter the infix expression : ";
    cin >> infix;
    for (i = 0; i < strlen(infix) - 1; i++)
    {
        if ((isoperator(infix[i])) && (isoperator(infix[i + 1])) == 1)
        {
            cout << "Wrong expression" << endl;
            getch();
            exit(1);
        }
        else
            continue;
    }
    inf_pos(infix, postfix);
    cout << "Postfix : " << postfix;
    // getch();
    return 0;
}