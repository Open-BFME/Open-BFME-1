// ?handle@Rva00733F50@@QAEXHH@Z
// partial score=1.0 date=2026-09-16
// BFME retail 0x00733F50: guarded indexed handle update (100 bytes).
// The owner remains address-derived: Rva00734730::findAndSet reaches this
// body through the retail ILT at 0x00049DD7, but no canonical tree-buffer
// method name is proven by that call site.

typedef int Int;
typedef unsigned char Bool;

struct Rva00733F50TreeRecord
{
	unsigned char m_pad00[0x40];
	Int m_state;
	unsigned char m_pad44[0xA0];
	Int m_handle;
};

struct Rva00733F50TreeTypeData
{
	unsigned char m_pad00[0x5C];
	Int m_handle;
};

struct Rva00733F50TreeType
{
	unsigned char m_pad00[0x20];
	Rva00733F50TreeTypeData *m_data;
	unsigned char m_pad24[0x38];
};

class Rva00733F50
{
public:
	void handle(Int index, Int useObjectHandle);

private:
	unsigned char m_pad0000[0x1B0];
	Rva00733F50TreeRecord m_trees[12000];
	Int m_numTrees;
	unsigned char m_pad2A7CB4[8];
	Rva00733F50TreeType m_treeTypes[64];
	unsigned char m_pad2A93BC[0x550];
	Bool m_anythingChanged;
	Bool m_guard;
};

// ?handle@Rva00733F50@@QAEXHH@Z
void Rva00733F50::handle(Int index, Int useObjectHandle)
{
	if (m_guard)
		return;
	if (index >= m_numTrees)
		return;

	Int state = m_trees[index].m_state;
	if (state < 0)
		return;

	Bool useHandle = (Bool)useObjectHandle;
	if (useHandle)
	{
		m_trees[index].m_handle = m_treeTypes[state].m_data->m_handle;
		m_anythingChanged = 1;
		return;
	}

	m_trees[index].m_handle = 0xFF;
	m_anythingChanged = 1;
}
