// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Complete destructor 0x00284AA0 and emitted scalar wrapper 0x00285490.
// Constructor 0x00284600 installs vtable 0x010BBBB8; its slot-zero path and
// the matched object-name/locomotor lookups identify the same module data.
// Keep both lifecycle bodies and pointer-vector helpers in this one source.
//
// The constructor is a 0x40-byte object (vptr + 0x3c, the size the matched
// factory 0x00119C40 news up before running it). Its two `clear()` calls on
// freshly default-constructed vectors are not redundant: retail still carries
// both inlined STLport `__copy_trivial` bodies, each with a folded-out
// `__last == __first` test and the surviving `__imp__BfmeMemMove` call, so the
// two vectors must be cleared in the ctor body rather than left to their own
// initializers. The base carries no ctor; the four dwords at +0x08..+0x14 are
// written from the derived body, which is the order retail emits them in.

extern "C" __declspec(dllimport) void *__cdecl memmove(
	void *destination, const void *source, unsigned int bytes );
#define memmove memmove
#include <vector>
#undef memmove

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef AsciiString BannerCarrierString;

// The two named-effect slots the constructor clears are plain pointers at
// +0x30/+0x34; nothing in the matched destructor runs for them, so they stay
// aggregate here rather than borrowing a destructor this TU cannot call.
struct BannerCarrierEffectSlot
{
	void *m_data;
};

class BannerCarrierObjectName
{
	BannerCarrierString m_name;
	unsigned char m_pad[0x2c];
	BannerCarrierString m_templateName;
};

class BannerCarrierUpgrade
{
public:
	~BannerCarrierUpgrade();
};

class BannerCarrierUpdateModuleDataBase
{
public:
	virtual ~BannerCarrierUpdateModuleDataBase() {}
protected:
	unsigned char m_unknown04[4];
	int m_field08;
	int m_field0C;
	int m_field10;
	int m_field14;
};

class BannerCarrierUpdateModuleData : public BannerCarrierUpdateModuleDataBase
{
public:
	BannerCarrierUpdateModuleData();
	virtual ~BannerCarrierUpdateModuleData();
private:
	std::vector<BannerCarrierObjectName *> m_objectNames;
	std::vector<BannerCarrierUpgrade *> m_upgrades;
	BannerCarrierEffectSlot m_bannerMorphFX;
	BannerCarrierEffectSlot m_unitSpawnFX;
	unsigned char m_replenishNearbyHorde;
	unsigned char m_replenishAllNearbyHordes;
	unsigned char m_padding[2];
	float m_scanHordeDistance;
};

BannerCarrierUpdateModuleData::BannerCarrierUpdateModuleData()
{
	// +0x08 = 75 and +0x0C/+0x10/+0x14 = 50, one shared 0x32 register.
	m_field08 = 75;
	m_field0C = 50;
	m_field10 = 50;
	m_field14 = 50;
	m_bannerMorphFX.m_data = 0;
	m_unitSpawnFX.m_data = 0;
	// Both keep their inlined erase() and its memmove; see the header note.
	m_objectNames.clear();
	m_upgrades.clear();
	m_replenishNearbyHorde = 0;
	m_replenishAllNearbyHordes = 0;
	m_scanHordeDistance = 0;
}

// ??1BannerCarrierUpdateModuleData@@UAE@XZ
BannerCarrierUpdateModuleData::~BannerCarrierUpdateModuleData()
{
	for (unsigned int i = 0; i < m_objectNames.size(); ++i)
		delete m_objectNames[i];
	m_objectNames.clear();

	for (unsigned int i = 0; i < m_upgrades.size(); ++i)
		delete m_upgrades[i];
	m_upgrades.clear();
}
