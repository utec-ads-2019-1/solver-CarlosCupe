#include "operation.h"

char operators[] = {'^', '/', '*', '-', '+'};

int maxOrder(string &equation, int &pos, bool &bracket);
bool isMaxOrder(char op, int &order);
void cleanEquation(string &equation);
bool countBrackets(string &equation);

map<string, int> vaul;

Operation* Operation::buildFromEquation(string equation) {
    int pos = -1;
    bool bracket;

    cleanEquation(equation);
    
    bracket = equation[0] == '(' && equation[equation.size() - 1] == ')';

    if (bracket)
        bracket = countBrackets(equation);

    switch (maxOrder(equation, pos, bracket)) {
    case 0:
        return new Pow(equation.substr(bracket, pos - bracket), equation.substr(pos + 1, equation.size() - pos - 1 - bracket));
        break;
    case 1:
        return new Division(equation.substr(bracket, pos - bracket), equation.substr(pos + 1, equation.size() - pos - 1 - bracket));
        break;
    case 2:
        return new Multiplication(equation.substr(bracket, pos - bracket), equation.substr(pos + 1, equation.size() - pos - 1 - bracket));
        break;
    case 3:
        return new Substract(equation.substr(bracket, pos - bracket), equation.substr(pos + 1, equation.size() - pos - 1 - bracket));
        break;
    case 4:
        return new Sum(equation.substr(bracket, pos - bracket), equation.substr(pos + 1, equation.size() - pos - 1 - bracket));
        break;
    case -1:
        for (char i : equation.substr(bracket, equation.size() - bracket))  {
            if ((i > 96 && i < 123) || (i > 64 && i < 91))
                return new Variable(equation.substr(bracket, equation.size() - bracket));    
        }
        return new Constant(equation.substr(bracket, equation.size() - bracket));
        break;
    default:
        break;
    }
}

float Variable::operate() {
    if (vaul.find(value) == vaul.end()) {
        cout << "Ingrese valor de la variable " << value << endl;
        cin >> vaul[value];
    }   return vaul[value];
}

void cleanEquation(string &equation) {
    string temp;
    int init = -1;
    int test = 0;
    bool r = true;
    bool open_bracket = false;
    for(int i = 0; i < equation.size(); ++i) {
        if (open_bracket) {
            test = 0;
            if (isMaxOrder(equation[i],test))
                temp += ')';
            open_bracket = false;
        }
        if (equation[i] == '+' || equation[i] == '-') {
            if (init == -1) {
                init = i;
                r = (equation[i] == '+');
            } else
                r = (r == (equation[i] == '+'));
        } else {
            if (init != -1) {                
                if (init > 0) {
                    if (equation[init - 1] == '*') {
                        temp += '(';
                        open_bracket = true;
                    }
                }
                temp += r ? '+' : '-';
                r = true;
                init = -1;
            }
            temp = temp + equation[i];
        }
    }

    if (open_bracket)
        temp += ')';

    equation = temp;
}

bool isMaxOrder(char op, int &order) {
    if (op > 47 && op < 58)
        return false;
    
    for(int i = order + 1; i < 5; ++i) {
        if(op == operators[i]) {
            order = i;
            return true;
        }
    }   return false;
}

int maxOrder(string &equation, int &pos, bool &bracket) {
    int count_bracket = 0;
    int order = -1;
    for(int i = 0 + bracket; i < equation.size() - bracket; ++i) {
        if (count_bracket == 0) {
            if (isMaxOrder(equation[i], order))
                pos = i;
        }
        if (equation[i] == '(') ++count_bracket;
        if (equation[i] == ')') --count_bracket;
    }   return order;
}


bool countBrackets(string &equation) {
    int count_bracket = 1;

    for(int i = 1; i < equation.size(); ++i) {
        if (equation[i] == '(') ++count_bracket;
        if (equation[i] == ')') --count_bracket;

        if (count_bracket == 0)
            return i == (equation.size() - 1);
    }
    exit(0);
}