//
// Created by blago on 8.1.2023 г..
//

#include <iostream>
#include "BinaryCalculator.h"


std::string BinaryCalculator::Add(const std::string &a, const std::string &b) //todo negative revision
{
    std::string result;

    int max_len = std::max(a.length(), b.length());
    std::string a_padded = std::string(max_len - a.length(), '0') + a;
    std::string b_padded = std::string(max_len - b.length(), '0') + b;

    int carry = 0;
    for (int i = max_len - 1; i >= 0; i--) {
        int digit_a = a_padded[i] - '0';
        int digit_b = b_padded[i] - '0';
        int sum = digit_a + digit_b + carry;
        result = std::to_string(sum % 2) + result;
        carry = sum / 2;
    }

    if (carry > 0) {
        result = std::to_string(carry) + result;
    }

    return result;
}

std::string BinaryCalculator::Multiply(const std::string &a, const std::string &b) //todo negative revision
{
    std::vector<int> result(a.size() + b.size(), 0);

    for (int i = a.size() - 1; i >= 0; i--) {
        for (int j = b.size() - 1; j >= 0; j--) {
            result[i + j + 1] += (a[i] - '0') * (b[j] - '0');
            result[i + j] += result[i + j + 1] / 2;
            result[i + j + 1] %= 2;
        }
    }

    std::string final_result;
    for (int digit: result) {
        final_result += (digit + '0');
    }
    while (final_result.size() > 1 && final_result[0] == '0') {
        final_result.erase(final_result.begin());
    }

    return final_result;
}

std::string BinaryCalculator::Subtract(const std::string &a, const std::string &b)//todo negative revision
{

    if (b == "0") {
        return a;
    }

    if (a == "0") {
        return "-" + b;
    }

    if (GreaterThanOrEqual(a, b)) {
        std::string result;
        int carry = 0;
        int i = a.size() - 1;
        int j = b.size() - 1;
        while (i >= 0 || j >= 0 || carry > 0) {
            int x = 0;
            int y = 0;
            if (i >= 0) {
                x = a[i] - '0';
                i--;
            }
            if (j >= 0) {
                y = b[j] - '0';
                j--;
            }
            int sum = x - y - carry;
            if (sum < 0) {
                sum += 2;
                carry = 1;
            } else {
                carry = 0;
            }
            result += std::to_string(sum);
        }
        std::reverse(result.begin(), result.end());

        if (result == "0000") return "0";

        int pos = 0;

        while (result[pos] == '0') {
            result = result.substr(pos + 1);
        }

        return result;
    } else {
        return "-" + Subtract(b, a);
    }
}

std::string BinaryCalculator::Divide(const std::string &a, const std::string &b) //todo negative revision
{
    std::string result;
    int a_length = a.length();
    int b_length = b.length();
    int divisor_length = b_length;
    std::string divisor = b;
    std::string dividend = a.substr(0, divisor_length);
    int quotient_length = a_length - b_length + 1;
    std::string quotient;
    for (int i = 0; i < quotient_length; i++) {
        int digit = 0;
        while (GreaterThanOrEqual(dividend, divisor)) {
            dividend = Subtract(dividend, divisor);
            digit++;
        }
        quotient += std::to_string(digit);
        if (i + divisor_length < a_length) {
            dividend += a[i + divisor_length];
        }
    }


    if (dividend == "0000" || dividend == "000" || dividend == "00" || dividend == "0" || dividend.empty()) {
        return quotient;
    }

    result = quotient + "." + dividend;
    return result;

}

std::string BinaryCalculator::calculate(std::string a, std::string b, const std::string &operation) {
    if (operation == "+")
        return Add(a, b);
    if (operation == "-")
        return Subtract(a, b);
    if (operation == "*")
        return Multiply(a, b);
    if (operation == "/")
        return Divide(a, b);
    throw new std::exception;
}

bool BinaryCalculator::isOperation(const std::string &op) {
    return op == "+" || op == "-" || op == "*" || op == "/";
}

std::string BinaryCalculator::evaluateRpn(std::stack<std::string> rpn) {

    std::vector<std::string> notation = stackToVector(rpn);

    std::stack<std::string> numbers;
    for (const auto &str: notation) {
        if (isOperation(str)) {
            std::string n2 = numbers.top();
            numbers.pop();
            std::string n1 = numbers.top();
            numbers.pop();

            std::string calculation = calculate(n1, n2, str);

            numbers.push(calculation);
        } else
            numbers.push(str);
    }

    return numbers.top();
}


std::vector<std::string> BinaryCalculator::stackToVector(std::stack<std::string> st) {

    std::vector<std::string> res;

    while (!st.empty()) {
        res.push_back(st.top());
        st.pop();
    }
    std::reverse(res.begin(), res.end());

    return res;
}


//std::string BinaryCalculator::SquareRoot(const std::string &number) {
//
//    // Handle special cases
//    if (number == "0") {
//        return "0";
//    }
//    if (number == "1") {
//        return "1";
//    }
//
//    std::string left = "1";
//    std::string right = number;
//    std::string squared;
//
//    std::cout << "left " << left << " right " << right << " sqrt " << squared << std::endl;
//
//    while (GreaterThanOrEqual(right, left)) {
//
//        std::string mid = Add(left, Divide(Subtract(right, left), "10"));
//        std::cout << "left " << left << " mid " << mid << " right " << right << " sqrt " << squared << std::endl;
//        if (GreaterThanOrEqual(Divide(number, mid), mid)) {
//            left = Add(mid, "1");
//            squared = mid;
//        } else {
//            right = Subtract(mid, "1");
//        }
//    }
//
//    return squared;
//}


bool BinaryCalculator::GreaterThanOrEqual(std::string a, std::string b) //todo negative revision
{
    if (a.size() > b.size()) {
        return true;
    } else if (a.size() < b.size()) {
        return false;
    } else {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] > b[i]) {
                return true;
            } else if (a[i] < b[i]) {
                return false;
            }
        }
        return true;
    }
}

std::string BinaryCalculator::DivideByTwo(const std::string &binary) {
    std::string result;
    int carry = 0;
    for (char c: binary) {
        int digit = c - '0';
        result += std::to_string(((digit + carry) / 2) + '0');
        carry = (digit % 2) * 10;
    }
    if (result.front() == '0' && result.size() > 1) {
        result = result.substr(1);
    }
    return result;
}