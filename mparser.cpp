//
// Created by Inquisition on 14.11.2022.
//
#include "mparser.h"

mparser::mparser(std::string expression) {
    priority = {
            {'(', 0},
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2},
            {'^', 3},
            {'~', 4}
    };
    infix_expr = expression;
    postfix_expr = to_postfix(infix_expr + "\r");
}

std::string mparser::get_string_num(std::string& expr, int& pos) {
    std::string str_num = "";
    for(;pos < expr.size(); pos++){
        if((expr[pos] >= '0' && expr[pos] <= '9') || expr[pos] == '.' || expr[pos] == ',') {
            if (expr[pos] == ',')
                expr[pos] = '.';
            str_num += expr[pos];
        }
        else{
            pos--;
            break;
        }
    }
    return str_num;
}

std::string mparser::to_postfix(std::string expr) {
    std::string tpostfix_expr = "";
    std::stack<char> operation;

    for(int i = 0; i < expr.size(); ++i){
        char c = expr[i];
        if(c >= '0' && c <= '9')
            tpostfix_expr += get_string_num(expr, i) + " ";
        else if(c == '('){
            operation.push(c);
        }
        else if(c == ')'){
            while (operation.size() > 0 && operation.top() != '('){
                tpostfix_expr += operation.top();
                operation.pop();
            }
            operation.pop();
        }
        else if(priority.find(c) != priority.end()){
            if(c == '-' && (i == 0 || (i >= 1 && priority.find(expr[i-1]) != priority.end())))
                c = '~';
            while(operation.size() > 0 && priority[operation.top()] >= priority[c]) {
                tpostfix_expr += operation.top();
                operation.pop();
            }
            operation.push(c);
        }
    }
    while(operation.size() != 0) {
        tpostfix_expr += operation.top();
        operation.pop();
    }
    return tpostfix_expr;
}

double mparser::execute(char op, double a, double b) {
    switch(op){
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '/':
            return a/b;
        case '*':
            return a*b;
        case '^':
            return std::pow(a, b);
    }
    return 0;
}

double mparser::calculate() {
    std::stack<double> local;
    int cnt = 0;
    for(int i = 0; i < postfix_expr.size(); ++i){
        char c = postfix_expr[i];
        if (c >= '0' && c <= '9') {
            std::string number = get_string_num(postfix_expr, i);
            local.push(std::stod(number));
        }
        else if(priority.find(c) != priority.end()){
            cnt++;
            if(c=='~'){
                double last = 0;
                if(local.size() > 0){
                    last = local.top();
                    local.pop();
                }
                local.push(execute('-', 0, last));
                continue;
            }
            double second = 0;
            if(local.size() > 0){
                second = local.top();
                local.pop();
            }
            double first = 0;
            if(local.size() > 0){
                first =     local.top();
                local.pop();
            }
            local.push(execute(c, first, second));
        }
    }
    return local.top();
}
