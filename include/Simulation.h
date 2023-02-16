#pragma once

#include <vector>
#include <string>

#include "Graph.h"
#include "Coalition.h"
#include "Agent.h"
using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    Party &getParty(int partyId, int dumby);
    const vector<vector<int>> getPartiesByCoalitions() const;
    int findAgentsCoalition(int agentId) const;
    Coalition &getCoalition(int coalitionId);
    void addClonedAgent(Agent &clonedAgent);


private:
    Graph mGraph;
    vector<Agent> mAgents={};
    vector<Coalition> mCoalitions={};
};