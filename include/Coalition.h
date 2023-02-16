#pragma once

#include <vector>

class Simulation;
class Party;

using std::vector;

class Coalition{
public:
    Coalition(int coalitionId, int mandates, int partyId);
    const int getCoalitionId() const;
    const int getCoalitionMandates() const;
    const vector<int> &getPartiesIdVec() const;
    const vector<int> &getAgentsInCoalitionVec() const;
    void addParty(const Party &party);
    void addAgentToVec(int agentIdToAdd);
    bool isInCoalition(int agentId) const;
    bool didOffer(int partyId, Simulation &s);


private:
    const int mId;
    int mNumOfMandates;
    vector<int> mPartiesIdVec={};
    vector<int> mAgentsInCoalitionVec = {};
};