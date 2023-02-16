#include "Coalition.h"
#include "Party.h"
#include "Simulation.h"



Coalition::Coalition(int coalitionId, int mandates, int partyId) : mId(coalitionId), mNumOfMandates(mandates) {
        mPartiesIdVec.push_back(partyId);
        mAgentsInCoalitionVec.push_back(coalitionId); // only happens in constructor of Simulation, when each agent represents a coalition
}

const int Coalition::getCoalitionId() const{ return mId; }
const int Coalition::getCoalitionMandates() const{ return mNumOfMandates; }
const vector<int> &Coalition::getPartiesIdVec() const {return mPartiesIdVec;}
const vector<int> &Coalition::getAgentsInCoalitionVec() const {return mAgentsInCoalitionVec;}

void Coalition::addParty(const Party &party){
    mNumOfMandates += party.getMandates();
    mPartiesIdVec.push_back(party.getId());
}

void Coalition::addAgentToVec(int agentIdToAdd){
    mAgentsInCoalitionVec.push_back(agentIdToAdd);
}

bool Coalition::isInCoalition(int agentId) const{
    for(int existingAgentId : mAgentsInCoalitionVec)
    {
        if(agentId == existingAgentId){return true;}
    }
    return false;
}

bool Coalition::didOffer(int partyId, Simulation &s){
    vector<int> agentsOfferedVec = s.getParty(partyId).getAgentsOfferedVec();
    for (int j : agentsOfferedVec) {
        if(this->isInCoalition(j)){
            return true;
        }
    }
    return false;
}