#include "a2d.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

struct Star {
    std::string name;
    float speed;
};

int main() {
    Graphics gfx;
    Input input;
    Random rand;
    Window winManager(400, 300, "Ananiah2D", "main");
    auto& window = winManager.GetWindow("main");


    gfx.NewFont("fonts/px.ttf", "pixel");
    auto& pixel = gfx.GetFont("pixel");
    gfx.NewText(pixel, "title");
    auto& title = gfx.GetText("title");
    title.setOrigin(gfx.GetTextCenter(title));
    title.setPosition({110.f, 100.f});

    title.setString("Annaiah2d");
    title.setFillColor(sf::Color::White);
    title.setCharacterSize(24);

    const int numStars = 150;
    std::vector<Star> stars;
    stars.reserve(numStars);

    for (int i = 0; i < numStars; ++i) {
        std::string name = "star_" + std::to_string(i);
        float size = rand.Float(1.f, 3.f);
        gfx.NewRect(size, size, name);
        auto& star = gfx.GetRect(name);
        star.setPosition({rand.Float(0.f, 400.f), rand.Float(0.f, 300.f)});
        sf::Color c(rand.Int(0, 255), rand.Int(0, 255), rand.Int(0, 255), rand.Int(80, 200));
        star.setFillColor(c);
        stars.push_back({name, rand.Float(0.05f, 0.3f)});
    }

    while (window.isOpen()) {
        winManager.pollEvents(window);

        window.clear();
        for (auto& s : stars) {
            auto& rect = gfx.GetRect(s.name);
            sf::Vector2f pos = rect.getPosition();
            pos.y += s.speed;
            if (pos.y > 300) {
                pos.y = 0;
                pos.x = rand.Float(0.f, 400.f);
            }
            rect.setPosition(pos);
        }
        for (auto& s : stars)
            window.draw(gfx.GetRect(s.name));
        window.draw(title);
        window.display();
    }
}
