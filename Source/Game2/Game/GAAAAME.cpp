#include "GAAAAME.h"
#include "player.h"
#include "Enemy.h"

#include "FrameWork/FrameWork.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Conponent/Sprite.h"


bool GAAAAME::Init()
{
   
    //Create Font/text Objects
    font = GET_RESOURCE(Twili::Font,"arcadeclassic.ttf", 24);
    font2 = GET_RESOURCE(Twili::Font,"ThaleahFat.ttf", 80);

    m_Scoretext = std::make_unique<Twili::Text>(font);
    m_Scoretext->Create(Twili::g_rend, "Score 0000", Twili::Color{ 1, 0, 1, 1 });

    m_Livestext = std::make_unique<Twili::Text>(font);
    m_Livestext->Create(Twili::g_rend, "Lives:", Twili::Color{ 1, 0, 1, 1 });

    m_Titletext = std::make_unique<Twili::Text>(font2);
    m_Titletext->Create(Twili::g_rend, "Asteroids", Twili::Color{ 1, 1, 1, 1 });

    m_Level1text = std::make_unique<Twili::Text>(font);
    m_Level1text->Create(Twili::g_rend, "Level 1", Twili::Color{ 1, 1, 1, 1 });

    m_Level2text = std::make_unique<Twili::Text>(font);
    m_Level2text->Create(Twili::g_rend, "Level 2", Twili::Color{ 1, 1, 1, 1 });

    m_Level3text = std::make_unique<Twili::Text>(font);
    m_Level3text->Create(Twili::g_rend, "Level 3", Twili::Color{ 1, 1, 1, 1 });

    m_Level4text = std::make_unique<Twili::Text>(font);
    m_Level4text->Create(Twili::g_rend, "Level 4", Twili::Color{ 1, 1, 1, 1 });

    m_Level5text = std::make_unique<Twili::Text>(font);
    m_Level5text->Create(Twili::g_rend, "Level 5", Twili::Color{ 1, 1, 1, 1 });

    m_GOvertext = std::make_unique<Twili::Text>(font2);
    m_GOvertext->Create(Twili::g_rend, "Game Over", Twili::Color{ 1, 1, 1, 1 });

    m_Winnertext = std::make_unique<Twili::Text>(font2);
    m_Winnertext->Create(Twili::g_rend, "You Won!!", Twili::Color{ 1, 1, 1, 1 });

    Twili::g_noise.AddAudio("Jump", "Jump.wav");
    Twili::g_noise.AddAudio("MakeItPop", "MakeItPop.wav");


    m_scene = std::make_unique<Twili::Scene>();
    m_scene->Load("resources.json");
    m_scene->Init();

	return true;
}

void GAAAAME::ShutDown()
{
}

void GAAAAME::Update(float dt)
{
    switch (m_state)
    {
    case GAAAAME::eState::Title:

        if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE))
        {
            m_state = eState::StartGame;
           //m_scene->getActorByName("spaceBackground")->active;
        }
        break;
    case GAAAAME::eState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_state = eState::StartLevel;
        break;
    case GAAAAME::eState::StartLevel:
        m_scene->RemoveAll();
        {
           /* auto weapon = INSTANTIATE(Twili::Weapon, "Rocket");
            weapon->transform = { transform.position, transform.rotation, 1 };
            weapon->Init();
            m_scene->Add(std::move(weapon));*/

            //create player
            auto player = INSTANTIATE(Player, "Player");
            player->transform = { player->transform.position, player->transform.rotation, 6 };
            player->m_game = this;

            player->Init();
            m_scene->Add(std::move(player));
        }
        m_state = eState::Level1;
        break;
    case GAAAAME::eState::Level1:

        m_spawn_timer += dt;
        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;

            auto enemy = INSTANTIATE(Enemy, "Enemy1");
            enemy->transform = { enemy->transform.position, enemy->transform.rotation, 6 };
            enemy->m_game = this;
           
            enemy->Init();
            m_scene->Add(std::move(enemy));
        }
        if (m_score >= 600)
        {
            m_state = eState::Level2;
        }
        break;
    case GAAAAME::eState::Level2: //Add Enemy 2
    {

      /*  for (int i = 0; i < 1; i++) {
            float UpgradePopUp = Twili::randomF(0.0f, 7.0f);
            UpgradePopUp -= dt;
            if (UpgradePopUp <= 0)
            {
               auto powerup = std::make_unique<Player>(0.0f, 0.0f, Twili::Transform{ {Twili::random(Twili::g_rend.getWidth()), Twili::random(Twili::g_rend.getHeight())}, 0, 3});
                powerup->m_tag = "PowerUp";
                powerup->m_game = this;
                m_scene->Add(std::move(powerup));
            }
        }*/
        m_spawn_timer += dt;
        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;
            for (int i = 0; i < 2; i++) {
                auto enemy = INSTANTIATE(Enemy, "Enemy1");
                enemy->transform = { enemy->transform.position, enemy->transform.rotation, 6 };
                enemy->m_game = this;

                enemy->Init();
                m_scene->Add(std::move(enemy));
            }
            auto enemy2 = INSTANTIATE(Enemy, "Enemy2");
            enemy2->transform = { enemy2->transform.position, enemy2->transform.rotation, 6 };
            enemy2->m_game = this;

            enemy2->Init();
            m_scene->Add(std::move(enemy2));
        }
        if (m_score >= 1800)//1800
        {
            m_state = eState::Level3;
        }
    }
    break;
    case GAAAAME::eState::Level3://Add Enemy 3: slower ships but beefier health
    {
       /* for (int i = 0; i < 1; i++) {
            float UpgradePopUp = Twili::randomF(0.0f, 7.0f);
            UpgradePopUp -= dt;
            if (UpgradePopUp <= 0)
            {
                auto powerup = std::make_unique<Player>(0.0f, 0.0f, Twili::Transform{ {Twili::random(Twili::g_rend.getWidth()), Twili::random(Twili::g_rend.getHeight())}, 0, 4});
                powerup->m_tag = "PowerUp2";
                powerup->m_game = this;
                m_scene->Add(std::move(powerup));
            }
        }
        for (int i = 0; i < 1; i++) {
            float UpgradePopUp = Twili::randomF(0.0f, 2.0f);
            UpgradePopUp -= dt;
            if (UpgradePopUp <= 0)
            {
                auto powerup = std::make_unique<Player>(0.0f, 0.0f, Twili::Transform{ {Twili::random(Twili::g_rend.getWidth()), Twili::random(Twili::g_rend.getHeight())}, 0, 3});
                powerup->m_tag = "PowerUp";
                powerup->m_game = this;
                m_scene->Add(std::move(powerup));
            }
        }*/
        m_spawnTime = 4;
        m_spawn_timer += dt;
        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;

            for (int i = 0; i < 4; i++) {
                auto enemy = INSTANTIATE(Enemy, "Enemy1");
                enemy->transform = { enemy->transform.position, enemy->transform.rotation, 6 };
                enemy->m_game = this;

                enemy->Init();
                m_scene->Add(std::move(enemy));
            }
            for (int i = 0; i < 4; i++) {
                auto enemy2 = INSTANTIATE(Enemy, "Enemy2");
                enemy2->transform = { enemy2->transform.position, enemy2->transform.rotation, 6 };
                enemy2->m_game = this;

                enemy2->Init();
                m_scene->Add(std::move(enemy2));
            }
            auto enemy3 = INSTANTIATE(Enemy, "Enemy3");
            enemy3->transform = { enemy3->transform.position, enemy3->transform.rotation, 6 };
            enemy3->m_game = this;

            enemy3->Init();
            m_scene->Add(std::move(enemy3));
        }
        if (m_score >= 3600)//3600
        {
            m_state = eState::Level4;
        }
    }
    break;
    case GAAAAME::eState::Level4://Add Enemy 4: similar to #3 but more extremes
        m_spawnTime = 6;
        m_spawn_timer += dt;
        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;

            for (int i = 0; i < 6; i++) {
                auto enemy = INSTANTIATE(Enemy, "Enemy1");
                enemy->transform = { enemy->transform.position, enemy->transform.rotation, 6 };
                enemy->m_game = this;

                enemy->Init();
                m_scene->Add(std::move(enemy));
            }
            for (int i = 0; i < 2; i++) {
                auto enemy2 = INSTANTIATE(Enemy, "Enemy2");
                enemy2->transform = { enemy2->transform.position, enemy2->transform.rotation, 6 };
                enemy2->m_game = this;

                enemy2->Init();
                m_scene->Add(std::move(enemy2));
            }
            auto enemy3 = INSTANTIATE(Enemy, "Enemy3");
            enemy3->transform = { enemy3->transform.position, enemy3->transform.rotation, 6 };
            enemy3->m_game = this;

            enemy3->Init();
            m_scene->Add(std::move(enemy3));

            auto enemy4 = INSTANTIATE(Enemy, "Enemy4");
            enemy4->transform = { enemy4->transform.position, enemy4->transform.rotation, 6 };
            enemy4->m_game = this;

            enemy4->Init();
            m_scene->Add(std::move(enemy4));
        }
        if (m_score >= 7200)//7200
        {
            m_state = eState::Level5;
        }
        break;
    case GAAAAME::eState::Level5:
    {
        m_spawnTime = 10;
        m_spawn_timer += dt;

       /* for (int i = 0; i < 1; i++) {
            float UpgradePopUp = Twili::randomF(0.0f, 7.0f);
            UpgradePopUp -= dt;
            if (UpgradePopUp <= 0)
            {
               auto powerup = std::make_unique<Player>(0.0f, 0.0f, Twili::Transform{ {Twili::random(Twili::g_rend.getWidth()), Twili::random(Twili::g_rend.getHeight())}, 0, 4});
                powerup->m_tag = "PowerUp2";
                powerup->m_game = this;
                m_scene->Add(std::move(powerup));
            }
        }
        for (int i = 0; i < 1; i++) {
            float UpgradePopUp = Twili::randomF(0.0f, 2.0f);
            UpgradePopUp -= dt;
            if (UpgradePopUp <= 0)
            {
                auto powerup = std::make_unique<Player>(0.0f, 0.0f, Twili::Transform{ {Twili::random(Twili::g_rend.getWidth()), Twili::random(Twili::g_rend.getHeight())}, 0, 3});
                powerup->m_tag = "PowerUp";
                powerup->m_game = this;
                m_scene->Add(std::move(powerup));
            }
        }*/

        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;
            for (int i = 0; i < 6; i++) {
                auto enemy = INSTANTIATE(Enemy, "Enemy1");
                enemy->transform = { enemy->transform.position, enemy->transform.rotation, 6 };
                enemy->m_game = this;

                enemy->Init();
                m_scene->Add(std::move(enemy));
            }
            auto enemy5 = INSTANTIATE(Enemy, "Enemy5");
            enemy5->transform = { enemy5->transform.position, enemy5->transform.rotation, 6 };
            enemy5->m_game = this;

            enemy5->Init();
            m_scene->Add(std::move(enemy5));
        }
        if (m_score == 14400)
        {
            m_stateTimer = 3;
            m_scene->RemoveAll();
            m_state = eState::WinnerStart;
        }
    }
        break;
    case GAAAAME::eState::PlayerDeadStart:
        m_stateTimer = 3;
        if (m_lives == 0) m_state = eState::GameOverStart;
            else m_state = eState::PlayerDead;
        break;
    case GAAAAME::eState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
         m_state = eState::StartLevel;
        }
        break;
    case GAAAAME::eState::GameOverStart:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::GameOver;
        }
        break;
    case GAAAAME::eState::GameOver:
       
            m_scene->RemoveAll();
            m_state = eState::Title;
       
        break;
    case GAAAAME::eState::WinnerStart:
        
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::Winner;
        }
        break;
    case GAAAAME::eState::Winner:
        m_spawnTime = 3;
        m_state = eState::Title;
        break;
    default:
        break;
    }

    m_Scoretext->Create(Twili::g_rend, "Score:  " + std::to_string(m_score), {1,1,1,1});
    m_Livestext->Create(Twili::g_rend, std::to_string(m_lives) + " :Lives" , { 1,1,1,1});

    m_scene->Update(dt);


}

void GAAAAME::Draw(Twili::Renderer& r)
{  
     m_scene->Draw(r);

    if (m_state == eState::Title)
    {
        m_Titletext->Draw(r, 250, 300);
    }
    if (m_state == eState::Level1)
    {
        m_Scoretext->Draw(r, 40, 20);
        m_Livestext->Draw(r, 680, 20);
        m_Level1text->Draw(r, 400, 20);
    }
    if (m_state == eState::Level2)
    {
        m_Scoretext->Draw(r, 40, 20);
        m_Livestext->Draw(r, 680, 20);
        m_Level2text->Draw(r, 400, 20);
    }
    if (m_state == eState::Level3)
    {
        m_Scoretext->Draw(r, 40, 20);
        m_Livestext->Draw(r, 680, 20);
        m_Level3text->Draw(r, 400, 20);
    }
    if (m_state == eState::Level4)
    {
        m_Scoretext->Draw(r, 40, 20);
        m_Livestext->Draw(r, 680, 20);
        m_Level4text->Draw(r, 400, 20);
    }
    if (m_state == eState::Level5)
    {
        m_Scoretext->Draw(r, 40, 20);
        m_Livestext->Draw(r, 680, 20);
        m_Level5text->Draw(r, 400, 20);
    }
    else if (m_state == eState::GameOverStart)
    {
        m_GOvertext->Draw(r, 250, 300);
    }
    else if (m_state == eState::WinnerStart)
    {
        m_Winnertext->Draw(r, 250, 300);
    }

  
}
