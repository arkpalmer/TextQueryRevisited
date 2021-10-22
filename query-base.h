#pragma once

#include <string>
#include <memory>

#include "text-query.h"
#include "types.h"

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
    Query(const std::string&); // builds a new Word_query
    // interface functions: call the corresponding Query_base operations
    Query_result eval(const Text_query& t) const;
    //std::string rep() const;

private:
    //Query(std::shared_ptr<Query_base> query);
    std::shared_ptr<Query_base> q_;
};

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