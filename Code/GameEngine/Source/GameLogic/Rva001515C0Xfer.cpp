// cl: /DNDEBUG /MD /O2 /EHs-c-

// Address-derived owner: retail RVA 0x001515C0.
// The body transfers a version, filters on CRC mode, walks the list at +0x04,
// recalculates each object's ID, and transfers fields at +0x08 through +0x28.
// No caller or vtable names the owning class, so the source keeps the safe
// address-derived name Rva001515C0.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

struct XferVersion
{
	XferVersion(Bool value) : m_version(value), m_currentVersion(value) {}
	Bool m_version;
	Bool m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual Bool isCRC();
	virtual Bool isLightCRC();
	virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23(); virtual void slot24(void *value); virtual void slot25();
	virtual void xferAsciiString(void *value);
	virtual void slot27(void *value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(int *value);
	virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual Bool xferBool(Bool *value);
};

namespace _STL
{
struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};

template <class T>
struct _List_node : public _List_node_base
{
	T _M_data;
};

template <class T>
class list
{
public:
	_List_node<T> *_M_node;
};
}

class Object
{
};

extern void __cdecl bfmeCalcTGC(void *xfer, int *value);

class Rva001515C0
{
public:
	void xfer(Xfer *xfer);

	void *m_vptr;
	_STL::list<Object *> m_objects;
	UnsignedInt m_value08;
	Bool m_value0c;
	Bool m_pad0d[3];
	Bool m_value10;
	Bool m_pad11[3];
	UnsignedInt m_value14;
	char m_pad18[4];
	void *m_value1c;
	char m_pad20[8];
	void *m_value28;
};

void Rva001515C0::xfer(Xfer *xfer)
{
	Rva001515C0 *self = this;
	XferVersion version(1);
	xfer->xferVersion(&version);
	if (!xfer->isCRC())
		return;

	_STL::_List_node<Object *> *node =
		(_STL::_List_node<Object *> *)self->m_objects._M_node->_M_next;
	while (node != self->m_objects._M_node)
	{
		Object *object = node->_M_data;
		ObjectID id = 0;
		if (object)
			id = *(ObjectID *)((char *)object + 0x74);
		bfmeCalcTGC(xfer, (int *)&id);
		node = (_STL::_List_node<Object *> *)node->_M_next;
	}

	xfer->xferUnsignedInt(&self->m_value08);
	xfer->slot27(&self->m_value0c);
	xfer->xferBool(&self->m_value10);
	xfer->xferUnsignedInt(&self->m_value14);
	xfer->slot24(&self->m_value1c);
	xfer->slot24(&self->m_value28);
}
