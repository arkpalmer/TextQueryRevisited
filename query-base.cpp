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
    cout << __PRETTY_FUNCTION__ << endl;
    return t.query(query_word_);
}

// 
std::string Word_query::rep() const 
{
    return (query_word_);
}

//
// I guess I'm not used to seeing an overloaded operator outside of a class (i.e. as a free function)
//
// these operators need access to the shared_ptr ctor (see p640 for more explanation)
// they create Not_query, Or_query and And_query respectively
// 
//
// sigh, book has inline, if I use inline, I get an undefined reference error
// answer: FOR INLINE, MUST BE DEFINED IN HEADER FILE
//inline Query operator~(const Query& query)
//  
#if 0
Query operator~(const Query& query)
{
    // Query(const std::string& s) : q_(new Word_query(s)) {} // builds a new Word_query
    // ??? how do I create a query which points to a Not_query? 
    //     the query ctor creates a Word_query ==> you don't, it has a Query which it negates

    // Query(std::shared_ptr<Query_base>& q)

// really not getting much value out of this whole exercise, it's so poorly documented...
    // doesn't work - says ctor is private return Query(std::make_shared<Not_query>(query));
    return std::shared_ptr<Query_base>(new Not_query(query));
}
#endif