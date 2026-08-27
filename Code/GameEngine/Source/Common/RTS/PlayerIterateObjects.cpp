// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x000CDCF0, 77 bytes. reverse/reloc_names.csv names it
// ?iterateObjects@Player@@QBEXP6AXPAVObject@@PAX@Z1@Z and the parameters are
// right -- the back-reference in that decoration only comes out as Z1@Z if the
// second argument really is the void * the function pointer already mentioned.
// The return type is not, and neither is it bool. The result of each visit is
// tested with test eax,eax and the two exits set the whole register, so both
// this function and the one it calls return an int-width value; declaring
// either as bool narrows the test to test al,al and shortens the exits by
// three bytes. So the row goes in as H, and the void name keeps its thunk.
//
// The member at +0x288 is a pointer to a list header, not the header itself:
// the walk starts at what it points at and stops when the node comes back
// round to it. Node next is at +0x00 and the object at +0x08. The header is
// re-read from the member on every turn because the visit call could have
// moved it.
//
// Each object gets the two arguments passed straight through and a bool back;
// the first false ends the walk.

typedef int Int;

class Object;

typedef void (*ObjectIterateFunc)(Object *object, void *userData);

class BfmeInnerIterable
{
public:
	Int bfmeVisit(ObjectIterateFunc func, void *userData);
};

class Gen_000c8a30
{
public:
	Int m(void);
};

class BfmeIterableObject
{
public:
	Int bfmeIterate(ObjectIterateFunc func, void *userData);	// ILT 0x0003DB68

private:
	char m_bfmeHead[0x274];
	BfmeInnerIterable *m_bfmeInnerList;				// +0x274
};

// ?bfmeIterate@BfmeIterableObject@@QAEHP6AXPAVObject@@PAX@Z1@Z		70 bytes
Int BfmeIterableObject::bfmeIterate(ObjectIterateFunc func, void *userData)
{
	BfmeInnerIterable *node = m_bfmeInnerList;

	while (node)
	{
		if (!node->bfmeVisit(func, userData))
			return 0;

		if (node)
			node = (BfmeInnerIterable *)((Gen_000c8a30 *)node)->m();
	}

	return 1;
}

class BfmeObjectListNode
{
public:
	BfmeObjectListNode *m_bfmeNext;					// +0x00
	BfmeObjectListNode *m_bfmePrev;					// +0x04
	BfmeIterableObject *m_bfmeObject;				// +0x08
};

class Player
{
public:
	Int iterateObjects(ObjectIterateFunc func, void *userData) const;

private:
	char m_bfmeHead[0x288];
	BfmeObjectListNode *m_bfmeObjectList;				// +0x288
};

// ?iterateObjects@Player@@QBEHP6AXPAVObject@@PAX@Z1@Z
Int Player::iterateObjects(ObjectIterateFunc func, void *userData) const
{
	for (BfmeObjectListNode *node = m_bfmeObjectList->m_bfmeNext;
		node != m_bfmeObjectList;
		node = node->m_bfmeNext)
	{
		if (!node->m_bfmeObject->bfmeIterate(func, userData))
			return 0;
	}

	return 1;
}
