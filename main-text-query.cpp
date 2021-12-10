#include <iostream>
#include <fstream>
#include <string>

#include "text-query.h"
#include "query-base.h"

using namespace std;

// text-query test code
// https://stackoverflow.com/questions/46877667/how-to-add-a-new-project-to-github-using-vs-code

int main()
{
    cout << "main" << endl;
//    return 0;
    std::ifstream file("text.txt");

    Text_query text_query(file);

    Query q = Query("there");

    auto res2 = q.eval(text_query);

    cout << "output of Query q:" << endl;
    print(cout, res2);
    
    auto qn = ~q; // this should call upon Not_query (I think)
    // later, could also do something like: qa & ~qb (again, I think)

    auto resnq = qn.eval(text_query);

    std::cout << qn.rep() << endl;

    cout << "output of Query qn:" << endl;
    print(cout, resnq); //test 2

    Query q1 = Query("first");
    Query q4 = Query("fourth");
    auto q1_or_q4 = (q1 | q4);

    cout << "output of Query q1_or_q4:" << endl;
    auto r = q1_or_q4.eval(text_query);
    print(cout, r); //test 2

    auto q1_and_q4 = (q1 & q4);
    cout << "output of Query q1_and_q4:" << endl;
    auto ra = q1_and_q4.eval(text_query);
    print(cout, ra); //test 2

    return 0;

// NEXT do the loop then answer 16.23
    std::string s("two");
    //std::string s("line");
    //std::string s("lineabc");
    auto res = text_query.query(s);
    print(cout, res);

    return 0;
}