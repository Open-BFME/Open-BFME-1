// cl: /DNDEBUG /MD /EHsc
// readable body of ?revealMapForPlayer@PartitionManager@@QAEXH@Z: Code/GameEngine/Source/GameLogic/Object/PartitionManager.cpp
// BFME's public PartitionManager is a thin delegate over its implementation
// pointer.  This TU models only the ABI slice exercised by the retail body.

typedef int Int;

class PartitionManagerImpl008F8D60;

class PartitionManagerImpl008F8D60Element
{
public:
	void updatePlayerCells008FC300(PartitionManagerImpl008F8D60 *manager, Int playerIndex);
	void updatePlayerCells008FC3B0(PartitionManagerImpl008F8D60 *manager, Int playerIndex);

private:
	char m_data[0x68];
};

class PartitionManagerImpl008F8D60
{
public:
	void revealMapForPlayer(Int playerIndex);

private:
	char m_head[0x24];
	Int m_width;
	Int m_height;
	PartitionManagerImpl008F8D60Element *m_elements;
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

void PartitionManagerImpl008F8D60::revealMapForPlayer(Int playerIndex)
{
	if (playerIndex < 0 || playerIndex >= 16) {
		return;
	}

	PartitionManagerImpl008F8D60Element *element = m_elements;
	PartitionManagerImpl008F8D60Element *end = element + m_width * m_height;
	while (element != end) {
		element->updatePlayerCells008FC300(this, playerIndex);
		element->updatePlayerCells008FC3B0(this, playerIndex);
		++element;
	}
}
