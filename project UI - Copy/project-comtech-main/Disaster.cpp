#include "BaseEvent.h"

// Constructor ของคลาสลูก
DisasterEvent::DisasterEvent(std::string type, int lvl, int life){
    this->eventType = type;
    this->level = lvl;
    this->lifespan = life;
    updateStat();
}

void DisasterEvent::updateStat(){
    if (eventType == "FIRE") {
        if (level == 1) {
            eventName = "Camp Fire";
            alertMessage = "Hotspot detected.";
            successMessage = "Fire-Retardant deployed. Hotspot neutralized.";
            damage = 5;
            StaminaCost = 2;
        }
        else if (level == 2) {
            eventName = "Raging Fire";
            alertMessage = "Ignition perimeter expanding.";
            successMessage = "Aerial drones dispatched. Fireline contained.";
            damage = 10;
            StaminaCost = 3;
        }
        else if (level == 3) {
            eventName = "Out of Control Fire";
            alertMessage = "Canopy ignition confirmed. Fireline uncontained.";
            successMessage = "Heavy retardant mortar fired. Canopy fire suppressed.";
            damage = 15;
            StaminaCost = 4;
        }
        else if (level >= 4) {
            eventName = "Devastating Firestorm";
            alertMessage = "Extreme heat signature.";
            successMessage = "Emergency chemical drop successful. Thermal runaway stopped.";
            damage = 20;
            StaminaCost = 5;
        }
    }
    //FLOOD
    else if (eventType == "FLOOD") {
        if (level == 1) {
            eventName = "Flash Flood";
            alertMessage = "Water levels rising fast.";
            successMessage = "Drainage gates opened. Water levels stabilized.";
            damage = 7;
            StaminaCost = 3;
        }
        else if (level == 2) {
            eventName = "Raging Torrent";
            alertMessage = "Dam integrity compromised.";
            successMessage = "Emergency flood barriers deployed. Dam secured.";
            damage = 12;
            StaminaCost = 4;
        }
        else {
            eventName = "Catastrophic Deluge";
            alertMessage = "Massive kinetic water force detected.";
            successMessage = "Massive kinetic shielding engaged. Flood diverted.";
            damage = 15;
            StaminaCost = 6;
        }
    }
    //STORM
    else if (eventType == "STORM") {
        if (level == 1) {
            eventName = "Hurricane Force";
            alertMessage = "Satellite telemetry confirms cyclonic anomaly.";
            successMessage = "Tower lockdown engaged. External structures secured.";
            damage = 8;
            StaminaCost = 3;
        }
        else {
            eventName = "Supercell Typhoon";
            alertMessage = "Atmospheric anomaly. Tower stress critical.";
            successMessage = "Seismic dampeners active. Tower stress normalized.";
            damage = 17;
            StaminaCost = 5;
        }
    }
    //LANDSLIDE
    else if (eventType == "LANDSLIDE") {
        if (level == 1) {
            eventName = "Minor Soil Erosion";
            alertMessage = "Deep fissure expansion detected.";
            successMessage = "Geotech mesh deployed. Soil stabilized.";
            damage = 6;
            StaminaCost = 3;
        }
        else {
            eventName = "Major Landslide";
            alertMessage = "Massive earth displacement tracking.";
            successMessage = "Heavy barricades erected. Earth displacement halted.";
            damage = 12;
            StaminaCost = 5;
        }
    }
    //TOXIC
    else if (eventType == "TOXIC") {
        if (level == 1) {
            eventName = "Suspicious Dumping";
            alertMessage = "Unregistered foreign objects detected.";
            successMessage = "Cleanup drones dispatched. Area sanitized.";
            damage = 5;
            StaminaCost = 2;
        }
        else {
            eventName = "Chemical Leak";
            alertMessage = "Hazardous compound detected.";
            successMessage = "Cleanup drones dispatched. Area sanitized.";
            damage = 10;
            StaminaCost = 4;
        }
    }
    //ANIMAL
    else if (eventType == "ANIMAL") {
        eventName = "Animal Panic";
        alertMessage = "Animal intrusion detected.";
        successMessage = "Drone sirens activated. Herd safely redirected.";
        damage = 2;
        StaminaCost = 2;
    }
    //PLANT
    else if (eventType == "PLANTCON") {
        if (level == 1) {
            eventName = "Spreading Necrosis";
            alertMessage = "Airborne plant virus spreading.";
            successMessage = "Anti-viral sprinklers activated. Pathogen destroyed.";
            damage = 3;
            StaminaCost = 1;
        }
        else {
            eventName = "Sterile Dead Zone";
            alertMessage = "Rapid biomass collapse.";
            successMessage = "Bio-purge initiated. Biomass collapse halted.";
            damage = 6;
            StaminaCost = 4;
        }
    }
    //PEST
    else if (eventType == "PEST") {
        if (level == 1) {
            eventName = "Minor Pest Swarm";
            alertMessage = "High-frequency buzzing anomaly detected.";
            successMessage = "Bio-pesticide released. Swarm dispersed.";
            damage = 3;
            StaminaCost = 2;
        }
        else if (level == 2) {
            eventName = "Locust Plague";
            alertMessage = "Massive swarm blocking thermal satellite view.";
            successMessage = "Drone swarm engaged. High-density pest control successful.";
            damage = 8;
            StaminaCost = 5;
        }
        else {
            eventName = "Apex Swarm Event";
            alertMessage = "Hyper-reproductive insect event.";
            successMessage = "Area-wide fumigation complete. Insectoid threat neutralized.";
            damage = 12;
            StaminaCost = 7;
        }
    }
    //HEATWAVE
    else if (eventType == "HEATWAVE") {
        eventName = "Heatwave";
        alertMessage = "Critical moisture depletion.";
        successMessage = "Underground aquifers rerouted. Moisture levels restored.";
        damage = 7;
        StaminaCost = 3;
    }
    //ACIDRAIN
    else if (eventType == "ACID_RAIN") {
        eventName = "Acid Rainfall";
        alertMessage = "Low pH atmospheric condensation.";
        successMessage = "Alkaline aerosol rockets launched. pH levels neutralized.";
        damage = 9;
        StaminaCost = 3;
    }
}

ActionResult DisasterEvent::Action() {
    ActionResult res = BaseEvent::Action();
    return res;
}

ActionResult DisasterEvent::triggerEffects() {
   ActionResult res;
   level++;// Increase level each day if ignored
   updateStat();
   return res;
}