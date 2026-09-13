// cl: /O2 /Ob0

class PartitionData;

class PartitionDirtyListOwner
{
public:
	void prependDirtyModule(PartitionData *node);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionData
{
	PartitionDirtyListOwner *m_owner;
	char m_pad[0x10];
	void *m_field14;

public:
	void maybePrepend();
};

void PartitionData::maybePrepend()
{
	if (!m_field14)
		m_owner->prependDirtyModule(this);
}
