#include <string>

#include "query-base.h"

using namespace std;

Query::Query(const string& word)  // TODO
{
    (void)word;
}

Query_result Query::eval(const Text_query& t) const
{
    return q_->eval(t);
}