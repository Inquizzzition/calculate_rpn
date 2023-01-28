//
// Created by Inquisition on 14.11.2022.
//

#ifndef CALCULATE_RPN_MPARSER_H
#define CALCULATE_RPN_MPARSER_H

#include <string>
#include <map>
#include <functional>
#include <stack>

class mparser {
public:
    std::string infix_expr;
    std::string postfix_expr;
    mparser(std::string expression);
    double calculate();
private:
    std::string get_string_num(std::string& expr, int& pos);
    std::map<char, int> priority;
    std::string to_postfix(std::string expr);
    double execute(char op, double a, double b);
};


#endif //CALCULATE_RPN_MPARSER_H
