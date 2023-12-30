#include <iostream>
using namespace std; // needed for just  cout << 
#include "MathExpr.h"
#include <string>
#include <iomanip> // for std::setprecision

MathExpr::MathExpr(string e) {
    this->expr = e;
    isValidExpr = false;
    pos = 0;
    opOccupied = false;
}

double MathExpr::parseExpr() {
    double t = parseTerm();
    bool add = false;
    while ((add=eat(true, '+')) || (eat(true, '-'))) {
        if (add) t += parseTerm();
        else t -= parseTerm();
    }
    return t;
}

double MathExpr::parseTerm() {
    double f = parseFact(false);
    bool mul = false;
    while ((mul=eat(true, '*')) || (eat(true, '/'))) {
        if (mul) f *= parseFact(false);
        else {
            double div = parseFact(false);
            if (div==0) throw std::runtime_error("Division by 0 error at pos=" + std::to_string(pos));;
            f /= div;
        };
    }
    return f;
}

// bool u is to detect if the parseFact function was called from the first if branch (i.e. the operand is from the - negative operator, in
// which case there cannot be any whitespace i.e. "-  3" is invalid, but "-3" is vald.
double MathExpr::parseFact(bool u) {
    bool error = true;
    double r = 0;
    if (eat(!u, '-')) {
        error = false;
        if (pos < expr.length() && expr[pos] == ' ') {  // Check for space after '-' when it's not allowed
            error = true;
        } else {
            r = 0 - parseFact(true);
        }
    }
    else if (eat(!u, '(')) {
        if (pos < expr.length() && expr[pos]==')') throw std::runtime_error("Empty Expression");
        error = false;
        r = parseExpr();
        if (!eat(true, ')')) {
            throw std::runtime_error("Mismatched parentheses at pos=" + std::to_string(pos));
        }
    }
    else {
        error = false; 
        r = scanNumber(); 
    }
    if (error) throw std::runtime_error("Syntax error at pos=" + std::to_string(pos));
    return r;
}

double MathExpr::parse() {
    pos = 0;
    isValidExpr = false;
    opOccupied = false;
    return parseExpr();
}

double MathExpr::parse(string expr) {
    this->expr = expr;
    pos = 0;
    isValidExpr = false;
    opOccupied = false;
    return parseExpr();
}

bool MathExpr::eat(bool white, char ch) {
    if (white) {
        // scan for whitespace
        while (pos < expr.length() && expr[pos]==' ') {
            pos++;
        }
    }
    if (pos < expr.length() && expr[pos]==ch) {
        pos++;
        return true; 
    }
    return false;
}

double MathExpr::scanNumber() {
    double db = 0;
    bool isDecimal = false;
    int decimalPlaces = 1;
    bool hasLeadingZero = false;
    bool isValidNum = true;

    while (pos < expr.length() && isValidNum) {
        char currentChar = expr[pos];
        if (isdigit(currentChar)) {
            if (db==0 && !isDecimal && currentChar == '0') {
                hasLeadingZero = true;
            } else if (!isDecimal && hasLeadingZero && currentChar != '.') {
                throw std::runtime_error("Invalid number format at pos=" + std::to_string(pos));
            }
            if (isDecimal) {
                double dp = currentChar - '0';
                for (int i = 0; i < decimalPlaces; i++) dp /= 10.0;
                db += dp;
                decimalPlaces++;
            } else {
                db = db * 10 + (currentChar - '0');
            }
        } else if (currentChar == '.' && !isDecimal) {
            isDecimal = true; // First decimal point encountered
        } else {
            isValidNum = false;
            break; // Non-digit character encountered
        }
        if (isValidNum) pos++;
    }
    return db;
}

int main(int argc, char* argv[]) {
    if (argc > 2) return 1;
    std::cout << std::fixed << std::setprecision(10);
    MathExpr m = MathExpr("111");
    double x = m.scanNumber();
    MathExpr m2 = MathExpr("733");
    double y = m2.scanNumber();
    MathExpr m3 = MathExpr(argv[1]);
    cout << argv[1] << ": " << m3.parse() << endl;
    return 0;
}
