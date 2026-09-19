// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: OverchargeBehaviorModuleData dtor (ICF TechBuilding).

class OverchargeNode
{
public:
	virtual ~OverchargeNode();
	OverchargeNode *m_next; // +0x04
	unsigned char m_pad[4];
	unsigned int m_zero; // +0x0c cleared before delete
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleData
{
public:
	virtual ~UpdateModuleData();
	unsigned int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OverchargeBehavior.h
class OverchargeBehaviorModuleData : public UpdateModuleData
{
public:
	virtual ~OverchargeBehaviorModuleData();
private:
	OverchargeNode *m_head; // +0x08
};

// ??1OverchargeBehaviorModuleData@@UAE@XZ
OverchargeBehaviorModuleData::~OverchargeBehaviorModuleData()
{
	OverchargeNode *p = m_head;
	while (p)
	{
		OverchargeNode *next = p->m_next;
		p->m_zero = 0;
		delete p;
		p = next;
	}
}
