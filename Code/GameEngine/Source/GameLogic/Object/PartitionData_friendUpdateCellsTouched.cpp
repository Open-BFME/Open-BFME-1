// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: PartitionData::friend_updateCellsTouched, retail 0x008F8BF0,
// 37 bytes. The canonical Zero Hour header exposes this public zero-argument
// facade over private updateCellsTouched(). BFME augments it by removing the
// object from an intrusive dirty list before rebuilding the touched cells.
//
// Retail +0x14 is a pointer to the link that currently names this node, and
// +0x18 is the following node. Rewriting the former makes removal work for
// either the list head or a predecessor's next link; the following node then
// inherits that backlink. The cleared backlink records that this node is no
// longer linked.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionData
{
public:
	void friend_updateCellsTouched();

private:
	void updateCellsTouched();
	unsigned char m_bfmePrefix[0x14];
	PartitionData **m_bfmeDirtyPrevLink; // +0x14
	PartitionData *m_bfmeDirtyNext;      // +0x18
};

// ?friend_updateCellsTouched@PartitionData@@QAEXXZ
void PartitionData::friend_updateCellsTouched()
{
	if (m_bfmeDirtyPrevLink != 0)
	{
		*m_bfmeDirtyPrevLink = m_bfmeDirtyNext;
		if (m_bfmeDirtyNext != 0)
			m_bfmeDirtyNext->m_bfmeDirtyPrevLink = m_bfmeDirtyPrevLink;
		m_bfmeDirtyPrevLink = 0;
	}
	updateCellsTouched();
}
