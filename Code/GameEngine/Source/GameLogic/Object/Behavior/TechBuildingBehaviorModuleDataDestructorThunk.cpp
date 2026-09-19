// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TechBuildingBehaviorModuleData dtor.
// Walk list at +0x08 (next at +0x04), zero +0x0c, delete, base dtor.

class TechBuildingNode
{
public:
	virtual ~TechBuildingNode();
	TechBuildingNode *m_next; // +0x04
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TechBuildingBehavior.h
class TechBuildingBehaviorModuleData : public UpdateModuleData
{
public:
	virtual ~TechBuildingBehaviorModuleData();
private:
	TechBuildingNode *m_head; // +0x08
};

// ??1TechBuildingBehaviorModuleData@@UAE@XZ
TechBuildingBehaviorModuleData::~TechBuildingBehaviorModuleData()
{
	TechBuildingNode *p = m_head;
	while (p)
	{
		TechBuildingNode *next = p->m_next;
		p->m_zero = 0;
		delete p;
		p = next;
	}
}
