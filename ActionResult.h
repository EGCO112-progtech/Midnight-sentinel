#include <iostream>
#include <string>

struct ActionResult{
    int staminaChange; //+ for stamina gain, - for stamina loss
    float hpChange; //+ for health gain, - for health loss
    bool isProjectFinished = false;
    std::string message ="";
    std::string storyBeats[5];
    int storySize = 0;
    std::string targetScene = "";

};