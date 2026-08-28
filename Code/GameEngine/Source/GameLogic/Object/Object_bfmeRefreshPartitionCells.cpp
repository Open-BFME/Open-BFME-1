// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Object partition-cell refresh wrapper, retail 0x001BFD70,
// 51 bytes. BFME's Object reaches PartitionData through a virtual base: the
// vbptr is at Object +0x68, vbtable[1] contributes 0x358, and the resulting
// interface begins at Object +0x3C0. Its five-slot table contains geometry,
// position, orientation, the partition-data setter, and friend_getPartitionData
// at slot 4 (+0x10). The duplicate lookup below intentionally reproduces the
// two retail virtual-base dispatches.
//
// The final canonical friend_updateCellsTouched facade unlinks PartitionData
// from the dirty list and then updates its touched cells. The BFME-only Object
// wrapper has no surviving source spelling, so its bfme-prefixed name remains
// descriptive.

class PartitionData
{
public:
	void friend_updateCellsTouched();
};

// The stand-in prefix exists only to put Object's virtual-base pointer at the
// observed retail offset. It makes no claim about the intervening fields.
class BfmeObjectPrefix
{
private:
	unsigned char m_bytes[0x68];
};

class BfmePartitionDataOwner
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot01() = 0;
	virtual void bfmeSlot02() = 0;
	virtual void bfmeSlot03() = 0;
	virtual PartitionData *friend_getPartitionData() const = 0; // +0x10
};

class Object : public BfmeObjectPrefix, virtual public BfmePartitionDataOwner
{
public:
	void bfmeRefreshPartitionCells();
};

// ?bfmeRefreshPartitionCells@Object@@QAEXXZ
void Object::bfmeRefreshPartitionCells()
{
	if (friend_getPartitionData())
		friend_getPartitionData()->friend_updateCellsTouched();
}
