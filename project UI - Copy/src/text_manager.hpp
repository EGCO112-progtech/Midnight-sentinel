#ifndef TEXT_MANAGER_HPP
#define TEXT_MANAGER_HPP

#include <vector>
#include <string>
#include <raylib.h>

struct TextManager
{
    // Text content
    std::vector<std::string> texts;
    
    // Typewriter animation variables
    int currentTextIndex = 0;
    std::string typewriterText = "";
    bool isClearing = false;
    float clearTimer = 0.0f;
    float clearDuration = 0.7f;
    
    // Character animation
    size_t charIndex = 0;
    float typewriterTimer = 0.0f;
    float charDelay = 0.05f;
    
    // Font and position
    Font font;
    Font font1;  // First font option
    Font font2;  // Second font option
    Vector2 textPosition = {98.0f, 472.6f};
    float fontSize = 15.0f;
    Color textColor = WHITE;

    // Plain text storage
    std::string plainText = "";
    Vector2 plainTextPosition = {0.0f, 0.0f};
    float plainTextFontSize = 15.0f;
    Color plainTextColor = WHITE;
    float plainTextSpacing = 1.0f;
    bool hasPlainText = false;

    // Constructor to initialize texts
    TextManager()
    {
        // Add all your story texts here
        texts.push_back("\nYear 2100.               \n\nThe forest is on the edge of collapse.           ");
        texts.push_back("\nDisasters are constant.              \n\nHumanity hasn't stopped.             ");
        texts.push_back("\nYou have one mission                          \n\nProtect the forest ... before it's gone.                       ");
        // Add more texts as needed below
        // texts.push_back("Your new text here");
        
        if (!texts.empty())
        {
            typewriterText = texts[currentTextIndex];
        }
    }

    void TextHorror()
    {
        // Add all your story texts here
        texts.push_back("\nHello World!           ");
        /*texts.push_back("\nDisasters are constant.              \n\nHumanity hasn't stopped.             ");
        texts.push_back("\nYou have one mission                          \n\nProtect the forest ... before it's gone.                       ");
        // Add more texts as needed below
        // texts.push_back("Your new text here");*/
        
        if (!texts.empty())
        {
            typewriterText = texts[currentTextIndex];
        }
    }

    // Update typewriter animation
    void Update()
    {
        if (!isClearing)
        {
            if (charIndex < typewriterText.length())
            {
                typewriterTimer += GetFrameTime();
                if (typewriterTimer >= charDelay)
                {
                    charIndex++;
                    typewriterTimer = 0.0f;
                }
            }
            else
            {
                // Finished current text, start clearing
                isClearing = true;
                clearTimer = 0.0f;
            }
        }
        else
        {
            clearTimer += GetFrameTime();
            if (clearTimer >= clearDuration)
            {
                // Finished clearing, next text
                currentTextIndex++;
                if (currentTextIndex < texts.size())
                {
                    typewriterText = texts[currentTextIndex];
                    charIndex = 0;
                    typewriterTimer = 0.0f;
                    isClearing = false;
                }
                // If all texts done, currentTextIndex will be >= texts.size()
            }
        }
    }

    // Draw the typewriter text
    void Draw() const
    {
        if (!isClearing && !texts.empty() && currentTextIndex < texts.size())
        {
            std::string displayText = typewriterText.substr(0, charIndex);
            DrawTextEx(font, displayText.c_str(), textPosition, fontSize, 1.0f, textColor);
        }
    }

    // Draw plain text immediately, without animation
    void DrawPlainText(const std::string &plainText, Vector2 position, float fontSizeValue, Color colorValue = WHITE, float spacing = 1.0f) const
    {
        DrawTextEx(font, plainText.c_str(), position, fontSizeValue, spacing, colorValue);
    }

    // Set plain text to draw later
    void SetPlainText(const std::string &text, Vector2 position, float fontSizeValue = 15.0f, Color colorValue = WHITE, float spacing = 1.0f)
    {
        plainText = text;
        plainTextPosition = position;
        plainTextFontSize = fontSizeValue;
        plainTextColor = colorValue;
        plainTextSpacing = spacing;
        hasPlainText = true;
    }

    // Clear stored plain text
    void ClearPlainText()
    {
        plainText.clear();
        hasPlainText = false;
    }

    // Draw stored plain text if set
    void DrawPlainText() const
    {
        if (hasPlainText)
        {
            DrawTextEx(font, plainText.c_str(), plainTextPosition, plainTextFontSize, plainTextSpacing, plainTextColor);
        }
    }

    // Reset to start
    void Reset()
    {
        currentTextIndex = 0;
        if (!texts.empty())
        {
            typewriterText = texts[currentTextIndex];
        }
        charIndex = 0;
        typewriterTimer = 0.0f;
        isClearing = false;
        clearTimer = 0.0f;
        ClearPlainText();
    }

    // Check if all texts have finished
    bool IsFinished() const
    {
        return currentTextIndex >= texts.size();
    }

    // Set both font options
    void SetFonts(Font f1, Font f2)
    {
        font1 = f1;
        font2 = f2;
        font = font1;  // Start with first font
    }

    // Switch to font1
    void UseFont1()
    {
        font = font1;
    }

    // Switch to font2
    void UseFont2()
    {
        font = font2;
    }

    // Toggle between fonts
    void ToggleFont()
    {
        if (font.texture.id == font1.texture.id)
        {
            font = font2;
        }
        else
        {
            font = font1;
        }
    }
};

#endif // TEXT_MANAGER_HPP
