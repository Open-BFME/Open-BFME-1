// Opaque owner reconstruction for the carved BFME transfer body.
// Field types are limited to offsets and helper ABIs proven by retail code.
// cl: /Ireference/shims/stlp_nodealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define BFME_STLP_NODE_ALLOC
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <vector>
#include <map>

#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class XferVersion
{
public:
	XferVersion(UnsignedByte major, UnsignedByte minor) :
		m_major(major), m_minor(minor) {}

	UnsignedByte m_major;
	UnsignedByte m_minor;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual Bool isDoingCRC();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08(void *data, Int size);
	virtual void xferUser(void *data, Int size);
	virtual void xferVersion(XferVersion &version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(AsciiString &value);
	virtual void xferReal(Real &value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt &value);
	virtual void xferInt(Int &value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool &value);
};

typedef _STL::vector<ObjectID> ObjectIDVector;

struct Rva000A3F30Value
{
	char m_body[4];
};

typedef _STL::pair<const int, Rva000A3F30Value> Rva000A3F30Pair;
typedef _STL::_Rb_tree<int,
	Rva000A3F30Pair,
	_STL::_Select1st<Rva000A3F30Pair>,
	_STL::less<int>,
	_STL::allocator<Rva000A3F30Pair> > Rva000A3F30Tree;

extern void __cdecl xferObjectID0010C3C0(Xfer *xfer, UnsignedInt *value);
extern Xfer *__cdecl Rva00372670XferObjectIDVector(Xfer *xfer, ObjectIDVector *vector);

class BfmeSeedTarget;

class Gen_00375590
{
public:
	void createPlayerObject();
};

class Gen_002B9EC0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);
};

class Rva00375A00Owner
{
public:
	void xfer(Xfer *xfer);

	unsigned char m_pad00[0x9c];
	UnsignedInt m_field9c;
	UnsignedInt m_fielda0;
	Bool m_fielda4;
	Bool m_fielda5;
	unsigned char m_pada6[2];
	Real m_fielda8;
	Bool m_fieldac;
	unsigned char m_padad[3];
	UnsignedInt m_fieldb0;
	unsigned char m_padb4[4];
	ObjectIDVector m_fieldb8;
	ObjectIDVector m_fieldc4;
	ObjectIDVector m_fieldd0;
	ObjectIDVector m_fielddc;
	unsigned char m_pade8[0x18];
	AsciiString m_field100;
	Int m_field104;
	Rva000A3F30Tree m_field108;
};

struct Rva00375A00VectorLayout
{
	ObjectID *m_begin;
	ObjectID *m_end;
	ObjectID *m_storage;
};

void Rva00375A00Owner::xfer(Xfer *xfer)
{
	ObjectID value;
	UnsignedInt fieldb8Count;
	UnsignedInt fieldc4Count;
	XferVersion version(1, 2);
	xfer->xferVersion(version);
	xfer->xferUser(&m_field9c, 4);
	xferObjectID0010C3C0(xfer, &m_fielda0);
	xfer->xferBool(m_fielda4);
	xfer->xferBool(m_fielda5);
	xfer->xferReal(m_fielda8);

	Rva00372670XferObjectIDVector(xfer, &m_fieldb8);
	xfer->xferInt(m_field104);
	fieldb8Count = m_fieldb8.size();
	xfer->xferInt(*reinterpret_cast<Int *>(&fieldb8Count));
	if (xfer->isSaving())
	{
		ObjectIDVector::iterator current = m_fieldb8.begin();
		while (current != m_fieldb8.end())
		{
			value = *current;
			xferObjectID0010C3C0(xfer, reinterpret_cast<UnsignedInt *>(&value));
			++current;
		}
	}
	else
	{
		Rva00375A00VectorLayout *vector =
			reinterpret_cast<Rva00375A00VectorLayout *>(&m_fieldb8);
		ObjectID *source = vector->m_end;
		ObjectID *destination = vector->m_begin;
		Int count = (int)(vector->m_end - source);
		while (count > 0)
		{
			*destination = *source;
			++source;
			++destination;
			--count;
		}
		vector->m_end = destination;
		for (Int i = 0; i < fieldb8Count; ++i)
		{
			xferObjectID0010C3C0(xfer, reinterpret_cast<UnsignedInt *>(&value));
			m_fieldb8.push_back(value);
		}
	}

	fieldc4Count = (UnsignedInt)m_fieldc4.size();
	xfer->xferInt(*reinterpret_cast<Int *>(&fieldc4Count));
	if (xfer->isSaving())
	{
		ObjectIDVector::iterator current = m_fieldc4.begin();
		while (current != m_fieldc4.end())
		{
			value = *current;
			xferObjectID0010C3C0(xfer, reinterpret_cast<UnsignedInt *>(&value));
			++current;
		}
	}
	else
	{
		for (Int i = 0; i < fieldc4Count; ++i)
		{
			xferObjectID0010C3C0(xfer, reinterpret_cast<UnsignedInt *>(&value));
			m_fieldc4.push_back(value);
		}
	}

	Rva00372670XferObjectIDVector(xfer, &m_fieldd0);
	xfer->xferUnsignedInt(m_fieldb0);
	if (version.m_minor >= 2)
	{
		xfer->xferBool(m_fieldac);
	}
	if (xfer->isLoading() && m_field9c != 0)
	{
		reinterpret_cast<Gen_00375590 *>(this)->createPlayerObject();
	}
	reinterpret_cast<Gen_002B9EC0 *>(this)->bfmeSeed(reinterpret_cast<BfmeSeedTarget *>(xfer));

	Rva00372670XferObjectIDVector(xfer, &m_fielddc);
	xfer->xferAsciiString(m_field100);
	if (xfer->isSaving())
	{
		Int count = m_field108.size();
		xfer->xferInt(count);
		Rva000A3F30Tree::iterator current = m_field108.begin();
		while (current != m_field108.end())
		{
			Int key = current->first;
			xfer->xferInt(key);
			UnsignedInt value = *reinterpret_cast<UnsignedInt *>(&current->second);
			xfer->xferUnsignedInt(value);
			++current;
		}
	}
	else
	{
		Int count;
		xfer->xferInt(count);
		while (count != 0)
		{
			Int key;
			UnsignedInt value;
			xfer->xferInt(key);
			xfer->xferUnsignedInt(value);
			Rva000A3F30Value mapped;
			*reinterpret_cast<UnsignedInt *>(&mapped) = value;
			m_field108.insert_unique(Rva000A3F30Pair(key, mapped));
			--count;
		}
	}
}
