#include "../../include/utils/parserAbstractParent.hpp"

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{

ParserAbstractParent::ParserAbstractParent(){}
ParserAbstractParent::~ParserAbstractParent(){}
ParserAbstractParent& ParserAbstractParent::operator=(const ParserAbstractParent&){
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
