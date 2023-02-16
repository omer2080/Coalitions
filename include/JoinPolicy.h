#pragma once
#include "Simulation.h"
#include "Coalition.h"
#include "SelectionPolicy.h"

class Agent;
class Simulation;
class Party;

class JoinPolicy { 
public:
    virtual void join(Party &party, Simulation &s) = 0;
    virtual ~JoinPolicy() = default;
    virtual JoinPolicy* clone() const = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
    virtual void join(Party &party, Simulation &s);
    virtual MandatesJoinPolicy* clone() const;
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    virtual void join(Party &party, Simulation &s);
    virtual LastOfferJoinPolicy* clone() const;
};