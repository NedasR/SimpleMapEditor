#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#define GRID_CELL_SIZE 16
#define PICKER_ONE_LINE_LENTGH 10
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define PICKER_MENU_WIDTH 320
#define PICKER_MENU_HEIGHT 336

class TilePicker
{
private:
    sf::Sprite palette;
    sf::Texture tex;
    sf::IntRect rectTex;
    sf::Vector2i pickedTex;
    sf::Vector2i pickermoveloc;
    sf::RectangleShape pickerMenu;
    sf::Vector2f pickermenusize;
    sf::Vector2i Offset;
    sf::Text pickerTEXT;
    sf::Font PickerFont;
    bool Loading = false;
    bool Saving = false;
    sf::Clock Time;
public:
    bool mousemovingpicker;
    TilePicker()
    {
        tex.loadFromFile("assets/set.png");
        rectTex.left = 0;
        rectTex.top = 0;
        rectTex.height = 16;
        rectTex.width = 16;
        palette.setTexture(tex);
        PickerFont.loadFromFile("assets/arial.ttf");
        pickerTEXT.setFont(PickerFont);
        pickerTEXT.setCharacterSize(16);
        pickermoveloc.x = 400;
        pickermoveloc.y = 400;
        pickermenusize.x = PICKER_MENU_WIDTH;
        pickermenusize.y = PICKER_MENU_HEIGHT;
        pickerMenu.setSize(pickermenusize);
        pickerMenu.setFillColor(sf::Color::Color(46, 43, 43));
        mousemovingpicker = false;
    }

    sf::Color IndicatorButton(bool on, sf::Color Color = sf::Color::Black, sf::Color indicatorColor = sf::Color(20, 163, 57))
    {
        return on ? indicatorColor : Color;
    }

    void Drawpicker(sf::RenderWindow& Target)
    {
        pickerMenu.setPosition(pickermoveloc.x - 16, pickermoveloc.y - 32);
        palette.setPosition(pickermoveloc.x, pickermoveloc.y);
        Target.draw(pickerMenu);
        Target.draw(palette);

        PickerMText("Material Picker", Target, 20, 6, 4, sf::Color(57, 68, 150));
        PickerMText("Load", Target, 210, 6, 6, IndicatorButton(Loading));
        PickerMText("Save", Target, 260, 6, 6, IndicatorButton(Saving));
    }

    bool LoadButton(const sf::Event& event) {
        bool output = ButtonForPicker(event.mouseButton, 200, 0, 50, 30);

        if (output) {
            Time.restart();
            Loading = true;
        }

        return output;
    }

    bool SaveButton(const sf::Event& event) {

        bool output = ButtonForPicker(event.mouseButton, 254, 0, 46, 30);

        if (output) {
            Time.restart();
            Saving = true;
        }

        return output;
    }

    void update() {
        if (Time.getElapsedTime() >= sf::seconds(1)) {
            Loading = Saving = false;
        }
    }

    bool PickingTex(const sf::Event::MouseButtonEvent& event)
    {
        if (event.x < pickermoveloc.x + 288 && event.y < pickermoveloc.y + 288)
        {
            if (event.x > pickermoveloc.x && event.y > pickermoveloc.y) {
                pickedTex.x = (event.x - pickermoveloc.x) / GRID_CELL_SIZE;
                pickedTex.y = (event.y - pickermoveloc.y) / GRID_CELL_SIZE;
                return event.x < pickermoveloc.x + 288 && event.y < pickermoveloc.y + 288 && event.x > pickermoveloc.x && event.y > pickermoveloc.y;
            }
        }
    }
    sf::Vector2i PickedMatterial()
    {
        return pickedTex;
    }

    void MovePicker(sf::RenderWindow& Target)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(Target);
        int x = pickerMenu.getPosition().x;
        int y = pickerMenu.getPosition().y;

        if (mousePos.x < x + PICKER_MENU_WIDTH && mousePos.y < y + PICKER_MENU_HEIGHT && mousePos.x > x && mousePos.y > y || mousemovingpicker)
        {
            if (!(mousePos.y > pickermoveloc.y && mousePos.y < pickermoveloc.y + 288 && mousePos.x > pickermoveloc.x && mousePos.x < pickermoveloc.x + 288) || mousemovingpicker) {
                mousemovingpicker = true;
                pickermoveloc.x = mousePos.x - Offset.x;
                pickermoveloc.y = mousePos.y - Offset.y;
            }
        }
        else {
            mousemovingpicker = false;
        }
    }
    sf::Vector2f PickerPos()
    {
        return pickerMenu.getPosition();
    }

    void MouseRectangleOffset(const sf::Event::MouseButtonEvent& event)
    {
        sf::Vector2f pickermenu = pickerMenu.getPosition();


        if (event.x < pickermenu.x + PICKER_MENU_WIDTH && event.y < pickermenu.y + PICKER_MENU_HEIGHT && event.x > pickermenu.x && event.y > pickermenu.y) {
            Offset.x = event.x - pickermoveloc.x;
            Offset.y = event.y - pickermoveloc.y;
        }

    }

    void PickerMText(std::string text, sf::RenderWindow& window, int posOnX = 0, int posOnY = 0, int thickness = 0, sf::Color OutColor = sf::Color::Black)
    {
        pickerTEXT.setString(text);
        pickerTEXT.setOutlineThickness(thickness);
        pickerTEXT.setOutlineColor(OutColor);
        pickerTEXT.setPosition(pickerMenu.getPosition().x + posOnX, pickerMenu.getPosition().y + posOnY);
        window.draw(pickerTEXT);
    }
    void MouseNotHeld()
    {
        mousemovingpicker = false;
    }

    bool ButtonForPicker(const sf::Event::MouseButtonEvent& event, int Button_LocX = 0, int Button_LocY = 0, int Button_width = 50, int Button_height = 30)
    {
        sf::Vector2f pickermenu = pickerMenu.getPosition();
        if (event.x < pickermenu.x + Button_LocX + Button_width && event.x > pickermenu.x + Button_LocX && event.y < pickermenu.y + Button_LocY + Button_height && event.y > pickermenu.y + Button_LocY)
        {
            return true;
        }
        return false;
    }
};

class TileBoard
{
private:
    std::fstream game;
    std::vector<std::vector<sf::RectangleShape>> myguy;
    sf::IntRect rect;
    sf::Texture tex;
public:
    TileBoard()
    {
        tex.loadFromFile("assets/set.png");
        myguy.resize(80);
        rect.height = 16;
        rect.width = 16;
        rect.top = 48;
        rect.left = 48;
        for (int i = 0; i < 80; i++)
        {
            myguy[i].resize(80);
            for (int j = 0; j < 80; j++) {
                myguy[i][j].setTextureRect(rect);
                myguy[i][j].setSize(sf::Vector2f(GRID_CELL_SIZE, GRID_CELL_SIZE));
                myguy[i][j].setFillColor(sf::Color(0, 0, 0));
                myguy[i][j].setPosition(GRID_CELL_SIZE * i, GRID_CELL_SIZE * j);
            }
        }
    }
    void Draw(sf::RenderWindow& Target)
    {
        for (int i = 0; i < 80; i++)
        {
            for (int j = 0; j < 80; j++) {
                Target.draw(myguy[i][j]);
            }
        }
    }

    void PickedTex(sf::Vector2i material, const sf::Vector2f& PickerPos, sf::RenderWindow& window, bool& movingpicker)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (!(movingpicker))
        {
            //this if statement makes sure that we only draw inside the game window
            if (!(mousePos.x < 0 || mousePos.x > WINDOW_WIDTH || mousePos.y < 0 || mousePos.y > WINDOW_HEIGHT)) {
                if (!(mousePos.x < PickerPos.x + PICKER_MENU_WIDTH && mousePos.y < PickerPos.y + PICKER_MENU_HEIGHT && mousePos.x > PickerPos.x && mousePos.y > PickerPos.y))
                {
                    rect.top = material.y * GRID_CELL_SIZE;
                    rect.left = material.x * GRID_CELL_SIZE;
                    int x = mousePos.x / GRID_CELL_SIZE;
                    int y = mousePos.y / GRID_CELL_SIZE;
                    myguy[x][y].setTextureRect(rect);
                    myguy[x][y].setTexture(&tex);
                    myguy[x][y].setFillColor(sf::Color::White);

                }
            }
        }
    }

    void LoadMapEditor()
    {
        int xp, yp;
        xp = yp = 0;
        game.open("GameSaveFile.txt", std::fstream::in);
        for (int y = 0; y < 80; y++) {
            for (int x = 0; x < 80; x++) {

                //std::cout << xp << " " << yp;
                game >> xp;
                game >> yp;
                rect.top = xp;
                rect.left = yp;
                myguy[y][x].setTextureRect(rect);
                myguy[y][x].setTexture(&tex);
                myguy[y][x].setFillColor(sf::Color::White);

            }
        }
        game.close();
        std::cout << "loading done";
    }
    void SaveMapEditor()
    {
        int xp = 0;
        int yp = 0;
        game.open("GameSaveFile.txt", std::fstream::out);
        for (int y = 0; y < 80; y++) {
            for (int x = 0; x < 80; x++) {
                xp = myguy[y][x].getTextureRect().top;
                yp = myguy[y][x].getTextureRect().left;
                game << xp;
                game << " ";
                game << yp;
                game << " ";
            }
            game << std::endl;
        }
        game.close();
        std::cout << "saving done";
    }
};

int main()
{
    TilePicker picker;
    TileBoard board;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Coffee's Map Editor");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == event.Closed) {
                window.close();
            }

            if (event.type == event.MouseButtonPressed)
            {
                picker.MouseRectangleOffset(event.mouseButton);
                picker.PickingTex(event.mouseButton);

                if (picker.SaveButton(event)) {
                    board.SaveMapEditor();
                }
                if (picker.LoadButton(event)) {
                    board.LoadMapEditor();
                }
            }
        }

        picker.update();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            picker.MovePicker(window);
        }
        else {
            picker.MouseNotHeld();

        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            board.PickedTex(picker.PickedMatterial(), picker.PickerPos(), window, picker.mousemovingpicker);
        }
        window.clear();
        board.Draw(window);
        picker.Drawpicker(window);
        window.display();
    }
    return 0;
}