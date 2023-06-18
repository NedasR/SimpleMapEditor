#include "TilePicker.h"

    TilePicker::TilePicker()
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

    sf::Color TilePicker::IndicatorButton(bool on, sf::Color Color = sf::Color::Black, sf::Color indicatorColor = sf::Color(20, 163, 57))
    {
        return on ? indicatorColor : Color;
    }

    void TilePicker::Drawpicker(sf::RenderWindow& Target)
    {
        pickerMenu.setPosition(pickermoveloc.x - 16, pickermoveloc.y - 32);
        palette.setPosition(pickermoveloc.x, pickermoveloc.y);
        Target.draw(pickerMenu);
        Target.draw(palette);

        PickerMText("Material Picker", Target, 20, 6, 4, sf::Color(57, 68, 150));
        PickerMText("Load", Target, 210, 6, 6, IndicatorButton(Loading));
        PickerMText("Save", Target, 260, 6, 6, IndicatorButton(Saving));
    }

    bool TilePicker::LoadButton(const sf::Event& event) {
        bool output = ButtonForPicker(event.mouseButton, 200, 0, 50, 30);

        if (output) {
            Time.restart();
            Loading = true;
        }

        return output;
    }

    bool TilePicker::SaveButton(const sf::Event& event) {

        bool output = ButtonForPicker(event.mouseButton, 254, 0, 46, 30);

        if (output) {
            Time.restart();
            Saving = true;
        }

        return output;
    }

    void TilePicker::update() {
        if (Time.getElapsedTime() >= sf::seconds(1)) {
            Loading = Saving = false;
        }
    }

    bool TilePicker::PickingTex(const sf::Event::MouseButtonEvent& event)
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
    sf::Vector2i TilePicker::PickedMatterial()
    {
        return pickedTex;
    }

    void TilePicker::MovePicker(sf::RenderWindow& Target)
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
    sf::Vector2f TilePicker::PickerPos()
    {
        return pickerMenu.getPosition();
    }

    void TilePicker::MouseRectangleOffset(const sf::Event::MouseButtonEvent& event)
    {
        sf::Vector2f pickermenu = pickerMenu.getPosition();


        if (event.x < pickermenu.x + PICKER_MENU_WIDTH && event.y < pickermenu.y + PICKER_MENU_HEIGHT && event.x > pickermenu.x && event.y > pickermenu.y) {
            Offset.x = event.x - pickermoveloc.x;
            Offset.y = event.y - pickermoveloc.y;
        }

    }

    void TilePicker::PickerMText(std::string text, sf::RenderWindow& window, int posOnX = 0, int posOnY = 0, int thickness = 0, sf::Color OutColor = sf::Color::Black)
    {
        pickerTEXT.setString(text);
        pickerTEXT.setOutlineThickness(thickness);
        pickerTEXT.setOutlineColor(OutColor);
        pickerTEXT.setPosition(pickerMenu.getPosition().x + posOnX, pickerMenu.getPosition().y + posOnY);
        window.draw(pickerTEXT);
    }
    void TilePicker::MouseNotHeld()
    {
        mousemovingpicker = false;
    }

    bool TilePicker::ButtonForPicker(const sf::Event::MouseButtonEvent& event, int Button_LocX = 0, int Button_LocY = 0, int Button_width = 50, int Button_height = 30)
    {
        sf::Vector2f pickermenu = pickerMenu.getPosition();
        if (event.x < pickermenu.x + Button_LocX + Button_width && event.x > pickermenu.x + Button_LocX && event.y < pickermenu.y + Button_LocY + Button_height && event.y > pickermenu.y + Button_LocY)
        {
            return true;
        }
        return false;
    }

