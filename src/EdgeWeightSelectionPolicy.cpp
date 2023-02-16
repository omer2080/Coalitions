#include "SelectionPolicy.h"
#include "Agent.h"
#include "Coalition.h"

int EdgeWeightSelectionPolicy::select(Agent &agent, Simulation &s){
    int myPartyId = agent.getPartyId();
    int maxEdge = 0;
    int partyIdToSelect = -1;
    int agentCoalitionId = s.findAgentsCoalition(agent.getId());
    int nParties = s.getGraph().getNumVertices();
    for (int i = 0; i < nParties; i++) {
        int currEdge = s.getGraph().getEdgeWeight(myPartyId,i);
        if ((s.getParty(i).getState() != State::Joined)
            && (currEdge > 0)
            && (!s.getCoalition(agentCoalitionId).didOffer(i,s)))
        {                    
                    if (currEdge > maxEdge) // if ==, lower Id wins -> no change
                    {    maxEdge = currEdge;
                        partyIdToSelect = i;
                    }
        }
    }
    return partyIdToSelect;
}

 EdgeWeightSelectionPolicy* EdgeWeightSelectionPolicy::clone() const{
    return new EdgeWeightSelectionPolicy(*this);
 }