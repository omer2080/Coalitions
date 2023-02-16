#include "Agent.h"
#include "SelectionPolicy.h"
#include "Simulation.h"
#include "Graph.h"
class Party;

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy){ //Constructor
}

//-------------------Rule of 3---------------------------

Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy){ //Copy Constructor
    mSelectionPolicy = other.mSelectionPolicy->clone();
}

Agent::~Agent(){ //Destructor
    if(mSelectionPolicy){
        delete mSelectionPolicy;
    }
}

Agent &Agent::operator=(const Agent &other){ //Copy Assignment Operator
    if(this!= &other){
        mAgentId= other.mAgentId;
        mPartyId= other.mPartyId;
        mSelectionPolicy= other.mSelectionPolicy->clone();
    }
    return *this;
}

//-------------------Rule of 5-------------------------
Agent::Agent(Agent &&other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy){ //Move Constructor
    other.mSelectionPolicy = nullptr;
}

Agent &Agent::operator=(Agent &&other){  //Move Assignment Operator
    if (mSelectionPolicy){
        delete mSelectionPolicy;
    }
    mSelectionPolicy = other.mSelectionPolicy;
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    other.mSelectionPolicy = nullptr;

    return *this;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

SelectionPolicy * Agent::getSelectionPolicy() const
{
    return mSelectionPolicy;
}


void Agent::step(Simulation &sim)
{       
    // calling select(...) to find which party should offer to (or none -> -1)
    int partyToOffer = mSelectionPolicy->select(*this,sim);
    if(partyToOffer != -1)
    {
        sim.getParty(partyToOffer, 0).setOfferVec(mAgentId);
        if(sim.getParty(partyToOffer).getState() == State::Waiting)
        {
           sim.getParty(partyToOffer, 0).setState(State::CollectingOffers); // and timer starts
        }
    }
}
