#pragma once

#include <string>
#include <memory>

#include "text-query.h"
#include "types.h"

// abstract class acts as a base class for concrete query types; all members are private
class Query_base
{
    friend class Query;

protected:
    // in types.h using line_no = Text_query::line_no;
    virtual ~Query_base() = default;
private:
    // eval returns the Query_result that matches this Query
    virtual Query_result eval(const Text_query&) const = 0;
    // rep is a string representation of the query
    virtual std::string rep() const = 0;
};

//
// looks for a given string. it is the only operation which actually performs 
// a query on the given Text_query object
//
// p642
//
class Word_query : public Query_base
{
//public:
    friend class Query; // Query uses the Word_query ctor

    Word_query(const std::string& s) : query_word_(s) { }

    Query_result eval(const Text_query&) const override;

    // returns the string that this word query represents (n.b. not the result of the query)
    std::string rep() const override;

private:
    std::string query_word_; // word for which to search
};

// tbd if this is the right/best place for Query class
// Interface class that holds the result of a query operation (p640)
class Query_base;
class Query
{
private:
    // these operators need access to the shared_ptr ctor
    //friend Query operator~(const Query&);
    //friend Query operator|(const Query&, const Query&);
    //friend Query operator&(const Query&, const Query&);

public:
    // this works but using make_shared in .cpp version of ctor didn't (private in context error)
    // this also has the private error 
    // Query(const std::string& s) : q_(std::make_shared<Word_query>(s)) {} // builds a new Word_query
    Query(const std::string& s) : q_(new Word_query(s)) {} // builds a new Word_query
    // interface functions: call the corresponding Query_base operations
    Query_result eval(const Text_query& t) const;
    //std::string rep() const;

private:
    //Query(std::shared_ptr<Query_base> query);
    std::shared_ptr<Query_base> q_;
};
