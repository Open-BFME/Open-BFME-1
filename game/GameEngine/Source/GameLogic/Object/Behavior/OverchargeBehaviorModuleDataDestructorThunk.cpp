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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
// Base dtor call lands on 0x009A1A40, matched ??1SubsystemInterface@@UAE@XZ
// (SubsystemInterface.cpp), per callees.py on this body.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	unsigned int m_name; // AsciiString handle
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OverchargeBehavior.h
class OverchargeBehaviorModuleData : public SubsystemInterface
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
