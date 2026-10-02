// cl: /Iinputs/reference/shims/stringbaseascii /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
// readable body of ??1W3DPropBuffer@@QAE@XZ: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBuffer.cpp
// Open-BFME: W3DPropBuffer::~W3DPropBuffer, retail 0x00702E50, 268 bytes.

typedef int Int;
typedef unsigned int UnsignedInt;

#include "Lib/BaseType.h"
#include "Common/AsciiString.h"
#include "light.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "Common/Snapshot.h"
inline Snapshot::Snapshot() {}
inline Snapshot::~Snapshot() {}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Tools/Launcher/Toolkit/Support/RefCounted.h
class RefCounted
{
public:
	virtual void deleteThis() = 0;

	void releaseRef()
	{
		if (--m_refCount == 0)
			deleteThis();
	}

private:
	UnsignedInt m_refCount;
};

// BFME array entries: 0x30-byte props and 0x18-byte prop types.
struct TProp
{
	TProp() {}
	~TProp() {}

	RefCounted *m_renderObject;
	char m_fields[0x2C];
};

struct TPropType
{
	RefCounted *m_renderObject;
	AsciiString m_renderObjectName;
	SphereClass m_bounds;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DPropBuffer.h
class W3DPropBuffer : Snapshot
{
public:
	W3DPropBuffer();
	~W3DPropBuffer();
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
	virtual void loadPostProcess();

private:
	TProp m_props[4000];
	Int m_numProps;
	bool m_anythingChanged;
	bool m_initialized;
	bool m_doCull;
	TPropType m_propTypes[96];
	Int m_numPropTypes;
	RefCounted *m_propShroudMaterialPass;
	void *m_bfmeExtraField;
	RefCounted *m_light;
};

static void release(RefCounted *&object)
{
	if (object)
	{
		object->releaseRef();
		object = 0;
	}
}

W3DPropBuffer::~W3DPropBuffer()
{
	for (Int i = 0; i < m_numProps; ++i)
		release(m_props[i].m_renderObject);

	for (Int i = 0; i < 96; ++i)
		release(m_propTypes[i].m_renderObject);

	release(m_light);
	release(m_propShroudMaterialPass);
}

// ?d_00702fa0@@YAXXZ
void d_00702fa0()
{
}

// The constructor's array counts and offsets use the BFME layout above.
// The canonical Snapshot and sphere inlines preserve retail's EH/store schedule.
// ??0W3DPropBuffer@@QAE@XZ
W3DPropBuffer::W3DPropBuffer()
	: m_numProps(0), m_anythingChanged(false), m_initialized(false),
	  m_doCull(false), m_numPropTypes(0), m_bfmeExtraField(0)
{
	for (int i = 0; i < 96; ++i) {
		m_propTypes[i].m_renderObject = 0;
		m_propTypes[i].m_bounds.Init(Vector3(0, 0, 0), 1);
	}
	for (int i = 0; i < 4000; ++i)
		m_props[i].m_renderObject = 0;

	// Keep the existing destructor's verified refcount-prefix view.
	m_light = (RefCounted *)new LightClass(LightClass::DIRECTIONAL);
	m_propShroudMaterialPass = (RefCounted *)new W3DShroudMaterialPassClass;
	m_initialized = true;
}
