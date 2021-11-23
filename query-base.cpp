#include <string>

#include "query-base.h"
#include "text-query.h"

using namespace std;

// takes a string and creates a new Word_query and bind its shared_ptr member
// to that newly created object
//Query::Query(const string& word)  // TODO
//{
    //q_ {new Word_query(word)};
    //q_ = std::make_shared<Word_query>(word);
//}

Query_result Query::eval(const Text_query& t) const
{
    cout << __PRETTY_FUNCTION__ << endl;
    return q_->eval(t);
}

Query_result Word_query::eval(const Text_query& t) const
{
    return t.query(query_word_);
}

// 
std::string Word_query::rep() const 
{
    return (query_word_);
}
