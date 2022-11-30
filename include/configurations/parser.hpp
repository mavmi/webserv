#pragma once

#include "utils.hpp"
#include "configuration.hpp"

namespace wsrv{

class Parser{
public:
    Parser();
    Parser(const std::string& inputFile);
    Parser(const Parser& other);
    
    ~Parser();

    Parser& operator=(const Parser& other);
    const configuration::Configuration& operator->();

    static Parser parseFile(const std::string& inputFile);
    const configuration::Configuration& getConfiguration() const;

private:
    configuration::Configuration configuration_;

};

}
