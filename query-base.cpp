#include <string>
#include <algorithm>

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
    auto q_result = query_.eval(tq);

    auto res_file = q_result.get_file();

    // cout << "res_file size:" << (*res_file).size() << endl << "contents:" << endl;

    // size_t l=1;
    // for (const auto& line : *res_file)
    // {
    //     // if count 
    //     cout << l++ << ": " << line << endl;
    // }

    auto lines = std::make_shared<std::set<line_no_t>>();
    
    for (size_t count = 0; count < (*res_file).size(); ++count)
    {
        size_t line_no = count + 1;

        if (std::find(q_result.begin(), q_result.end(), line_no) != q_result.end())
        {
            //cout << "line_no " << line_no << " is in intial_res" << endl;
            continue;
        }

        // line is not in initial result (i.e. unnegated input), so added to negated output
        lines->emplace(line_no);

        //cout << "rkp1:" << (*res_file)[count] << endl;
    }

    //auto new_qresult = Query_result(query_.rep(), lines, q_result.get_file());

    return Query_result(query_.rep(), lines, q_result.get_file());
}
