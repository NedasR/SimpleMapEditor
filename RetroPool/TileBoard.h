#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#define GRID_CELL_SIZE 16
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define PICKER_MENU_WIDTH 320
#define PICKER_MENU_HEIGHT 336

class TileBoard
{
private:
    std::fstream game;
    std::vector<std::vector<sf::RectangleShape>> myguy;
    sf::IntRect rect;
    sf::Texture tex;
public:
    TileBoard();

    void Draw(sf::RenderWindow& Target);

    void PickedTex(sf::Vector2i material, const sf::Vector2f& PickerPos, sf::RenderWindow& window, bool& movingpicker);

    void LoadMapEditor();
    
    void SaveMapEditor();

};