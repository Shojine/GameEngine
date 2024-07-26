#include "SpaceGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Game.h"
#include "GameData.h"
#include "Enemy.h"
#include "Pickup.h"
#include "Font.h"
#include <string>
//#include "Text.h"

bool SpaceGame::Initialize()
{
    m_scene = new Scene(this);
    m_font = new Font();
    m_font->Load("ArcadeClassic.ttf", 20);
    
    m_fontLarge = new Font();
    m_fontLarge->Load("ArcadeClassic.ttf", 72);

    m_textScore = new Text(m_font);
    m_textLives = new Text(m_font);
    m_textRound = new Text(m_font);
    m_textTitle = new Text(m_fontLarge);

    return true;
}

void SpaceGame::Shutdown()
{

}

void SpaceGame::Update(float dt)
{
    switch (m_state)
    {
    case SpaceGame::eState::Title:
       
        if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
        {
            m_state = eState::StartGame;
        }
        break;
    case SpaceGame::eState::StartGame:
       
        m_lives = 3;
        m_score = 0;
        m_state = eState::StartLevel;
        break;
    case SpaceGame::eState::StartLevel:
    {
        m_scene->RemoveAll();
        Transform transform{ { g_engine.GetRenderer().GetWidth() / 2, g_engine.GetRenderer().GetHeight() / 2}, 0, 2 };
        Model* model = new Model{ GameData::shipPoints, Color{0,1,1} };
        auto player = std::make_unique<Player>(randomf(300, 500), transform, model);
        player->SetDamping(2.0f);
        player->SetTag("Player");
        m_scene->AddActor(std::move(player));
       
    }
    m_spawnTime = 10;
    m_spawnTimer = m_spawnTime;
    m_roundCounter = 0;
    m_enemyCount = 1;

        m_state = eState::Game;
        break;
    case SpaceGame::eState::Game:
        m_spawnTimer -= dt;
       
        if(m_spawnTimer <= 0)
        {
            m_spawnTime -= 0.2f;
            m_spawnTime = Math::Max(m_spawnTime,0.5f);
            m_spawnTimer = m_spawnTime;
        //create enemy

            m_roundCounter += 1;
            // every 5 rounds it should add an enemy more
            if (m_roundCounter % 5 == 0)
            {
                m_enemyCount += 1;
            }
            for (int i = 0; i < m_enemyCount; i++)
            {
                auto* enemyModel = new Model{ GameData::shipPoints, Color{1,0,0} };
                auto enemy = std::make_unique<Enemy>(100.0f, Transform{ {random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight())},0,2 }, enemyModel);
                enemy->SetDamping(1.0f);
                enemy->SetTag("Enemy");
                m_scene->AddActor(std::move(enemy));
            }

        //create pickup
        auto* pickupModel = new Model{ GameData::pickupPoints, Color{1,0,1} };
        auto pickup = std::make_unique<Pickup>(Transform{ {random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight())},0,2 }, pickupModel);
        pickup->SetDamping(1.0f);
        pickup->SetTag("Pickup");
        m_scene->AddActor(std::move(pickup));


       
        


        }


        break;
    case SpaceGame::eState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
        m_state = eState::StartLevel;
        }
        break;
    case SpaceGame::eState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
        m_state = eState::Title;
        }
        break;
    default:
        break;
    }

    m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
    //Game title
    switch (m_state)
    {
    case SpaceGame::eState::Title:
        m_textTitle->Create(renderer, "Pew Pew", Color{ 0, 1, 0, 1 });
        m_textTitle->Draw(renderer, 260, 300);

        break;                                                                                                                                                                                                                                                     
    case SpaceGame::eState::GameOver:
        m_textTitle->Create(renderer, "Game Over", Color{ 1, 0, 0, 1 });
        m_textTitle->Draw(renderer, 260, 300);
        break;
    }

    std::string text = "Score" + std::to_string(m_score);
    m_textScore->Create(renderer, text, { 0,1,0,1 });
    m_textScore->Draw(renderer, 20, 20);

    text = "Lives" + std::to_string(m_lives);
    m_textLives->Create(renderer, text, { 0,1,0,1 });
    m_textLives->Draw(renderer, renderer.GetWidth() - 100, 20);

    text = "Round" + std::to_string(m_roundCounter);
    m_textRound->Create(renderer, text, { 0,1,0,1 });
    m_textRound->Draw(renderer, renderer.GetWidth() / 2, 20);

    m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    m_lives--;
    m_state = (m_lives == 0 ) ? eState::GameOver : eState::PlayerDead;
    m_stateTimer = 3;
    
}
