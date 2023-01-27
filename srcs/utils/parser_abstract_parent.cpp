#include "../../include/utils/parser_abstract_parent.hpp"

namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{

ParserAbstractParent::ParserAbstractParent(){
    isDone_ = false;
}
ParserAbstractParent::~ParserAbstractParent(){}
ParserAbstractParent& ParserAbstractParent::operator=(const ParserAbstractParent& other){
    isDone_ = other.isDone_;
    return *this;
}

void ParserAbstractParent::done(){
    checkValidity_();
    isDone_ = true;
}
bool ParserAbstractParent::isDone() const{
    return isDone_;
}

}
}