#pragma once
#include <list>
#include "Actor.h"

namespace Twili
{
    class Renderer;

    class Scene
    {
    public:
        Scene() = default;

        bool Init();
        void Update(float dt);
        void Draw(Renderer& renderer);

        void Add(std::unique_ptr<Actor> actor);
        void Remove(Actor* actor);
        void RemoveAll();

        bool Load(const std::string& filename);
        void Read(const json_t& value);


        template<typename T>
        T* getActor();

        friend class Actor;

    private:
        std::list<std::unique_ptr<Actor>> m_actors;
    };
    template<typename T>
    inline T* Scene::getActor()
    {
        for (auto& actor : m_actors)
        {
            T* result = dynamic_cast<T*> (actor.get());

            if (result)
                return result;
       }
        return nullptr;
    }
}
