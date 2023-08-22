#pragma once

#include "FrameWork/Actor.h"


namespace Twili
{
class Weapon : public Actor
{
public:
    
    CLASS_DECLARATION(Weapon)
    
    bool Init() override;

    void Update(float dt) override;
    virtual void onCollision(Actor* actor);

private:
    float speed = 0;
};

}

