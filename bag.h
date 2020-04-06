#ifndef BAG_H
#define BAG_H
#include <cstdlib> //provides size_t

class bag
{
public:
    //TYPEDEFS AND MEMBER FUNCTIONS
    typedef int value_type;
    typedef std::size_t size_type;
    static const size_type DEFAULT_CAPACITY = 30;

    //CONSTRUCTORS AND DESTRUCTORS
    bag(size_type initial_capacity = DEFAULT_CAPACITY);
    bag(const bag& source);
    ~bag();

    //MODIFICATION MEMBER FUNCTION
    void reserve(size_type new_capacity);
    bool erase_one(const value_type& target);
    size_type erase(const value_type& target);
    void insert(const value_type& entry);
    void operator+=(const bag& addend);
    void operator =(const bag& source);

    //CONSTANT MEMBER FUNCTIONS
    size_type size() const{return used;}
    size_type count(const value_type& target)const;

private:
    value_type *data;
    size_type used;
    size_type capacity;
};

    //NON-MEMBER FUNCTION FOR THE BAG CLASS
    bag operator +(const bag& b1, const bag& b2);

#endif // BAG_H
