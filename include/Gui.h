#ifndef GUI_H
#define GUI_H

#include "HospitalSystem.h"
#include <SFML/Graphics.hpp>

class Gui
{
private:
    struct Button
    {
        sf::FloatRect area;
        int actionId;
        char label[60];
    };

    struct InputField
    {
        char label[40];
        char value[520];
        int maxLength;
    };

    HospitalSystem *system;
    sf::RenderWindow window;
    sf::Font font;
    sf::View uiView;

    int loginRole;
    char loginId[30];
    char loginPassword[50];
    int loginActiveField;

    int currentAction;
    int formActiveField;
    int fieldCount;
    InputField fields[5];
    Button menuButtons[12];
    int menuButtonCount;
    char infoText[20000];

    int invalidDateAttempts;
    int invalidTopUpAttempts;

    void configureMenuButtons();
    void clearForm();
    void prepareAction(int actionId);
    void refreshActionPreview();
    void submitCurrentAction();
    void processEvents();
    void handleMouseClick(float x, float y);
    void updateView(unsigned int width, unsigned int height);
    void handleTextInput(unsigned int unicode);
    void handleBackspace();
    void render();
    void renderLoginScreen();
    void renderDashboard();
    void drawButton(const Button &button, bool selected);
    void drawTextBlock(const char *text, float x, float y, unsigned int size, sf::Color color);
    void drawWrappedText(const char *text, float x, float y, float maxWidth, unsigned int size, sf::Color color);
    void drawInputBox(float x, float y, float width, float height, const char *label, const char *value, bool active, bool hideText);
    bool loadFont();
    void maskPassword(const char *source, char *masked, int bufferSize);

public:
    Gui();

    bool initialize(HospitalSystem *hospitalSystem);
    void run();
};

#endif
