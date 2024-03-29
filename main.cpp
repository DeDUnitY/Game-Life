﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>

struct X_Y
{
    int x;
    int y;
};
// min + (rand() % static_cast<int>(max - min + 1))
int main()
{
    srand(time(NULL));
    std::cout << "Input, X window size >= 600 and Y window size >= 600, through Enter\nStock 600 x 600\n";
    int x, y;
    std::cin >> x >> y;
    if (x < 600) 
        x = 600;
    if (y < 600)
        y = 600;
    X_Y window_size = { x,y };
    std::cout << "Input, X block size and Y block size through Enter\nStock 10 x 10\n";
    std::cin >> x >> y;
    if (x < 1)
        x = 1;
    if (y < 1)
        y = 1;
    X_Y block_size = { x,y };
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Life Game");
    window.setFramerateLimit(5);
    sf::RectangleShape shape(sf::Vector2f(block_size.x, block_size.y));
    shape.setFillColor(sf::Color::White);
    sf::RectangleShape gridx(sf::Vector2f(window_size.x, 2));
    gridx.setFillColor(sf::Color(130,130,130));
    sf::RectangleShape gridy(sf::Vector2f(2, window_size.y));
    gridy.setFillColor(sf::Color(130, 130, 130));
    int temp = 0;
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text Count;
    Count.setFont(font);
    Count.setString("\"SPACE\" - pause(Draw Mode)\n\"Left Mouse Button\" - Delite block\n\"Right Mouse Button\" - Create block\n\"R\" - Restart\n\"C\" - Clear\n\"G\" -  Off grid");
    Count.setCharacterSize(25);
    Count.setPosition(window_size.x / 2-250, window_size.y / 2-150);
    Count.setStyle(sf::Text::Bold);
    Count.setColor(sf::Color::White);
    std::vector<std::vector<int>> lifes;
    lifes.resize(window_size.x/block_size.x + 2);
    for (int i = 0; i < lifes.size(); i++) {
        lifes[i].resize(window_size.y / block_size.y+2);
    }
    for (int i = 1; i < lifes.size()-1; i++) {
        for (int j = 1; j < lifes[i].size()-1; j++) {
            lifes[i][j] = rand() % 2;
        }
    }
    for (int i = 0; i < lifes.size(); i+=lifes.size()) {
        for (int j = 0; j < lifes[i].size(); j += lifes[0].size()) {
            lifes[i][j] = 0;
        }
    }
    std::vector<std::vector<int>> lifesT;
    lifesT.resize(window_size.x / block_size.x + 2);
    for (int i = 0; i < lifesT.size(); i++) {
        lifesT[i].resize(window_size.y / block_size.y + 2);
    }
    bool flag_grid = true;
    bool flag_stop = true;
    while (flag_stop && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
                flag_stop = false;
            
        }
        window.draw(Count);
        window.display();
    }

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
                flag_stop = !flag_stop;
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::G))
                flag_grid = !flag_grid;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                for (int i = 0; i < lifes.size(); i ++) {
                    for (int j = 0; j < lifes[i].size(); j ++) {
                        lifes[i][j] = 0;
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                for (int i = 1; i < lifes.size() - 1; i++) {
                    for (int j = 1; j < lifes[i].size() - 1; j++) {
                        lifes[i][j] = rand() % 2;
                    }
                }
            }
        }
        if (0 < event.mouseButton.x / block_size.x + 1 && 0 < event.mouseButton.y / block_size.y + 1 ) {
            std::cout << event.mouseButton.x << std::endl;
            if (event.mouseButton.button == 1) {
                lifes[event.mouseButton.x / block_size.x + 1][event.mouseButton.y / block_size.y + 1] = 1;
            }
            if (event.mouseButton.button == 0) {
                std::cout << event.mouseButton.x << std::endl;
                lifes[event.mouseButton.x / block_size.x + 1][event.mouseButton.y / block_size.y + 1] = 0;
            }
        }
        
        if (!flag_stop) {
            temp = 0;
            for (int i = 1; i < lifes.size() - 1; i++) {
                for (int j = 1; j < lifes[i].size() - 1; j++) {
                    temp = lifes[i - 1][j - 1] + lifes[i][j - 1] + lifes[i + 1][j - 1] + lifes[i - 1][j] + lifes[i + 1][j] + lifes[i - 1][j + 1] + lifes[i][j + 1] + lifes[i + 1][j + 1];
                    if (lifes[i][j] == 0 && temp == 3) lifesT[i][j] = true;
                    else if (temp > 3 || temp < 2) lifesT[i][j] = false;
                    else lifesT[i][j] = lifes[i][j];
                }
            }
            lifes = lifesT;
        }
        
            window.clear();//sf::Color(255,255,255));
            for (int i = 1; i < lifes.size() - 1; i++) {
                for (int j = 1; j < lifes[i].size() - 1; j++) {
                    if (lifes[i][j]) {
                        shape.setPosition((i - 1) * block_size.x, (j - 1) * block_size.y);
                        window.draw(shape);
                    }
                }
            }
            if (block_size.y > 3 && flag_grid)
            for (int i = 0; i < window_size.x/block_size.x+1; i++) {
                gridy.setPosition(i * block_size.x-1, 0);
                window.draw(gridy);
                
            }
            if (block_size.x > 3 && flag_grid)
            for (int i = 0; i < window_size.y / block_size.y + 1; i++) {
                gridx.setPosition(0, i * block_size.y - 1);
                window.draw(gridx);

            }
            window.display();
    }

    return 0;
}