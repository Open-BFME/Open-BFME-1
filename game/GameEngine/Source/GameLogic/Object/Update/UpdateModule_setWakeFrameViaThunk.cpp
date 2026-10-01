// cl: /O2 /Ob0

class Object;

// Forward declaration only: the spelling is needed for the setWakeFrame
// signature below, and the definition lives in
// game/GameEngine/Include/GameLogic/Module/UpdateModule.h, which this TU does
// not include (its prefix view keeps retail's offsets local to this file).
enum UpdateSleepTime;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
	char m_lead[8];
	Object *m_object;
	char m_mid[0x14];
	unsigned char m_flag;

public:
	void setWakeFrameViaThunk();

protected:
	void setWakeFrame(Object *, UpdateSleepTime);
};

void UpdateModule::setWakeFrameViaThunk()
{
	Object *obj = m_object;
	m_flag = 0;
	setWakeFrame(obj, (UpdateSleepTime)1);
}
