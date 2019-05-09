#include "operation.h"

char operators[] = {'^', '/', '*', '-', '+'};

int maxOrder(string equation, int &pos, bool &bracket);
void cleanEquation(string &equation);

Operation* Operation::buildFromEquation(string equation) {
    //cleanEquation(equation);
    int pos = -1;
    bool bracket;
    switch (maxOrder(equation, pos, bracket)) {
    case 1:
    cout << equation.substr(0 + bracket, pos - bracket) <<" " << equation.substr(pos + 1, equation.size() - pos - 1 - bracket) << endl;
        return new Division(equation.substr(0 + bracket, pos - bracket), equation.substr(pos + 1, equation.size() - pos - 1 - bracket));
        break;
    case 2:
    cout << equation.substr(0 + bracket, pos - bracket) <<" " << equation.substr(pos + 1, equation.size() - pos - 1 - bracket) << endl;
        return new Multiplication(equation.substr(0 + bracket, pos - bracket), equation.substr(pos + 1, equation.size() - pos - 1 - bracket));
        break;
    case 3:
    cout << equation.substr(0 + bracket, pos - bracket) <<" " << equation.substr(pos + 1, equation.size() - pos - 1 - bracket) << endl;
        return new Substract(equation.substr(0 + bracket, pos - bracket), equation.substr(pos + 1, equation.size() - pos - 1 - bracket));
        break;
    case 4:
    cout << equation.substr(0 + bracket, pos - bracket) <<" " << equation.substr(pos + 1, equation.size() - pos - 1 - bracket) << endl;
        return new Sum(equation.substr(0 + bracket, pos - bracket), equation.substr(pos + 1, equation.size() - pos - 1 - bracket));
        break;
    case -1:
        return new Variable(equation.substr(bracket, equation.size() - bracket));
        break;
    default:
        break;
    }
}

void cleanEquation(string &equation) {
    string temp;
    int init = -2, last = -2;
    bool r = true;
    for(int i = 0; i < equation.size(); ++i) {
        if (equation[i] == '+' || equation[i] == '-') {
            if (init == -2) {
                last = init = i;
                r = r && (equation[i] == '+');
            } else {
                if (i == last + 1) {
                    r = r && (equation[i] == '+');
                    last = i;
                }
            }
        } else {
            if (last - init > 0) {
                if (r)
                    temp = temp + '+';
                else
                    temp = temp + '-';
            } else
                temp = temp + equation[init];
            init = last = -2;
            temp = temp + equation[i];
        }
    }
    equation = temp;
    cout <<"Clear " <<equation << endl;
}


bool isMaxOrder(char op, int &order) {
    for(int i = order + 1; i < 5; ++i) {
        if(op == operators[i]) {
            order = i;
            return true;
        }
    }   return false;
}

int maxOrder(string equation, int &pos, bool &bracket) {
    bracket = equation[0] == '(' && equation[equation.size() - 1] == ')';

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
