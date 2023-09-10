#pragma once
#include <memory>  // for shared pointer

#include <SFML/Graphics/Sprite.hpp>

#include <array>

#include "State.hpp"
#include "Game.hpp"
#include "Snake.hpp"


class GamePlay : public Engine::State {
private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_grass;
    sf::Sprite m_food;
    std::array<sf::Sprite, 4> m_walls;
    Snake m_snake;
    sf::Vector2f m_snakeDirection;
    sf::Time m_elapsedTime;
    
public:
    GamePlay(std::shared_ptr<Context> &Context);
    ~GamePlay();
    virtual void Init() override;
    virtual void ProcessInput() override;
    virtual void Update(sf::Time deltaTime) override;
    virtual void Draw() override;
    virtual void Pause() override;
    virtual void Start() override;
};