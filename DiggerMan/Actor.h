#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"
#include <algorithm>

const int DM_START_X = 30;
const int DM_START_Y = 60;

class StudentWorld; //Forward declaration

enum BoulderState
{
    stable, falling, waiting
};
enum GoldNuggetState
{
    sleep, awake
};

enum ProtesterState
{
    rest, leaveOilField, dead, start
};
enum SonarState
{

};

class Actor : public GraphObject
{
public:
    Actor(StudentWorld * world, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)
        :GraphObject(imageID, startX, startY, right, size, depth)
    {
        m_hitpoints = 1;
        m_world = world;
    }

    inline void setHitpoints(int newHitpoints)
    {
        this->m_hitpoints = newHitpoints;
    }
    inline int getHitpoints()
    {
        return m_hitpoints;
    }
    virtual bool isAlive()
    {
        return m_hitpoints > 0;
    }
    virtual StudentWorld* getWorld()
    {
        return m_world;
    }

    virtual void doSomething();

private:
    int m_hitpoints;
    StudentWorld * m_world;
};

class DiggerMan : public Actor
{
public:
    DiggerMan(StudentWorld * world)
        : Actor(world, IMID_PLAYER, DM_START_X, DM_START_Y)
    {
        setVisible(true);
        m_water = 50;
        m_goldNuggets = 0;
        m_sonarCharges = 900;
    }

    virtual void doSomething();

    inline int getGold()
    {
        return m_goldNuggets;
    }
    inline void decreaseGold()
    {
        m_goldNuggets--;
    }
    inline void increaseGold()
    {
        m_goldNuggets++;
    }
    inline int getWater()
    {
        return m_water;
    }
    inline void setWater(int water)
    {
        m_water = water;
    }
    inline void addWater(int water)
    {
        m_water += water;
    }
    inline int getSonar()
    {
        return m_sonarCharges;
    }
    inline void increaseSonar()
    {
        m_sonarCharges++;
    }
    inline void decreaseSonar()
    {
        m_sonarCharges--;
    }
    inline void reduceWater()
    {
        m_water--;
    }

    inline DiggerMan* getDiggerMan()
    {
        return this;
    }
    virtual StudentWorld* getWorld()
    {
        return Actor::getWorld();
    }

private:
    int m_water;
    int m_sonarCharges;
    int m_goldNuggets;
    unsigned int waitTime = 0;
};

class Squirt : public Actor
{
public:

    Squirt(StudentWorld* world, int startX, int startY, Direction dir)
        : Actor(world, IMID_WATER_SPURT, startX, startY, dir, 1.0, 1)
    {
        setVisible(true);
        distanceTraveled = 0;
    }

    virtual void doSomething();

private:

    int distanceTraveled;
    unsigned int waitTime = 0;


};

class Dirt : public Actor
{
public:
    Dirt(StudentWorld * world, int startX, int startY)
        : Actor(world, IMID_DIRT, startX, startY, right, 0.25, 3)
    {
        setVisible(true);
    }

private:

};

class Barrel : public Actor
{
public:
    Barrel(StudentWorld * world, int startX, int startY)
        : Actor(world, IMID_BARREL, startX, startY, right, 1.0, 2)
    {
        setVisible(false); //Barrels should start hidden and only be discovered when walked over
    }

    virtual void doSomething();

};

class GoldNugget : public Actor
{
public:
    GoldNugget(StudentWorld * world, int startX, int startY)
        : Actor(world, IMID_GOLD, startX, startY, right, 1.0, 2)
    {
        this->m_state = sleep;
        setVisible(false);
    }

    void doSomething();
    bool isStable();
private:
    GoldNuggetState m_state;
    //	unsigned int nearBy = 



};

class Boulder : public Actor
{
    //Must start in a stable state, must add code later
public:
    Boulder(StudentWorld * world, int startX, int startY)
        :Actor(world, IMID_BOULDER, startX, startY, down, 1.0, 1)
    {
        this->m_state = stable;
        setVisible(true);
    }

    void doSomething();
    bool isStable();
    BoulderState getState()

    {
        return m_state;
    }

private:
    BoulderState m_state;
    unsigned int waitTime = 0;
};

class Protester : public Actor
{
public:

    Protester(StudentWorld * world, int startX, int startY)
        :Actor(world, IMID_PROTESTER, 60, 60, left, 1.0, 0)
    {
        setVisible(true);
        setHitpoints(5);
        m_state = start;
        tickToWaitBetweenMoves = 0;
        ticks = 0;
        step = false;
    }

    void doSomething();
    ProtesterState getState() { return m_state; }
    void setState(ProtesterState state)
    {
        m_state = state;
    }

private:

    unsigned int tickToWaitBetweenMoves;
    unsigned int waitingTime = 0;
    unsigned int nonRestingTicks = 0;
    unsigned int ticks;
    bool step;

    ProtesterState m_state;
};

class WaterPool : public Actor
{
public:
    WaterPool(StudentWorld* world, int startX, int startY)
        :Actor(world, IMID_WATER_POOL, startX, startY, right, 1.0, 2)
    {
        setVisible(true);
        ticks = 0;

    }

    virtual void doSomething();

private:
    int ticks;
};

class SonarKit : public Actor
{
public:
    SonarKit(StudentWorld* world, int startX, int startY)
        :Actor(world, IMID_SONAR, startX, startY, right, 1.0, 2)
    {
        setVisible(true);
        ticks = 0;
    }

    void doSomething();

private:
    int ticks;
};

class HardcoreProtester : public Protester
{};

#endif // ACTOR_H_