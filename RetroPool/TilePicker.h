#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

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

    TilePicker();

    sf::Color IndicatorButton(bool on, sf::Color Color, sf::Color indicatorColor);

    sf::Vector2f PickerPos();

    void Drawpicker(sf::RenderWindow& Target);

    bool LoadButton(const sf::Event& event);

    bool SaveButton(const sf::Event& event);

    void update();

    bool PickingTex(const sf::Event::MouseButtonEvent& event);

    sf::Vector2i PickedMatterial();

    void MovePicker(sf::RenderWindow& Target);

    void MouseRectangleOffset(const sf::Event::MouseButtonEvent& event);

    void PickerMText(std::string text, sf::RenderWindow& window, int posOnX, int posOnY, int thickness, sf::Color OutColor);

    void MouseNotHeld();

    bool ButtonForPicker(const sf::Event::MouseButtonEvent& event, int Button_LocX, int Button_LocY , int Button_width, int Button_height);
    
};