// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Complete destructor 0x0028FCC0 and emitted scalar wrapper 0x00290190.
// Constructor 0x00290740, typed factories, and module-name getter establish
// the class; wrapper ILT 0x0000922D reaches the complete teardown.
// This destructor uses the BFME-era UpdateModule and emotion-container layout.
// Keep the recovered view in the proper source family instead of changing the
// shared reference headers.

#include <set>
#include <vector>

class Gen_dtor_00113d40
{
public:
	virtual ~Gen_dtor_00113d40();

private:
	const void *m_moduleData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113d40
{
private:
	void *m_object;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

struct Gen_t_000ef440_k4
{
	int a[1];
	Gen_t_000ef440_k4();
	Gen_t_000ef440_k4(const Gen_t_000ef440_k4&);
	~Gen_t_000ef440_k4();
	Gen_t_000ef440_k4& operator=(const Gen_t_000ef440_k4&);
};

bool operator==(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);
bool operator<(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);

class EmotionTrackerUpdateSecondaryBase
{
public:
	virtual void slot();
};

class EmotionTrackerUpdate
	: public UpdateModule,
	  public EmotionTrackerUpdateSecondaryBase
{
public:
	virtual ~EmotionTrackerUpdate();

private:
	unsigned char m_unreconstructed_24[0x5c];
	_STL::vector<int> m_vector;
	unsigned char m_unreconstructed_8c[8];
	_STL::set<Gen_t_000ef440_k4> m_set;
};

// ??1EmotionTrackerUpdate@@UAE@XZ
EmotionTrackerUpdate::~EmotionTrackerUpdate()
{
}
