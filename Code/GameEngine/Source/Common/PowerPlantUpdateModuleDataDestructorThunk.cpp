// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift ModuleData dtor MASM dump to clean C++.
// Retail SEH dtor walking the linked list at this+0x08 (m_next at +0x20),
// deleting each node via its scalar deleting destructor and storing the
// advanced head back each iteration, then calling the base class dtor
// (ICF-folded @0x009A1A40).

class SteeringNode
{
public:
	virtual ~SteeringNode();
	char m_pad[0x1c];
	SteeringNode *m_next;	// +0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleData
{
public:
	virtual ~UpdateModuleData();	// out-of-line; pinned at 0x009A1A40
	unsigned int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PowerPlantUpdate.h
class PowerPlantUpdateModuleData : public UpdateModuleData
{
public:
	virtual ~PowerPlantUpdateModuleData();

private:
	SteeringNode *m_head;	// +0x08
};

// ??1PowerPlantUpdateModuleData@@UAE@XZ
PowerPlantUpdateModuleData::~PowerPlantUpdateModuleData()
{
	while (m_head)
	{
		SteeringNode *next = m_head->m_next;
		delete m_head;
		m_head = next;
	}
}
