// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DeletionUpdateModuleData dtor.
// Walk list at +0x08 (next +0x04), delete, zero head and +0x0c, base dtor.

class DeletionNode
{
public:
	virtual ~DeletionNode();
	DeletionNode *m_next; // +0x04
};

class DeletionUpdateModuleDataBase
{
public:
	virtual ~DeletionUpdateModuleDataBase();
	unsigned int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DeletionUpdate.h
class DeletionUpdateModuleData : public DeletionUpdateModuleDataBase
{
public:
	virtual ~DeletionUpdateModuleData();
private:
	DeletionNode *m_head; // +0x08
	unsigned int m_0c; // +0x0c zeroed after walk
};

// ??1DeletionUpdateModuleData@@UAE@XZ
DeletionUpdateModuleData::~DeletionUpdateModuleData()
{
	DeletionNode *p = m_head;
	while (p)
	{
		DeletionNode *next = p->m_next;
		delete p;
		p = next;
	}
	m_head = 0;
	m_0c = 0;
}
