#include <time.h>
#include <stdlib.h>

#include <SFML/Window/Event.hpp>

#include "GamePlay.hpp"
#include "GameOver.hpp"

GamePlay::GamePlay(std::shared_ptr<Context> &Context) : 
    m_context(Context), 
    m_snakeDirection({16.f, 0.f}),
    m_elapsedTime(sf::Time::Zero) {
        srand(time(nullptr));
}

GamePlay::~GamePlay() {

}


void GamePlay::Init() {
    m_context->m_assets->AddTexture(SNAKE, "assets/textures/green.png", true);
    m_context->m_assets->AddTexture(GRASS, "assets/textures/grass.png", true);
    m_context->m_assets->AddTexture(FOOD, "assets/textures/food.png");
    m_context->m_assets->AddTexture(WALL, "assets/textures/white.png", true);  // wantRepeated is set to true

    // setting Grass textures
    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
    // Todo: import an image instead of sprite
    // sf::Texture texture;
    // texture.loadFromFile("assets/textures/main3.jpg");  // loading background image for main menu
    // sf::Sprite sprite(texture);
    // sprite.setScale((float)m_context->m_window->getSize().x / (float)texture.getSize().x ,
                    // (float)m_context->m_window->getSize().y / (float)texture.getSize().y);
    
    // setting Wall textures
    for (auto& wall : m_walls) {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }
    m_walls[0].setTextureRect({0, 0, 640, 16});  // defining the texture for top wall
    m_walls[1].setTextureRect({0, 0, 16, 368});  // definfing the texture for left wall
    m_walls[2].setTextureRect({0, 0, 16, 368});  // defining the texture for right wall
    m_walls[2].setPosition({640-16, 0});  // definfing position for right wall
    m_walls[3].setTextureRect({0, 0, 640, 16});  // bottom wall
    m_walls[3].setPosition({0, 368-16});  // definfing position for right wall

    // setting Food textures
    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setPosition({640/2, 368/2});

    
    m_snake.Init(m_context->m_assets->GetTexture(SNAKE));
    
  

}

void GamePlay::ProcessInput(){
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::KeyPressed){
            sf::Vector2f newDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up: {
                newDirection = {0.f, -16.f};
                break;
            }
            case sf::Keyboard::Down: {
                newDirection = {0.f, 16.f};
                break;
            }
            case sf::Keyboard::Left: {
                newDirection = {-16.f, 0.f};
                break;
            }
            case sf::Keyboard::Right: {
                newDirection = {16.f, 0.f};
                break;
            }
            default:
                newDirection = m_snakeDirection;  // dir. stays same
                break;
            }
            if(std::abs(newDirection.x) != std::abs(m_snakeDirection.x) ||
               std::abs(newDirection.y) != std::abs(m_snakeDirection.y)){
                m_snakeDirection = newDirection;    
            }
        }
    }   

}

void GamePlay::Update(sf::Time deltaTime) {
    m_elapsedTime += deltaTime;
    if(m_elapsedTime.asSeconds() > 0.075){

        // check if snake hits the wall  
        for (auto& wall : m_walls) {
            if (m_snake.IsON(wall)){
                    m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
                break;
            }
        }

        // check if snake is on food
        if(m_snake.IsON(m_food)) {
            m_snake.Grow(m_snakeDirection);
            // rand gen. of fruit inside the walls
            int x = std::clamp<int>( rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2*16 );
            int y = std::clamp<int>( rand() % m_context->m_window->getSize().y,  16, m_context->m_window->getSize().y - 2*16 );
            m_food.setPosition(x, y);
        }
        else 
            m_snake.Move(m_snakeDirection);
        m_elapsedTime = sf::Time::Zero;
    }
}

void GamePlay::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);
    for (auto& wall : m_walls) {
        m_context->m_window->draw(wall);
    }
    m_context->m_window->draw(m_food);
    m_context->m_window->draw(m_snake);
    m_context->m_window->display();
}

void GamePlay::Pause() {

}

void GamePlay::Start() {
}