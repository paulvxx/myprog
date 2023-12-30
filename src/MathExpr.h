#include <iostream>
using namespace std; // needed for just  cout << 

// new class to parse mathematical expressions
class MathExpr {
    public:
        MathExpr(string e);
        void printExpr();
        double parse(bool cmp);
        double parse(string expr, bool cmp);
        double parseExpr();
        double parseTerm();
        double parseFact(bool u);
        bool eat(bool white, char ch);
        double scanNumber();
    private:
        string expr;
        double result;
        int pos;
};

bool parseToDouble(string d, double *db);