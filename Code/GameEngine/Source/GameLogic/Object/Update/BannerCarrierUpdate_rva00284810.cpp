// ?rva00284810@BannerCarrierUpdate@@QAEXPAVBannerCarrierObjectName@@_N@Z
// partial score=0.36 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Address-derived method name. The BannerCarrierUpdate class and member
// layout are established by the adjacent ctor and module-data methods.

#include "../../../../reference/shims/stringinline/StringInline.h"

typedef bool Bool;

struct Coord3D { float x, y, z; };

class BfmeConditionFlags
{
public:
	BfmeConditionFlags(int end, int a, int b, int c, int d, int e, int f,
		int g, int h, int i, int j, int k) throw();
	unsigned int words[10];
};

class BannerCarrierString;
class BannerCarrierObjectName;
class Object;

class BannerCarrierObjectPayload
{
public:
	BannerCarrierString *m_nameStorage;
	unsigned int m_fields[9];
};

class FXList
{
public:
	Bool isEmpty() const;
	void doFXObj(const Object *primary, const Object *secondary) const;
};

class BannerCarrierUpdateModuleData
{
public:
	BannerCarrierObjectPayload *rva00284700FindObjectName(
		BannerCarrierObjectPayload *result, const BannerCarrierString *name) const;
	AsciiString rva00283A20FindLocomotorName(
		const BannerCarrierString *name) const;

public:
	unsigned char m_prefix[0x30];
	FXList *m_bannerMorphFX;
};

class AIUpdateInterface
{
public:
	virtual void slots000();
	// Retail dispatches through vtable byte offset 0x1fc.  The intervening
	// declarations only establish that ABI slot.
	virtual void slots004(); virtual void slots008(); virtual void slots00c();
	virtual void slots010(); virtual void slots014(); virtual void slots018();
	virtual void slots01c(); virtual void slots020(); virtual void slots024();
	virtual void slots028(); virtual void slots02c(); virtual void slots030();
	virtual void slots034(); virtual void slots038(); virtual void slots03c();
	virtual void slots040(); virtual void slots044(); virtual void slots048();
	virtual void slots04c(); virtual void slots050(); virtual void slots054();
	virtual void slots058(); virtual void slots05c(); virtual void slots060();
	virtual void slots064(); virtual void slots068(); virtual void slots06c();
	virtual void slots070(); virtual void slots074(); virtual void slots078();
	virtual void slots07c(); virtual void slots080(); virtual void slots084();
	virtual void slots088(); virtual void slots08c(); virtual void slots090();
	virtual void slots094(); virtual void slots098(); virtual void slots09c();
	virtual void slots0a0(); virtual void slots0a4(); virtual void slots0a8();
	virtual void slots0ac(); virtual void slots0b0(); virtual void slots0b4();
	virtual void slots0b8(); virtual void slots0bc(); virtual void slots0c0();
	virtual void slots0c4(); virtual void slots0c8(); virtual void slots0cc();
	virtual void slots0d0(); virtual void slots0d4(); virtual void slots0d8();
	virtual void slots0dc(); virtual void slots0e0(); virtual void slots0e4();
	virtual void slots0e8(); virtual void slots0ec(); virtual void slots0f0();
	virtual void slots0f4(); virtual void slots0f8(); virtual void slots0fc();
	virtual void slots100(); virtual void slots104(); virtual void slots108();
	virtual void slots10c(); virtual void slots110(); virtual void slots114();
	virtual void slots118(); virtual void slots11c(); virtual void slots120();
	virtual void slots124(); virtual void slots128(); virtual void slots12c();
	virtual void slots130(); virtual void slots134(); virtual void slots138();
	virtual void slots13c(); virtual void slots140(); virtual void slots144();
	virtual void slots148(); virtual void slots14c(); virtual void slots150();
	virtual void slots154(); virtual void slots158(); virtual void slots15c();
	virtual void slots160(); virtual void slots164(); virtual void slots168();
	virtual void slots16c(); virtual void slots170(); virtual void slots174();
	virtual void slots178(); virtual void slots17c(); virtual void slots180();
	virtual void slots184(); virtual void slots188(); virtual void slots18c();
	virtual void slots190(); virtual void slots194(); virtual void slots198();
	virtual void slots19c(); virtual void slots1a0(); virtual void slots1a4();
	virtual void slots1a8(); virtual void slots1ac(); virtual void slots1b0();
	virtual void slots1b4(); virtual void slots1b8(); virtual void slots1bc();
	virtual void slots1c0(); virtual void slots1c4(); virtual void slots1c8();
	virtual void slots1cc(); virtual void slots1d0(); virtual void slots1d4();
	virtual void slots1d8(); virtual void slots1dc(); virtual void slots1e0();
	virtual void slots1e4(); virtual void slots1e8(); virtual void slots1ec();
	virtual void slots1f0(); virtual void slots1f4(); virtual void slots1f8();
	virtual void rvaSlot1FC(int locomotorSet);
};

class Object
{
public:
	void clearAndSetModelConditionFlags(const BfmeConditionFlags &clear,
		const BfmeConditionFlags &set);
	void bfmeRefreshPartitionCells();

	unsigned char m_prefix[0x38];
	Coord3D m_direction;
	unsigned char m_gap44[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

extern BfmeConditionFlags g_rva00284810ClearFlags;
extern const char *TheLocomotorSetNames[];
extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)

class INI
{
public:
	static int scanIndexList(const char *text, const char *const *names);
};

class BannerCarrierObjectName
{
public:
	unsigned char m_prefix[0x20];
	BannerCarrierString *m_nameView;
};

class BannerCarrierUpdate
{
public:
	void rva00284810(BannerCarrierObjectName *entry, Bool playMorphFX);

private:
	void *m_vtable;
	BannerCarrierUpdateModuleData *m_moduleData;
	Object *m_object;
};

void BannerCarrierUpdate::rva00284810(BannerCarrierObjectName *entry,
	Bool playMorphFX)
{
	BannerCarrierUpdateModuleData *const moduleData = m_moduleData;
	Object *const object = m_object;
	BannerCarrierObjectPayload payload;
	const BannerCarrierString *name =
		(const BannerCarrierString *)((unsigned char *)entry + 0x20);
	moduleData->rva00284700FindObjectName(&payload, name);

	static BfmeConditionFlags clearFlags(0, 0xcb, 0xae, 0xaf, 0xb0, 0xb1,
		0xb2, 0xb8, 0xb9, 0xba, 0xbb, 0xbc);
	object->clearAndSetModelConditionFlags(clearFlags,
		*(const BfmeConditionFlags *)&payload);

	const float directionX = object->m_direction.x;
	const float directionY = object->m_direction.y;
	const float directionZ = object->m_direction.z;
	const float length = (float)sqrt(directionX * directionX +
		directionY * directionY + directionZ * directionZ);
	if (length > 0.0f)
		object->bfmeRefreshPartitionCells();

	FXList *const morphFX = moduleData->m_bannerMorphFX;
	if (morphFX != 0 && playMorphFX && !morphFX->isEmpty())
		morphFX->doFXObj(object, 0);

	AsciiString locomotorName = moduleData->rva00283A20FindLocomotorName(name);
	void *stringData = *(void **)&locomotorName;
	if (stringData != 0 && *(unsigned short *)((char *)stringData + 4) != 0)
	{
		int set = INI::scanIndexList(locomotorName.str(), TheLocomotorSetNames);
		object->m_ai->rvaSlot1FC(set);
	}
}
