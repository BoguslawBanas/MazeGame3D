#include <raylib.h>
#include <string.h>

class GameButton{
    Rectangle rectangle;
    Color c1;
    Color c2;
    int current_mode;
    char name[];

    public:
    GameButton(Rectangle, Color, Color, const char*);
    GameButton(const float, const float, const float, const float, Color, Color, const char*);
    ~GameButton();
    Rectangle getRectangle();
    bool isMouseOn();
    bool isButtonClicked();
    void drawButton();
};