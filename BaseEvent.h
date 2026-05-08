#ifndef BASEEVENT_H
#define BASEEVENT_H

#include <string>
#include "ActionAble.h"

class BaseEvent : public ActionAble {
    protected:
        std::string eventName;
        std::string successMessage;
        std::string alertMessage;
        int StaminaCost;
        float damage;
        int lifespan;
    public:
        virtual ~BaseEvent() {} //destructor

        BaseEvent(std::string name="", std::string alertMsg = "",int cost=0, float dmg=0,int life = 0) {//constructor
            this->eventName = name; 
            this->alertMessage = alertMsg;
            this->StaminaCost = cost; 
            this->damage = dmg;
            this->lifespan = life;
        } 
        virtual ActionResult Action() override;
        virtual ActionResult triggerEffects()=0;
        virtual std::string getName() override {return eventName;}
        virtual std::string getAlertMessage() { return alertMessage; }
        virtual int getStaminaCost() {return StaminaCost;}
        virtual float getDamage() {return damage;}
        virtual std::string getType() = 0;
        virtual int getLifespan() const { return lifespan; }
        virtual void reduceLifespan() { lifespan--; }
        virtual bool isExpired() const { return lifespan <= 0; }
        
        
};

class DisasterEvent : public BaseEvent{
    private:
        std::string eventType;
        int level;
    public:
        ~DisasterEvent() {} //destructor

        DisasterEvent(std::string eventType, int eventLevel = 1, int life = 1);
        ActionResult Action() override;
        ActionResult triggerEffects() override;
        std::string getType() override {return eventType;}
        void updateStat();
};

class MissionEvent : public BaseEvent{
    private:
        std::string missionType;
        int cost1,cost2,cost3;
        int damage1,damage2,damage3;
        std::string scene;
        std::string storyText1,storyText2,storyText3,storyText4,storyText5;
        std::string choice1Text,choice2Text,choice3Text;
        std::string successText1,successText2,successText3;
    public:
        ~MissionEvent() {} //destructor

        MissionEvent(std::string type,int life);
        ActionResult Action() override;
        ActionResult triggerEffects() override;
        void updateStat();
        float getDamage() override { return damage3;}
        std::string getType() override {return "Mission";}
        std::string getMissionType() {return missionType;}
        ActionResult getStory();
        std::string getChoice(int choiceIndex);
        int getChoicecost(int choiceIndex);
        ActionResult executeChoice(int choiceIndex);

};
#endif