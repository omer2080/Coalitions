#pragma once
#include "Simulation.h"

class Agent;
class Coalition;

class SelectionPolicy 
{
public:
    virtual int select(Agent &agent, Simulation &s) = 0;
    virtual ~SelectionPolicy() = default;
    virtual SelectionPolicy* clone() const = 0;

};

class MandatesSelectionPolicy: public SelectionPolicy
{
public:

    virtual int select(Agent &agent, Simulation &s) override;
    virtual MandatesSelectionPolicy* clone() const;

private:

};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
public:

    virtual int select(Agent &agent, Simulation &s) override;
    virtual EdgeWeightSelectionPolicy* clone() const;


private:

};