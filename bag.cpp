#include <algorithm>
#include <cassert>
#include "bag.h"

    //ALWAYS INCLUDE STATIC MEMBER IF USED ON DEFINITION. Don't include the word static and
    //include bag::size_type and bag::DEFAULT_CAPACITY; no need to include = 30 since it's already initialized on bag::
    const bag::size_type bag::DEFAULT_CAPACITY;

    //CONSTRUCTORS AND DESTRUCTORS
    bag::bag(size_type initial_capacity = DEFAULT_CAPACITY){ //constructor is a default constructor because the parameter has a default argument.
                                                             //initialization of variables. data now is a dynamic array since it's a pointer of value_type int
      data = new value_type[initial_capacity];     //data is now a dynamic array of value_type initialized at 30 capacity.
      capacity = initial_capacity;                 // at this point is 30
      used = 0;                                    //this is the constructor that is built when the object is instantiated, therefore the bag is empty.

      //at this point we have:
      //a bag, with a data dynamic array of default capacity = 30 which is the initial capacity
      //with used = 0 because the bag is empty when it's created
    }

    bag::bag(const bag& source){    //COPY CONSTRUCTOR to create a copy, the compiler first creates a temporary by invoking the default
                                    //constructor of the new object. Then uses the copy constructor to initialize as a copy of that
                                    //temporary. Temporary objects are created while program execution are always of const type.
                                    //So, the keyword is required. The & is used to modified the copied object.
      data = new value_type[source.capacity];
      capacity = source.capacity;               //copy data, capacity, used from source bag to new bag.
      used = source.used;
      copy(source.data,source.data+used, data);   //from <algorithms> copy(start, end(stat + end), result);

    }
    bag::~bag(){
        delete []data;    //this releases the used memory from the dynamic array back to the heap.
    }


    /*    typedef int value_type;
          typedef std::size_t size_type;
          static const size_type DEFAULT_CAPACITY = 30;
    */

    /*    value_type *data;
          size_type used;
          size_type capacity;
    */

    //MODIFICATION MEMBER FUNCTION
                                                //parameter takes a new_capacity of type int for increasing the size of the capacity
    void bag::reserve(size_type new_capacity){    //function reserves another chunk of memory in case the capacity gets filled for efficiency
        value_type *large_array;    //pointer to a large array of value_type int

        if(new_capacity == capacity)
            return;                         //if new_capacity is equal to capacity do nothing. Allocated memory is already the right size

        if(new_capacity < used)             //if new_capacity is less than used, then new_capacity = used.
            new_capacity = used;

        larger_array = new value_type[new_capacity];  //create a new dynamic array of new_capacity if capacity is greater than used.
        copy(data, data + used, large_array);    //copy data from the bag to the large_array.
        delete [] data;                          //since we have a new array, we release the memory allocated for data to the heap.
        data = large_array;                      //now data memory allocation is overwritten with the large_array
        capacity = new_capacity;                 //also, capacity gets overwritten.
    }


    bool erase_one(const value_type& target){  //same as the regular bag, takes an element from bag of type int, finds it and erases it (one copy)
        size_type index;                       //the location of target in the array
        index = 0;
        while((index < used)&&(data[index]!= target))  //index is less than used and data at index is not equal to the target
            ++index;                                    //increment index by one

        if(index == used)                               //if index == used target is not in the bag return false end of function
            return false;

        --used;                                         //at this point target is in the bag and we decrement used by one and copy the last item onto data[index]
        data[index] = data[used];
        return true;

    }

    bag::size_type bag::erase(const value_type& target){  // erases all copies of one target, goes over the entire array.
        size_type index = 0;                              // works almost the same way as erase_one
        size_type many_removed = 0;
        while (index < used){

            if(data[index] == target){
                 --used;
            data[index] = data[used];
            ++many_removed;
        }
        else
            ++index;
    }
    return many_removed;
    }


    void bag::insert(const value_type& entry){        // function to insert items in the bag, takes a value_type int and adds it to the bag without makes changes
        if(used == capacity)                          // if used reaches the same number as capacity
            reserve(used+1);                          // use reserved memory to enlarge the array of data using used + 1
        data[used] = entry;                           // insert element into the data array at position used and increment used.
        ++used;
    }

    void bag::operator +=(const bag& addend){          // addend means a number that is added to another in this case a bag added no another
        if(used + addend.used > capacity))              // ensures that there is enough room for the new items.
        reserve(used + addend.used);                    //

        copy(addend.data, addend.data + addend.user, data + used);
        used += addend.user;
    }
    void operator =(const bag& source);

    //CONSTANT MEMBER FUNCTIONS
    size_type size() const{return used;}
    size_type count(const value_type& target)const;


    //NON-MEMBER FUNCTION FOR THE BAG CLASS
    bag operator +(const bag& b1, const bag& b2);



