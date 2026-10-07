// BFME layout reconstruction of BfmeThingAGA::bfmeFinishAGA.  This method
// drains the auxiliary list at +0x18 through the owning subobject at -0x20.

class BfmeFinishNodeAGA
{
public:
	BfmeFinishNodeAGA *m_bfmeNext;
	unsigned char m_bfmeGap[4];
	void *m_bfmeItem;
};

// ILT 0x00014F51 -> 0x00226800, the matched
// remove@Rva226800RemoveContain@@QAEXPAVObject@@_N@Z (OpenContain list removal).
class Object;

class Rva226800RemoveContain
{
public:
	void remove(Object *obj, bool exposeStealthUnits);
};

class BfmeThingAGA
{
public:
	unsigned char m_bfmeHead[0x18];
	BfmeFinishNodeAGA *m_bfmeList;

	void bfmeFinishAGA(void *what);
};

void BfmeThingAGA::bfmeFinishAGA(void *what)
{
	BfmeFinishNodeAGA *node = m_bfmeList->m_bfmeNext;
	while (node != m_bfmeList)
	{
		Rva226800RemoveContain *dispatcher =
			reinterpret_cast<Rva226800RemoveContain *>(
				reinterpret_cast<unsigned char *>(this) - 0x20);
		dispatcher->remove(static_cast<Object *>(node->m_bfmeItem), *reinterpret_cast<bool *>(&what));
		node = m_bfmeList->m_bfmeNext;
	}
}
