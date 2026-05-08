#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include "button.hpp"
#include "text_manager.hpp"
#include "../project-comtech-main/ForestManager.h"

enum GameState { MENU, HOW_TO_PLAY, CHARACTER, CHARACTER_JE, CHARACTER_ME, STORY_BEGIN, STORY_JE, STORY_ME, PLAYING, DAY, HORROR_INTRO, HORROR, END_DAY, VICTORY, STORYJE_END, STORYME_END, GAMEOVER };

static bool fileExists(const char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    if (file)
    {
        fclose(file);
        return true;
    }
    return false;
}

static std::string locateAsset(const char *fileName)
{
    const char *paths[] = {"Graphics/", "../Graphics/", "src/Graphics/", "../src/Graphics/", "resourse/", "../resourse/", "src/resourse/", "../src/resourse/"};

    for (const char *prefix : paths)
    {
        std::string path = prefix;
        path += fileName;
        if (fileExists(path.c_str()))
        {
            return path;
        }
    }

    return std::string("Graphics/") + fileName; // fallback path
}

static Texture2D LoadTextureAsset(const char *fileName)
{
    std::string path = locateAsset(fileName);
    Texture2D texture = LoadTexture(path.c_str());
    if (texture.width == 0)
    {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    return texture;
}

static Font LoadFontAsset(const char *fileName, int fontSize = 32)
{
    std::string path = locateAsset(fileName);
    Font font = LoadFontEx(path.c_str(), fontSize, nullptr, 0);
    if (font.texture.width == 0)
    {
        std::cout << "Failed to load font: " << path << std::endl;
        font = GetFontDefault(); // fallback to default font
    }
    return font;
}

static void DrawTextMultiline(Font font, const std::string &text, Vector2 position, float fontSize, float spacing, Color color)
{
    Vector2 drawPos = position;
    std::string line;
    for (char c : text)
    {
        if (c == '\n')
        {
            if (!line.empty())
            {
                DrawTextEx(font, line.c_str(), drawPos, fontSize, spacing, color);
                line.clear();
            }
            drawPos.y += fontSize + spacing;
            drawPos.x = position.x;
        }
        else
        {
            line.push_back(c);
        }
    }
    if (!line.empty())
    {
        DrawTextEx(font, line.c_str(), drawPos, fontSize, spacing, color);
    }
}

int main()
{
    InitWindow(800, 600, "MIDNIGHT SENTINEL: forest protocol");
    //ToggleFullscreen();

    SetTargetFPS(60);

    ForestManager game;

    Texture2D background = LoadTextureAsset("real_bg.jpg");
    bool backgroundLoaded = (background.width > 0);

    Texture2D howtoBackground = LoadTextureAsset("howtop1.png");
    bool howtoTextureLoaded = (howtoBackground.width > 0);
    Texture2D howtoBackground2 = LoadTextureAsset("howtop2.png");
    bool howtoTextureLoaded2 = (howtoBackground2.width > 0);
    Texture2D howtoBackground3 = LoadTextureAsset("howtop3.png");
    bool howtoTextureLoaded3 = (howtoBackground3.width > 0);
    Texture2D howtoBackground4 = LoadTextureAsset("howtop4.png");
    bool howtoTextureLoaded4 = (howtoBackground4.width > 0);
    Texture2D howtoBackground5 = LoadTextureAsset("howtop5.png");
    bool howtoTextureLoaded5 = (howtoBackground5.width > 0);

    Texture2D storybegin = LoadTextureAsset("story_start.png");
    bool storybeginLoaded = (storybegin.width > 0);
    Texture2D characterBackground = LoadTextureAsset("character.png");
    bool characterTextureLoaded = (characterBackground.width > 0);
    Texture2D characterJe = LoadTextureAsset("character_je.png");
    bool characterJeLoaded = (characterJe.width > 0);
    Texture2D characterMe = LoadTextureAsset("character_me.png");
    bool characterMeLoaded = (characterMe.width > 0);
    Texture2D storyJe = LoadTextureAsset("storyje.png");
    Texture2D storyMe = LoadTextureAsset("storyme.png");
    bool storyJeLoaded = (storyJe.width > 0);
    bool storyMeLoaded = (storyMe.width > 0);
    Texture2D playing = LoadTextureAsset("playing.png");
    bool playingLoaded = (playing.width > 0);
    Texture2D horror = LoadTextureAsset("mission.png");
    bool horrorLoaded = (horror.width > 0);
    Texture2D horrorintro = LoadTextureAsset("mission_intro.png");
    bool horrorintroLoaded = (horrorintro.width > 0);
    Texture2D endday = LoadTextureAsset("end_day.png");
    bool enddayLoaded = (endday.width > 0);
    Texture2D victory = LoadTextureAsset("victory.png");
    bool victoryLoaded = (victory.width > 0);
    Texture2D storyje_end = LoadTextureAsset("storyje_end.png");
    bool storyje_endLoaded = (storyje_end.width > 0);
    Texture2D storyme_end = LoadTextureAsset("storyme_end.png");
    bool storyme_endLoaded = (storyme_end.width > 0);
    Texture2D gameover = LoadTextureAsset("gameover.png");
    bool gameoverLoaded = (gameover.width > 0);

    Texture2D day1 = LoadTextureAsset("day1.png");
    bool day1Loaded = (day1.width > 0);
    Texture2D day2 = LoadTextureAsset("day2.png");
    bool day2Loaded = (day2.width > 0);
    Texture2D day3 = LoadTextureAsset("day3.png");
    bool day3Loaded = (day3.width > 0);
    Texture2D day4 = LoadTextureAsset("day4.png");
    bool day4Loaded = (day4.width > 0);
    Texture2D day5 = LoadTextureAsset("day5.png");
    bool day5Loaded = (day5.width > 0);
    Texture2D day6 = LoadTextureAsset("day6.png");
    bool day6Loaded = (day6.width > 0);
    Texture2D day7 = LoadTextureAsset("day7.png");
    bool day7Loaded = (day7.width > 0);
    int day = game.getCurrentDay();


    Font pixelFont = LoadFontAsset("PublicPixel-rv0pA.ttf", 32);
    Font horrorFont = LoadFontAsset("bloodcrow.ttf", 32);
    Font endDayFont = LoadFontAsset("RobotoMono-VariableFont_wght.ttf", 28);

    // Initialize text managers
    TextManager textManager;
    textManager.SetFonts(pixelFont, horrorFont);  // Set both fonts, starts with pixelFont
    
    TextManager textManagerJE;
    textManagerJE.SetFonts(pixelFont, horrorFont);
    textManagerJE.texts.clear();
    textManagerJE.texts.push_back("\n\tFresh start in the woods, \n\n\tand I'm already facing the silence.            ");
    textManagerJE.texts.push_back("\n\tThe goal: Heal the grove.                ");
    textManagerJE.texts.push_back("\n\tThe limit: Seven sunrises.                ");
    textManagerJE.texts.push_back("\n\tThe elders gave me their blessing... \n\n\tbut they didn't give me any backup.                ");
    textManagerJE.texts.push_back("\n\tTime to save the green!!!                      ");
    if (!textManagerJE.texts.empty()) {
        textManagerJE.typewriterText = textManagerJE.texts[0];
    }
    
    TextManager textManagerME;
    textManagerME.SetFonts(pixelFont, horrorFont);
    textManagerME.texts.clear();
    textManagerME.texts.push_back("\n\tFirst day on the job, \n\n\tand I'm already flying solo.                 ");
    textManagerME.texts.push_back("\n\tThe mission: Save the forest.               ");
    textManagerME.texts.push_back("\n\tThe deadline: Seven days.                 ");
    textManagerME.texts.push_back("\n\tThey left me the keys and a warning... \n\n\tbut didn't leave any help.                 ");
    textManagerME.texts.push_back("\n\tTime to get to work!!!                      ");
    if (!textManagerME.texts.empty()) {
        textManagerME.typewriterText = textManagerME.texts[0];
    }
    
    // End story text managers
    TextManager textManagerJEEnd;
    textManagerJEEnd.SetFonts(pixelFont, horrorFont);
    textManagerJEEnd.texts.clear();
    textManagerJEEnd.texts.push_back("\n\tThe grove is healing.\n\n\tI can feel it in the air.            ");
    textManagerJEEnd.texts.push_back("\n\tSeven days of work, pain, and choices.\n\n\tBut it was worth it.               ");
    textManagerJEEnd.texts.push_back("\n\tThe forest remembers.\n\n\tAnd so do I.                ");
    if (!textManagerJEEnd.texts.empty()) {
        textManagerJEEnd.typewriterText = textManagerJEEnd.texts[0];
    }
    
    TextManager textManagerMEEnd;
    textManagerMEEnd.SetFonts(pixelFont, horrorFont);
    textManagerMEEnd.texts.clear();
    textManagerMEEnd.texts.push_back("\n\tThe forest survived.\n\n\tI actually did it.            ");
    textManagerMEEnd.texts.push_back("\n\tSeven days of decisions, \n\n\tlosses, and victories.              ");
    textManagerMEEnd.texts.push_back("\n\tNow I know what I'm capable of.            ");
    textManagerMEEnd.texts.push_back("\n\tThe woods are counting on me.\n\n\tAnd I won't let them down.                ");
    if (!textManagerMEEnd.texts.empty()) {
        textManagerMEEnd.typewriterText = textManagerMEEnd.texts[0];
    }
    
    std::string continuetext = "            - PRESS SPACEBAR TO CONTINUE -";
    Vector2 textPosition = {98.0f, 504.1f};
    
    // Track which character was selected
    bool isCharacterJE = false;

    // Track HOW_TO_PLAY page (1-5)
    int howToPlayPage = 1;

    Rectangle charJeRect = {86.4f, 145.9f, 294.9f, 376.1f};
    Rectangle charMeRect = {418.7f, 145.9f, 294.9f, 376.1f};
    //Rectangle alertRect = {556.4f, 206.6f, 27.5f, 27.5f};

    Button titleButton{locateAsset("title.png").c_str(), {140, 90}, 0.85};
    Button startButton{locateAsset("playbt.png").c_str(), {290, 330}, 0.65};
    Button howtoButton{locateAsset("howto2.png").c_str(), {160, 420}, 1.05};
    Button exitButton{locateAsset("exitbt.png").c_str(), {410, 420}, 0.65};
    Button backButton{locateAsset("front.png").c_str(), {715, 300}, 0.65}; 
    Button frontButton{locateAsset("back.png").c_str(), {40, 300}, 0.65};
    bool exit = false;
    Button chooseje{locateAsset("chooseje.png").c_str(), {85, 144}, 1.39};
    Button chooseme{locateAsset("chooseme.png").c_str(), {418, 144}, 1.39};
    Button alert{locateAsset("alert_message.png").c_str(), {95, 234}, 1.20f};
    Button alertclose{locateAsset("alert_message_close.png").c_str(), {651, 233}, 1.20f};
    //Button horrortest{locateAsset("horrortest.png").c_str(), {600, 420}, 0.5};
    //Button minigametest{locateAsset("minigametest.png").c_str(), {200, 420}, 1.0f};


    int selectedEventIndex = -1;
    int selectedProjectIndex = -1;
    bool showAlertButton = false;
    bool showMissionChoices = false;
    bool justEnteredPlaying = false;
    std::string selectedAlertText = "";
    std::string selectedEventName = "";
    std::string selectedProjectText = "";
    std::string missionCoreText = "";
    std::vector<std::string> missionIntroLines;
    int missionIntroLineIndex = 0;
    float missionIntroTimer = 0.0f;
    bool missionIntroComplete = false;
    MissionEvent* currentMission = nullptr;

    GameState currentState = MENU;

    while(WindowShouldClose() == false && exit == false)
    {
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        day = game.getCurrentDay();

        if(currentState == MENU)
        {
            if(startButton.isPressed(mousePosition, mousePressed))
            {
                std::cout << "Start Button Pressed" << std::endl;
                currentState = STORY_BEGIN;
                // Reset typewriter effect
                textManager.Reset();
            }

            if(howtoButton.isPressed(mousePosition, mousePressed))
            {
                std::cout << "How to Play Button Pressed" << std::endl;
                howToPlayPage = 1;  // Reset to first page
                currentState = HOW_TO_PLAY;
            }

            if(exitButton.isPressed(mousePosition, mousePressed))
            {
                exit = true;
            }
        }
        else if(currentState == HOW_TO_PLAY)
        {
            if(backButton.isPressed(mousePosition, mousePressed))
            {
                if (howToPlayPage < 5)
                {
                    howToPlayPage++;
                }
                else
                {
                    howToPlayPage = 1;  // Reset page
                    currentState = MENU;
                }
            }
            
            if(frontButton.isPressed(mousePosition, mousePressed))
            {
                if (howToPlayPage > 1)
                {
                    howToPlayPage--;
                }
                else
                {
                    howToPlayPage = 1;  // Reset page
                    currentState = MENU;
                }
            }
        }
        else if(currentState == STORY_BEGIN)
        {
            if(IsKeyPressed(KEY_SPACE))
            {
                currentState = CHARACTER;
            }

            // Update typewriter effect
            textManager.Update();

            // Show continue text only after the story animation finished
            if (textManager.IsFinished() && !textManager.hasPlainText)
            {
                textManager.SetPlainText("    - PRESS SPACEBAR TO CONTINUE -", {98.0f, 514.1f}, 15, WHITE, 1.0f);
            }
        }
        else if(currentState == CHARACTER)
        {
            bool hoverCharJe = CheckCollisionPointRec(mousePosition, charJeRect);
            bool hoverCharMe = CheckCollisionPointRec(mousePosition, charMeRect);

            if (hoverCharJe)
            {
                currentState = CHARACTER_JE;
            }
            if (hoverCharMe)
            {
                currentState = CHARACTER_ME;
            }
        }

        else if(currentState == CHARACTER_JE)
        {
            //bool hoverCharMe = CheckCollisionPointRec(mousePosition, charMeRect);
            /*if(backButton.isPressed(mousePosition, mousePressed))
            {
                currentState = CHARACTER;
            }*/

            if(chooseje.isPressed(mousePosition, mousePressed))
            {
                isCharacterJE = true;
                textManagerJE.Reset();
                currentState = STORY_JE;
            }
            
            else if(bool hoverCharMe = CheckCollisionPointRec(mousePosition, charMeRect) == 1)
            {
                currentState = CHARACTER_ME;
    
            }
        }

        else if(currentState == CHARACTER_ME)
        {
            //bool hoverCharJe = CheckCollisionPointRec(mousePosition, charJeRect);
            /*if(backButton.isPressed(mousePosition, mousePressed))
            {
                currentState = CHARACTER;
            }*/

            if(chooseme.isPressed(mousePosition, mousePressed))
            {
                isCharacterJE = false;
                textManagerME.Reset();
                currentState = STORY_ME;
            }
            else if(bool hoverCharJe = CheckCollisionPointRec(mousePosition, charJeRect) == 1)
            {
                currentState = CHARACTER_JE;
            }
        }
        else if(currentState == STORY_JE)
        {
            if(IsKeyPressed(KEY_SPACE))
            {
                if (!textManagerJE.IsFinished())
                {
                    // Continue animation if not finished
                    textManagerJE.Update();
                }
                else
                {
                    // All text finished, move to next state
                    game.DailyEvents();
                    currentState = DAY;
                }
            }
            else
            {
                // Update typewriter effect
                textManagerJE.Update();

                // Show continue text only after the story animation finished
                if (textManagerJE.IsFinished() && !textManagerJE.hasPlainText)
                {
                    textManagerJE.SetPlainText("    - PRESS SPACEBAR TO CONTINUE -", {98.0f, 504.1f}, 15, WHITE, 1.0f);
                }
            }
        }
        else if(currentState == STORY_ME)
        {
            if(IsKeyPressed(KEY_SPACE))
            {
                if (!textManagerME.IsFinished())
                {
                    // Continue animation if not finished
                    textManagerME.Update();
                }
                else
                {
                    // All text finished, move to next state
                    game.DailyEvents();
                    currentState = DAY;
                }
            }
            else
            {
                // Update typewriter effect
                textManagerME.Update();

                // Show continue text only after the story animation finished
                if (textManagerME.IsFinished() && !textManagerME.hasPlainText)
                {
                    textManagerME.SetPlainText("    - PRESS SPACEBAR TO CONTINUE -", {98.0f, 504.1f}, 15, WHITE, 1.0f);
                }
            }
        }
        else if(currentState == STORYJE_END)
        {
            if(IsKeyPressed(KEY_SPACE))
            {
                if (!textManagerJEEnd.IsFinished())
                {
                    textManagerJEEnd.Update();
                }
                else
                {
                    currentState = VICTORY;
                }
            }
            else
            {
                textManagerJEEnd.Update();
                if (textManagerJEEnd.IsFinished() && !textManagerJEEnd.hasPlainText)
                {
                    textManagerJEEnd.SetPlainText("    - PRESS SPACEBAR TO CONTINUE -", {98.0f, 504.1f}, 15, WHITE, 1.0f);
                }
            }
        }
        else if(currentState == STORYME_END)
        {
            if(IsKeyPressed(KEY_SPACE))
            {
                if (!textManagerMEEnd.IsFinished())
                {
                    textManagerMEEnd.Update();
                }
                else
                {
                    currentState = VICTORY;
                }
            }
            else
            {
                textManagerMEEnd.Update();
                if (textManagerMEEnd.IsFinished() && !textManagerMEEnd.hasPlainText)
                {
                    textManagerMEEnd.SetPlainText("    - PRESS SPACEBAR TO CONTINUE -", {98.0f, 504.1f}, 15, WHITE, 1.0f);
                }
            }
        }
        else if(currentState == DAY)
        {
            if(IsKeyPressed(KEY_SPACE))
            {
                currentState = PLAYING;
                justEnteredPlaying = true;
            }
            else if ((game.getEventCount() == 0 || game.getCurrentStamina() == 0) && IsKeyPressed(KEY_Q))
            {
                game.processEndOfDay();
                currentState = END_DAY;
                selectedEventIndex = -1;
                showAlertButton = false;
                showMissionChoices = false;
            }
        }
        else if(currentState == HORROR_INTRO)
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                if (missionIntroLineIndex < missionIntroLines.size() - 1)
                {
                    missionIntroLineIndex++;
                }
                else
                {
                    currentState = HORROR;
                }
            }
        }
        else if(currentState == PLAYING)
        {
            int eventCount = game.getEventCount();
            const float eventStartX = 80.0f;
            const float eventStartY = 120.0f;
            const float eventRowHeight = 32.0f;

            const float projectStartX = 67.6f;
            const float projectRowHeight = 26.0f;
            const int projectCount = 3;

            if (mousePressed)
            {
                bool clickedEvent = false;
                for (int i = 0; i < eventCount; i++)
                {
                    Rectangle rowRec = {eventStartX, eventStartY + i * eventRowHeight, 540.0f, eventRowHeight};
                    if (CheckCollisionPointRec(mousePosition, rowRec))
                    {
                        selectedEventIndex = i;
                        selectedProjectIndex = -1;
                        showAlertButton = true;
                        showMissionChoices = false;
                        BaseEvent* event = game.getEvent(i);
                        selectedAlertText = event ? event->getAlertMessage() : "";
                        selectedEventName = event ? event->getName() : "";
                        game.setSystemMessage("");  // Clear system message when new event is chosen
                        clickedEvent = true;
                        break;
                    }
                }

                if (!clickedEvent)
                {
                    float projectStartY = 379.0f;
                    for (int i = 0; i < projectCount; i++)
                    {
                        Rectangle projRec = {projectStartX, projectStartY + i * projectRowHeight, 540.0f, projectRowHeight};
                        if (CheckCollisionPointRec(mousePosition, projRec))
                        {
                            Project* proj = game.getProject(i);
                            if (proj)
                            {
                                selectedProjectIndex = i;
                                selectedEventIndex = -1;
                                showAlertButton = true;
                                showMissionChoices = false;
                                selectedAlertText.clear();
                                selectedProjectText = "Project: " + proj->getName();
                                game.setSystemMessage("");
                            }
                            break;
                        }
                    }
                }

                if (showAlertButton && selectedEventIndex >= 0 && alertclose.isPressed(mousePosition, mousePressed))
                {
                    BaseEvent* event = game.getEvent(selectedEventIndex);
                    if (event)
                    {
                        if (event->getType() == "Mission")
                        {
                            MissionEvent* mission = static_cast<MissionEvent*>(event);
                            ActionResult story = mission->getStory();
                            missionIntroLines.clear();
                            missionCoreText.clear();
                            for (int si = 0; si < story.storySize; si++)
                            {
                                missionIntroLines.push_back(story.storyBeats[si]);
                                if (si > 0) missionCoreText += "\n";
                                missionCoreText += story.storyBeats[si];
                            }
                            currentMission = mission;
                            selectedEventIndex = -1;
                            showAlertButton = false;
                            showMissionChoices = false;
                            selectedAlertText.clear();
                            missionIntroLineIndex = 0;
                            missionIntroTimer = 0.0f;
                            missionIntroComplete = false;
                            currentState = HORROR_INTRO;
                        }
                        else
                        {
                            game.handleEvent(event);
                            selectedEventIndex = -1;
                            showAlertButton = false;
                        }
                    }
                }
                else if (showAlertButton && selectedProjectIndex >= 0 && alertclose.isPressed(mousePosition, mousePressed))
                {
                    Project* proj = game.getProject(selectedProjectIndex);
                    if (proj)
                    {
                        game.handleProject(proj);
                        selectedProjectIndex = -1;
                        showAlertButton = false;
                        selectedProjectText.clear();
                    }
                }
            }

            // End day only when the player presses Q.
            if (IsKeyPressed(KEY_Q))
            {
                game.processEndOfDay();
                currentState = END_DAY;
                selectedEventIndex = -1;
                showAlertButton = false;
                showMissionChoices = false;
            }

            // Do not automatically end the day when events run out or stamina depletes.
            // The player must press Q to proceed to END_DAY.
            justEnteredPlaying = false;
        }
        else if(currentState == HORROR)
        {
            if (currentMission)
            {
                int choice = -1;
                if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) choice = 1;
                else if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)) choice = 2;
                else if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3)) choice = 3;
                
                if (choice != -1)
                {
                    game.handleMission(currentMission, choice);
                    currentMission = nullptr; // Clear the mission
                    currentState = PLAYING;
                    justEnteredPlaying = true;
                }
            }
        }
        else if(currentState == END_DAY)
        {
            if(IsKeyPressed(KEY_SPACE))
            {
                game.nextDay();
                
                if (game.getForestHP() <= 0)
                {
                    currentState = GAMEOVER;
                }
                else if (game.getCurrentDay() > 7)
                {
                    if (isCharacterJE)
                    {
                        textManagerJEEnd.Reset();
                        currentState = STORYJE_END;
                    }
                    else
                    {
                        textManagerMEEnd.Reset();
                        currentState = STORYME_END;
                    }
                }
                else
                {
                    game.DailyEvents();
                    currentState = DAY;
                }
            }
        }
        else if(currentState == VICTORY)
        {
            if(IsKeyPressed(KEY_SPACE))
            {
                game.reset();
                currentMission = nullptr;
                selectedEventIndex = -1;
                selectedProjectIndex = -1;
                showAlertButton = false;
                showMissionChoices = false;
                selectedAlertText.clear();
                selectedProjectText.clear();
                justEnteredPlaying = false;
                currentState = MENU;
            }
        }
        else if(currentState == GAMEOVER)
        {
            if(IsKeyPressed(KEY_SPACE))
            {
                game.reset();
                currentMission = nullptr;
                selectedEventIndex = -1;
                selectedProjectIndex = -1;
                showAlertButton = false;
                showMissionChoices = false;
                selectedAlertText.clear();
                selectedProjectText.clear();
                justEnteredPlaying = false;
                currentState = MENU;
            }
        }
        else
        {
            //currentState = CHARACTER;
        }

        // Immediate game over if HP drops to zero or below at any time
        // Allow returning to MENU from GAMEOVER even if HP is still zero or below.
        if (game.getForestHP() <= 0 && currentState != GAMEOVER && currentState != MENU)
        {
            currentState = GAMEOVER;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if(currentState == MENU)
        {
            if (backgroundLoaded)
            {
                DrawTexturePro(
                    background,
                    Rectangle{0.0f, 0.0f, (float)background.width, (float)background.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            titleButton.Draw();
            startButton.Draw();
            howtoButton.Draw();
            exitButton.Draw();
            //DrawText("MENU", 10, 10, 20, WHITE);
        }
        else if(currentState == HOW_TO_PLAY)
        {
            Texture2D currentHowToTexture = howtoBackground;
            bool currentHowToLoaded = howtoTextureLoaded;
            
            switch(howToPlayPage)
            {
                case 1:
                    currentHowToTexture = howtoBackground;
                    currentHowToLoaded = howtoTextureLoaded;
                    break;
                case 2:
                    currentHowToTexture = howtoBackground2;
                    currentHowToLoaded = howtoTextureLoaded2;
                    break;
                case 3:
                    currentHowToTexture = howtoBackground3;
                    currentHowToLoaded = howtoTextureLoaded3;
                    break;
                case 4:
                    currentHowToTexture = howtoBackground4;
                    currentHowToLoaded = howtoTextureLoaded4;
                    break;
                case 5:
                    currentHowToTexture = howtoBackground5;
                    currentHowToLoaded = howtoTextureLoaded5;
                    break;
            }
            
            if(currentHowToLoaded)
            {
                DrawTexturePro(
                    currentHowToTexture,
                    Rectangle{0.0f, 0.0f, (float)currentHowToTexture.width, (float)currentHowToTexture.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            
            if (howToPlayPage > 1)
            {
                frontButton.Draw();
            }
            
            backButton.Draw();  // Always available: go to next page or MENU on page 5
        }
        else if(currentState == STORY_BEGIN)
        {
            if(howtoTextureLoaded)
            {
                DrawTexturePro(
                    storybegin,
                    Rectangle{0.0f, 0.0f, (float)storybegin.width, (float)storybegin.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }

            // Draw typewriter text
            textManager.Draw();
            textManager.DrawPlainText();
        }
        else if(currentState == STORY_JE)
        {
            if (storyJeLoaded)
            {
                DrawTexturePro(
                    storyJe,
                    Rectangle{0.0f, 0.0f, (float)storyJe.width, (float)storyJe.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }

            // Draw typewriter text
            textManagerJE.Draw();
            textManagerJE.DrawPlainText();
        }
        else if(currentState == STORY_ME)
        {
            if (storyMeLoaded)
            {
                DrawTexturePro(
                    storyMe,
                    Rectangle{0.0f, 0.0f, (float)storyMe.width, (float)storyMe.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }

            // Draw typewriter text
            textManagerME.Draw();
            textManagerME.DrawPlainText();
        }
        else if(currentState == STORYJE_END)
        {
            if (storyje_endLoaded)
            {
                DrawTexturePro(
                    storyje_end,
                    Rectangle{0.0f, 0.0f, (float)storyje_end.width, (float)storyje_end.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }

            textManagerJEEnd.Draw();
            textManagerJEEnd.DrawPlainText();
        }
        else if(currentState == STORYME_END)
        {
            if (storyme_endLoaded)
            {
                DrawTexturePro(
                    storyme_end,
                    Rectangle{0.0f, 0.0f, (float)storyme_end.width, (float)storyme_end.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }

            textManagerMEEnd.Draw();
            textManagerMEEnd.DrawPlainText();
        }
        else if(currentState == CHARACTER)
        {
            if (characterTextureLoaded)
            {
                DrawTexturePro(
                    characterBackground,
                    Rectangle{0.0f, 0.0f, (float)characterBackground.width, (float)characterBackground.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }

            //backButton.Draw();
        }
        else if(currentState == CHARACTER_JE)
        {
            if (characterJeLoaded)
            {
                DrawTexturePro(
                    characterJe,
                    Rectangle{0.0f, 0.0f, (float)characterJe.width, (float)characterJe.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            chooseje.Draw();
            //backButton.Draw();
        }
        else if(currentState == CHARACTER_ME)
        {
            if (characterMeLoaded)
            {
                DrawTexturePro(
                    characterMe,
                    Rectangle{0.0f, 0.0f, (float)characterMe.width, (float)characterMe.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            chooseme.Draw();
            //backButton.Draw();
        }

        else if(currentState == DAY)
        {
            switch (day)
            {
            case 1:
                if (day1Loaded)
            {
                DrawTexturePro(
                    day1,
                    Rectangle{0.0f, 0.0f, (float)day1.width, (float)day1.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            break;

            case 2:
                if (day2Loaded)
            {
                DrawTexturePro(
                    day2,
                    Rectangle{0.0f, 0.0f, (float)day2.width, (float)day2.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            break;

            case 3:
                if (day3Loaded)
            {
                DrawTexturePro(
                    day3,
                    Rectangle{0.0f, 0.0f, (float)day3.width, (float)day3.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            break;
            
            case 4:
                if (day4Loaded)
            {
                DrawTexturePro(
                    day4,
                    Rectangle{0.0f, 0.0f, (float)day4.width, (float)day4.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            break;

            case 5:
                if (day5Loaded)
            {
                DrawTexturePro(
                    day5,
                    Rectangle{0.0f, 0.0f, (float)day5.width, (float)day5.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            break;

            case 6:
                if (day6Loaded)
            {
                DrawTexturePro(
                    day6,
                    Rectangle{0.0f, 0.0f, (float)day6.width, (float)day6.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            break;

            case 7:
                if (day7Loaded)
            {
                DrawTexturePro(
                    day7,
                    Rectangle{0.0f, 0.0f, (float)day7.width, (float)day7.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            break;
            
            default:
                break;
            }

            if (game.getEventCount() == 0 || game.getCurrentStamina() == 0)
            {
                DrawTextEx(pixelFont, "Press Q to skip to end of day.", {25.6f, 560.0f}, 14.0f, 1.0f, DARKGRAY);
            }
        }
         else if(currentState == PLAYING)
        {
            if (playingLoaded)
            {
                DrawTexturePro(
                    playing,
                    Rectangle{0.0f, 0.0f, (float)playing.width, (float)playing.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }

            DrawTextEx(pixelFont, TextFormat("Day: %d", game.getCurrentDay()), {25.6f, 11.2f}, 15.0f, 1.0f, LIGHTGRAY);
            DrawTextEx(pixelFont, TextFormat("Forest HP: %d", (int)game.getForestHP()), {577.1f, 12.9f}, 14.0f, 1.0f, LIGHTGRAY);
            DrawTextEx(pixelFont, TextFormat("Stamina: %d", game.getCurrentStamina()), {625.1f, 577.7f}, 14.0f, 1.0f, LIGHTGRAY);

            //DrawTextEx(pixelFont, "Available Events:", {60.0f, 100.0f}, 22.0f, 1.0f, YELLOW);
            int eventCount = game.getEventCount();
            const float eventStartX = 67.6f;
            const float eventStartY = 120.0f;
            const float eventRowHeight = 30.0f;
            const float projectRowHeight = 30.0f;

            //float projectStartY = eventStartY + eventCount * eventRowHeight + 36.0f;
            float projectStartY = 382.0f;
            const int projectCount = 3;
            
            if (eventCount == 0)
            {
                DrawTextEx(pixelFont, "No active events", {278.6f, 149.7f}, 14.0f, 1.0f, BLACK);
                DrawTextEx(pixelFont, "Continue running projects \n\nor press Q to end the day", {218.6f, 199.7f}, 14.0f, 1.0f, BLACK);
            }
            else
            {
                for (int i = 0; i < eventCount; i++)
                {
                    BaseEvent* event = game.getEvent(i);
                    if (!event) continue;

                    Rectangle rowRec = {eventStartX, eventStartY + i * eventRowHeight, 670.0f, eventRowHeight};
                    if (i == selectedEventIndex)
                    {
                        DrawRectangleLinesEx(rowRec, 2.0f, ORANGE);
                    }

                    std::string alertText = event->getAlertMessage();
                    if (alertText.size() > 70)
                    {
                        alertText = alertText.substr(0, 67) + "...";
                    }
                    std::string eventLine = TextFormat("%d. %s [Cost %d]", i + 1, alertText.c_str(), event->getStaminaCost());
                    DrawTextEx(pixelFont, eventLine.c_str(), {eventStartX + 10, eventStartY + i * eventRowHeight + 4.0f}, 11.5f, 1.0f, BLACK);
                }
            }

            //DrawTextEx(pixelFont, "Projects:", {eventStartX, projectStartY - 24.0f}, 16.0f, 1.0f, BLACK);
            for (int i = 0; i < projectCount; i++)
            {
                Project* proj = game.getProject(i);
                if (!proj) continue;

                Rectangle projRec = {eventStartX, projectStartY + i * projectRowHeight, 670.0f, projectRowHeight};
                if (i == selectedProjectIndex)
                {
                    DrawRectangleLinesEx(projRec, 2.0f, SKYBLUE);
                }
                else
                {
                    //DrawRectangleLinesEx(projRec, 1.0f, GRAY);
                }

                std::string projectLine;
                if (proj->isComplete(proj->getName()))
                {
                    projectLine = TextFormat("%d. %s - COMPLETE", i + 11, proj->getName().c_str());
                }
                else
                {
                    projectLine = TextFormat("%d. %s [%d/%d] (Cost %d)", i + 11, proj->getName().c_str(), proj->getProgress(), proj->getMaxProgress(), proj->getStaminaCost());
                }
                DrawTextEx(pixelFont, projectLine.c_str(), {eventStartX + 10, projectStartY + i * projectRowHeight + 4.0f}, 11.0f, 1.0f, BLACK);
            }

            if (showAlertButton && selectedEventIndex >= 0)
            {
                alert.Draw();
                alertclose.Draw();
                std::string alertTitle = selectedEventName.empty() ? "Process alert" : "Process alert: "; //+ selectedEventName;
                DrawTextEx(pixelFont, alertTitle.c_str(), {135.0f, 255.0f}, 14.0f, 1.0f, BLACK);
                DrawTextMultiline(pixelFont, selectedEventName, {155.0f, 305.0f}, 13.0f, 1.0f, BLACK);
            }
            else if (showAlertButton && selectedProjectIndex >= 0)
            {
                alert.Draw();
                alertclose.Draw();
                DrawTextEx(pixelFont, "Process project alert", {135.0f, 255.0f}, 14.0f, 1.0f, BLACK);
                DrawTextMultiline(pixelFont, selectedProjectText, {130.0f, 305.0f}, 11.0f, 1.0f, BLACK);
            }

            if (showMissionChoices && selectedEventIndex >= 0)
            {
                BaseEvent* event = game.getEvent(selectedEventIndex);
                MissionEvent* mission = static_cast<MissionEvent*>(event);
                if (mission)
                {
                    Rectangle choice1 = {420.0f, 240.0f, 300.0f, 40.0f};
                    Rectangle choice2 = {420.0f, 290.0f, 300.0f, 40.0f};
                    Rectangle choice3 = {420.0f, 340.0f, 300.0f, 40.0f};

                    DrawRectangleRec(choice1, Fade(BLACK, 0.5f));
                    DrawRectangleRec(choice2, Fade(BLACK, 0.5f));
                    DrawRectangleRec(choice3, Fade(BLACK, 0.5f));
                    DrawRectangleLinesEx(choice1, 2.0f, SKYBLUE);
                    DrawRectangleLinesEx(choice2, 2.0f, SKYBLUE);
                    DrawRectangleLinesEx(choice3, 2.0f, SKYBLUE);

                    DrawTextEx(pixelFont, mission->getChoice(1).c_str(), {choice1.x + 10.0f, choice1.y + 8.0f}, 18.0f, 1.0f, WHITE);
                    DrawTextEx(pixelFont, mission->getChoice(2).c_str(), {choice2.x + 10.0f, choice2.y + 8.0f}, 18.0f, 1.0f, WHITE);
                    DrawTextEx(pixelFont, mission->getChoice(3).c_str(), {choice3.x + 10.0f, choice3.y + 8.0f}, 18.0f, 1.0f, WHITE);
                }
            }

            std::string systemMsg = game.getSystemMessage();
            if (!systemMsg.empty())
            {
                size_t splitPos = systemMsg.rfind(" (");
                if (splitPos != std::string::npos && systemMsg.back() == ')')
                {
                    std::string topLine = systemMsg.substr(0, splitPos);
                    std::string bottomLine = systemMsg.substr(splitPos + 1);
                    DrawTextMultiline(pixelFont, topLine + "\n" + bottomLine, {40.0f, 530.0f}, 12.0f, 1.0f, GREEN);
                }
                else
                {
                    DrawTextMultiline(pixelFont, systemMsg, {40.0f, 535.0f}, 12.0f, 1.0f, GREEN);
                }
            }
            //DrawTextEx(pixelFont, "RUN OUT OF STAMINA : PRESS Q TO END THE DAY", {130.0f, 305.0f}, 20.0f, 1.0f, RED);
        }
        else if(currentState == HORROR_INTRO)
        {
            if (horrorintroLoaded)
            {
                DrawTexturePro(
                    horrorintro,
                    Rectangle{0.0f, 0.0f, (float)horrorintro.width, (float)horrorintro.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            if (missionIntroLineIndex < missionIntroLines.size())
            {
                DrawTextMultiline(horrorFont, missionIntroLines[missionIntroLineIndex], {40.0f, 280.0f}, 26.0f, 4.0f, WHITE);
                DrawTextEx(horrorFont, "- PRESS SPACEBAR TO CONTINUE -", {240.0f, 520.0f}, 20.0f, 1.0f, LIGHTGRAY);
            }
            else
            {
                DrawTextEx(horrorFont, "- PRESS SPACEBAR TO ENTER THE MISSION -", {130.0f, 420.0f}, 24.0f, 1.0f, LIGHTGRAY);
            }
        }
        else if(currentState == HORROR)
        {
            if (horrorLoaded)
            {
                DrawTexturePro(
                    horror,
                    Rectangle{0.0f, 0.0f, (float)horror.width, (float)horror.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            if (currentMission)
            {
                // Display the mission event name
                DrawTextMultiline(horrorFont, currentMission->getName(), {100.0f, 160.0f}, 29.0f, 2.0f, WHITE);
                
                // Display choices
                DrawTextEx(horrorFont, "WHAT WOULD YOU DO?", {100.0f, 240.0f}, 28.0f, 1.0f, LIGHTGRAY);
                DrawTextEx(horrorFont, ("1. " + currentMission->getChoice(1)).c_str(), {120.0f, 280.0f}, 25.0f, 1.0f, WHITE);
                DrawTextEx(horrorFont, ("2. " + currentMission->getChoice(2)).c_str(), {120.0f, 315.0f}, 25.0f, 1.0f, WHITE);
                DrawTextEx(horrorFont, ("3. " + currentMission->getChoice(3)).c_str(), {120.0f, 350.0f}, 25.0f, 1.0f, WHITE);
                
                DrawTextEx(horrorFont, "- PRESS 1 OR 2 OR 3 TO CHOOSE -", {260.0f, 460.0f}, 20.0f, 1.0f, LIGHTGRAY);
            }
        }
        else if(currentState == END_DAY)
        {
            if (enddayLoaded)
            {
                DrawTexturePro(
                    endday,
                    Rectangle{0.0f, 0.0f, (float)endday.width, (float)endday.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }

            std::string dailySummary = game.getDailySummary();
            for (char &c : dailySummary)
            {
                if (c == '\t')
                {
                    c = ' ';
                }
            }

            std::string endDayText = TextFormat(
                "          DAY %d SUMMARY\n---------------------------------\nForest HP: %.0f\nStamina Left: %d\nDamage Today: %.0f\n---------------------------------\nThreat Summary:\n%s",
                day,
                game.getForestHP(),
                game.getCurrentStamina(),
                game.getDailyDamage(),
                dailySummary.c_str()
            );

            //DrawRectangle(40, 110, 720, 360, Fade(BLACK, 0.35f));
            //DrawRectangleLinesEx({40.0f, 110.0f, 720.0f, 360.0f}, 2.0f, SKYBLUE);
            DrawTextMultiline(endDayFont, endDayText, {150.0f, 190.0f}, 26.0f, 4.0f, Color{106, 113, 21, 255});
            DrawTextEx(endDayFont, continuetext.c_str(), {135.0f, 577.0f}, 20.0f, 1.0f, Color{106, 113, 21, 255});
        }
        else if(currentState == VICTORY)
        {
            if (victoryLoaded)
            {
                DrawTexturePro(
                    victory,
                    Rectangle{0.0f, 0.0f, (float)victory.width, (float)victory.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
            DrawTextEx(pixelFont, TextFormat("Forest HP Left: %.0f", game.getForestHP()), {136.3f, 322.9f}, 28.0f, 1.0f, Color{230, 232, 216, 255});
            //DrawTextEx(pixelFont, "- Press SPACE to return to MENU -", {120.0f, 590.0f}, 20.0f, 1.0f, LIGHTGRAY);
        }
        else if(currentState == GAMEOVER)
        {
            if (gameoverLoaded)
            {
                DrawTexturePro(
                    gameover,
                    Rectangle{0.0f, 0.0f, (float)gameover.width, (float)gameover.height},
                    Rectangle{0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            }
        }
         else
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
        }

        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(howtoBackground);
    UnloadTexture(storybegin);
    UnloadTexture(characterBackground);
    UnloadTexture(characterJe);
    UnloadTexture(characterMe);
    UnloadTexture(storyJe);
    UnloadTexture(storyMe);
    UnloadTexture(playing);
    UnloadTexture(day1);
    UnloadTexture(day2);
    UnloadTexture(day3);
    UnloadTexture(day4);
    UnloadTexture(day5);
    UnloadTexture(day6);
    UnloadTexture(day7);
    UnloadTexture(horror);
    UnloadTexture(endday);
    UnloadTexture(victory);
    UnloadTexture(gameover);

    UnloadFont(pixelFont);
    UnloadFont(horrorFont);
    UnloadFont(endDayFont);

    CloseWindow();
}
