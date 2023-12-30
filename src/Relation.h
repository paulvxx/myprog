#include <iostream>
using namespace std; // needed for just  cout << 
#include "MathExpr.h"
#include <string>
#include <iomanip> // for std::setprecision

// new class to parse mathematical Relations
class Relation {
    public:
        Relation(string rel);
        string cmp(string a, string b);
        string getRel();
        void setRel(string r);
        void setPos(int p);
        int getPos();
        string parse();
        string parse(string rel);
        bool eat(bool white, string sub);
    private:
        string rel;
        int pos;
};

class MathRelation : Relation {
    public:
        MathRelation(string e);
        string parse();
        string parse(string rel);
    private:
        string exprRel;
        int ref;
};
