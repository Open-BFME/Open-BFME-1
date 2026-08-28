// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditionsInterface : public SubsystemInterface
{
public:
	virtual ~ScriptConditionsInterface() {}
};

class TransportStatus
{
public:
	virtual ~TransportStatus();
};

static TransportStatus *s_transportStatuses;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions : public ScriptConditionsInterface
{
public:
	virtual ~ScriptConditions();
};

ScriptConditions::~ScriptConditions()
{
	delete s_transportStatuses;
	s_transportStatuses = 0;
}
