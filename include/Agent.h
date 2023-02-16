#pragma once

#include <vector>
class SelectionPolicy;
class Simulation;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

//--------Rule of 5-----------:
    Agent(const Agent &other);
    ~Agent();
    Agent& operator=(const Agent& other);
    Agent(Agent &&other);
    Agent& operator=(Agent &&other);
    
    int getPartyId() const;
    int getId() const;
    SelectionPolicy * getSelectionPolicy() const;
    void step(Simulation &);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
};
