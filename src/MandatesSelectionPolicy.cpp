#include "SelectionPolicy.h"
#include "Agent.h"
#include "Coalition.h"


int MandatesSelectionPolicy::select(Agent &agent, Simulation &s) {
    int myPartyId = agent.getPartyId();
    int maxMandates = 0;
    int partyIdToSelect = -1;
    int agentCoalitionId = s.findAgentsCoalition(agent.getId());
    int nParties = s.getGraph().getNumVertices();
    for (int i = 0; i < nParties; i++) {
        if ((s.getParty(i).getState() != State::Joined)
            && (s.getGraph().getEdgeWeight(myPartyId, i) > 0)
            && (!s.getCoalition(agentCoalitionId).didOffer(i,s)))
        {
            int currMandates = s.getParty(i).getMandates();
            if (currMandates > maxMandates) { // if ==, lower Id wins -> no change
                maxMandates = currMandates;
                partyIdToSelect = i;
            }
        }
    }
    return partyIdToSelect;
}

 MandatesSelectionPolicy* MandatesSelectionPolicy::clone() const{
    return new MandatesSelectionPolicy(*this);
 }