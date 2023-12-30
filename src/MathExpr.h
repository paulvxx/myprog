#include <iostream>
using namespace std; // needed for just  cout << 

// new class to parse mathematical expressions
class MathExpr {
    public:
        MathExpr(string e);
        void printExpr();
        double parse();
        double parse(string expr);
        double parseExpr();
        double parseTerm();
        double parseFact(bool u);
        bool eat(bool white, char ch);
        double scanNumber();
    private:
        string expr;
        double result;
        bool isValidExpr;
        bool opOccupied;
        int pos;
};

bool parseToDouble(string d, double *db);