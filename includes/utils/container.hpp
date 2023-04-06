#pragma once

#include <memory>
#include <vector>

#include "utils.hpp"
#include "wrapper.hpp"

namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{
class Configuration;
class RouteConfiguration;
class ServerConfiguration;
}
}

namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{

class ContainerException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    ContainerException(const char* msg);
    ContainerException(const std::string& msg);

    ContainerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ContainerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ContainerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    ContainerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    std::string output_() const;

};

// It is wrapper class for configuration classes's container.
template <typename T>
class Container{
public:
    typedef size_t                                          SizeType;
    typedef size_t                                          DifferenceType;
    typedef T                                               ValueType;
    typedef T*                                              PointerType;
    typedef T&                                              ReferenceType;
    typedef const T&                                        ConstReferenceType;
    typedef ContainerException                              ExceptionType;

    Container(){
        data_ = NULL;
        size_ = 0;
        capacity_ = 0;
    }
    Container(const Container& other){
        copyData_(other);
    }
    ~Container(){
        delete[] data_;
    }

    Container& operator=(const Container& other){
        delete[] data_;
        copyData_(other);
        return *this;
    }

    SizeType size() const {
        return size_;
    }
    SizeType capacity() const {
        return capacity_;
    }

    ReferenceType at(DifferenceType position) {
        if (position >= size_) throw ExceptionType("Out of bounds", EXC_ARGS);
        return data_[position];
    }
    ConstReferenceType at(DifferenceType position) const {
        if (position >= size_) throw ExceptionType("Out of bounds", EXC_ARGS);
        return data_[position];
    }

    void push_back(ReferenceType value){
        if (size_ == capacity_) updateCapacity_((capacity_ == 0) ? 1 : capacity_ * 2);
        data_[size_++] = value;
    }
    void push_back(ConstReferenceType value){
        if (size_ == capacity_) updateCapacity_((capacity_ == 0) ? 1 : capacity_ * 2);
        data_[size_++] = value;
    }

    ReferenceType front(){
        if (size_) return data_[0];
        throw ExceptionType("Container is emtpy", EXC_ARGS);
    }
    ConstReferenceType front() const {
        if (size_) return data_[0];
        throw ExceptionType("Container is emtpy", EXC_ARGS);
    }

    ReferenceType back(){
        if (size_) return data_[size_ - 1];
        throw ExceptionType("Container is emtpy", EXC_ARGS);
    }
    ConstReferenceType back() const {
        if (size_) return data_[size_ - 1];
        throw ExceptionType("Container is emtpy", EXC_ARGS);
    }

private:
    SizeType size_;
    SizeType capacity_;
    PointerType data_;

    void updateCapacity_(SizeType capacity){
        if (capacity_ >= capacity) return;

        capacity_ = capacity;
        PointerType newData = new ValueType[capacity_];
        for (SizeType i = 0; i < size_; i++){
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
    }

    void copyData_(const Container& other){
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new ValueType[capacity_];
        for (SizeType i = 0; i < size_; i++){
            data_[i] = other.data_[i];
        }
    }

};

}
}
