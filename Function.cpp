////
//// Created by kanstancin on 6/11/19.
////
//
//#include "Function.h"
//#include <stack>
//
//int Function::set_function(std::string const& source)
//{
//    expression = source;
//    m_rpn_expr = convert(simplify(expression));
//}
//
//std::string Function::simplify(std::string const& source)
//{
//    std::string result;
//
//    for (size_t i = 0; i < source.size(); ++i)
//    {
//        if (is_operator(source[i]))
//            if (i == 0 || source[i - 1] == '(')
//            {
//                result += '0';
//            }
//
//        result += source[i];
//        if (!isalpha(source[i]) || source[i] == 'x') { continue; }
//
//        size_t j;
//        for (j = i + 1; j < source.size() && isalpha(source[j]); ++j)
//            result += source[j];
//        result += '#';
//        i = j - 1;
//    }
//
//    return result;
//}
//
//bool Function::is_operator(char const& c)
//{
//    return (
//            c == '*' || c == '/' ||
//            c == '+' || c == '-' ||
//            c == '^' || c == '#' ||
//            c == '(' || c == ')'
//    );
//}
//
//int Function::priority(char const& c) const
//{
//    if (c == '#')
//        return 5;
//    if (c == '^')
//        return 4;
//    if (c == '*' || c == '/')
//        return 3;
//    if (c == '+' || c == '-')
//        return 2;
//    if (c == '(')
//        return 1;
//    return 0;
//}
//
//T Function::run(const T &xvalue)
//{
//    std::stack<Unit> st;
//    double result = 0;
//
//    for (auto cur : m_rpn_expr)
//    {
//        if (cur.type == OPERATOR)
//        {
//            Unit val2 = st.top(); st.pop();
//            Unit val1 = st.top(); st.pop();
//
//            switch (cur.operation)
//            {
//                case '+':
//                    result = val1.value + val2.value;
//                    break;
//                case '-':
//                    result = val1.value - val2.value;
//                    break;
//                case '*':
//                    result = val1.value * val2.value;
//                    break;
//                case '/':
//                    result = val1.value / val2.value;
//                    break;
//                case '^':
//                    result = pow(val1.value, val2.value);
//                    break;
//                case '#':
//                    result = val1.function(val2.value);
//                    break;
//                default:
//                    result = 0;
//            }
//
//            st.push(Unit(result));
//        } else {
//            if (cur.type == VARIABLE)
//                st.push(Unit(xvalue));
//            else
//                st.push(cur);
//        }
//    }
//    return result;
//}
//
//
//Function::RPN Function::convert(std::string const& s)
//{
//    std::stack<Unit> st;
//    Function::RPN result;
//
//    std::string buffer;
//    for (char i : s)
//    {
//
//        if (i == '(') {
//            st.push(Unit((char('('))));
//            continue;
//        }
//        if (i == ')') {
//            if (!buffer.empty()) {
//                if (isdigit(buffer[0])) {
//                    // that's number
//                    char *kek;
//                    Unit tmp(strtod(buffer.c_str(), &kek));
//                    result.push_back(tmp);
//                } else if (buffer == "x") {
//                    Unit tmp("x");
//                    result.push_back(tmp);
//                } else {
//                    Unit tmp(buffer);
//                    result.push_back(tmp);
//                }
//                buffer = "";
//            }
//
//            while (!st.empty() && st.top().operation != '(')
//                result.push_back(st.top()),
//                        st.pop();
//            if (!st.empty() && st.top().operation == '(') st.pop();
//            continue;
//        }
//        if (is_operator(i)) {
//            if (!buffer.empty()) {
//
//                if (isdigit(buffer[0])) {
//                    // that's number
//                    char *kek;
//                    Unit tmp(strtod(buffer.c_str(), &kek));
//                    result.push_back(tmp);
//                } else if (buffer == "x") {
//                    Unit tmp("x");
//                    result.push_back(tmp);
//                } else {
//                    Unit tmp(buffer);
//                    result.push_back(tmp);
//                }
//            }
//            while (!st.empty() && priority(st.top().operation) >= priority(i))
//                result.push_back(st.top()),
//                        st.pop();
//            st.push(Unit(i));
//
//            buffer = "";
//        } else {
//            buffer += i;
//        }
//    }
//    if (!buffer.empty()) {
//        if (isdigit(buffer[0])) {
//            // that's number
//            char *kek;
//            Unit tmp(strtod(buffer.c_str(), &kek));
//            result.push_back(tmp);
//        } else if (buffer == "x") {
//            Unit tmp("x");
//            result.push_back(tmp);
//        } else {
//            Unit tmp(buffer);
//            result.push_back(tmp);
//        }
//    }
//    while (!st.empty()) result.push_back(st.top()), st.pop();
//    return result;
//}
//
