//
// Created by kanstancin on 6/11/19.
//

#ifndef CONSOLECHART_FUNCTION_H
#define CONSOLECHART_FUNCTION_H


#include <string>
#include <vector>
#include <math.h>
#include <stack>

enum UnitType{NUMBER, VARIABLE, FUNCTION, OPERATOR, UNDEFINED};

template <class T>
class Function
{
public:
    Function() = default;
    virtual ~Function() = default;

    int set_function(const std::string& source);
    T run(const T &xvalue);

protected:

    struct Unit;
    typedef std::vector<Unit> RPN;


    std::string expression;
    RPN m_rpn_expr;

    static bool is_operator(const char& c);
    int priority(const char& c) const;

    RPN convert(const std::string& source);
    std::string simplify(const std::string& source);
private:
};


template<class T>
struct Function<T>::Unit
{
    typedef T (*_Function)(T);

    UnitType type;
    T value;
    _Function function;
    char operation;

    Unit() = default;
    explicit Unit(const T & x) : value(x), type(NUMBER) {}
    explicit Unit(std::string const& s) {
        if (s == "x") {
            type = VARIABLE;
        } else {
            type = FUNCTION;
            if (s == "sin")
                function = sin;
            else if (s == "cos")
                function = cos;
            else
                function = tan;
        }
    }
    explicit Unit(char const& c) {
        type = OPERATOR;
        if (Function<T>::is_operator(c))
            operation = c;
        else
            operation = '*';
    }
};


template<class T>
int Function<T>::set_function(const std::string& source)
{
    expression = source;
    m_rpn_expr = convert(simplify(expression));
    return 0;   // todo: remove returns
}

template<class T>
std::string Function<T>::simplify(const std::string& source)
{
    std::string result;

    for (size_t i = 0; i < source.size(); ++i)
    {
        if (is_operator(source[i]))
            if (i == 0 || source[i - 1] == '(')
            {
                result += '0';
            }

        result += source[i];
        if (!isalpha(source[i]) || source[i] == 'x') { continue; }

        size_t j;
        for (j = i + 1; j < source.size() && isalpha(source[j]); ++j)
            result += source[j];
        result += '#';
        i = j - 1;
    }

    return result;
}

template<class T>
bool Function<T>::is_operator(const char& c)
{
    return (
            c == '*' || c == '/' ||
            c == '+' || c == '-' ||
            c == '^' || c == '#' ||
            c == '(' || c == ')'
    );
}

template<class T>
int Function<T>::priority(const char& c) const
{
    if (c == '#')
        return 5;
    if (c == '^')
        return 4;
    if (c == '*' || c == '/')
        return 3;
    if (c == '+' || c == '-')
        return 2;
    if (c == '(')
        return 1;
    return 0;
}

template<class T>
T Function<T>::run(const T &xvalue)
{
    std::stack<Unit> st;
    long double result = 0;

    for (auto cur : m_rpn_expr)
    {
        if (cur.type == OPERATOR)
        {
            Unit val2 = st.top(); st.pop();
            Unit val1 = st.top(); st.pop();

            switch (cur.operation)
            {
                case '+':
                    result = val1.value + val2.value;
                    break;
                case '-':
                    result = val1.value - val2.value;
                    break;
                case '*':
                    result = val1.value * val2.value;
                    break;
                case '/':
                    result = val1.value / val2.value;
                    break;
                case '^':
                    result = pow(val1.value, val2.value);
                    break;
                case '#':
                    result = val1.function(val2.value);
                    break;
                default:
                    result = 0;
            }

            st.push(Unit{result});
        } else {
            if (cur.type == VARIABLE)
                st.push(Unit(xvalue));
            else
                st.push(cur);
        }
    }
    return result;
}


template<class T>
typename Function<T>::RPN Function<T>::convert(const std::string& s)
{
    std::stack<Unit> st;
    Function<T>::RPN result;

    std::string buffer;
    for (char i : s)
    {

        if (i == '(') {
            st.push(Unit((char('('))));
            continue;
        }
        if (i == ')') {
            if (!buffer.empty()) {
                if (isdigit(buffer[0])) {
                    // that's number
                    char *kek;
                    Unit tmp(static_cast<long double>(strtod(buffer.c_str(), &kek)));       // TODO: Look for a more beautiful solution
                    result.push_back(tmp);
                } else if (buffer == "x") {
                    Unit tmp("x");
                    result.push_back(tmp);
                } else {
                    Unit tmp(buffer);
                    result.push_back(tmp);
                }
                buffer.clear();
            }

            while (!st.empty() && st.top().operation != '(')
                result.push_back(st.top()),
                        st.pop();
            if (!st.empty() && st.top().operation == '(') st.pop();
            continue;
        }
        if (is_operator(i)) {
            if (!buffer.empty()) {

                if (isdigit(buffer[0])) {
                    // that's number
                    char *kek;
                    Unit tmp(static_cast<long double>(strtod(buffer.c_str(), &kek)));
                    result.push_back(tmp);
                } else if (buffer == "x") {
                    Unit tmp("x");
                    result.push_back(tmp);
                } else {
                    Unit tmp(buffer);
                    result.push_back(tmp);
                }
            }
            while (!st.empty() && priority(st.top().operation) >= priority(i))
                result.push_back(st.top()),
                        st.pop();
            st.push(Unit(i));

            buffer.clear();
        } else {
            buffer += i;
        }
    }
    if (!buffer.empty()) {
        if (isdigit(buffer[0])) {
            // that's number
            char *kek;
            Unit tmp(static_cast<long double>(strtod(buffer.c_str(), &kek)));
            result.push_back(tmp);
        } else if (buffer == "x") {
            Unit tmp("x");
            result.push_back(tmp);
        } else {
            Unit tmp(buffer);
            result.push_back(tmp);
        }
    }
    while (!st.empty()) result.push_back(st.top()), st.pop();
    return result;
}



#endif //CONSOLECHART_FUNCTION_H
