// cl: /O2 /Ob0

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
	char m_lead[8];
	Object *m_object;
	char m_mid[0x14];
	unsigned char m_flag;

public:
	void setWakeFrame(Object *, unsigned);
	void setWakeFrameViaThunk();
};

void UpdateModule::setWakeFrameViaThunk()
{
	Object *obj = m_object;
	m_flag = 0;
	setWakeFrame(obj, 1);
}
