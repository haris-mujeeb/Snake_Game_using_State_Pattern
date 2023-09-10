#pragma once

#include <memory>  // for shared pointer
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"

class GameOver : public Engine::State {
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameOverTitle;
    sf::Text m_retryButton;
    sf::Text m_exitButton;
    sf::Text m_developerName;
    sf::Sprite m_backGroundSprite;

    bool m_isRetryButtonSelected;
    bool m_isRetryButtonPressed;

    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

public:
    GameOver(std::shared_ptr<Context> &context);
    ~GameOver();
    void Init() override;   // overriding the virtual function from the base class.
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};