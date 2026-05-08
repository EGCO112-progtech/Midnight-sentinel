#ifndef ACTIONABLE_H
#define ACTIONABLE_H

#include <string>
#include "ActionResult.h"

class ActionAble {
    public:
        virtual ~ActionAble() {} //destructor

        virtual ActionResult Action() = 0;
        virtual std::string getName() = 0;
        virtual int getStaminaCost() = 0;

};

#endif