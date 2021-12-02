#include <string>

#include "query-base.h"
#include "text-query.h"

using namespace std;

Query_result Query::eval(const Text_query& t) const
{
    cout << __PRETTY_FUNCTION__ << endl;
    return q_->eval(t);
}

Query_result Word_query::eval(const Text_query& t) const
{
    cout << __PRETTY_FUNCTION__ << endl;
    return t.query(query_word_);
}

// 
std::string Word_query::rep() const 
{
    return (query_word_);
}
