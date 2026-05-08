#include "BaseEvent.h"

//======BaseEvent=========
ActionResult BaseEvent::Action() {
    ActionResult res;
    res.staminaChange = -StaminaCost;
    res.message = successMessage;
    res.isProjectFinished = false;
    return res;
}

