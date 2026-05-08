#ifndef ALERTLIST_H
#define ALERTLIST_H

#include "Node.h"
#include "BaseEvent.h"

class AlertList {
    private:
        Node* head;
        int count;
    public:
        AlertList();
        ~AlertList();

        void add(BaseEvent* event);
        void remove(BaseEvent* event);
        float endDay();
        int getTotalStaminaCost();
        int getSize() const;
        BaseEvent* getAlertAt(int index) const;
        void updateLifespans();
};
#endif