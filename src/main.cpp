#include "a2d.hpp"

Input input;

Graphics gfx;

float speed = 5.0f;

int main()
{
    Window window(400, 300, "Annaiah2d", "main");

    window.GetWindow("main").setFramerateLimit(60);

    gfx.NewTexture("textures/yab.png", "yab");
    gfx.NewTexture("textures/nyn.jpg", "mylan");
    gfx.NewSprite(gfx.GetTexture("yab"), "bg");
    gfx.NewSprite(gfx.GetTexture("mylan"), "player");

    gfx.GetSprite("bg").setScale({
        400.0f / gfx.GetSprite("bg").getTexture().getSize().x,
        400.0f / gfx.GetSprite("bg").getTexture().getSize().y
    });

    gfx.GetSprite("player").setScale({
        50.0f / gfx.GetSprite("player").getTexture().getSize().x,
        50n.0f / gfx.GetSprite("player").getTexture().getSize().y
    });

    while (window.GetWindow("main").isOpen())
    {
        window.GetWindow("main").setSize(sf::Vector2u(400, 400));

        window.pollEvents(window.GetWindow("main"));

        if (input.escape()) {
            window.GetWindow("main").close();
        }

         if(input.right()) {
            gfx.GetSprite("player").move({speed, 0.0f});
         }

        if(input.left()) {
          gfx.GetSprite("player").move({-speed, 0.0f});
        }

        if(input.up()) {
          gfx.GetSprite("player").move({0.0f, -speed});
        }

         if(input.down()) {
           gfx.GetSprite("player").move({0.0f, speed});
         }

        window.GetWindow("main").clear();

        window.GetWindow("main").draw(gfx.GetSprite("bg"));

        window.GetWindow("main").draw(gfx.GetSprite("player"));

        window.GetWindow("main").display();
    }
}
