#include <iostream>
#include <stack>
using namespace std;
struct P {
    char oper;//для операций
    double numb;//для чисел
};

int prioritet(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '^') {
        return 3;
    }
    else return 0;
}


bool  Maths(stack <P>& Stack_n, stack <P>& Stack_o, P& item) {
    double a, b, c;
    a = Stack_n.top().numb;
    Stack_n.pop();
    switch (Stack_o.top().oper) {
    case '+':
        b = Stack_n.top().numb;
        Stack_n.pop();
        c = a + b;
        item.oper = 0;
        item.numb = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '-':
        b = Stack_n.top().numb;
        Stack_n.pop();
        c = b - a;
        item.oper = 0;
        item.numb = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '*':
        b = Stack_n.top().numb;
        Stack_n.pop();
        c = a * b;
        item.oper = 0;
        item.numb = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    case '/':
        b = Stack_n.top().numb;
        if (a != 0) {
            Stack_n.pop();
            c = b / a;
            item.oper = 0;
            item.numb = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;
        }
        else {
            cout << "Error" << endl;
            exit(EXIT_FAILURE);
        }
    case '^':
        b = Stack_n.top().numb;
        Stack_n.pop();
        c = pow(b, a);
        item.oper = 0;
        item.numb = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;
    }
}
int main()
{
    char Ch;
    double num;
    stack <P> Stack_n;
    stack <P> Stack_o;
    P item;
    bool flag = 1;

    while (1) {
        Ch = cin.peek();
        if (Ch == '\n') break;
        if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) {
            cin >> num;
            item.oper = '0';
            item.numb = num;
            Stack_n.push(item);
            flag = 0;
            continue;
        }
        if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch == '^' || Ch == ')' || Ch == '(') {
            if (Stack_o.size() == 0) {
                item.oper = Ch;
                item.numb = 0;
                Stack_o.push(item);
                cin.ignore();
                continue;
            }
            if (Ch == '(') {
                flag = 1;
                item.oper = Ch;
                item.numb = 0;
                Stack_o.push(item);
                cin.ignore();
                continue;
            }
            if (Ch == ')') {
                while (Stack_o.top().oper != '(') {
                    if (Maths(Stack_n, Stack_o, item) == false) {
                        system("pause");
                        return 0;
                    }
                    else continue;
                }
                Stack_o.pop();
                cin.ignore();
                continue;
            }
            if (Stack_o.size() != 0 && prioritet(Ch) > prioritet(Stack_o.top().oper)) {
                item.oper = Ch;
                item.numb = 0;
                Stack_o.push(item);
                cin.ignore();
                continue;
            }
            if (Stack_o.size() != 0 && prioritet(Ch) <= prioritet(Stack_o.top().oper)) {
                if (Maths(Stack_n, Stack_o, item) == false) {
                    system("pause");
                    return 0;
                }
                continue;
            }
        }
    }
    while (Stack_o.size() != 0) {
        if (Maths(Stack_n, Stack_o, item) == false) {
            system("pause");
            return 0;
        }
        else continue;
    }
    cout << "Result: " << Stack_n.top().numb << endl;
    return 0;
}