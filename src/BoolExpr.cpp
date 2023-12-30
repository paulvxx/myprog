#include <iostream>
#include "BoolExpr.h"
#include <string>
using namespace std;

BoolExpr::BoolExpr(string e) {
    this->expr = e;
    pos = 0;
}

string BoolExpr::parse() {
    pos = 0;
    string r = parseOr();
    eat(true, "");
    if (pos < expr.length()) {
        throw std::runtime_error("Syntax error at pos=" + std::to_string(pos));
    }
    return r;
}

string BoolExpr::parse(string expr) {
    this->expr = expr;
    pos = 0;
    string r = parseOr();
    eat(true, "");
    if (pos < expr.length()) {
        throw std::runtime_error("Syntax error at pos=" + std::to_string(pos));
    }
    return r;
}

string BoolExpr::parseOr() {
    string orop = parseAnd();
    while (eat(true, "||")) {
        string nextop = parseAnd();
        if (orop=="true" || nextop=="true") orop="true";
        else if (orop=="null" || nextop=="null") orop="null";
        else orop="false";
    }
    return orop;
}

string BoolExpr::parseAnd() {
    string andop = parseCond();
    while (eat(true, "&&")) {
        string nextop = parseAnd();
        if (andop=="false" || nextop=="false") andop="false";
        else if (andop=="null" || nextop=="null") andop="null";
        else andop="true";
    }
    return andop;    
}

string BoolExpr::parseCond() {
    string cond = parseUnary(false);
    while (eat(true, "->")) {
        if (cond=="true" || cond=="null") cond="null";
        else cond="true";
    }
    return cond;
}

string BoolExpr::parseUnary(bool u) {
    string res = "";
    bool error = true;
    if (eat(!u, "!")) {
        error = false;
        if (pos < expr.length() && expr[pos] == ' ') {  // Check for space after "!" when it's not allowed
            error = true;
        }
        else {
            res = parseUnary(true);
            if (res=="true") res="false";
            else if (res=="false") res="true";
        }
    }
    else if (eat(!u, "??")) {
        error = false;
        if (pos < expr.length() && expr[pos] == ' ') {  // Check for space after "??" when it's not allowed
            error = true;
        }
        else {
            res = parseUnary(true);
            if (res=="null") res="true";
            else res="false";
        }
    }
    else if (eat(!u, "(")) {
        if (pos < expr.length() && expr[pos]==')') throw std::runtime_error("Empty Expression");
        error = false;
        res = parseOr();
        if (!eat(true, ")")) {
            throw std::runtime_error("Mismatched parentheses at pos=" + std::to_string(pos));
        }
    }
    else if (eat(!u, "true")) { error = false; res="true"; }
    else if (eat(!u, "false")) {error = false; res="false"; } 
    else if (eat(!u, "null")) {error = false; res="null"; }
    if (error) throw std::runtime_error("Syntax error at pos=" + std::to_string(pos));
    return res;
}

bool BoolExpr::eat(bool white, string sub) {
    if (white) {
        // scan for whitespace
        while (pos < expr.length() && expr[pos] == ' ') {
            pos++;
        }
    }
    int len = sub.length();
    if (pos + len <= expr.length() && expr.substr(pos, len) == sub) {
        pos += len;
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc > 2) return 1;
    BoolExpr m = BoolExpr(argv[1]);
    cout << argv[1] << ": " << m.parse() << endl;
    return 0;
}
