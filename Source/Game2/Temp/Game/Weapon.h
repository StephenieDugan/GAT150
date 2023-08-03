#pragma once

#include "FrameWork/Actor.h"

class Weapon : public Twili::Actor
{
public:
    Weapon(float speed, const Twili::Transform& transform, std::shared_ptr<Twili::Model> model) :
        Actor{ transform, model },
        m_speed{ speed }
    {
        m_lifespan = 1.0f;
    }

    void Update(float dt) override;
    virtual void onCollision(Actor* actor) override;

private:
    float m_speed = 0;
};

