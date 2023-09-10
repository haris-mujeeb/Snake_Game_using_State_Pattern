#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "MainMenu.hpp"
#include "GamePlay.hpp"

MainMenu::MainMenu(std::shared_ptr<Context> &context) 
    : m_context(context), m_isPlayButtonSelected(true),
      m_isPlayButtonPressed(false), m_isExitButtonSelected(false), 
      m_isExitButtonPressed(false) {}
    
MainMenu::~MainMenu() {}

void MainMenu::Init() {

// Importing and setting textures and fonts:
    // adding fonts and textures to AssetMan asset map
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    m_context->m_assets->AddFont(CASUAL_FONT, "assets/fonts/DancingScript-VariableFont_wght.ttf");
    m_context->m_assets->AddTexture(MAIN_MENU_BG, "assets/textures/main1.jpg");

    // Setting the textures and fonts on the output window:
    // loading background image for main menu
    m_backGroundSprite.setTexture(m_context->m_assets->GetTexture(MAIN_MENU_BG));
    m_backGroundSprite.setScale(
        (float)m_context->m_window->getSize().x / 
        (float)m_context->m_assets->GetTexture(MAIN_MENU_BG).getSize().x ,
                    (float)m_context->m_window->getSize().y / 
                    (float)m_context->m_assets->GetTexture(MAIN_MENU_BG).getSize().y);

    // Title
    // setting the font on the output window
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("Snake Game");
    m_gameTitle.setFillColor(sf::Color::White);
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width/2,     // setting new origin
                          m_gameTitle.getLocalBounds().height/2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x /2,
                            m_context->m_window->getSize().y /2 - 150.f);

    // Play Button
    // setting the font on the output window
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_playButton.setString("Play");
    m_playButton.setOrigin(m_playButton.getLocalBounds().width/2,     // setting new origin
                          m_playButton.getLocalBounds().height/2);
    m_playButton.setPosition(m_context->m_window->getSize().x /2,
                            m_context->m_window->getSize().y /2 - 25.f);
    m_playButton.setCharacterSize(20);

// Exit Button:
    // setting the font on the output window
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width/2,     // setting new origin
                          m_exitButton.getLocalBounds().height/2);
    m_exitButton.setPosition(m_context->m_window->getSize().x /2,
                            m_context->m_window->getSize().y /2 + 25.f);
    m_exitButton.setCharacterSize(20);

// Developer's name:
    // setting the font on the output window
    m_developerName.setFont(m_context->m_assets->GetFont(CASUAL_FONT));
    m_developerName.setString("made by M. Haris Mujeeb");
    // m_developerName.setOrigin(m_developerName.getLocalBounds().width/2,     // setting new origin
                        //   m_developerName.getLocalBounds().height/2);
    m_developerName.setPosition(m_context->m_window->getSize().x/2 + 25.f,
                            m_context->m_window->getSize().y /2 + 125.f);
    m_developerName.setCharacterSize(20);
}

void MainMenu::ProcessInput(){
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::KeyPressed){
            switch (event.key.code)
            {
            case sf::Keyboard::Up: {
                if(!m_isPlayButtonSelected){
                    m_isPlayButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down: {
                if(!m_isExitButtonSelected){
                    m_isPlayButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return: {
                m_isPlayButtonPressed = false;
                m_isExitButtonPressed = false;
                if(m_isPlayButtonSelected) {
                    m_isPlayButtonPressed = true;
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

void MainMenu::Update(sf::Time deltaTime){
    if(m_isPlayButtonSelected){
        m_playButton.setFillColor(sf::Color::Yellow);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else {
        m_exitButton.setFillColor(sf::Color::Yellow);
        m_playButton.setFillColor(sf::Color::White);
    }

    if(m_isPlayButtonPressed){
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if(m_isExitButtonPressed){
        m_context->m_window->close();
    }
}

void MainMenu::Draw(){  
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_backGroundSprite);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
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