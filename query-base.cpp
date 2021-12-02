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

Query_result Not_query::eval(const Text_query& tq) const 
{ 
    // Text_query stuff:
    // Query_result query(const std::string& str) const;
    //
    // private:
    // std::shared_ptr<stored_file_t> file_; // contents of file
    // std::map<std::string, std::shared_ptr<std::set<line_no_t>>> wm_;
    //
    //auto res = q_->

    auto initial_res = query_.eval(tq);

    return initial_res;
}
