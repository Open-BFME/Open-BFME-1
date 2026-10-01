// Open-BFME5: clean C++ conversion of the indefinite wake-frame reset.

class Object;

// Forward declaration only: the spelling is needed for the setWakeFrame
// signature below, and the definition lives in
// game/GameEngine/Include/GameLogic/Module/UpdateModule.h, which this TU does
// not include (its prefix view keeps retail's offsets local to this file).
enum UpdateSleepTime;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	void resetWakeState();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime wakeDelay);

private:
	char m_pad00[8];
	Object *m_object;
	char m_pad0C[0x20];
	unsigned int m_wakeFrame;
	bool m_isAwake;
};

void UpdateModule::resetWakeState()
{
	m_isAwake = true;
	m_wakeFrame = 0x3FFFFFFF;
	setWakeFrame(m_object, (UpdateSleepTime)0x3FFFFFFF);
}
