#include <iostream>
using namespace std; // needed for just  cout << 
#include "Relation.h"
#include <string>
#include <iomanip> // for std::setprecision

Relation::Relation(string rel) {
    this->rel = rel;
    pos = 0;
}

string Relation::getRel() {
    return rel;
}

void Relation::setRel(string r) {
    this->rel = r;
}

string Relation::parse() {
    pos = 0;
    return "null";
}

void Relation::setPos(int p) {
    pos = p;
}

int Relation::getPos() {
    return pos;
}

string Relation::parse(string rel) {
    this->rel = rel;
    pos = 0;
    return "null";
}


MathRelation::MathRelation(string e) : Relation(e) {
    this->exprRel = getRel();
    ref = 0;
    setPos(0);
};

string MathRelation::parse(string rel) {
    setRel(rel);
    return parse();
}

string MathRelation::parse() {
    ref = 0;
    setPos(0);
    bool isNull = false;
    int cmpOp = -1;
    double x, y;
    MathExpr m(getRel());
    if (eat(true, "null")) {
        isNull = true;
    }
    else {
        //cout << "test " << endl;
        x = m.parse(true, ref);
        setPos(ref);
    }

    if (eat(true, "==")) cmpOp = 0;
    else if (eat(true, ">=")) cmpOp = 1;
    else if (eat(true, "<=")) cmpOp = 2;
    // Order is important to ensure we don't miss scanning important symbols
    // i.e. if '>' came before '>=' we would fail to scan the last '='
    else if (eat(true, ">")) cmpOp = 3;
    else if (eat(true, "<")) cmpOp = 4;
    else throw std::runtime_error("Syntax error at pos=" + std::to_string(getPos()));

    if (eat(true, "null")) {
        isNull = true;
    }
    else {
        string remaining = exprRel.substr(getPos(), exprRel.length());
        y = m.parse(remaining, false, ref); 
        setPos(ref);
    }
    if (isNull) return "null";

    string result = "false";
    switch (cmpOp) {
        case 0:
        if (x==y) result = "true";
        break;
        case 1:
        if (x>=y) result = "true";
        break;
        case 2:
        if (x<=y) result = "true";
        break;
        case 3:
        if (x>y) result = "true";
        break;
        default:
        if (x<y) result = "true";
        break;
    }

    return result;
}



bool Relation::eat(bool white, string sub) {
    if (white) {
        // scan for whitespace
        while (pos < rel.length() && rel[pos] == ' ') {
            pos++;
        }
    }
    int len = sub.length();
    if (pos + len <= rel.length() && rel.substr(pos, len) == sub) {
        pos += len;
        return true;
    }
    return false;
}


int main(int argc, char* argv[]) {
    if (argc > 2) return 1;
    std::cout << std::fixed << std::setprecision(10);
    MathRelation m = MathRelation(argv[1]);
    cout << argv[1] << ": " << m.parse() << endl;
    return 0;
}
