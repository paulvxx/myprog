#include <iostream>
using namespace std;
#include <string>

// new class to parse Boolean Expressions
class BoolExpr {
    public:
        BoolExpr(string e);
        string parse();
        string parse(string expr);
        string parseOr();
        string parseAnd();
        string parseCond();
        string parseUnary(bool u);
        bool eat(bool white, string sub);
    private:  
        string expr;
        string result;
        int pos;    
};

