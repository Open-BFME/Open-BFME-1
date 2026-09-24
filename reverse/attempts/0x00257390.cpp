// ?xfer@ObjectSMCHelper@@MAEXPAVXfer@@@Z
// partial score=0.99 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ObjectSMCHelper::xfer, retail 0x00257390 (290 bytes).
//
// Identity: slot 3 of vftable 0x0109EBBC, which the matched ObjectSMCHelper
// constructor 0x001C54A0 installs; slot 3 is the xfer position, as for the
// matched RadarObject::xfer.  The body transfers the base helper, then (unless
// the xfer is a light CRC pass) version 1 and the list of pending
// (model condition, frame) timers that setModelConditionState fills.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual void slot03();
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
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
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
};

class MidVirtualSlot90Receiver;

void Rva0010BDC0(MidVirtualSlot90Receiver *xfer, void *value);

class FlagPairTarget;

// The base helper's xfer, matched at 0x00256C90 under this address name.
class Rva00256C90Caller
{
public:
	void invoke(FlagPairTarget *xfer);
};

struct __declspec(align(8)) Rva002571A0Elem
{
	UnsignedInt m_condition;
	UnsignedInt m_frame;
};

typedef _STL::list<Rva002571A0Elem> Rva002571A0List;

class Object;

class UpdateModule
{
public:
	virtual void updateModuleAnchor();

protected:
	void *m_moduleData;
	Object *m_object;
};

class ObjectHelper : public UpdateModule
{
public:
	virtual ~ObjectHelper();
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectSMCHelper.h
class ObjectSMCHelper : public ObjectHelper,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_padding[0xc];
	Rva002571A0List m_timers;
};

// ?xfer@ObjectSMCHelper@@MAEXPAVXfer@@@Z
void ObjectSMCHelper::xfer(Xfer *xfer)
{
	((Rva00256C90Caller *)this)->invoke((FlagPairTarget *)xfer);

	if (xfer->IsLightCRC())
		return;

	{
		XferVersion version;
		version.m_version = 1;
		version.m_currentVersion = 1;
		xfer->xferVersion(&version);
	}

	{
	Int count = m_timers.size();
	xfer->xferInt(&count);

	if (xfer->IsStoring())
	{
		for (Rva002571A0List::iterator it = m_timers.begin(); it != m_timers.end(); )
		{
			Rva002571A0Elem timer = *it;
			++it;
			Rva0010BDC0((MidVirtualSlot90Receiver *)xfer, &timer.m_condition);
			xfer->xferUnsignedInt(&timer.m_frame);
		}
	}
	else
	{
		for (Int i = 0; i < count; ++i)
		{
			Rva002571A0Elem timer;
			Rva0010BDC0((MidVirtualSlot90Receiver *)xfer, &timer.m_condition);
			xfer->xferUnsignedInt(&timer.m_frame);
			m_timers.push_back(timer);
		}
	}
	}
}
