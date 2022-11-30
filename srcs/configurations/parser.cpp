#include "../../include/configurations/parser.hpp"

namespace wsrv{

Parser::Parser(){}
Parser::Parser(const std::string& inputFile){
    configuration_.parseFile(inputFile);
}
Parser::Parser(const Parser& other)
    : configuration_(other.configuration_) {

}

Parser& Parser::operator=(const Parser& other){
    configuration_ = other.configuration_;
    return *this;
}
const configuration::Configuration& Parser::operator->(){
    return configuration_;
}

Parser::~Parser(){}

Parser Parser::parseFile(const std::string& inputFile){
    return Parser(inputFile);
}
const configuration::Configuration& Parser::getConfiguration() const{
    return configuration_;
}

}
