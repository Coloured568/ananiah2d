#include <iostream>
#include <chrono>
#include <thread>

#include "a2d.hpp"

Input input;

Graphics gfx;

float speed = 5.0f;

int main()
{
    Window window(400, 300, "Annaiah2d", "main");
    bool splash = true;

    window.GetWindow("main").setFramerateLimit(60);

    gfx.NewFont("fonts/px.ttf", "pixel");
    gfx.NewText(gfx.GetFont("pixel"), "title");

    gfx.GetText("title").setString("Annaiah2d");
    gfx.GetText("title").setFillColor(sf::Color::White);
    gfx.GetText("title").setCharacterSize(24);

    auto& title = gfx.GetText("title");
    title.setOrigin(gfx.GetTextCenter(title));
    title.setPosition({200.f, 100.f});

    gfx.NewRectangle(50, 50, "player");

    while (window.GetWindow("main").isOpen())
    {
        window.GetWindow("main").setSize(sf::Vector2u(400, 400));

        window.pollEvents(window.GetWindow("main"));

        while(splash == true) {
          window.GetWindow("main").clear();
          window.GetWindow("main").draw(gfx.GetText("title"));
          window.GetWindow("main").display();
          std::this_thread::sleep_for(std::chrono::seconds(2));
          splash = false;
        }

        if (input.escape()) {
            window.GetWindow("main").close();
        }

         if(input.right()) {
            gfx.GetRect("player").move({speed, 0.0f});
         }

        if(input.left()) {
          gfx.GetRect("player").move({-speed, 0.0f});
        }

        if(input.up()) {
          gfx.GetRect("player").move({0.0f, -speed});
        }

         if(input.down()) {
           gfx.GetRect("player").move({0.0f, speed});
         }

        window.GetWindow("main").clear();

        window.GetWindow("main").draw(gfx.GetRect("player"));

        window.GetWindow("main").display();
    }
}
