#pragma once

#include "utils.hpp"
#include "configuration.hpp"

namespace MAIN_NAMESPACE{

class Parser{
public:
    Parser();
    Parser(const std::string& inputFile);
    Parser(const Parser& other);
    
    ~Parser();

    Parser& operator=(const Parser& other);
    const CONFIG_NAMESPACE::Configuration& operator->();

    static Parser parseFile(const std::string& inputFile);
    const CONFIG_NAMESPACE::Configuration& getConfiguration() const;

private:
    CONFIG_NAMESPACE::Configuration configuration_;

};

}
