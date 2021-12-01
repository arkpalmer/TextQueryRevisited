#pragma once

#include <string>
#include <memory>

#include "text-query.h"
#include "types.h"

class Query;

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

class Query_base;

//
// tbd if this is the right/best place for Query class
// Interface class that points to an object of a type derived from Query_base (p640 Table 15.1)
// Interface class that holds the result of a query operation (p640)
//
// Query class provides the interface to (and hides) the Query_base inheritance hierarchy.
// Points to an object of a type derived from Query_base
//
class Query
{
private:
    //
    // these operators need access to the shared_ptr ctor (see p640 for more explanation)
    // they create Not_query, Or_query and And_query respectively
    // 
    friend Query operator~(const Query&);
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
    Query(std::shared_ptr<Query_base> q) : q_(q) {}

    std::shared_ptr<Query_base> q_;
};

//
// p640 class derived from Query_base that represents the set of lines in which
// Query operand does not appear
//
class Not_query : public Query_base
{
    // I guess this operator needs access to Not_query's ctor (?tbc) 
    friend Query operator~(const Query&);

    Not_query(const Query& query) : query_(query) { }

    // holds a Query object, which it negates via eval
    Query query_;

    // TODO
    Query_result eval(const Text_query&) const override { return Query_result(); } 

    // returns the string that this word query represents (n.b. not the result of the query)
    std::string rep() const override { return "TODO"; }
};

inline Query operator~(const Query& query)
{
    // Query(const std::string& s) : q_(new Word_query(s)) {} // builds a new Word_query
    // ??? how do I create a query which points to a Not_query? 
    //     the query ctor creates a Word_query ==> you don't, it has a Query which it negates

    // Query(std::shared_ptr<Query_base>& q)

// really not getting much value out of this whole exercise, it's so poorly documented...
    // doesn't work - says ctor is private return Query(std::make_shared<Not_query>(query));
    return std::shared_ptr<Query_base>(new Not_query(query));
}

