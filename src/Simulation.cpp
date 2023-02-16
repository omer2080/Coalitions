#include "Simulation.h"
#include "Party.h"
#include"Graph.h"
#include "Agent.h"
#include "Coalition.h"


Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
    // initialize Coalitions into vector<Coalition> mCoalitions:
    for(Agent agent : agents){
        int numMandates = graph.getParty(agent.getPartyId()).getMandates();
        mCoalitions.push_back(Coalition(agent.getId(),numMandates,agent.getPartyId()));    
    }
}

void Simulation::step()
{
    for (int i=0 ; i < mGraph.getNumVertices() ; i++){
        mGraph.getParty(i, 0).step(*this);
    }
    for (Agent agent : mAgents){
        agent.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    //checks if a coalition has 61+ mandates
    for (Coalition coal : mCoalitions){
        if (coal.getCoalitionMandates() >= 61){
            return true; // there is a >=61 coalition
        }
    }
    //checks if all coalitions joined
    int nOfParties = mGraph.getNumVertices();
    for(int i = 0 ; i < nOfParties ; i++){
        if(mGraph.getParty(i).getState() != State::Joined){
            return false; // don't termainate - there are parties out of coalition
        }
    }
    return true; // all parties are "Joined"
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party &Simulation::getParty(int partyId, int dumby)
{
    return mGraph.getParty(partyId , dumby);
}

int Simulation::findAgentsCoalition(int agentId) const{
    int coId = -1;
    for(const Coalition &co : mCoalitions){
        if(co.isInCoalition(agentId)){
            coId = co.getCoalitionId();
            return coId;
        }
    }
    return coId;
}

Coalition &Simulation::getCoalition(int coalitionId){
    return mCoalitions[coalitionId];
}

void Simulation::addClonedAgent(Agent &clonedAgent){
    mAgents.push_back(clonedAgent);
}


/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> partiesByCoalition = {};
    for(Coalition coal : mCoalitions){     
        partiesByCoalition.push_back(coal.getPartiesIdVec());
    }
    return partiesByCoalition;
}
