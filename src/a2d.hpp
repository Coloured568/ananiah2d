#ifndef A2D_HPP
#define A2D_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <random>
#include <memory>

// hey so maybe u should start documenting ur stuff :D

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
    void NewRect(float w, float h, const std::string& name) {
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
      sprites.insert({name, sf::Sprite(texture)});
    }

    sf::Sprite& GetSprite(const std::string& name) {
      return sprites.at(name);
    }

    void NewFont(const std::string Filepath, const std::string& name) {
      sf::Font font(Filepath);
      fonts[name] = font;
    }

    sf::Font& GetFont(const std::string& font) {
      return fonts.at(font);
    }

    void NewText(const sf::Font font, const std::string name) {
      texts.insert({name, sf::Text(font)});
    }

    sf::Text& GetText(const std::string& name) {
      return texts.at(name);
    }

    sf::Vector2f GetTextCenter(const sf::Text& text)
    {
        sf::FloatRect bounds = text.getLocalBounds();
        return {
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
        };
    }

    void NewTriangle(float size, const std::string& name) {
        sf::ConvexShape tri;
        tri.setPointCount(3);
        tri.setPoint(0, {0.f, size});
        tri.setPoint(1, {size / 2.f, 0.f});
        tri.setPoint(2, {size, size});
        triangles[name] = tri;
    }

    sf::ConvexShape& GetTriangle(const std::string& name) {
        return triangles.at(name);
    }

private:
    std::unordered_map<std::string, sf::RectangleShape> rectangles;
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Sprite> sprites;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::Text> texts;
    std::unordered_map<std::string, sf::ConvexShape> triangles;
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

class Audio {
public:
    void NewAudio(const std::string& filepath, const std::string& name) {
        auto music = std::make_unique<sf::Music>();
        if (!music->openFromFile(filepath)) {
            throw std::runtime_error("Failed to open audio file: " + filepath);
        }
        audios[name] = std::move(music);
        filepaths[name] = filepath;
    }

    sf::Music& GetAudio(const std::string& name) {
        return *audios.at(name);
    }

    std::string GetFilepath(const std::string& name) {
      return filepaths.at(name);
    }

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> audios;
    std::unordered_map<std::string, std::string> filepaths;
};

class Random {
public:
    Random()
        : rng(std::random_device{}()) {}

    float Float(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }

    int Int(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    bool Chance(float probability) {
        std::bernoulli_distribution dist(probability);
        return dist(rng);
    }

private:
    std::mt19937 rng;
};

class Camera {
public:
    float x, y;
    float fov; // This is effectively the zoom factor

    Camera(float px = 0, float py = 0, float zoom = 1.f)
        : x(px), y(py), fov(zoom) {}

    void apply(sf::RenderWindow& window) {
        sf::View view;
        view.setCenter({x, y}m );

        // Zoom: SFML zoom multiplies the size of the view
        view.setSize(window.getDefaultView().getSize());
        view.zoom(fov);

        window.setView(view);
    }

    void setPosition(float posX, float posY) {
        x = posX;
        y = posY;
    }

    void setZoom(float d) {
        fov = d;
    }
};


#endif
