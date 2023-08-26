#pragma once
#include "FrameWork/Actor.h"
#include "FrameWork/Conponent/Physics.h"

namespace Twili
{
class Weapon : public Actor
{
public:
    
    CLASS_DECLARATION(Weapon)
    
    bool Init() override;

    void Update(float dt) override;
    virtual void onCollisionEnter(Actor* actor);

private:
    float speed = 0;
    Twili::Physics* m_physComp = nullptr;
};

}

