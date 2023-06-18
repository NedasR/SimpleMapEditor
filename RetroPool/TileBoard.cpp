#include "TileBoard.h"

TileBoard::TileBoard()
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

void TileBoard::Draw(sf::RenderWindow& Target)
{
    for (int i = 0; i < 80; i++)
    {
        for (int j = 0; j < 80; j++) {
            Target.draw(myguy[i][j]);
        }
    }
}

void TileBoard::PickedTex(sf::Vector2i material, const sf::Vector2f& PickerPos, sf::RenderWindow& window, bool& movingpicker)
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

void TileBoard::LoadMapEditor()
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

void TileBoard::SaveMapEditor()
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
