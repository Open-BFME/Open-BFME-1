namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate(unsigned int n);
	};
}

inline void *__cdecl operator new(unsigned int size, void *place)
{
	return place;
}

class BfmeThingXR
{
public:
	BfmeThingXR *bfmeResolveXR();

	unsigned char m_bfmeHeadXR[4];
	BfmeThingXR *m_bfmeSubXR;
	unsigned char m_bfmePadXR[8];
	void *m_bfmeValueXR;
};

struct BfmeValXR
{
	BfmeValXR(void *a, void *b)
	{
		m_bfmeAXR = a;
		m_bfmeBXR = b;
	}

	void *m_bfmeAXR;
	void *m_bfmeBXR;
};

struct BfmeLinkXR
{
	BfmeLinkXR *m_bfmePrevXR;
	BfmeLinkXR *m_bfmeNextXR;
	BfmeValXR m_bfmeValXR;
};

class BfmeOwnerXR
{
public:
	void bfmePushXR(BfmeThingXR *thing, void *extra);

	unsigned char m_bfmeHeadXR[0x650];
	BfmeLinkXR *m_bfmeListXR;
};

void BfmeOwnerXR::bfmePushXR(BfmeThingXR *thing, void *extra)
{
	BfmeThingXR *node = thing->m_bfmeSubXR;

	if (node != 0)
	{
		if (node->m_bfmeSubXR != 0)
			node = node->m_bfmeSubXR->bfmeResolveXR();
	}
	else
	{
		node = thing;
	}

	void *value = node->m_bfmeValueXR;
	// read early so it survives the allocation in a callee-saved register
	void *payload = *(void *volatile *)&extra;
	BfmeLinkXR *list = m_bfmeListXR;
	BfmeLinkXR *fresh = (BfmeLinkXR *)_STL::__new_alloc::allocate(0x10);

	new (&fresh->m_bfmeValXR) BfmeValXR(value, payload);

	BfmeLinkXR *next = list->m_bfmeNextXR;

	fresh->m_bfmePrevXR = list;
	fresh->m_bfmeNextXR = next;
	next->m_bfmePrevXR = fresh;
	list->m_bfmeNextXR = fresh;
}
