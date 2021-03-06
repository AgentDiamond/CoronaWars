#pragma once

#include "header.h"
#include "CollidableGameImageObject.h"
#include "CollisionCallbacks.h"

class Mine final : public CollidableGameImageObject
{
public:
    Mine(CollisionCallbacks* pCollisionCallbacks, BaseEngine* pBaseEngine, const std::string& strURL, int xStart = 0, int yStart = 0, bool isMaskable = false, int maskColour = BLACK, bool isDraggable = false, bool useTopLeftFor00 = true, bool bVisible = true) :
        CollidableGameImageObject(pBaseEngine, strURL, xStart, yStart, isMaskable, maskColour, isDraggable, useTopLeftFor00, bVisible),
        mpCollisionCallbacks(pCollisionCallbacks)
    {
    }

    ~Mine()
    {
    }

    void checkFinishDrag(int newX, int newY) override
    {
        CollidableGameImageObject::checkFinishDrag(newX, newY);
        mpCollisionCallbacks->onMineDrop(this);
    }

    bool hasCollided(GameImageObject* pVirus) override
    {
        // collision is based on whether two circles overlap
        // These are circles with the virus image's radius and one with the mine's radius
        double x1c = pVirus->getXDbl() + ((double)pVirus->getImageWidth() / 2.0);
        double x2c = (double)getX() + ((double)getWidth() / 2.0);
        double y1c = pVirus->getYDbl() + ((double)pVirus->getImageHeight() / 2.0);
        double y2c = (double)getY() + ((double)getHeight() / 2.0);
        double r1 = (double)pVirus->getImageWidth() / 2.0; // actually the radius, but the centre is also the radius
        double r2 = (double)getWidth() / 2.0;
        return (sqrt(pow(x2c - x1c, 2.0) + pow(y2c - y1c, 2.0)) <= (r1 + r2));
    }

    void onCollision() override
    {
        mpCollisionCallbacks->onMineCollision(this);
    }

    int getX() override { return DisplayableObject::m_iCurrentScreenX; }
    int getY() override { return DisplayableObject::m_iCurrentScreenY; }
    int getWidth() override { return DisplayableObject::getDrawWidth(); }
    int getHeight() override { return DisplayableObject::getDrawHeight(); }

private:
    CollisionCallbacks* mpCollisionCallbacks;
};
