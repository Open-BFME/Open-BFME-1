// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading() const;
	virtual Bool isStoring() const;
	virtual void slot03();
	virtual Bool isLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *data, UnsignedInt size);
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(void *snapshot);
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
	virtual void xferAsciiString(void *value);
	virtual void xferReal(float *value);
	virtual void slot28();
	virtual void xferUnsignedInt(unsigned int *value);
	virtual void xferInt(Int *value);
	virtual void xferUnsignedShort(UnsignedShort *value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

struct BfmeFormattedText
{
	void *text;
	Int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *result, Int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern void j_0000240a();

static __forceinline void xferParticleSystemID(Xfer *xfer, void *value)
{
	typedef void (*XferParticleSystemID)(Xfer *, void *);
	union
	{
		void (*raw)(void);
		XferParticleSystemID call;
	} function;
	function.raw = j_0000240a;
	function.call(xfer, value);
}

union BoneFXUpdateXferLocal
{
	XferVersion version;
	BfmeFormattedText error;
};

class VectorInt
{
public:
	Int *m_begin;
	Int *m_end;
	Int *m_capacity;
};

class BehaviorModulePrimary
{
public:
	virtual void slot();
	const void *m_moduleData;
	void *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void slot();
};

class BehaviorModule : public BehaviorModulePrimary, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	protected:
	virtual void xfer(Xfer *xfer);

protected:
	Int m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	Int m_updateState;
};

class BoneFXUpdate : public UpdateModule
{
	protected:
	virtual void xfer(Xfer *xfer);

	private:
	std::vector<ParticleSystemID> m_particleSystemIDs;
	Int m_nextFXFrame[4][8];
	Int m_nextOCLFrame[4][8];
	Int m_nextParticleSystemFrame[4][8];
	unsigned char m_FXBonePositions[4][8][12];
	unsigned char m_OCLBonePositions[4][8][12];
	unsigned char m_PSBonePositions[4][8][12];
	Int m_curBodyState;
	Bool m_bonesResolved[4];
	Bool m_active;
};

// ?xfer@BoneFXUpdate@@MAEXPAVXfer@@@Z
void BoneFXUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->isLightCRC())
		return;

	BoneFXUpdateXferLocal local;
	local.version.m_version = 1;
	local.version.m_currentVersion = 1;
	xfer->xferVersion(&local.version);

	UnsignedShort particleSystemCount = m_particleSystemIDs.size();
	xfer->xferUnsignedShort(&particleSystemCount);
	ParticleSystemID systemID;
	if (xfer->isStoring())
	{
		for (std::vector<ParticleSystemID>::const_iterator it = m_particleSystemIDs.begin();
			it != m_particleSystemIDs.end(); ++it)
		{
			systemID = *it;
			xferParticleSystemID(xfer, &systemID);
		}
	}
	else
	{
		if (m_particleSystemIDs.empty() == false)
		{
			bfmeFormatText(&local.error, 5, 0);
			_CxxThrowException(&local.error, (void *)0x011DFE5C);
		}
		for (UnsignedShort i = 0; i < particleSystemCount; ++i)
		{
			xferParticleSystemID(xfer, &systemID);
			m_particleSystemIDs.push_back(systemID);
		}
	}

	xfer->xferUser(m_nextFXFrame, sizeof(Int) * 4 * 8);
	xfer->xferUser(m_nextOCLFrame, sizeof(Int) * 4 * 8);
	xfer->xferUser(m_nextParticleSystemFrame, sizeof(Int) * 4 * 8);
	xfer->xferUser(m_FXBonePositions, sizeof(unsigned char) * 4 * 8 * 12);
	xfer->xferUser(m_OCLBonePositions, sizeof(unsigned char) * 4 * 8 * 12);
	xfer->xferUser(m_PSBonePositions, sizeof(unsigned char) * 4 * 8 * 12);
	xfer->xferUser(&m_curBodyState, sizeof(Int));
	xfer->xferUser(m_bonesResolved, sizeof(Bool) * 4);
	xfer->xferBool(&m_active);
}
