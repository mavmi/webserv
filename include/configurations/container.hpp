#pragma once

#include "utils.hpp"

namespace configuration {

// It is wrapper class for configuration classes's container.
template <typename T>
class Container {
public:
    typedef std::vector<T>                                  InnerContainerType;
    typedef typename InnerContainerType::size_type          SizeType;
    typedef typename InnerContainerType::difference_type    DifferenceType;
    typedef T                                               ValueType;
    typedef T*                                              PointerType;
    typedef T&                                              ReferenceType;
    typedef const T&                                        ConstReferenceType;

    Container(){}
    Container(const Container& other){
        operator=(other);
    }
    ~Container(){}

    Container& operator=(const Container& other){
        innerContainer_ = other.innerContainer_;
        return *this;
    }

    SizeType size() const {
        return innerContainer_.size();
    }

    ReferenceType at(DifferenceType position) {
        return innerContainer_.at(position);
    }
    ConstReferenceType at(DifferenceType position) const {
        return innerContainer_.at(position);
    }

    void push_back(ReferenceType value){
        innerContainer_.push_back(value);
    }
    void push_back(ConstReferenceType value){
        innerContainer_.push_back(value);
    }

    ReferenceType front(){
        return innerContainer_.front();
    }
    ConstReferenceType front() const {
        return innerContainer_.front();
    }

    ReferenceType back(){
        return innerContainer_.back();
    }
    ConstReferenceType back() const {
        return innerContainer_.back();
    }

private:
    InnerContainerType innerContainer_;

};

}
