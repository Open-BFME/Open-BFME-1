// cl: /DNDEBUG /MD /EHsc
// readable body of ?freeListOfMapObjects@WorldHeightMap@@SAXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp

// Open-BFME5: WorldHeightMap::freeListOfMapObjects, retail 0x00746E90, 38
// bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// A static with no this. The list head lives one indirection behind the global
// at 0x012ED5DC: when it is set, virtual slot 0 is called with 1 to free it and
// the head is cleared -- and the global is re-read for that clear rather than
// kept, so the source reads it twice.
//
// The tail is a thiscall on the global object at 0x012ED5E0 itself, which is
// loaded as an immediate address rather than dereferenced, so that one is an
// object and not a pointer to one.

class BfmeMapObjectListEntry
{
public:
	virtual void bfmeDeleteThis(int freeIt) = 0;		// vtable slot 0
};

class BfmeMapObjectListHolder
{
public:
	BfmeMapObjectListEntry *m_bfmeHead;			// +0x00
};

class BfmeMapObjectExtra
{
public:
	void bfmeReset(void);					// retail 0x00033F46
};

extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;	// 0x012ED5DC
extern BfmeMapObjectExtra BfmeTheMapObjectExtra;		// 0x012ED5E0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	static void freeListOfMapObjects(void);
};

// ?freeListOfMapObjects@WorldHeightMap@@SAXXZ
void WorldHeightMap::freeListOfMapObjects(void)
{
	if (BfmeTheMapObjectListHolder->m_bfmeHead != 0)
	{
		BfmeTheMapObjectListHolder->m_bfmeHead->bfmeDeleteThis(1);
		BfmeTheMapObjectListHolder->m_bfmeHead = 0;
	}

	BfmeTheMapObjectExtra.bfmeReset();
}
