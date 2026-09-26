// ?xfer@ObjectSMCHelper@@MAEXPAVXfer@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ObjectSMCHelper::xfer at retail RVA 0x00257390.
// The matched constructor at 0x001C54A0 installs vtable 0x0109EBBC; slot 3
// is the xfer body. The timer list at this+0x20 is witnessed by the matched
// update, setModelConditionState, and destructor bodies.

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

// Retail reuses this aligned slot for the two-byte version, load index, and
// storing-path timer. The loading timer remains live with the index and uses
// its own eight-byte local.
union XferLocalStorage
{
	XferVersion m_version;
	Int m_index;
	Rva002571A0Elem m_storingTimer;
};

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

void ObjectSMCHelper::xfer(Xfer *xfer)
{
	((Rva00256C90Caller *)this)->invoke((FlagPairTarget *)xfer);

	if (xfer->IsLightCRC())
		return;

	{
		XferLocalStorage local;
		local.m_version.m_version = 1;
		local.m_version.m_currentVersion = 1;
		xfer->xferVersion(&local.m_version);

		{
			Int count = m_timers.size();
			xfer->xferInt(&count);

			if (xfer->IsStoring())
			{
				for (Rva002571A0List::iterator it = m_timers.begin(); it != m_timers.end(); )
				{
					local.m_storingTimer = *it;
					++it;
					Rva0010BDC0((MidVirtualSlot90Receiver *)xfer,
						&local.m_storingTimer.m_condition);
					xfer->xferUnsignedInt(&local.m_storingTimer.m_frame);
				}
			}
			else
			{
				for (local.m_index = 0; local.m_index < count; ++local.m_index)
				{
					Rva002571A0Elem timer;
					Rva0010BDC0((MidVirtualSlot90Receiver *)xfer,
						&timer.m_condition);
					xfer->xferUnsignedInt(&timer.m_frame);
					m_timers.push_back(timer);
				}
			}
		}
	}
}
