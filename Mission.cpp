#include "BaseEvent.h"
#include <cstdlib>
#include <ctime>

MissionEvent::MissionEvent(std::string type,int life){
    this->missionType = type;
    this->eventName = "Mission: " + eventName;
    this->lifespan = 1;
    this->StaminaCost = 0; // ค่าเริ่มต้นของภารกิจคือไม่เสียสตามินา
    updateStat();
}

void MissionEvent::updateStat(){
    if(missionType == "FAKE"){
        int random = rand() % 8;
        switch(random) {
            case 0:
                eventName = "Passing Wildlife Noise";
                alertMessage = "Movement detected in nearby bushes.";
                storyText1 = "You hear rustling in the bushes...\n";
                storyText2 = "Something runs past you quickly...\n";
                storyText3 = "It disappears into the forest...\n";
                choice1Text = "[ Log as 'False Alarm' ]";
                choice2Text = "[ Calibrate Motion Sensors ]";
                choice3Text = "[ Dismiss Alert ]";
                successText1 = "Event logged as False Alarm. Motion cache cleared.";
                successText2 = "Sensors recalibrating... Done. Sensitivity adjusted.";
                successText3 = "Alert dismissed. Returning to standard surveillance.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 1; cost2 = 1; cost3 = 1;
                break;
            case 1:
                eventName = "Passing Wildlife Noise";
                alertMessage = "Rustling sound reported.";
                storyText1 = "Leaves crunch under unseen movement...\n";
                storyText2 = "A shadow darts between trees...\n";
                storyText3 = "It fades into the distance...\n";
                choice1Text = "[ Mute Proximity Alert ]";
                choice2Text = "[ Mark as 'Harmless Fauna' ]";
                choice3Text = "[ Clear Terminal Screen ]";
                successText1 = "Proximity alert muted. Audio sensors placed on standby.";
                successText2 = "Database updated. Subject classified as harmless fauna.";
                successText3 = "Terminal cleared. Visual feed restored.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 1; cost2 = 1; cost3 = 1;
                break;
            case 2:
                eventName = "Equipment Maintenance";
                alertMessage = "Minor equipment issue detected.";
                storyText1 = "Your equipment shows minor irregularities...\n";
                storyText2 = "It still functions normally...\n";
                storyText3 = "A quick check might help...\n";
                choice1Text = "[ Run Quick Diagnostic ]";
                choice2Text = "[ Ignore & Continue ]";
                choice3Text = "[ Snooze Warning (24H) ]";
                successText1 = "Diagnostic complete. No critical hardware failures detected.";
                successText2 = "Warning bypassed. Hardware status monitored in background.";
                successText3 = "Notification snoozed. Reminder set for 24 hours.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 1; cost2 = 1; cost3 = 1;
                break;
            case 3:
                eventName = "Equipment Maintenance";
                alertMessage = "Routine maintenance is due.";
                storyText1 = "A system reminder appears...\n";
                storyText2 = "Routine maintenance is due...\n";
                storyText3 = "No immediate issues detected...\n";
                choice1Text = "[ Mark as 'Completed' ]";
                choice2Text = "[ Bypass Protocol ]";
                choice3Text = "[ Clear Notification ]";
                successText1 = "Maintenance log updated. Next routine check scheduled.";
                successText2 = "Protocol bypassed. Admin override recorded.";
                successText3 = "Notification dismissed from dashboard.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 1; cost2 = 1; cost3 = 1;
                break;
            case 4:
                eventName = "Radio Interference";
                alertMessage = "Radio interference detected.";
                storyText1 = "Your radio fills with static...\n";
                storyText2 = "The signal fluctuates briefly...\n";
                storyText3 = "It stabilizes on its own...\n";
                choice1Text = "[ Auto-Tune Frequency ]";
                choice2Text = "[ Switch to Backup Channel ]";
                choice3Text = "[ Clear Static Cache ]";
                successText1 = "Auto-tuning... Frequency locked. Signal stabilized.";
                successText2 = "Rerouting communication to Backup Channel Alpha.";
                successText3 = "Cache purged. Receiver latency improved.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 1; cost2 = 1; cost3 = 1;
                break;
            case 5:
                eventName = "Radio Interference";
                alertMessage = "Radio interference detected.";
                storyText1 = "A short burst interrupts your communication...\n";
                storyText2 = "You adjust the channel...\n";
                storyText3 = "The issue resolves itself...\n";
                choice1Text = "[ Reboot Comms Array ]";
                choice2Text = "[ Ignore Static Anomaly ]";
                choice3Text = "[ Log Network Error ]";
                successText1 = "Comms array rebooting... Online. Signal strength 100%.";
                successText2 = "Anomaly ignored. Continuing passive transmission monitoring.";
                successText3 = "Error code 404-RF logged to server maintenance queue.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 1; cost2 = 1; cost3 = 1;
                break;
            case 6:
                eventName = "Falling Tree Sound";
                alertMessage = "Distant acoustic anomaly detected.";
                storyText1 = "A loud crack echoes through the forest...\n";
                storyText2 = "A tree collapses somewhere far away...\n";
                storyText3 = "The sound fades quickly...\n";
                choice1Text = "[ Log as 'Natural Decay' ]";
                choice2Text = "[ Dismiss Audio Alert ]";
                choice3Text = "[ Recalibrate Microphones ]";
                successText1 = "Acoustic signature matched with natural decay. Logged.";
                successText2 = "Audio alert dismissed. Acoustic sensors reset.";
                successText3 = "Microphones recalibrated. Wind noise filter applied.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 1; cost2 = 1; cost3 = 1;
                break;
            case 7:
                eventName = "Falling Tree Sound";
                alertMessage = "Minor ground vibration recorded.";
                storyText1 = "You hear wood splinter in the distance...\n";
                storyText2 = "The ground trembles slightly...\n";
                storyText3 = "It's just natural forest activity...\n";
                choice1Text = "[ Ignore Tremor Data ]";
                choice2Text = "[ Mark as 'Safe Zone' ]";
                choice3Text = "[ Clear Sensor Logs ]";
                successText1 = "Tremor data archived. No structural threat detected.";
                successText2 = "Coordinates marked as safe. Geological activity normal.";
                successText3 = "Seismic logs cleared. Ready for next input.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 1; cost2 = 1; cost3 = 1;
                break;
            default:
                break;
        }
    }
   //Real event
   else if(missionType == "REAL"){
        int random = rand() % 20;
        switch(random){
            //Mission 1: Illegal Logging
            case 0:
                eventName = "Illegal Logging Detected";
                alertMessage = "Cutting sounds detected nearby";
                storyText1 = "You hear the distant roar of a chainsaw...\n";
                storyText2 = "You move closer and see trees being cut down rapidly...\n";
                storyText3 = "The loggers haven't noticed you yet...\n";
                choice1Text = "Observe and report their location";
                choice2Text = "Rush in and confront the loggers";
                choice3Text = "Do nothing";
                successText1 = "Coordinates logged and transmitted to local authorities.";
                successText2 = "Confrontation recorded. Loggers dispersed from the sector.";
                successText3 = "Alert dismissed. Unauthorized logging activity continuing.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 1:
                eventName = "Illegal Logging Detected";
                alertMessage = "Suspicious transport activity spotted";
                storyText1 = "Fresh logs are stacked near a hidden trail...\n";
                storyText2 = "You follow it and find a truck being loaded...\n";
                storyText3 = "Someone is guarding the area...\n";
                choice1Text = "Disable their tools quietly";
                choice2Text = "Sabotage the truck directly";
                choice3Text = "Do nothing";
                successText1 = "Equipment sabotaged. Transport delayed indefinitely.";
                successText2 = "Vehicle disabled. Logging transport operation halted.";
                successText3 = "Alert dismissed. Suspect vehicle departed the area.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
                //Mission 2: Wildlife Trafficking
            case 2:
                eventName = "Wildlife Trafficking";
                alertMessage = "Animal distress sounds reported";
                storyText1 = "You find a steel trap stained with fresh blood...\n";
                storyText2 = "A wounded animal cries somewhere ahead...\n";
                storyText3 = "A hunter waits nearby in silence...\n";
                choice1Text = "Free the trapped animal quietly";
                choice2Text = "Confront the poacher directly";
                choice3Text = "Do nothing";
                successText1 = "Trap disarmed. Local fauna successfully released.";
                successText2 = "Poacher apprehended. Area secured.";
                successText3 = "Alert dismissed. Biological signature fading.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 3:
                eventName = "Wildlife Trafficking";
                alertMessage = "Unusual camp activity detected";
                storyText1 = "A carcass lies abandoned on the ground...\n";
                storyText2 = "Tracks lead you to a dimly lit camp...\n";
                storyText3 = "Someone is preparing the animal for transport...\n";
                choice1Text = "Follow and mark their camp location";
                choice2Text = "Destroy traps and chase them off";
                choice3Text = "Do nothing";
                successText1 = "Camp coordinates marked. Surveillance drone deployed.";
                successText2 = "Encampment destroyed. Hostiles fleeing the sector.";
                successText3 = "Alert dismissed. Suspects proceeding with extraction.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
                //Mission 3: Illegal Drug Activity
            case 4:
                eventName = "Illegal Drug Activity Detected";
                alertMessage = "Suspicious group movement detected";
                storyText1 = "Your radio picks up a strange coded transmission...\n";
                storyText2 = "You spot a group moving crates through the trees...\n";
                storyText3 = "They seem alert to their surroundings...\n";
                choice1Text = "Track their route silently";
                choice2Text = "Intercept and stop them directly";
                choice3Text = "Do nothing";
                successText1 = "Tracking beacon attached. Route data uploading to database.";
                successText2 = "Intercept successful. Contraband secured.";
                successText3 = "Alert dismissed. Signal lost.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 5:
                eventName = "Illegal Drug Activity Detected";
                alertMessage = "Frequent activity on hidden trail";
                storyText1 = "A narrow trail shows heavy recent use...\n";
                storyText2 = "Footsteps echo nearby, more than one person...\n";
                storyText3 = "You might already be too close...\n";
                choice1Text = "Mark the path for later investigation";
                choice2Text = "Ambush the group directly";
                choice3Text = "Do nothing";
                successText1 = "Trailway mapped and flagged for tactical team.";
                successText2 = "Ambush protocol executed. Threat neutralized.";
                successText3 = "Alert dismissed. Footstep audio signature fading.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            //Mission 4: Illegal Mining
            case 6:
                eventName = "Illegal Mining";
                alertMessage = "Ground disturbance detected";
                storyText1 = "The ground trembles slightly beneath your feet...\n";
                storyText2 = "You discover a hidden excavation site...\n";
                storyText3 = "Machinery hums loudly from below...\n";
                choice1Text = "Observe and document the operation";
                choice2Text = "Shut down the mining activity";
                choice3Text = "Do nothing";
                successText1 = "Photographic evidence compiled and archived.";
                successText2 = "Power generators disabled. Excavation halted.";
                successText3 = "Alert dismissed. Seismic vibrations continuing.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;    
            case 7:
                eventName = "Illegal Mining";
                alertMessage = "Water contamination source suspected";
                storyText1 = "The river water is murky and unnatural...\n";
                storyText2 = "You discover a makeshift mining site...\n";
                storyText3 = "Workers and guards occupy the site...\n";
                choice1Text = "Disrupt their equipment quietly";
                choice2Text = "Confront the workers directly";
                choice3Text = "Do nothing";
                successText1 = "Water pumps jammed. Contamination rate slowing.";
                successText2 = "Site cleared. Mining equipment confiscated.";
                successText3 = "Alert dismissed. Water contamination levels rising.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            //Mission 5: Illegal Industrial Dumping
            case 8:
                eventName = "Illegal Industrial Dumping";
                alertMessage = "Possible chemical leak detected";
                storyText1 = "A foul smell lingers in the air...\n";
                storyText2 = "You discover leaking barrels in the soil...\n";
                storyText3 = "The contamination is spreading...\n";
                choice1Text = "Record evidence and report it";
                choice2Text = "Stop the dumping immediately";
                choice3Text = "Do nothing";
                successText1 = "Chemical signatures recorded and reported to EPA.";
                successText2 = "Containers sealed. Bio-hazard containment initiated.";
                successText3 = "Alert dismissed. Toxicity levels increasing in soil.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 9:
                eventName = "Illegal Industrial Dumping";
                alertMessage = "Vehicle spotted near water source";
                storyText1 = "A truck is parked near a riverbank...\n";
                storyText2 = "Liquid waste is being discharged into the water...\n";
                storyText3 = "The driver hasn't noticed you yet...\n";
                choice1Text = "Contain the spill as best as possible";
                choice2Text = "Confront the driver directly";
                choice3Text = "Do nothing";
                successText1 = "Absorbent barriers deployed. Spill radius contained.";
                successText2 = "Driver detained. Discharge valve shut off.";
                successText3 = "Alert dismissed. Contaminants entering water supply.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
                //Mission 6: Illegal Rare Plant Harvesting
            case 10:
                eventName = "Illegal Rare Plant Harvesting";
                alertMessage = "Protected vegetation disturbance detected";
                storyText1 = "A once dense patch of plants is now stripped bare...\n";
                storyText2 = "You hear quiet voices nearby...\n";
                storyText3 = "Collectors are storing rare plants...\n";
                choice1Text = "Monitor and record the activity";
                choice2Text = "Stop the collectors immediately";
                choice3Text = "Do nothing";
                successText1 = "Collector profiles logged. Species inventory updated.";
                successText2 = "Harvesting interrupted. Flora assets recovered.";
                successText3 = "Alert dismissed. Bio-diversity declining.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 11:
                eventName = "Illegal Rare Plant Harvesting";
                alertMessage = "Soil disruption in restricted zone";
                storyText1 = "You notice disturbed soil across a protected zone...\n";
                storyText2 = "Someone is carefully digging up roots...\n";
                storyText3 = "They haven't seen you yet...\n";
                choice1Text = "Confiscate harvested plants quietly";
                choice2Text = "Drive them out of the area";
                choice3Text = "Do nothing";
                successText1 = "Flora confiscated and prepped for replanting.";
                successText2 = "Intruders expelled. Protected zone secured.";
                successText3 = "Alert dismissed. Soil disturbance continuing.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
                //Mission 7: Forest Encroachment
            case 12:
                eventName = "Forest Encroachment";
                alertMessage = "Unauthorized land clearing detected";
                storyText1 = "You find newly cleared land deep in the forest...\n";
                storyText2 = "Temporary shelters have been set up...\n";
                storyText3 = "People are expanding into protected land...\n";
                choice1Text = "Warn and document the settlers";
                choice2Text = "Force them to leave immediately";
                choice3Text = "Do nothing";
                successText1 = "Eviction notice issued. Area mapped for monitoring.";
                successText2 = "Encroachers removed. Temporary structures dismantled.";
                successText3 = "Alert dismissed. Deforestation expanding.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 13:
                eventName = "Forest Encroachment";
                alertMessage = "Human settlement signs found";
                storyText1 = "You spot farmland where forest should be...\n";
                storyText2 = "Smoke rises from a nearby fire...\n";
                storyText3 = "The area is being permanently altered...\n";
                choice1Text = "Destroy temporary structures";
                choice2Text = "Confront the group aggressively";
                choice3Text = "Do nothing";
                successText1 = "Unauthorized structures demolished. Land marked for rehab.";
                successText2 = "Group dispersed. Agricultural conversion halted.";
                successText3 = "Alert dismissed. Land permanently altered.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
                //Mission 8: Illegal Slash-and-Burn Agriculture
            case 14:
                eventName = "Slash-and-Burn Activity";
                alertMessage = "Smoke detected within forest area";
                storyText1 = "You smell smoke in the air...\n";
                storyText2 = "Small controlled fires are spreading...\n";
                storyText3 = "The flames are starting to grow...\n";
                choice1Text = "Contain the fire edges";
                choice2Text = "Extinguish the fire completely";
                choice3Text = "Do nothing";
                successText1 = "Firebreak established. Spread velocity reduced to zero.";
                successText2 = "Suppressants deployed. Ignition sources neutralized.";
                successText3 = "Alert dismissed. Thermal anomalies expanding.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 15:
                eventName = "Slash-and-Burn Activity";
                alertMessage = "Burned ground spreading detected";
                storyText1 = "Charred ground stretches across the forest floor...\n";
                storyText2 = "Fire is being used to clear land...\n";
                storyText3 = "It may get out of control soon...\n";
                choice1Text = "Monitor the spread carefully";
                choice2Text = "Chase off those responsible";
                choice3Text = "Do nothing";
                successText1 = "Thermal mapping active. Spread vectors calculated.";
                successText2 = "Arsonists expelled. Firefighting drones dispatched.";
                successText3 = "Alert dismissed. Canopy threat level critical.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
                //Mission 9: Illegal Hunting
            case 16:
                eventName = "Illegal Hunting Camp";
                alertMessage = "Suspicious campsite located";
                storyText1 = "You discover a hidden campsite...\n";
                storyText2 = "Weapons and traps are scattered around...\n";
                storyText3 = "The hunters may return soon...\n";
                choice1Text = "Scout and gather information";
                choice2Text = "Raid the camp directly";
                choice3Text = "Do nothing";
                successText1 = "Intel gathered. Weapon types and quantities logged.";
                successText2 = "Raid successful. Weapons and traps confiscated.";
                successText3 = "Alert dismissed. Poaching activity undetected.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 17:
                eventName = "Illegal Hunting Camp";
                alertMessage = "Active fire spotted in restricted zone";
                storyText1 = "Smoke rises from a distant campfire...\n";
                storyText2 = "You see silhouettes moving around...\n";
                storyText3 = "This is an active hunting group...\n";
                choice1Text = "Disable traps quietly";
                choice2Text = "Ambush the hunters";
                choice3Text = "Do nothing";
                successText1 = "Local traps disarmed. Wildlife safe corridors established.";
                successText2 = "Ambush executed. Hostiles neutralized and detained.";
                successText3 = "Alert dismissed. Gunshots detected in the distance.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
                //Mission 10: Illegal Industrial Dumping
            case 18:
                eventName = "Oil Spill in Forest Area";
                alertMessage = "Possible fuel contamination detected";
                storyText1 = "A dark liquid spreads across the ground...\n";
                storyText2 = "The smell of fuel fills the air...\n";
                storyText3 = "Wildlife nearby is already affected...\n";
                choice1Text = "Contain the spill partially";
                choice2Text = "Stop the source immediately";
                choice3Text = "Do nothing";
                successText1 = "Containment booms deployed. Environmental damage mitigated.";
                successText2 = "Leak plugged. Cleanup protocols initiated.";
                successText3 = "Alert dismissed. Ecological toxicity rising.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 19:
                eventName = "Oil Spill in Forest Area";
                alertMessage = "Damaged vehicle leaking substance";
                storyText1 = "You find a damaged transport vehicle...\n";
                storyText2 = "Oil is leaking into the soil...\n";
                storyText3 = "The spill is getting worse...\n";
                choice1Text = "Mark and isolate the area";
                choice2Text = "Force shutdown of the operation";
                choice3Text = "Do nothing";
                successText1 = "Hazard zone established. Automated alerts sent to cleanup crews.";
                successText2 = "Vehicle systems overridden. Leak effectively stopped.";
                successText3 = "Alert dismissed. Fluid levels reaching critical saturation.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            default:
                break; 
            }
        }
        //Suspecious event
    else if(missionType == "SUS"){
        int random = rand() % 10;
        switch(random){
            //Mission 1: Mysterious Lights
            case 0:
                eventName = "Mysterious Lights in Forest";
                alertMessage = "Distant light briefly observed";
                storyText1 = "You spot a distant light through the forest...\n";
                storyText2 = "It moves for a moment...\n";
                storyText3 = "Then disappears behind the trees...\n";
                choice1Text = "[ Log as Light Anomaly ]";
                choice2Text = "[ Dismiss Visual Alert ]";
                choice3Text = "[ Clear Camera Feed ]";
                successText1 = "Logged as natural light reflection. No threat detected.";
                successText2 = "Visual alert dismissed. Returning to standard view.";
                successText3 = "Camera feed cleared and refreshed.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 0; cost2 = 0; cost3 = 0;
                break;
            case 1:
                eventName = "Mysterious Lights in Forest";
                alertMessage = "Moving light detected in forest";
                storyText1 = "A faint light flickers between the trees...\n";
                storyText2 = "It moves quickly, like someone running with a flashlight...\n";
                storyText3 = "The light suddenly turns in your direction...\n";
                choice1Text = "Observe from a distance and stay hidden";
                choice2Text = "Approach the person directly";
                choice3Text = "Do nothing";
                successText1 = "Surveillance mode active. Target tracking initiated.";
                successText2 = "Intercept protocol engaged. Closing distance.";
                successText3 = "Alert dismissed. Target lost in the tree line.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
                //Mission 2: Distant Machinery Noise
            case 2:
                eventName = "Distant Machinery Noise";
                alertMessage = "Active mechanical sound detected";
                storyText1 = "A low mechanical sound echoes nearby...\n";
                storyText2 = "It grows louder as if something is operating close...\n";
                storyText3 = "You hear metal hitting metal just ahead...\n";
                choice1Text = "Move carefully toward the sound";
                choice2Text = "Head straight in quickly";
                choice3Text = "Do nothing";
                successText1 = "Acoustic sensors triangulating coordinates stealthily.";
                successText2 = "Direct scan initiated. Machinery location pinpointed.";
                successText3 = "Alert dismissed. Mechanical noise fading.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 3:
                eventName = "Faint mechanical noise reported";
                alertMessage = "Active mechanical sound detected";
                storyText1 = "You hear faint mechanical noise in the distance...\n";
                storyText2 = "It gradually fades away...\n";
                storyText3 = "Nothing unusual remains...\n";
                choice1Text = "[ Log as Ambient Noise ]";
                choice2Text = "[ Mute Audio Channel ]";
                choice3Text = "[ Clear Audio Buffer ]";
                successText1 = "Sound classified as ambient. Database updated.";
                successText2 = "Audio channel muted. Filtering background noise.";
                successText3 = "Audio buffer cleared. Ready for new inputs.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 0; cost2 = 0; cost3 = 0;
                break;
                //Mission 3: Strange Radio Signal
            case 4:
                eventName = "Strange Radio Signal";
                alertMessage = "Unusual radio transmission detected";
                storyText1 = "Your radio picks up a broken transmission...\n";
                storyText2 = "A voice comes through briefly, speaking in a hurry...\n";
                storyText3 = "It sounds like someone trying to avoid being heard...\n";
                choice1Text = "Listen and try to understand the message";
                choice2Text = "Respond and reveal your position";
                choice3Text = "Do nothing";
                successText1 = "Audio enhancing... Decrypting transmission data.";
                successText2 = "Comms channel opened. Position broadcasted.";
                successText3 = "Alert dismissed. Transmission ignored.";
                damage1 = 3; damage2 = 2; damage3 = 0;
                cost1 = 2; cost2 = 1; cost3 = 0;
                break;
            case 5:
                eventName = "Strange Radio Signal";
                alertMessage = "Brief signal interference detected";
                storyText1 = "Static fills your radio for a moment...\n";
                storyText2 = "It clears up quickly...\n";
                storyText3 = "The signal returns to normal...\n";
                choice1Text = "[ Auto-Correct Signal ]";
                choice2Text = "[ Ignore Static ]";
                choice3Text = "[ Reset Receiver ]";
                successText1 = "Signal corrected. Interference filtered.";
                successText2 = "Static ignored. Monitoring continues.";
                successText3 = "Receiver reset. Frequency locked.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 0; cost2 = 0; cost3 = 0;
                break;
                //Mission 4: Multiple Human Footprints
            case 6:
                eventName = "Multiple Human Footprints";
                alertMessage = "Multiple footprints found in area";
                storyText1 = "You find several fresh footprints on the ground...\n";
                storyText2 = "They lead deeper into a restricted area...\n";
                storyText3 = "You hear faint movement not far ahead...\n";
                choice1Text = "Follow the tracks cautiously";
                choice2Text = "Move quickly to catch up";
                choice3Text = "Do nothing";
                successText1 = "Tracking mode engaged. Analyzing footprint trajectory.";
                successText2 = "Speed pursuit authorized. Closing distance to targets.";
                successText3 = "Alert dismissed. Tracks abandoned.";
                damage1 = 5; damage2 = 3; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 7:
                eventName = "Multiple Human Footprints";
                alertMessage = "Scattered tracks detected nearby";
                storyText1 = "You notice a few footprints crossing the path...\n";
                storyText2 = "They seem to be heading away...\n";
                storyText3 = "The area is quiet again...\n";
                choice1Text = "[ Log as Old Tracks ]";
                choice2Text = "[ Mark Area Safe ]";
                choice3Text = "[ Dismiss Ground Alert ]";
                successText1 = "Tracks logged as outdated. No immediate threat.";
                successText2 = "Area scanned and marked as safe zone.";
                successText3 = "Ground alert dismissed. Sensors recalibrated.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 0; cost2 = 0; cost3 = 0;
                break;
                //Mission 5: Unseen Movement
            case 8:
                eventName = "Unseen Movement";
                alertMessage = "Movement detected between trees";
                storyText1 = "You notice movement between the trees...\n";
                storyText2 = "A figure quickly passes out of sight...\n";
                storyText3 = "It seems like someone trying to avoid you...\n";
                choice1Text = "Stay still and observe carefully";
                choice2Text = "Move in quickly to investigate";
                choice3Text = "Do nothing";
                successText1 = "Motion sensors focused. Scanning for thermal signatures.";
                successText2 = "Investigation team rerouted to last known movement vector.";
                successText3 = "Alert dismissed. Unseen entity departed.";
                damage1 = 4; damage2 = 2; damage3 = 0;
                cost1 = 3; cost2 = 2; cost3 = 0;
                break;
            case 9:
                eventName = "Unseen Movement";
                alertMessage = "Possible visual disturbance reported";
                storyText1 = "You think you saw something move...\n";
                storyText2 = "But after looking again, there's nothing there...\n";
                storyText3 = "It was likely just your imagination...\n";
                choice1Text = "[ Log as Sensor Glitch ]";
                choice2Text = "[ Recalibrate Optics ]";
                choice3Text = "[ Dismiss Notification ]";
                successText1 = "Movement logged as optical illusion/glitch.";
                successText2 = "Optical sensors recalibrated. Visibility clear.";
                successText3 = "Notification dismissed. Resuming patrol sequence.";
                damage1 = 0; damage2 = 0; damage3 = 0;
                cost1 = 0; cost2 = 0; cost3 = 0;
                break;
            default:
                break;
            }
        }
        lifespan = 1;

    }
    
ActionResult MissionEvent::Action() {
    ActionResult res = BaseEvent::Action();
    return res;
}
ActionResult MissionEvent::triggerEffects() {
    ActionResult res;
    return res;
}

ActionResult MissionEvent::getStory(){
   ActionResult res;
    res.storySize = 3;
    res.storyBeats[0] = storyText1;
    res.storyBeats[1] = storyText2;
    res.storyBeats[2] = storyText3;

    res.targetScene = scene;
    res.message = "";
    res.staminaChange = 0;

    return res;
}

std::string MissionEvent::getChoice(int choiceIndex){
    if(choiceIndex == 1) return choice1Text;
    else if(choiceIndex == 2) return choice2Text;
    else if(choiceIndex == 3) return choice3Text;
    else return "";
}

int MissionEvent::getChoicecost(int choiceIndex) {
    if(choiceIndex == 1) return cost1;
    else if(choiceIndex == 2) return cost2;
    else if(choiceIndex == 3) return cost3;
    else return 0;
}

// ตัวอย่างการคำนวณผลลัพธ์
ActionResult MissionEvent::executeChoice(int choiceIndex) {
    ActionResult res;
    
    if (choiceIndex == 1) {
        res.message = successText1 + " (Stamina consumed: " + std::to_string(getChoicecost(1)) + " | Damage: " + std::to_string(damage1) + ")";
        res.staminaChange = -cost1;
        res.hpChange = -damage1;
    } 
    else if (choiceIndex == 2) {
        res.message = successText2 + " (Stamina consumed: " + std::to_string(getChoicecost(2)) + " | Damage: " + std::to_string(damage2) + ")";
        res.staminaChange = -cost2;
        res.hpChange = -damage2;
    }
    
    else if (choiceIndex == 3) {
        res.message = successText3 + " (Stamina consumed: " + std::to_string(getChoicecost(3)) + " | Damage: " + std::to_string(damage3) + ")";
        res.staminaChange = -cost3;
        res.hpChange = -damage3;
    }
    
    return res;
}