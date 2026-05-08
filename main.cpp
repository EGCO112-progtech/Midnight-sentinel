#include <iostream>
#include <string>
#include "ForestManager.h"
using namespace std;

enum GameScreen { 
    SCREEN_PLAYING,     // ค่าที่เป็นไปได้ที่ 1: หมายถึงหน้าจอหลัก
    SCREEN_TRANSITION,  // ค่าที่เป็นไปได้ที่ 2: หมายถึงหน้าจอดำๆ คั่นวัน
    SCREEN_MISSION,      // ค่าที่เป็นไปได้ที่ 3: หมายถึงหน้าจอ Popup ภารกิจ
    SCREEN_END
};

void renderUI(const ForestManager& game,string systemMessage);
void handleEventWithStory(const ForestManager& game, const ActionResult& res);
int main() {

    ForestManager game;
    string uiMsg =""; //ข้อความจาก uiMsg จะขึ้นด้านล่าง

    int dailyDmg;
    //========================================
    // 1. Intro Scene (อาจจะมีเนื้อเรื่องหรือคำแนะนำก่อนเริ่มเกม) 
    // ตรงนี้ทำเป็นเนื้อเรื่องแทน 
    // ให้กดคลิก/กด Enter เพื่อเปลี่ยนข้อความ
    //========================================
    cout << "========================================\n";
    cout << "    WELCOME TO FOREST RANGER    \n";
    cout << "========================================\n";
    cout << "         How to play? for dev\n";
    cout << "1. enter event number from list\n";
    cout << "2. press 1 to confirm action or else to cancle\n";
    cout << "3. enjoy kub\n";
    cout << "\n[ press Enter ... ]\n";
            
            cin.clear();
            while (cin.peek() != '\n' && cin.peek() != EOF) {
                cin.ignore();
            }
            string dummy;
            getline(cin, dummy);



    GameScreen currentScreen = SCREEN_PLAYING;
    MissionEvent* activeMission = nullptr;

    // 2. Game Loop หลัก (รันไปเรื่อยๆ จนกว่า HP ป่าจะหมด)
    while (!game.isGameOver()) {

        //cout << "[DEBUG 3] Go to DailyEvents..." << endl;
        game.DailyEvents(); // random daily events and add to list   
        //cout << "[DEBUG 4] Complete DailyEvents!" << endl;
        
        bool endDay = false;
        
    // 3. Action Loop
        while (!endDay && !game.isGameOver()) {
            if(game.getSystemMessage() != "") {
                uiMsg = game.getSystemMessage();
                game.setSystemMessage("");
            }
            
            //=============================================
            //  MAIN SCENE 
            //  หน้าจอคอมพิวเตอร์เอาไว้จัดการ task เล่น minigame
            //  (ฟังก์ชันแยกอยู่ renderUI ด้านล่าง) 
            //=============================================
            if(currentScreen == SCREEN_PLAYING){
                //Show UI
                renderUI(game,uiMsg);
                uiMsg = "";

                //=============================================
                // Main Choices
                // ให้กดที่ลิตส์เลย
                // + เลือกลิตส์แล้วกดปุ่ม confirm เพื่อ action
                //=============================================
                
            //4.Player input
                int mainChoice;
                if (!(cin>>mainChoice)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    uiMsg = "Invalid input";
                    continue;
                }
                int confirmChoice;
                int count = game.getEventCount();
                
                //5.Process input
                if (mainChoice >= 1 && mainChoice <= count) {
                    cout << "Confirm action press 1: ";
                    if (!(cin >> confirmChoice)) { 
                        cin.clear(); 
                        cin.ignore(10000, '\n'); 
                        continue; 
                    }
                    if(confirmChoice == 1){
                        int eventIndex = mainChoice - 1;
                        BaseEvent* targetEvent = game.getEvent(eventIndex);

                            // เช็คประเภทว่าเป็น Mission หรือ Disaster
                            //=============================================
                            //              MISSION EVENT
                            //  เปลี่ยนฉากรอบที่ 1 ออกไปเดินในป่า มีเนื้อเรื่องประมาณนึง
                            //  เปลี่ยนฉากรอบที่ 2 เป็นการเจอ Mission ที่ต้องเลือก choice
                            //=============================================
                            
                        if (targetEvent->getType() == "Mission") {
                            cin.ignore(10000, '\n');
                            // change to MissionEvent
                            activeMission = static_cast<MissionEvent*>(targetEvent);
                            currentScreen = SCREEN_MISSION;   
                        } 
                        else {
                            //=============================================
                            //  DISASTER EVENT
                            //  ทำเมื่อกดทำจะมี minigame ของแต่ละ event
                            //=============================================
                            // ถ้าเป็น DisasterEvent ธรรมดา กดทำแล้วลบสตามินา เอาevent ออกไปจาก list
                            game.handleEvent(targetEvent);
                        }
                    }
                    else {
                        uiMsg = "Cancel";
                    }
                }
                else if (mainChoice >= 11 && mainChoice <= 13) {
                    cout << "Confirm action press 1: ";
                     if (!(cin >> confirmChoice)) { 
                        cin.clear(); 
                        cin.ignore(10000, '\n'); 
                        continue; 
                    }
                    if(confirmChoice == 1){
                        int projIdx = mainChoice - 11;
                        Project* p = game.getProject(projIdx);
                        if (p != nullptr) {
                            if (game.getCurrentStamina() >= p->getStaminaCost()) { 
                                game.handleProject(p);
                            } 
                            else {
                                uiMsg = "Not enough stamina to work on project!";
                            }
                        } 
                        else {
                            uiMsg = "Invalid Project or already completed!";
                        }
                    }
                }
                else if (mainChoice == 0) {
                    endDay = true;
                    uiMsg = "";
                    currentScreen = SCREEN_TRANSITION;
                }
                else {
                    uiMsg = "Cancel";
                }
            }

            if(currentScreen == SCREEN_MISSION){
                ActionResult Story = activeMission->getStory();     
                //เนื้อเรื่อง 
                handleEventWithStory(game,Story);
                int choice;
                    
                cout << "\n--- Mission: " << activeMission->getName() << " ---" << endl;
                    
                cout << "\n What would you do?" << endl;
                cout << "1. " << activeMission->getChoice(1) << endl;
                cout << "2. " << activeMission->getChoice(2) << endl;    
                cout << "3. " << activeMission->getChoice(3) << endl;
                cout << ">> Choose (1-3): "; // 0 to go back อาจจะทำปุ่มให้คลิกย้อนกลับ

                cin >> choice;
                while(choice < 1 || choice > 3) {
                        cout << "\nInvalid choice. Try again: ";
                        cin >> choice;
                }
                if(game.getCurrentStamina() < activeMission->getChoicecost(choice)){
                    cout << "\nNot enough stamina.";
                    cin >> choice;
                }
                else{
                    game.handleMission(activeMission, choice);
                }
                currentScreen = SCREEN_PLAYING;
            }

            if (currentScreen == SCREEN_TRANSITION)
            {
                // 1. ล้างหน้าจอ UI การเล่นทิ้งให้หมด
                system("cls");
                game.processEndOfDay(); // ฟังก์ชันนี้จะไปเรียก endDay() ของ list และหักเลือดป่า
                // 2. วาดหน้าจอสรุปผล
                cout << "\n\n\n";
                cout << "   ====================================================\n";
                cout << "                  SHIFT REPORT : NIGHT " << game.getCurrentDay()<< " \n"; 
                cout << "   ====================================================\n";
                cout << "                 Active Threats Tonight: " << game.getDailyDamage() << "\n";
                cout << game.getDailySummary();
                cout << "   ----------------------------------------------------\n";
                cout << "                 Total Damage     : " << game.getDailyDamage() << "\n";
                cout << "                 Passive Recovery : " << game.getLastDayRecovery() << "\n";
                cout << "                 Forest HP Left   : " << game.getForestHP() << "\n";
                cout << "   ====================================================\n\n";
                
                cout << "                   [ Press Enter ... ]";
                cin.ignore(10000, '\n'); 
                cin.get();
                
                dailyDmg = game.getDailyDamage();//ส่งไปหน้าจบเกม
                game.nextDay();
                if (!game.isGameOver()) {
                    currentScreen = SCREEN_PLAYING;
                    continue;
                }
                else {
                    currentScreen = SCREEN_END;
                    break;
                }
            }
        } // จบ Action Loop       
    } // ถ้ายังไม่ game over วนต่อ

    //=============================================
    // 5. Game Over
    //  ตัดไปหน้า game over
    //=============================================
    if(currentScreen == SCREEN_END){
        system("cls");
        if(game.getCurrentDay()<=7){
            cout << "   ====================================================" << endl;
            cout << "                     GAME OVER at Night " << game.getCurrentDay()-1 << endl;
            //cout << "                 Total Damage     : " << dailyDmg << "\n";
            //cout << "                 Forest HP Left   : " << game.getForestHP() << "\n";
            cout << "   ====================================================\n" << endl;
        }
        else{
            cout << "   ====================================================" << endl;
            cout << "                          VICTORY                        " << endl;
            //cout << "                 Total Damage     : " << dailyDmg << "\n";
            cout << "                 Forest HP Left   : " << game.getForestHP() << endl;
            cout << "   ====================================================" << endl;
        }
        
        return 0;
    }
}

void renderUI(const ForestManager& game,string systemMessage){
    system("cls");
    int count = game.getEventCount();
    
    cout << "\n========================================" << endl;
    cout << "Day: " << game.getCurrentDay() << " | HP : " << game.getForestHP() << " | Stamina: " << game.getCurrentStamina() << endl;
    cout << "========================================" << endl;
    
    //--- EVENTS ---
    cout << "[ Alert List ]" << endl;
    for (int i = 0; i < count; i++) {
        BaseEvent* ev = game.getEvent(i);
        cout << i+1 << ". " << ev->getAlertMessage() << " [" << ev->getStaminaCost() <<"]"<< endl;
    }    
    // --- PROJECTS ---
    cout << "\n [  AVAILABLE PROJECTS ] " << endl;
    for (int i = 0; i < 3; i++) {
        Project* p = game.getProject(i);
        cout << " " << i+11 << ". " << p->getName(); 
        
        if (p != nullptr) {
            if(p->getProgress() < p->getMaxProgress()){
                cout << " [" << p->getProgress() << "/" << p->getMaxProgress() << "]" << endl; 
            } 
            else {
                cout << "[Completed]" << endl;
            }
        }
    }
    
    if(systemMessage != "") {
        cout << "\n>> " << systemMessage << endl;
    }

    cout << "\n>>Enter Action: ";
}

void handleEventWithStory(const ForestManager& game, const ActionResult& res) {
    int i;
        for (i = 0; i < res.storySize; i++) {
            system("cls");
            if( i == res.storySize-1 && res.targetScene!=""){
                //เปลี่ยนฉาก ตาม targetScene
                cout<<"\n [ SYSTEM: change scene -> "<<res.targetScene<<endl;
            }
            cout << res.storyBeats[i]; 
            cout << "\n[ press Enter ... ]\n";
            
            cin.clear();
            while (cin.peek() != '\n' && cin.peek() != EOF) {
                cin.ignore();
            }
            string dummy;
            getline(cin, dummy); 
        }
}