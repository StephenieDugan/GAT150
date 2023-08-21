#pragma once

#include "FrameWork/Actor.h"


namespace Twili
{
class Weapon : public Actor
{
public:
    
    Weapon(float speed, const Twili::Transform& transform) :
        Actor{ transform},
        speed{ speed }
    {
        lifespan = 1.0f;
    }
    
    bool Init() override;

    void Update(float dt) override;
    virtual void onCollision(Actor* actor);

    void Read(const json_t& value);

private:
    float speed = 0;
};

}

