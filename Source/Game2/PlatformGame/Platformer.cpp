#include "Platformer.h"
#include "FrameWork/FrameWork.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Conponent/Sprite.h"

namespace Twili
{

    bool Platformer::Init()
    {       
        Twili::g_noise.AddAudio("Jump", "Jump.wav");
        Twili::g_noise.AddAudio("MakeItPop", "MakeItPop.wav");


        m_scene = std::make_unique<Twili::Scene>();
        m_scene->Load("Scene/PlatformScene.json");
        m_scene->Load("Scene/tilemap.json");
        m_scene->Init();

        //m_scene->getActorByName("Title")->active = true;

        //add events
        EVENT_SUBSCRIBE("AddPoints", Platformer::AddPoints);
        EVENT_SUBSCRIBE("onPlayerDeath", Platformer::onPlayerDeath);

        return true;
    }

    void Platformer::ShutDown()
    {
    }

    void Platformer::Update(float dt)
    {
        switch (m_state)
        {
        case Platformer::eState::Title:
        {/*
            auto actor = INSTANTIATE(Actor, "Crate");
            actor->transform.position = { Twili::random(0,Twili::g_rend.getWidth()), 100 };
            actor->Init();

            m_scene->Add(std::move(actor));*/
        }
            break;
        case Platformer::eState::StartGame:
            m_score = 0;
            m_lives = 3;
            m_state = eState::StartLevel;
            break;
        case Platformer::eState::StartLevel:
            m_scene->RemoveAll();
            m_state = eState::Level1;
            break;
        case Platformer::eState::Level1:

            break;
        case Platformer::eState::Level2: //Add Enemy 2
       
        break;
        case Platformer::eState::Level3://Add Enemy 3: slower ships but beefier health
       
        break;
        case Platformer::eState::Level4://Add Enemy 4: similar to #3 but more extremes
         
            break;
        case Platformer::eState::Level5:
       
        break;
        case Platformer::eState::PlayerDeadStart:
       
            break;
        case Platformer::eState::PlayerDead:
          
            break;
        case Platformer::eState::GameOverStart:
          
            break;
        case Platformer::eState::GameOver:

            break;
        case Platformer::eState::WinnerStart:

            break;
        case Platformer::eState::Winner:
           
            break;
        default:
            break;
        }

        m_scene->Update(dt);

    }

    void Platformer::Draw(Twili::Renderer& r)
    {
        m_scene->Draw(r);
    }

    void Platformer::AddPoints(const Twili::Event& event)
    {
        m_score += std::get<int>(event.data);

    }

    void Platformer::onPlayerDeath(const Twili::Event& event)
    {
        m_lives--;
        m_state = eState::PlayerDeadStart;
    }

}
