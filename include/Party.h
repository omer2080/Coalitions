#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class Simulation;
class JoinPolicy;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    //--------Rule of 5-----------:
    Party(const Party &other);
    ~Party();
    Party& operator=(const Party& other);
    Party(Party &&other);
    Party& operator=(Party &&other);


    State getState() const;
    void setState(State state);
    int getMandates() const;
    const string &getName() const;
    const int getId() const;
    void setOfferVec(int agentID);
    const vector<int>& getAgentsOfferedVec() const;
    void step(Simulation &s);



private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int mTimer;
    vector<int> mAgentsOfferedVec={};
};
