#ifndef FORESTMANAGER_H
#define FORESTMANAGER_H

#include <iostream>
#include "AlertList.h"
#include "Project.h"
using namespace std;

class ForestManager {
    private:
        float forestHP;
        int maxStamina = 10;
        int currentStamina;
        int currentDay;
        float dailyDamage;
        int dailyStaminaUsed;
        float lastDayRecovery;
        bool buff1;
        bool buff2;
        bool buff3;
        bool activated1;
        bool activated2;
        bool activated3;
        string systemMessage = "";
        string DailySummary;

        AlertList activeEvents;
        Project* projects[3];
    public:
        ForestManager();
        ~ForestManager();

        void DailyEvents();
        void nextDay();
        bool isGameOver();
        void processEndOfDay();

        void handleEvent(BaseEvent* event);
        void handleMission(MissionEvent* m,int choice);
        void handleProject(Project* proj);
        void applyResult(ActionResult res);
        void activateBuff(string projectName);
        void updateStamina(int amount);
        void setSystemMessage(string msg) { systemMessage = msg;}
        void addSystemMessage(string msg) { 
            if(systemMessage!=""){
                systemMessage += "\n>> ";
            }
            systemMessage += msg;
        }
        string getSystemMessage() const{ return systemMessage; }
        float getDailyDamage() const{ return dailyDamage; }
        float getForestHP() const{ return forestHP; }
        int getCurrentDay() const{ return currentDay; }
        int getCurrentStamina() const{ return currentStamina; }
        int getEventCount() const{ return activeEvents.getSize(); }
        float getLastDayRecovery() const { return lastDayRecovery; }
        string getDailySummary() const { return DailySummary; }

        BaseEvent* getEvent(int index) const{ return activeEvents.getAlertAt(index); }
        Project* getProject(int index) const;
        void reset();
};
#endif