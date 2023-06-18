#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "TileBoard.h"
#include "TilePicker.h"

#define GRID_CELL_SIZE 16
#define PICKER_ONE_LINE_LENTGH 10
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define PICKER_MENU_WIDTH 320
#define PICKER_MENU_HEIGHT 336

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
