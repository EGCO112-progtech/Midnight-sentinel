#include "AlertList.h"
#include "BaseEvent.h"
#include <iostream>

AlertList::AlertList() : head(nullptr), count(0) {}

AlertList::~AlertList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current->data; // delete the BaseEvent object
        delete current; // delete the node itself
        current = nextNode;
    }
}

// Insert sorted by stamina cost (highest first)
void AlertList::add(BaseEvent* item) {
    Node* newNode = new Node(item);
    if (head == nullptr || item->getStaminaCost() > head->data->getStaminaCost()) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->data->getStaminaCost() >= item->getStaminaCost()) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    count++;
}

// Delete a specific event from the list
void AlertList::remove(BaseEvent* targetItem) {
    if (head == nullptr) return;

    // Head case
    if (head->data == targetItem) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
        count--;
        return;
    }

    // Middle or end case
    Node* current = head;
    while (current->next != nullptr && current->next->data != targetItem) {
        current = current->next;
    }

    // delete if found
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = temp->next; // connect previous node to next node, skipping the one to delete
        delete temp;
        count--;
    }
}

//  End of Day: Trigger effects of all events in the list
float AlertList::endDay() {
    Node* current = head;
    float totalDamage = 0.0f;
    
    while (current != nullptr) {
        
        if (current->data != nullptr) {
            totalDamage += current->data->getDamage();
            current->data->triggerEffects(); 
        }

        current = current->next;
    }
    return totalDamage;
}

int AlertList::getTotalStaminaCost(){
    int totalCost = 0;
    Node* current = head;
    while (current != nullptr) {
        if (current->data != nullptr) {
            totalCost += current->data->getStaminaCost(); // Convert negative cost to positive for summation
        }
        current = current->next;
    }
    return totalCost;
}

int AlertList::getSize() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

BaseEvent* AlertList::getAlertAt(int index) const {
    Node* current = head;
    int count = 0;

    while (current != nullptr) {
        if (count == index) {
            return current->data; 
        }
        count++;
        current = current->next;
    }
    return nullptr;
}

void AlertList::updateLifespans() {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        current->data->reduceLifespan();

        if (current->data->isExpired()) {
            Node* temp = current;
            
            if (prev == nullptr) {
                head = current->next;
                current = head;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            
            delete temp->data;
            delete temp;
            count--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void AlertList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current->data;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    count = 0;
}
