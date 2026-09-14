// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clearRva00359530Nodes(Rva00359530Record *) -- retail 0x003595F0, 54 bytes.
//
// Twin of Rva00359330StringRecordClearNodes.cpp (0x003593F0) for the second
// string-record table (Rva00359530StringRecordTable in
// Rva00359330StringRecordRelease.cpp): same 20-byte record, same +0x10 node
// slot, but the chain holds the Y node family whose destructor is ILT
// 0x00028EC0 (??1BfmeNodeY, the body bfmeUnregisterY at 0x0035ADC0 drains).
// The record struct is respelled with the table's own address so the two
// TUs do not share a placeholder type; the function name is address-derived.
//
// Shape lever (docs/shape_levers.md): the next link is read through the
// field, not the local, so VC7.1 keeps the delete null test after the store
// (retail test/store/branch). A do-while lands 51 B, a volatile reload 54 B
// with the test before the store.

void __cdecl operator delete(void *);

class BfmeNodeY
{
public:
	~BfmeNodeY();
	BfmeNodeY *m_next;
};

struct Rva00359530Record
{
	int m_previous;
	int m_next;
	void *m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	BfmeNodeY *m_nodes;
};

// ?clearRva00359530Nodes@@YAXPAURva00359530Record@@@Z
void clearRva00359530Nodes(Rva00359530Record *record)
{
	while (record->m_nodes)
	{
		BfmeNodeY *node = record->m_nodes;

		record->m_nodes = record->m_nodes->m_next;
		delete node;
	}
}
