#include "JoinPolicy.h"
#include "Agent.h"
#include "Simulation.h"
#include "Party.h"

void MandatesJoinPolicy::join(Party &party, Simulation &s){
    int coalitionToJoin = 0;
    int maxMandates = 0;
    int maxAgentId = -1;
    vector<int> tempVec = party.getAgentsOfferedVec();
    for(int agentId : tempVec){
        int currCoalitionId = s.findAgentsCoalition(agentId);
        int currMandates = s.getCoalition(currCoalitionId).getCoalitionMandates();
        if(currMandates > maxMandates){ // a better coalition
            maxMandates = currMandates;
            coalitionToJoin = currCoalitionId;
            maxAgentId = agentId;
        }
    }

    // clone agent:
    int clonedAgentId = s.getAgents().size();
    int clonedPartyId = party.getId();
    SelectionPolicy* clonedSelectionPolicyP = s.getAgents()[maxAgentId].getSelectionPolicy()->clone();
    Agent clonedAgent(clonedAgentId,clonedPartyId,clonedSelectionPolicyP);
    s.addClonedAgent(clonedAgent);

    // add cloned agent to the coalition:
    s.getCoalition(coalitionToJoin).addAgentToVec(clonedAgentId);
    // add party to the coalition:
    s.getCoalition(coalitionToJoin).addParty(party);
    party.setState(State::Joined);
}

 MandatesJoinPolicy* MandatesJoinPolicy::clone() const{
    return new MandatesJoinPolicy(*this);
 }