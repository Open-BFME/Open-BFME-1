// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/Common/System /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// stlport
// Drawable::Drawable(const ThingTemplate *, DrawableStatus, Int), retail
// 0x00418DA0, 2484 bytes. Identity: the matched W3DGameClient::
// friend_createDrawable (0x006FBB20) news a 0x3D4-byte object and calls this
// body through ILT 0x000315B1; it installs the Drawable vtables 0x010F1560 /
// 0x010F154C that the matched Drawable::~Drawable (0x00419A10) installs.
// Ported from the Zero Hour Drawable constructor; the member layout follows
// the destructor TU (DrawableDestructor.cpp). Retail's EH states are
// Thing (0), Snapshot (1), the reference holder at +0x10C (2), the two
// strings at +0x2D4/+0x2D8 (3, 4), the vector at +0x2F8 (5) and the 0x90-byte
// object at +0x31C (6). Members BFME added keep offset-derived names.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "matrix3d.h"
#include "coord3d.h"
#include "snapshot.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long *);
#include <string.h>

// The retail ModuleInfo::getNthName return type (pinned spelling at ILT
// 0x0000EB56) and the 0x00887940 buffer release it destroys with.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
	void clear() { releaseBuffer(); }
	// Retail inlines the comparison: length first, then the data pointer,
	// memicmp over the shorter length, then the length difference.
	Int compareNoCase(const char *s) const
	{
		Int len = m_data ? m_data->length : 0;
		const char *p = m_data ? m_data->data : "";
		Int slen = strlen(s);
		Int c = _memicmp(p, s, len < slen ? len : slen);
		if (c != 0)
			return c;
		return len - slen;
	}

private:
	void releaseBuffer();
	struct Header
	{
		Int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};
	Header *m_data;
};

class ThingTemplate;
class Module;
class ModuleData;
class Xfer;

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0
};

enum ModuleType
{
	MODULETYPE_BEHAVIOR = 0,
	MODULETYPE_DRAW = 1,
	MODULETYPE_CLIENT_UPDATE = 2,
	MODULETYPE_2B8 = 3
};

// Thing is the 0x60-byte primary base; its constructor is matched at 0x001328C0.
class Thing
{
public:
	Thing(const ThingTemplate *thingTemplate);
	virtual ~Thing();

private:
	char m_04[0x5c];
};

// Module-data virtuals the constructor reads.
class DrawableModuleData00418DA0
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
	virtual void s30(); virtual void s34();
	virtual Int getMinimumRequiredGameLOD() const;
	virtual void s3c();
	virtual Bool s40() const;
};

class DrawableModule00418DA0
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
	virtual void s10();
	virtual void onObjectCreated();
};

// ThingTemplate's ModuleInfo: a vector of 20-byte nuggets, data at +8.
class ModuleInfo
{
public:
	struct Nugget
	{
		char m_00[8];
		const ModuleData *second;
		char m_0c[8];
	};

	Int getCount() const { return m_info.size(); }
	const ModuleData *getNthData(Int i) const
	{
		if (i >= 0 && i < m_info.size())
			return m_info[i].second;
		return 0;
	}
	BFMERetailAsciiString getNthName(Int i) const;

private:
	std::vector<Nugget> m_info;
};

class ThingTemplateView00418DA0
{
public:
	char m_00[0xc8];
	unsigned char m_kindof;
	char m_c9[0x2a0 - 0xc9];
	ModuleInfo m_drawModuleInfo;
	ModuleInfo m_clientUpdateModuleInfo;
	ModuleInfo m_2b8;
	char m_2c4[0x3c0 - 0x2c4];
	Real m_assetScale;
};

inline const ThingTemplateView00418DA0 *view(const ThingTemplate *t)
{
	return reinterpret_cast<const ThingTemplateView00418DA0 *>(t);
}

class ModuleFactory
{
public:
	Module *newModule(Thing *thing, const BFMERetailAsciiString &name,
		const ModuleData *data, ModuleType type);
};
extern ModuleFactory *TheModuleFactory;

class Drawable;

class GameClient
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
	virtual void s20(); virtual void s24();
	virtual void registerDrawable(Drawable *draw);
};
extern GameClient *TheGameClient;

class GlobalData
{
public:
	char m_00[0x1a];
	Bool m_1a;
	char m_1b;
	Bool m_1c;
};
extern GlobalData *TheWritableGlobalData;

class GameLODManager
{
public:
	char m_00[0x16c4];
	Int m_16c4;
};
extern GameLODManager *TheGameLODManager;

class GameLogic
{
public:
	char m_00[0x69];
	Bool m_69;
};
extern GameLogic *TheGameLogic;

class GameState
{
public:
	char m_00[0x54];
	Bool m_54;
};
extern GameState *TheGameState;

class AudioManager
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18();
	virtual void removeAudioEvent(UnsignedInt);
};
extern AudioManager *TheAudio;

class Audio00418DA0
{
public:
	char m_00[0x10];
	UnsignedInt m_10;
};

class BodyModule00418DA0
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
	virtual Int s20() const;
};

class Object00418DA0
{
public:
	char m_00[0x200];
	BodyModule00418DA0 *m_200;
};

// The body at 0x00417710 (ILT 0x0002CB79), existing pinned spelling.
class Gen_00417cb0
{
	friend class Drawable;
	void bfmeEmit(void *, void *);
};

class RefTarget00418DA0
{
public:
	virtual ~RefTarget00418DA0();
	long m_04;
	void release()
	{
		long count = InterlockedDecrement(&m_04);
		if (count <= 0)
			delete this;
	}
};

class RefHolder00418DA0
{
public:
	RefHolder00418DA0() : p(0) {}
	~RefHolder00418DA0()
	{
		if (p)
			p->release();
	}
	RefTarget00418DA0 *p;
};

// The five-dword block at +0x23C; its constructor sets the first field to -1.
struct Info00418DA0
{
	Info00418DA0() : m_00(-1), m_04(0), m_08(0), m_0c(0), m_10(0) {}
	Int m_00;
	UnsignedInt m_04;
	void *m_08;
	UnsignedInt m_0c;
	UnsignedInt m_10;
};

// Three 40-byte bit sets at +0x250/+0x278/+0x2A0, each cleared by its
// constructor.
struct Flags00418DA0
{
	Flags00418DA0() { memset(w, 0, sizeof(w)); }
	UnsignedInt w[10];
};

// The 0x90-byte object at +0x31C, constructor matched at 0x00413400.
struct Rva00413400Owner
{
	Rva00413400Owner();
	char matrices[0x60];
	Coord3D points[4];
};

class Drawable : public Thing, public Snapshot
{
public:
	Drawable(const ThingTemplate *thingTemplate, DrawableStatus statusBits, Int drawableID);
	virtual ~Drawable();

	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &);

private:
	static void initStaticImages();

	void *m_64;
	void *m_colorTintEnvelope;
	Vector3 m_6c;
	UnsignedInt m_78;
	UnsignedInt m_7c;
	UnsignedInt m_80;
	UnsignedInt m_84;
	UnsignedInt m_88;
	void *m_8c;
	UnsignedInt m_90;
	UnsignedInt m_94;
	UnsignedInt m_98;
	UnsignedInt m_9c;
	UnsignedInt m_a0;
	UnsignedInt m_a4;
	Int m_a8;
	Real m_ac;
	Real m_b0;
	Real m_b4;
	Real m_b8;
	Real m_bc;
	Real m_c0;
	Real m_c4;
	UnsignedInt m_c8;
	Real m_cc;
	UnsignedInt m_d0;
	Int m_d4;
	UnsignedInt m_d8;
	UnsignedInt m_dc;
	UnsignedInt m_e0;
	unsigned char m_e4;
	UnsignedInt m_e8;
	UnsignedInt m_ec;
	UnsignedInt m_f0;
	Real m_f4;
	Real m_f8;
	Object00418DA0 *m_object;
	UnsignedInt m_id;
	Drawable *m_nextDrawable;
	Drawable *m_prevDrawable;
	RefHolder00418DA0 m_10c;
	UnsignedInt m_status;
	UnsignedInt m_114;
	UnsignedInt m_118;
	UnsignedInt m_11c;
	UnsignedInt m_120;
	UnsignedInt m_124;
	UnsignedInt m_128;
	UnsignedInt m_12c;
	UnsignedInt m_130;
	UnsignedInt m_134;
	void *m_locoInfo;
	UnsignedInt m_13c;
	Bool m_140;
	Bool m_141;
	Bool m_142;
	Bool m_143;
	Audio00418DA0 *m_ambientSound;
	Audio00418DA0 *m_148;
	Audio00418DA0 *m_14c;
	Module **m_modules[3];
	UnsignedInt m_15c;
	UnsignedInt m_160;
	UnsignedInt m_164;
	Matrix3D m_168;
	Matrix3D m_198;
	Matrix3D m_1c8;
	Real m_instanceScale;
	Int m_1fc;
	Matrix3D m_200;
	Vector3 m_230;
	Info00418DA0 m_23c;
	Flags00418DA0 m_250;
	Flags00418DA0 m_278;
	Flags00418DA0 m_2a0;
	Real m_2c8;
	void *m_2cc;
	void *m_captionDisplayString;
	BFMERetailAsciiString m_2d4;
	BFMERetailAsciiString m_2d8;
	UnsignedInt m_2dc;
	void *m_2e0;
	UnsignedInt m_2e4;
	UnsignedInt m_2e8;
	UnsignedInt m_2ec;
	Int m_2f0;
	UnsignedInt m_2f4;
	std::vector<UnsignedInt> m_2f8;
	Int m_304;
	UnsignedInt m_308;
	UnsignedInt m_30c;
	UnsignedInt m_310;
	UnsignedInt m_314;
	Bool m_318;
	Bool m_319;
	Bool m_31a;
	Bool m_31b;
	Rva00413400Owner m_31c;
	Bool m_3ac;
	Bool m_3ad;
	Bool m_3ae;
	Bool m_3af;
	Bool m_3b0;
	Bool m_3b1;
	Bool m_3b2;
	Bool m_3b3;
	Bool m_3b4;
	UnsignedInt m_3b8;
	void *m_3bc;
	UnsignedInt m_3c0;
	char m_3c4[0x10];
};

Drawable::Drawable(const ThingTemplate *thingTemplate, DrawableStatus statusBits, Int drawableID)
	: Thing(thingTemplate),
	  m_64(0), m_colorTintEnvelope(0),
	  m_78(0), m_7c(0), m_80(0), m_84(0), m_88(0), m_8c(0),
	  m_a8(7),
	  m_ac(1.0f), m_b0(1.0f), m_b4(1.0f), m_b8(1.0f), m_bc(1.0f), m_c0(1.0f), m_c4(1.0f),
	  m_c8(0), m_cc(1.0f), m_d0(0), m_d4(10), m_d8(0), m_dc(0), m_e0(0), m_e4(0),
	  m_f0(0), m_f4(1.0f), m_f8(0.03f),
	  m_object(0), m_id(0), m_nextDrawable(0), m_prevDrawable(0),
	  m_status(statusBits),
	  m_114(0), m_118(0), m_11c(0), m_120(0), m_124(0), m_128(0), m_12c(0), m_130(0), m_134(0),
	  m_locoInfo(0), m_13c(0),
	  m_140(true), m_141(true), m_142(true), m_143(true),
	  m_ambientSound(0), m_148(0), m_14c(0),
	  m_15c(0), m_160(0), m_164(0),
	  m_1fc(-1),
	  
	  m_2c8(-1.0f), m_2cc(0), m_captionDisplayString(0),
	  m_2dc(0), m_2e0(0), m_2e4(0), m_2e8(0), m_2ec(0),
	  m_2f4(0),
	  m_304(-1), m_308(0), m_30c(0), m_310(0), m_314(0),
	  m_318(false), m_319(false), m_31a(false), m_31b(false),
	  m_3ac(false), m_3ad(false), m_3ae(false), m_3af(true), m_3b0(false),
	  m_3b2(true), m_3b3(true), m_3b4(false),
	  m_3b8(0), m_3bc(0)
{
	Int i;
	memset(m_modules, 0, sizeof(m_modules));

	m_198.Make_Identity();
	m_200.Make_Identity();
	m_230.Set(0.0f, 0.0f, 0.0f);
	m_168.Make_Identity();

	m_23c.m_04 = 0;
	m_23c.m_08 = this;
	m_23c.m_0c = 0;
	m_23c.m_10 = 0;

	m_6c.Set(1.0f, 1.0f, 1.0f);

	m_90 = 0;
	m_94 = 0;
	m_98 = 0;
	m_9c = 0;
	m_a0 = 0;
	m_a4 = 0;

	m_instanceScale = view(thingTemplate)->m_assetScale;
	m_2f0 = drawableID;

	TheGameClient->registerDrawable(this);
	if (TheGameClient == 0)
		return;

	Int modIdx;
	Module **m;
	Int lod = TheGameLODManager->m_16c4;

	const ModuleInfo &drawMI = view(thingTemplate)->m_drawModuleInfo;
	m_modules[0] = new Module *[drawMI.getCount() + 1];
	m = m_modules[0];
	for (modIdx = 0; modIdx < drawMI.getCount(); ++modIdx)
	{
		const ModuleData *newModData = drawMI.getNthData(modIdx);
		const DrawableModuleData00418DA0 *data =
			reinterpret_cast<const DrawableModuleData00418DA0 *>(newModData);
		if (TheWritableGlobalData->m_1c && data->getMinimumRequiredGameLOD() > lod)
			continue;
		*m++ = TheModuleFactory->newModule(this, drawMI.getNthName(modIdx), newModData, MODULETYPE_DRAW);
		if (!data->s40())
			m_31b = true;
	}
	*m = 0;

	const ModuleInfo &cuMI = view(thingTemplate)->m_clientUpdateModuleInfo;
	if (cuMI.getCount())
	{
		m_modules[1] = new Module *[cuMI.getCount() + 1];
		m = m_modules[1];
		for (modIdx = 0; modIdx < cuMI.getCount(); ++modIdx)
		{
			const ModuleData *newModData = cuMI.getNthData(modIdx);
			if ((view(thingTemplate)->m_kindof & 0x40) &&
				!TheWritableGlobalData->m_1a &&
				cuMI.getNthName(modIdx).compareNoCase("SwayClientUpdate") == 0)
				continue;
			*m++ = TheModuleFactory->newModule(this, cuMI.getNthName(modIdx), newModData, MODULETYPE_CLIENT_UPDATE);
		}
		*m = 0;
	}

	const ModuleInfo &thirdMI = view(thingTemplate)->m_2b8;
	if (thirdMI.getCount())
	{
		m_modules[2] = new Module *[thirdMI.getCount() + 1];
		m = m_modules[2];
		for (modIdx = 0; modIdx < thirdMI.getCount(); ++modIdx)
		{
			const ModuleData *newModData = thirdMI.getNthData(modIdx);
			*m++ = TheModuleFactory->newModule(this, thirdMI.getNthName(modIdx), newModData, MODULETYPE_2B8);
		}
		*m = 0;
	}

	for (i = 0; i < 3; ++i)
	{
		for (Module **mm = m_modules[i]; mm && *mm; ++mm)
			reinterpret_cast<DrawableModule00418DA0 *>(*mm)->onObjectCreated();
	}

	initStaticImages();

	if (TheGameLogic != 0 && !TheGameLogic->m_69 && TheGameState != 0 && !TheGameState->m_54 &&
		m_140 && m_141 && m_143)
	{
		if (m_ambientSound)
			TheAudio->removeAudioEvent(m_ambientSound->m_10);
		if (m_148)
			TheAudio->removeAudioEvent(m_148->m_10);
		Int bodyState = 0;
		if (m_object)
			bodyState = m_object->m_200->s20();
		reinterpret_cast<Gen_00417cb0 *>(this)->bfmeEmit(reinterpret_cast<void *>(bodyState), 0);
	}

	m_3c0 = 0;
	m_2d4.clear();
	m_2d8.clear();
}
