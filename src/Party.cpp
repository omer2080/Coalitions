#include "Party.h"
#include "Simulation.h"
#include "JoinPolicy.h"


Party::Party(int id, string name, int mandates, JoinPolicy *jp) :
        mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(State::Waiting), mTimer(0) {
}

//----------------------Rule of 3--------------------

Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), mTimer(other.mTimer){ //Copy Constructor
    for(int i : other.mAgentsOfferedVec){
        mAgentsOfferedVec.push_back(i);
    }
    mJoinPolicy = other.mJoinPolicy->clone();
}

Party::~Party(){ //Destructor
    if(mJoinPolicy){
        delete mJoinPolicy;
    }
}

Party &Party::operator=(const Party &other){ //Copy Assignment Operator
    if(this!= &other){
        mId= other.mId;
        mName= other.mName;
        mMandates= other.mMandates;
        mJoinPolicy= other.mJoinPolicy->clone();
        mState= other.mState;
        mTimer= other.mTimer;
        for(int i : other.mAgentsOfferedVec){
            mAgentsOfferedVec.push_back(i);
        }
    }
    return *this;
}

//----------------------Rule of 5--------------------

Party::Party(Party &&other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), mTimer(other.mTimer){ // Move Constructor
    mAgentsOfferedVec = other.mAgentsOfferedVec;
    other.mJoinPolicy = nullptr;
}

Party &Party::operator=(Party &&other){ //Move Assignment Operator
    if(mJoinPolicy){
        delete mJoinPolicy;
    }
    mJoinPolicy = other.mJoinPolicy;
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mState = other.mState;
    mAgentsOfferedVec = other.mAgentsOfferedVec;
    mTimer = other.mTimer;
    other.mJoinPolicy = nullptr;

    return *this;
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
    if(state == State::CollectingOffers)
    {
        mTimer++;
    }
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

const int Party::getId() const 
{
    return mId;
}

// Update of a single offer:
void Party::setOfferVec(int agentID){
    mAgentsOfferedVec.push_back(agentID);
}

const vector<int>& Party::getAgentsOfferedVec() const{
    return mAgentsOfferedVec;
}

void Party::step(Simulation &s)
{
    if (mState == State::CollectingOffers){ //otherwise, no action needed
        if (mTimer == 3){
            mJoinPolicy->join(*this, s);
            mState = State::Joined;
        }
        mTimer++;
    }
}