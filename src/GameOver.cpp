#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "GameOver.hpp"
#include "GamePlay.hpp"

GameOver::GameOver(std::shared_ptr<Context> &context) 
    : m_context(context), m_isRetryButtonSelected(true),
      m_isRetryButtonPressed(false), m_isExitButtonSelected(false), 
      m_isExitButtonPressed(false) {}

GameOver::~GameOver() {
}

void GameOver::Init() {
// Importing and setting textures and fonts:
    // adding fonts and textures to AssetMan asset map
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    m_context->m_assets->AddFont(CASUAL_FONT, "assets/fonts/DancingScript-VariableFont_wght.ttf");
    m_context->m_assets->AddTexture(GAME_OVER_BG, "assets/textures/GameOver.jpg");

// Setting the textures and fonts on the output window:
    // loading background image for main menu
    m_backGroundSprite.setTexture(m_context->m_assets->GetTexture(GAME_OVER_BG));
    m_backGroundSprite.setScale(
        (float)m_context->m_window->getSize().x / 
        (float)m_context->m_assets->GetTexture(GAME_OVER_BG).getSize().x ,
                    (float)m_context->m_window->getSize().y / 
                    (float)m_context->m_assets->GetTexture(GAME_OVER_BG).getSize().y);

    // Title
    // setting the font on the output window
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString("You Lost!");
    m_gameOverTitle.setFillColor(sf::Color::Red);
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width/2,     // setting new origin
                          m_gameOverTitle.getLocalBounds().height/2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x /2,
                            m_context->m_window->getSize().y /2 - 150.f);

    // Retry Button
    // setting the font on the output window
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString("Retry");
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width/2,     // setting new origin
                          m_retryButton.getLocalBounds().height/2);
    m_retryButton.setPosition(m_context->m_window->getSize().x /2 - 40.f,
                            m_context->m_window->getSize().y /2 + 120.f);
    m_retryButton.setCharacterSize(20);

    // Exit Button
    // setting the font on the output window
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width/2,     // setting new origin
                          m_exitButton.getLocalBounds().height/2);
    m_exitButton.setPosition(m_context->m_window->getSize().x /2  + 60.f,
                            m_context->m_window->getSize().y /2 + 120.f);
    m_exitButton.setCharacterSize(20);

    // Developer's name
    // setting the font on the output window
    m_developerName.setFont(m_context->m_assets->GetFont(CASUAL_FONT));
    m_developerName.setString("made by M. Haris Mujeeb");
    m_developerName.setFillColor(sf::Color::Red);
    m_developerName.setPosition(m_context->m_window->getSize().x/2 + 25.f,
                            m_context->m_window->getSize().y /2 + 150.f);
    m_developerName.setCharacterSize(20);
}


void GameOver::ProcessInput(){
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::KeyPressed){
            switch (event.key.code)
            {
            case sf::Keyboard::Up: {
                if(!m_isRetryButtonSelected){
                    m_isRetryButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Left: {
                if(!m_isRetryButtonSelected){
                    m_isRetryButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down: {
                if(!m_isExitButtonSelected){
                    m_isRetryButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Right: {
                if(!m_isExitButtonSelected){
                    m_isRetryButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return: {
                m_isRetryButtonPressed = false;
                m_isExitButtonPressed = false;
                if(m_isRetryButtonSelected) {
                    m_isRetryButtonPressed = true;
                }
                else {
                    m_isExitButtonPressed = true;
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

void GameOver::Update(sf::Time deltaTime){
    if(m_isRetryButtonSelected){
        m_retryButton.setFillColor(sf::Color::Blue);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else {
        m_exitButton.setFillColor(sf::Color::Blue);
        m_retryButton.setFillColor(sf::Color::White);
    }

    if(m_isRetryButtonPressed){
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if(m_isExitButtonPressed){
        m_context->m_window->close();
    }
}

void GameOver::Draw(){
      m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_backGroundSprite);
    m_context->m_window->draw(m_gameOverTitle);
    m_context->m_window->draw(m_retryButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->draw(m_developerName);
    m_context->m_window->display();
    
    sf::Event event;
        while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
    }
}