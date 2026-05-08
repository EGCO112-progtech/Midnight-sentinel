#include "Project.h"

bool Project::isComplete(std::string name) {
    if(projectName == name && progress >= maxProgress) {
        return true;
    }
        else return false;
}

ActionResult Project::Action() {
    ActionResult res;
    if (isComplete(projectName)) {
        res.message = projectName + " already completed";
        res.staminaChange = 0; 
        res.isProjectFinished = false; 
        
        return res;
    }

    progress++;
    res.staminaChange = -StaminaCost; 
    res.hpChange = 0;
    
    if (isComplete(projectName)) {
        res.message = "You have complete " + projectName;
        
        res.isProjectFinished = true; 
        
    } else {
        res.message = "You are working on " + projectName;
        res.isProjectFinished = false;
    }

    return res;
}

void Project::reset() {
    progress = 0;
}

