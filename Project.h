#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include "ActionAble.h"

class Project : public ActionAble {
    protected:
        std::string projectName;
        int maxProgress;
        int StaminaCost;
        int progress;
    public:
        ~Project() {}//destructor

        Project(std::string name, int maxProgress, int staminaCost): projectName(name), maxProgress(maxProgress), StaminaCost(staminaCost), progress(0) {} //constructor
        ActionResult Action() override;
        std::string getName() override {return projectName;}
        int getStaminaCost() override {return StaminaCost;}
        int getProgress() {return progress;}
        int getMaxProgress() {return maxProgress;}
        bool isComplete(std::string name);
};

#endif