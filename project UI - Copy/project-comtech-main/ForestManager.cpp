#include "ForestManager.h"
#include "BaseEvent.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
//=========Constructor and Destructor=========
ForestManager::ForestManager(){
    //cout << "\n  [Init-Debug] 1. CONSTRUCTOR..." << endl;
    // Initialize projects
    projects[0] = new Project("Reforestation (Recovery Rate +2%)", 5, 1);
    projects[1] = new Project("Fire Prevention (Reduce Damage 30%)", 6, 1);
    projects[2] = new Project("Wildlife Protection (Max Stamina +3)", 7, 1);

    //Initialize data
    forestHP = 100;
    maxStamina = 10;
    currentStamina = 10;
    currentDay = 1;
    dailyDamage = 0;
    buff1 = false;
    buff2 = false;
    buff3 = false;
    activated1 = false;
    activated2 = false;
    activated3 = false;

    // Seed random number generator
    srand(time(0));
}

ForestManager::~ForestManager() {
    for (int i = 0; i < 3; i++) {
        delete projects[i];
    }
}
//=========Game Logic=========
void ForestManager::DailyEvents() {
    int phase = 1;
    int totalEventStamina = 6;
    int staminathreshold = 4; // Base threshold for events
    if(currentDay > 5) {
        phase = 3;
        totalEventStamina = 12;
        staminathreshold = 8;
    }
    else if(currentDay > 2 ) {
        phase = 2;
        totalEventStamina = 10;
        staminathreshold = 7;
    }
    int ThreatCost = activeEvents.getTotalStaminaCost();
    
    //mission events
    ActionResult res;
    BaseEvent* newEvent = nullptr;
    int random = rand() % 2;

    if(phase == 1) {
        switch(random){
            case 0:
                newEvent = new MissionEvent("FAKE", 1);
                break;
            case 1:
                newEvent = new MissionEvent("SUS", 1);
                break;
        }
    } 
    else if(phase == 2) {
        switch (random)
        {
        case 0:
            newEvent = new MissionEvent("SUS", 1);
            break;
        case 1:
            newEvent = new MissionEvent("REAL", 1);
            break;
        default:
            break;
        }
    }
    else if(phase == 3) newEvent = new MissionEvent("REAL", 1);
    activeEvents.add(newEvent);
    ThreatCost += newEvent->getStaminaCost();
    
    while(ThreatCost < totalEventStamina) {
        newEvent = nullptr;
        //======Phase 1: Basic Events=======
        if(phase == 1){
            int eventType = rand() % 3;
            switch(eventType) {
                case 0:
                    newEvent = new DisasterEvent("FIRE",1,4); //name, level, lifespan
                    break;
                case 1:
                    newEvent = new DisasterEvent("ANIMAL",1,1);
                    break;
                case 2:
                    newEvent = new DisasterEvent("PLANTCON",1,1);
                    break;
                case 3:
                    newEvent = new DisasterEvent("PEST",1,2);
                    break;
                case 4:
                    newEvent = new DisasterEvent("FLOOD",1,2);
                    break;
                default: break; // No event
                }
            }

        else if(phase == 2) {
            int eventType = rand() % 8;
            switch(eventType) {
                case 0:
                    newEvent = new DisasterEvent("FIRE",2,3);
                    break;
                case 1:
                    newEvent = new DisasterEvent("ANIMAL",1,1);
                    break;
                case 2:
                    newEvent = new DisasterEvent("PLANTCON",1,1);
                    break;
                case 3:
                    newEvent = new DisasterEvent("LANDSLIDE",1,2);
                    break;
                case 4:
                    newEvent = new DisasterEvent("PEST",1,2);
                    break;
                case 5:
                    newEvent = new DisasterEvent("TOXIC",1,2);
                    break;
                case 6:
                    newEvent = new DisasterEvent("HEATWAVE",1,2);
                    break;
                case 7:
                    newEvent = new DisasterEvent("ACID_RAIN",1,2);
                    break;
                default: break; // No event
            }   
        }
        else if(phase == 3) {
            int eventType = rand() % 9;
            switch(eventType) {
                case 0:
                    newEvent = new DisasterEvent("FIRE",3,2);
                    break;
                case 1:
                    newEvent = new DisasterEvent("LANDSLIDE",1,2);
                    break;
                case 2:
                    newEvent = new DisasterEvent("FLOOD",1,2);
                    break;
                case 3:
                    newEvent = new DisasterEvent("STORM",1,2);
                    break;
                case 4:
                    newEvent = new DisasterEvent("PLANTCON",1,1);
                    break;
                case 5:
                    newEvent = new DisasterEvent("PEST",1,2);
                    break;
                case 6:
                    newEvent = new DisasterEvent("TOXIC",1,2);
                    break;
                case 7:
                    newEvent = new DisasterEvent("HEATWAVE",1,2);
                    break;
                case 8:
                    newEvent = new DisasterEvent("ACID_RAIN",1,2);
                    break;
                
                default: break; // No event
            }
        }
        if(newEvent != nullptr){
            int eventCost = newEvent->getStaminaCost();
            if(ThreatCost + eventCost <= totalEventStamina) {
                activeEvents.add(newEvent);
                ThreatCost += eventCost;
            }
            else {
                delete newEvent; // Clean up if we can't add it
                break;
            }
        }
        else {
            delete newEvent;
            break;
        }
    }
}

void ForestManager::processEndOfDay() {
    // summarize daily events
    DailySummary = "";
    int count = getEventCount();
    for(int i = 0; i < count; i++) {
        BaseEvent* ev = getEvent(i);
        DailySummary += "\t- " + ev->getAlertMessage() + " [Dmg: " + to_string((int)ev->getDamage()) + "]\n";
    }
    if (DailySummary == "") {
        DailySummary = "- No active threats!\n";
    }

    dailyDamage += activeEvents.endDay();

    if(buff2) dailyDamage *= 0.7; // Buff 2: Fire Prevention - Reduce damage from fire events by 30%
    if(buff3) maxStamina = 13; // Buff 3: Wildlife Protection - Increase max stamina by 2
    
    
    //passive recovery forestHP 
    int recoveryRate;
    if(forestHP >= 80){
        recoveryRate = 3;
    } 
    else if(forestHP >=40 && forestHP < 80){
        recoveryRate = 1;
    } 
    else{
        recoveryRate = 0;
    } 
    if(buff1) recoveryRate += 2; // Buff 1: Reforestation - Increase forest HP by 5 each day
    forestHP -= dailyDamage; // Apply damage to forest HP
    forestHP = forestHP+recoveryRate;
    
    if(forestHP >= 100) forestHP = 100;
    if(forestHP <= 0) forestHP = 0;
    
    lastDayRecovery = recoveryRate;
    activeEvents.updateLifespans();
}

void ForestManager::nextDay() { // End of day processing rest Events effects
    // Refill stamina at the end of the day
    currentStamina = maxStamina;
    dailyDamage = 0;
    currentDay++;
    if(isGameOver()) {
        return;
    }
}
// update status
void ForestManager::applyResult(ActionResult res) {
    currentStamina += res.staminaChange;
    forestHP += res.hpChange;

    //รับค่าdamage จาก mission ไปสรุปผล
    if (res.hpChange < 0) {
        this->dailyDamage += (res.hpChange * -1); 
    }

    if(res.message != ""){
        addSystemMessage(res.message);
    }
}

bool ForestManager::isGameOver() {
    if(forestHP <= 0 || currentDay > 7){
        return true;
    }
    else return false;
}

// Event handling
void ForestManager::handleEvent(BaseEvent* event) {
    int cost = event->getStaminaCost();

    if (currentStamina >= cost) {
        ActionResult res = event->Action();
        applyResult(res);
        activeEvents.remove(event);
    } else {
        addSystemMessage("No Stamina! (need " + to_string(cost) + ")");
    }
}


// Mission Handling
void ForestManager::handleMission(MissionEvent* m, int choice) {
    int cost = m->getChoicecost(choice); // ถามราคาของตัวเลือกนั้นๆ ก่อน
    
    if (currentStamina >= cost) {
        ActionResult res = m->executeChoice(choice);
        applyResult(res);
        activeEvents.remove(m);
    } else {
        addSystemMessage("No Stamina! (need " + to_string(cost) + ")");
    }
}

// Project handling
void ForestManager::handleProject(Project* proj) {
    ActionResult res = proj->Action();
    applyResult(res); 
    if (res.isProjectFinished) {
        activateBuff(proj->getName());
    }
    
}

Project* ForestManager::getProject(int index) const {
        if (index >= 0 && index < 3) {
            return projects[index];
        }
        return nullptr;
    }
    
void ForestManager::activateBuff(string projectName) {
    if(projectName == "Reforestation (Recovery Rate +2%)") {
        if(activated1){
            addSystemMessage("Already completed!");
        }
        else{
            buff1 = true;
            activated1 = true;
            addSystemMessage("Buff Activated: Forest HP recovery rate increases by 2%!");
        }
    }
    else if(projectName == "Fire Prevention (Reduce Damage 30%)") {
        if(activated2){
            addSystemMessage("Already completed!");
        }
        else{
            activated2 = true;
            buff2 = true;
            addSystemMessage("Buff Activated: Reduce damage from fire events by 30%!");
        }
    }
    else if(projectName == "Wildlife Protection (Max Stamina +3)") {
        if(activated2){
            addSystemMessage("Already completed!");
        }
        else{
            activated3 = true;
            buff3 = true;
            addSystemMessage("Buff Activated: Increase max stamina by 3!");
        }
    }
}

void ForestManager::updateStamina(int amount) {
    currentStamina += amount; 
    
    if (currentStamina < 0) {
        currentStamina = 0; // กันติดลบ
    }
    if (currentStamina > maxStamina) {
        currentStamina = maxStamina; // กันเติมพลังงานล้นเกินหลอด
    }
}

void ForestManager::reset() {
    activeEvents.clear();
    forestHP = 100;
    maxStamina = 10;
    currentStamina = maxStamina;
    currentDay = 1;
    dailyDamage = 0;
    lastDayRecovery = 0;
    buff1 = buff2 = buff3 = false;
    activated1 = activated2 = activated3 = false;
    systemMessage.clear();
    DailySummary.clear();

    for (int i = 0; i < 3; i++) {
        if (projects[i]) {
            projects[i]->reset();
        }
    }
}
