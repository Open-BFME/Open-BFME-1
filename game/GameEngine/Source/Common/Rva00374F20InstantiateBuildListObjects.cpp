// ?instantiateBuildListObjects@Rva00374F20Receiver@@QAEX_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/AsciiString.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class BfmeTableERJ;
extern BfmeTableERJ *g_bfmeTableERJ;

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
	Object *rva00371650(BuildListInfo *info, bool state);
	void registerOwnedObject(Object *object);
};

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

	while (reinterpret_cast<BfmeIndexedMapOwner *>(g_bfmeTableERJ)->bfmeFindAndUse(
		key, index, reinterpret_cast<BfmeIndexedMapConsumer *>(&info)))
	{
		++index;
		reinterpret_cast<CastleBehavior *>(this)->registerOwnedObject(
			reinterpret_cast<CastleBehavior *>(this)->rva00371650(&info, state));
	}
}
