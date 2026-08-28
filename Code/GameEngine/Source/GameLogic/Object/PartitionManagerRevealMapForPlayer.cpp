// cl: /DNDEBUG /MD /EHsc
// readable body of ?revealMapForPlayer@PartitionManager@@QAEXH@Z: Code/GameEngine/Source/GameLogic/Object/PartitionManager.cpp
// BFME's public PartitionManager is a thin delegate over its implementation
// pointer.  This TU models only the ABI slice exercised by the retail body.

typedef int Int;

class PartitionManagerImpl008F8D60
{
public:
	void revealMapForPlayer(Int playerIndex);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionManager
{
public:
	void revealMapForPlayer(Int playerIndex);

private:
	char m_bfmeHead[0x0c];
	PartitionManagerImpl008F8D60 *m_impl;
};

void PartitionManager::revealMapForPlayer(Int playerIndex)
{
	m_impl->revealMapForPlayer(playerIndex);
}
