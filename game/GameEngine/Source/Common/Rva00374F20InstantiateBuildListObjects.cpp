// ?instantiateBuildListObjects@Rva00374F20Receiver@@QAEX_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/AsciiString.h"

#include "../../Include/Common/NameKeyType.h"




// Canonical retail type of the 0x012EF428 singleton; pointee only, so a forward
// declaration is enough.  The definition lives in
// game/GameEngine/Source/Common/System/game_engine_subsystems.h.
class SidesList;

// Retail global at 0x012EF428, ?TheSidesList@@3PAVSidesList@@A.
extern SidesList *TheSidesList;

class BfmeIndexedMapConsumer;
class BfmeIndexedMapOwner
{
public:
	bool bfmeFindAndUse(int key, int index, BfmeIndexedMapConsumer *consumer);
};

class Object;
class Rva00374F20Receiver;

class BuildListInfo
{
public:
	BuildListInfo();

private:
	AsciiString m_buildingName;
	AsciiString m_templateName;
	char m_unmodelledTail[0x80];

protected:
	virtual ~BuildListInfo();
	friend class Rva00374F20Receiver;
};

// These are callee-only ABI views; the target method's owner stays opaque.
class CastleBehavior
{
public:
	void registerOwnedObject(Object *object);
};
// The body at 0x00371650 is linked as the gen-dump ?d_00371650@@YAXXZ, so the
// thiscall is reached through a member-pointer call (the pattern the Apt
// callers of ?d_008cc940 use).
extern void d_00371650();
typedef Object *(CastleBehavior::*CastleBehavior00371650)(BuildListInfo *info, bool state);

// The call site passes its receiver in ECX and consumes this callee's EAX.
class Rva0036EF70Owner
{
public:
	NameKeyType d_0036ef70Method(void);
};

class Rva00374F20Receiver
{
public:
	void instantiateBuildListObjects(bool state);
};

void Rva00374F20Receiver::instantiateBuildListObjects(bool state)
{
	const NameKeyType key =
		reinterpret_cast<Rva0036EF70Owner *>(this)->d_0036ef70Method();
	int index = 0;
	BuildListInfo info;
	union { void (*fn)(); CastleBehavior00371650 call; } make = { d_00371650 };

	while (reinterpret_cast<BfmeIndexedMapOwner *>(TheSidesList)->bfmeFindAndUse(
		key, index, reinterpret_cast<BfmeIndexedMapConsumer *>(&info)))
	{
		++index;
		reinterpret_cast<CastleBehavior *>(this)->registerOwnedObject(
			(reinterpret_cast<CastleBehavior *>(this)->*make.call)(&info, state));
	}
}
