#include "JoinPolicy.h"
#include "Agent.h"
#include "Simulation.h"
#include "Party.h"



void LastOfferJoinPolicy::join(Party &party, Simulation &s){ 
    int lastAgentId = party.getAgentsOfferedVec().back();
    int coalitionToJoin = s.findAgentsCoalition(lastAgentId);
    
    // clone agent:
    int clonedAgentId = s.getAgents().size();
    int clonedPartyId = party.getId();
    SelectionPolicy* clonedSelectionPolicyP = s.getAgents()[lastAgentId].getSelectionPolicy()->clone();

    Agent clonedAgent(clonedAgentId,clonedPartyId,clonedSelectionPolicyP);
    s.addClonedAgent(clonedAgent);   
    
    // add cloned agent to the coalition:
    s.getCoalition(coalitionToJoin).addAgentToVec(clonedAgentId);
    // add party to the coalition:
    s.getCoalition(coalitionToJoin).addParty(party);
    party.setState(State::Joined);
}

 LastOfferJoinPolicy* LastOfferJoinPolicy::clone() const{
    return new LastOfferJoinPolicy(*this);
 }