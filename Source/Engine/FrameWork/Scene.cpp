#include "Scene.h"
#include "Renderer/Renderer.h"
#include "FrameWork/CollisionComp.h"

namespace Twili
{
    bool Scene::Init()
    {
        for (auto& actor : m_actors)
        {
            actor->Init();
        }

        return true;
    }
    void Scene::Update(float dt)
    {
            //update and removed destroyed actors
           auto iter = m_actors.begin();

           while (iter != m_actors.end())
           { 
               if ((*iter)->active) (*iter)->Update(dt);
               ((*iter)->destroyed) ? iter = m_actors.erase(iter) : iter++;
              
           }

           ////check collisions
           //for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++)
           //{
           //    for (auto iter2 = std::next(iter1,1); iter2 != m_actors.end(); iter2++)
           //    {
           //        CollisionComp* collision1 = (*iter1)->getComponent<CollisionComp>();
           //        CollisionComp* collision2 = (*iter2)->getComponent<CollisionComp>();


           //        if (collision1 == nullptr || collision2 == nullptr) continue;

           //        if (collision1->CheckCollision(collision2))
           //        {
           //            (*iter1)->onCollision(iter2->get());
           //            (*iter2)->onCollision(iter1->get());
           //            //boom

           //        }
           //    }
           //}
       
    }

    void Scene::Draw(Renderer& renderer)
    {
        for (auto& actor : m_actors)
        {
            if(actor->active) actor->Draw(renderer);
        }
    }

    void Scene::Add(std::unique_ptr<Actor> actor)
    {
        actor->m_scene = this;
        m_actors.push_back(std::move(actor));
    }

    void Scene::Remove(Actor* actor)
    {
        //m_actors.remove(actor);
    }

    void Scene::RemoveAll(bool force)
    {
        auto iter = m_actors.begin();

        while (iter != m_actors.end())
        {
           (force || !(*iter)->persistent) ? iter = m_actors.erase(iter) : iter++;
        }

        m_actors.clear();
    }

    bool Scene::Load(const std::string& filename)
    {
        rapidjson::Document document;
        if (!Json::Load(filename, document))
        {
            ERROR_LOG("Could not load scene file: " << filename);
            return false;
        }
        Read(document);
        return true;        
    }

    void Scene::Read(const json_t& value)
    {
        //copy from Actor.cpp read
        if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
        {
            for (auto& actorValue : GET_DATA(value, actors).GetArray())
            {
                std::string type;
                READ_DATA(actorValue, type);

                auto actor = CREATE_BASE_CLASS(Actor, type);
                actor->Read(actorValue);

                if (actor->prototype)
                {
                    std::string name = actor->name;
                    Factory::Instance().RegisterPrototype(name, std::move(actor));
                }
                else
                {
                    Add(std::move(actor));
                }

                


            }
        }
    }

}