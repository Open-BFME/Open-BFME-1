// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// OpenContain::finishUpdate at retail RVA 0x00224340.
// The OpenContain update caller and the 0x0000BA50 ILT identify this method.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

class Drawable
{
public:
	void rva00411DD0(Bool value);
};

class Object
{
public:
#define OBJECT_SLOT(n) virtual void *objectSlot##n();
	OBJECT_SLOT(00) OBJECT_SLOT(01) OBJECT_SLOT(02) OBJECT_SLOT(03)
	OBJECT_SLOT(04) OBJECT_SLOT(05) OBJECT_SLOT(06) OBJECT_SLOT(07)
	OBJECT_SLOT(08) OBJECT_SLOT(09)
	virtual Drawable *getDrawable();
#undef OBJECT_SLOT
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
	void destroyObject(Object *object);
};

extern GameLogic *TheGameLogic;

class BFMEReportDamageSource
{
public:
	void report(Object *owner, int setting);
};

class Rva00227B60ContainDispatch
{
public:
#define CONTAIN_SLOT(n) virtual void *containSlot##n();
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
	CONTAIN_SLOT(28) CONTAIN_SLOT(29) CONTAIN_SLOT(30) CONTAIN_SLOT(31)
	CONTAIN_SLOT(32) CONTAIN_SLOT(33) CONTAIN_SLOT(34) CONTAIN_SLOT(35)
	virtual void dispatch(Object *object, Bool flag);
#undef CONTAIN_SLOT
};

class OpenContainPrimaryBase
{
	virtual void primarySlot();

public:
	unsigned char m_padding[0x1c];
};

class OpenContain : public OpenContainPrimaryBase, public Rva00227B60ContainDispatch
{
public:
	void finishUpdate();

private:
	unsigned char m_padding24[0x14];
	_STL::list<Object *> m_containList;
	unsigned char m_padding44[0x80];
	int m_firstObjectID;
	int m_secondObjectID;
	int m_countdown;
};

void OpenContain::finishUpdate()
{
	if (m_firstObjectID == 0)
		return;
	if (m_countdown <= 0)
		return;
	--m_countdown;
	if (m_countdown != 0)
		return;

	Object *object = TheGameLogic->findObjectByID(m_firstObjectID);
	if (object == 0)
		return;

	dispatch(object, false);
	object->getDrawable()->rva00411DD0(true);

	Object *owner = TheGameLogic->findObjectByID(m_secondObjectID);
	if (owner != 0)
		((BFMEReportDamageSource *)owner)->report(object, 1);

	if (std::find(m_containList.begin(), m_containList.end(), object) ==
		m_containList.end())
		TheGameLogic->destroyObject(object);
}
