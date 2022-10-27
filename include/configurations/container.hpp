#pragma once

#include "utils.hpp"

// It is wrapper class for configuration classes's container.
template <typename T>
class Container {
public:
    typedef std::vector<T>                                  INNER_CONTAINER_TYPE;
    typedef typename INNER_CONTAINER_TYPE::size_type        SIZE_TYPE;
    typedef typename INNER_CONTAINER_TYPE::difference_type  DIFFERENCE_TYPE;
    typedef T                                               VALUE_TYPE;
    typedef T*                                              POINTER_TYPE;
    typedef T&                                              REFERENCE_TYPE;
    typedef const T&                                        CONST_REFERENCE_TYPE;

    Container(){}
    Container(const Container& other){
        operator=(other);
    }
    ~Container(){}

    Container& operator=(const Container& other){
        innerContainer_ = other.innerContainer_;
        return *this;
    }

    SIZE_TYPE size() const {
        return innerContainer_.size();
    }

    REFERENCE_TYPE at(DIFFERENCE_TYPE position) {
        return innerContainer_.at(position);
    }
    CONST_REFERENCE_TYPE at(DIFFERENCE_TYPE position) const {
        return innerContainer_.at(position);
    }

    void push_back(REFERENCE_TYPE value){
        innerContainer_.push_back(value);
    }
    void push_back(CONST_REFERENCE_TYPE value){
        innerContainer_.push_back(value);
    }

    REFERENCE_TYPE front(){
        return innerContainer_.front();
    }
    CONST_REFERENCE_TYPE front() const {
        return innerContainer_.front();
    }

    REFERENCE_TYPE back(){
        return innerContainer_.back();
    }
    CONST_REFERENCE_TYPE back() const {
        return innerContainer_.back();
    }

private:
    INNER_CONTAINER_TYPE innerContainer_;

};
