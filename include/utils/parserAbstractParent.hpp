#pragma once

#include "utils.hpp"

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{

class ParserAbstractParent{
public:
    void done();
    bool isDone() const;

protected:
    bool isDone_;

    ParserAbstractParent();
    ~ParserAbstractParent();

    ParserAbstractParent& operator=(const ParserAbstractParent& other);

    virtual void checkValidity_() const = 0;
    virtual void throwOnDone_() const = 0;

};

}
