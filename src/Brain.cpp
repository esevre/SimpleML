//
// Created by Erik Sevre on 5/15/18.
//

#include "Brain.hpp"


Brain &Brain::operator=(const Brain &brain) {
    directions.resize(brain.size());
    std::copy(brain.cbegin(), brain.cend(), this->begin());
    step = 0;
    return *this;
}


