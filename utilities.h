#ifndef __EX16_2_H__ 
#define __EX16_2_H__

#include <functional>
#include <cstring>
#include <iostream>

// dummy class for testing
class Channel
{
public:
    ~Channel() 
    { 
        //std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};
 
template <typename T>
class Debug_delete2
{
public:
    Debug_delete2(std::ostream& os = std::cout) : os_(os)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    void operator() (const T* p)
    {
        os_ << "Debug_delete2" << std::endl;
        delete p;
    }

private:
    std::ostream& os_;
};

class Debug_delete
{
public:
    Debug_delete(const std::string& s = "", std::ostream& os = std::cout) : s_(s), os_(os)
    {
        //std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    template <typename T> void operator() (const T* p)
    {
        os_ << "Debug_delete: " << s_ << " ," << typeid(p).name() << std::endl;
        delete p;
    }

private:
    std::string   s_;
    std::ostream& os_;
};



#endif