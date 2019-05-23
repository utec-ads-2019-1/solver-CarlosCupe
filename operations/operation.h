#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <math.h>

using namespace std;


class Operation {
    protected:
        string equation;
        Operation *left;
        Operation *right;

    public: 
        Operation(string name) : equation(name) { }

        static Operation* buildFromEquation(string equation);

        inline string name() { return equation; }

        virtual float operate() = 0;
};


class Sum : public Operation {    
public:
    Sum(string equation_left, string equation_right)
    : Operation("Suma") {
        Operation::left = Operation::buildFromEquation(equation_left);
        Operation::right = Operation::buildFromEquation(equation_right);
    }
    
    float operate() {
        return Operation::left->operate() + Operation::right->operate();
    }
    ~Sum();
};


class Substract : public Operation {    
public:
    Substract(string equation_left, string equation_right)
    : Operation("Resta") {
        Operation::left = Operation::buildFromEquation(equation_left);
        Operation::right = Operation::buildFromEquation(equation_right);
    }
    
    float operate() {
        return Operation::left->operate() - Operation::right->operate();
    }
    ~Substract();
};


class Division : public Operation {    
public:
    Division(string equation_left, string equation_right)
    : Operation("Division") {
        Operation::left = Operation::buildFromEquation(equation_left);
        Operation::right = Operation::buildFromEquation(equation_right);
    }
    
    float operate() {
        return Operation::left->operate() / Operation::right->operate();
    }
    ~Division();
};


class Multiplication : public Operation {    
public:
    Multiplication(string equation_left, string equation_right)
    : Operation("Multiplicacion") {
        Operation::left = Operation::buildFromEquation(equation_left);
        Operation::right = Operation::buildFromEquation(equation_right);
    }
    
    float operate() {
        return Operation::left->operate() * Operation::right->operate();
    }
    ~Multiplication();
};


class Pow : public Operation {    
public:
    Pow(string equation_left, string equation_right)
    : Operation("Potencia") {
        Operation::left = Operation::buildFromEquation(equation_left);
        Operation::right = Operation::buildFromEquation(equation_right);
    }
    
    float operate() {
        return pow(Operation::left->operate(), Operation::right->operate());
    }
    ~Pow();
};


class Variable : public Operation {    
    string value;
public:
    Variable(string _value_)
    : Operation("Variable"), value(_value_) { }
    
    float operate();
    ~Variable();
};


class Constant : public Operation {    
    string value;
public:
    Constant(string _value_)
    : Operation("Constante"), value(_value_) { }
    
    float operate() {
        if (value == "")
            return 0;
        return strtof(value.c_str(),0);
    }
    ~Constant();
};

#endif