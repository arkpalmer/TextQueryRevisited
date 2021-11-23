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

    Query q = Query("two");

    auto res2 = q.eval(text_query);

    print(cout, res2);

    return 0;

// NEXT do the loop then answer 16.23
    std::string s("two");
    //std::string s("line");
    //std::string s("lineabc");
    auto res = text_query.query(s);
    print(cout, res);

    return 0;
}