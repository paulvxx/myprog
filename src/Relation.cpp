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
    setPos(0);
};

string MathRelation::parse() {
    setPos(0);
    return "null";
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