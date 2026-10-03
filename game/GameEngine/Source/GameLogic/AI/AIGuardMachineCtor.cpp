// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "StringInline.h"
#include "Lib/BaseType.h"
// BFME storage/ABI views. ZH AIGuard.h has Object* only and a 0x38-byte
// StateMachine; retail and matched callers prove Object*+AsciiString and 0x44.
// Other field names remain address-qualified. The available StateMachine.h
// transitively selects the incompatible base, so no shared header is changed.
// Canonical strings and Coord3D are included above.
// Evidence: identity_evidence/0015d1d0-native-guard-machine.md.
class Object;
class StateMachine;
class State;
typedef bool (*StateTransFuncPtr)(State *,void *);
struct StateConditionInfo {
 StateTransFuncPtr test;unsigned int toStateID;void *userData;
 StateConditionInfo(StateTransFuncPtr t,unsigned int i,void *d):test(t),toStateID(i),userData(d){}
};
class StateMachine {
public: StateMachine(Object *,AsciiString,bool);
protected: virtual ~StateMachine();
 void defineState(unsigned int,State *,unsigned int,unsigned int,const StateConditionInfo * = 0);
private: char m_rva0015d1d0_base[0x40];
};
class State {
public: State(StateMachine *,AsciiString);virtual ~State();
private: char m_rva000a19e0_base[0x20];
};
class AIInternalMoveToState: public State {
public: AIInternalMoveToState(StateMachine *,AsciiString);
protected: virtual ~AIInternalMoveToState();
private: char m_rva0014f280_tail[0x2c];
};
class AIGuardReturnState: public AIInternalMoveToState {
public: AIGuardReturnState(StateMachine *m):AIInternalMoveToState(m,"AIGuardReturn"){m_rva0015d1d0_50=0;}
protected:virtual ~AIGuardReturnState();
private: unsigned int m_rva0015d1d0_50;
};
class AIGuardIdleState:public State {
public: AIGuardIdleState(StateMachine *m):State(m,"AIGuardIdleState"){}
protected:virtual ~AIGuardIdleState();
private:char m_rva0015d1d0_tail[0x10];
};
class AIGuardInnerState:public State {public:AIGuardInnerState(StateMachine *);private:char m_rva0015ce00_tail[0x28];};
class AIGuardOuterState:public State {public:AIGuardOuterState(StateMachine *);private:char m_rva0015ced0_tail[0x24];};
class AIPickUpCrateState:public AIInternalMoveToState {
public:AIPickUpCrateState(StateMachine *m):AIInternalMoveToState(m,"AIAttackPickUpCrateState"){m_rva0015d1d0_50=0;}
protected:virtual ~AIPickUpCrateState();
private:unsigned int m_rva0015d1d0_50;
};
class AIGuardPickUpCrateState:public AIPickUpCrateState {
public:AIGuardPickUpCrateState(StateMachine *m):AIPickUpCrateState(m){}
protected:virtual ~AIGuardPickUpCrateState();
};
class AIGuardAttackAggressorState:public State {public:AIGuardAttackAggressorState(StateMachine *);private:char m_rva0015d090_tail[0x24];};
extern "C" bool __cdecl Rva0015C280Predicate(State *,void *);
class AIGuardMachine:public StateMachine {
public:AIGuardMachine(Object *,AsciiString);
protected:virtual ~AIGuardMachine();
private:
 unsigned int m_rva0015d1d0_44,m_rva0015d1d0_48,m_rva0015d1d0_4c;
 Coord3D m_rva0015d1d0_50,m_rva0015d1d0_5c;
 bool m_rva0015d1d0_68;
 unsigned int m_rva0015d1d0_6c,m_rva0015d1d0_70,m_rva0015d1d0_74;
};
AIGuardMachine::AIGuardMachine(Object *owner,AsciiString name):StateMachine(owner,name,false),
 m_rva0015d1d0_44(0),m_rva0015d1d0_48(0),m_rva0015d1d0_4c(0),m_rva0015d1d0_68(false),
 m_rva0015d1d0_6c(0),m_rva0015d1d0_70(0),m_rva0015d1d0_74(0)
{
 m_rva0015d1d0_50.zero();m_rva0015d1d0_5c.zero();
 static const StateConditionInfo attackAggressors[]={StateConditionInfo(Rva0015C280Predicate,5005,0),StateConditionInfo(0,0,0)};
 defineState(5003,new AIGuardReturnState(this),5001,5000,attackAggressors);
 defineState(5001,new AIGuardIdleState(this),5000,5003,attackAggressors);
 defineState(5000,new AIGuardInnerState(this),5002,5002);
 defineState(5002,new AIGuardOuterState(this),5004,5004);
 defineState(5004,new AIGuardPickUpCrateState(this),5003,5003);
 defineState(5005,new AIGuardAttackAggressorState(this),5003,5003);
}
