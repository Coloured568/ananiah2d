#ifndef A2D_HPP
#define A2D_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

class Input
{
public:
    bool left() const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left); }
    bool right() const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right); }
    bool up() const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up); }
    bool down() const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down); }
    bool escape() const { return sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape); }
};

class Graphics {
public:
    void NewRectangle(float w, float h, const std::string& name) {
        sf::RectangleShape rect({w, h});
        rectangles[name] = rect;  // store it in the map
    }

    sf::RectangleShape& GetRect(const std::string& name) {
        return rectangles.at(name);
    }

    void NewTexture(const std::string& Filepath, const std::string& name) {
        sf::Texture texture;
        if (!texture.loadFromFile(Filepath)) {
            throw std::runtime_error("failed to load texture: " + Filepath);
        }
        textures[name] = std::move(texture);
    }



    sf::Texture& GetTexture(const std::string& name) {
      return textures.at(name);
    }

    void NewSprite(const sf::Texture &texture, const std::string& name) {
      sf::Sprite sprite(texture);
      sprites.insert({name, sf::Sprite(texture)});
    }

    sf::Sprite& GetSprite(const std::string& name) {
      return sprites.at(name);
    }
private:
    std::unordered_map<std::string, sf::RectangleShape> rectangles;
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Sprite> sprites;
};

// add fullscreen support n stuff later
class Window {
public:
    Window(unsigned int w, unsigned int h, const std::string& title, const std::string& name) {
        auto window = std::make_unique<sf::RenderWindow>(sf::VideoMode({w, h}), title);
        windows[name] = std::move(window);
    }

    // usage: window.GetWindow("main")->setFramerateLimit(60);
    sf::RenderWindow& GetWindow(const std::string& name) {
        return *windows.at(name);
    }

    void pollEvents(sf::RenderWindow& window)
    {
        const auto onClose = [&window](const sf::Event::Closed&)
        {
            window.close();
        };

        const auto onKeyPressed = [&window](const sf::Event::KeyPressed& e)
        {
            if (e.scancode == sf::Keyboard::Scan::Escape)
                window.close();
        };

        window.handleEvents(onClose, onKeyPressed);
    }

private:
    std::unordered_map<std::string, std::unique_ptr<sf::RenderWindow>> windows;
};

#endif
