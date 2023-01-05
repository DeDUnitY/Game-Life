#include <SFML/Graphics.hpp>
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
    X_Y window_size = {600,600 };
    X_Y block_size = { 20,20 };
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Life Game");
    window.setFramerateLimit(5);
    sf::RectangleShape shape(sf::Vector2f(block_size.x, block_size.y));
    shape.setFillColor(sf::Color::White);
    sf::RectangleShape gridx(sf::Vector2f(window_size.x, 2));
    gridx.setFillColor(sf::Color(130,130,130));
    sf::RectangleShape gridy(sf::Vector2f(2, window_size.y));
    gridy.setFillColor(sf::Color(130, 130, 130));
    int temp = 0;
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

    bool flag_stop = false;

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
                flag_stop = !flag_stop;
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
        if (event.mouseButton.button == 1) {
            lifes[event.mouseButton.x / block_size.x + 1][event.mouseButton.y / block_size.y + 1] = 1;
        }
        if (event.mouseButton.button == 0) {
            lifes[event.mouseButton.x / block_size.x + 1][event.mouseButton.y / block_size.y + 1] = 0;
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
            for (int i = 0; i < window_size.x/block_size.x+1; i++) {
                gridy.setPosition(i * block_size.x-1, 0);
                window.draw(gridy);
                
            }
            for (int i = 0; i < window_size.y / block_size.y + 1; i++) {
                gridx.setPosition(0, i * block_size.y - 1);
                window.draw(gridx);

            }
            window.display();
    }

    return 0;
}