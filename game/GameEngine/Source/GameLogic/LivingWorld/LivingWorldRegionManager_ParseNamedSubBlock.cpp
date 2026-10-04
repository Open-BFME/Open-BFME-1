// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// The Region field table registers this callback for LivingWorldRegion.  The
// parser allocates the 0xF4-byte region whose constructor installs vtable
// 0x01117258, calls BfmeThingDCG::bfmeGoDCG, then appends the pointer to the
// campaign vector at instance+0x30.

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
};

class BfmeOtherDCG;

class BfmeThingDCG
{
public:
	void bfmeGoDCG(BfmeOtherDCG *other);

private:
	void *m_vtable;
};

// The ctor body at 0x0061AF80 is LivingWorldRegion's (vtable 0x01117258);
// only its declaration is needed here, the definition lives in
// LivingWorldRegionConstructor.cpp.
class LivingWorldRegion : public BfmeThingDCG
{
public:
	LivingWorldRegion(const AsciiString &name);

private:
	char m_body[0xF0];
};

#include <vector>

class LivingWorldRegionManager
{
public:
	static void parseNamedSubBlock(INI *ini, void *instance, void *store, const void *userData);
};

class LivingWorldRegionStore
{
public:
	char m_pad[0x30];
	std::vector<LivingWorldRegion *> m_regions;
};

// ?parseNamedSubBlock@LivingWorldRegionManager@@SAXPAVINI@@PAX1PBX@Z
void LivingWorldRegionManager::parseNamedSubBlock(
	INI *ini, void *instance, void *store, const void *userData)
{
	LivingWorldRegion *region = 0;
	const char *token = ini->getNextToken();
	region = new LivingWorldRegion(AsciiString(token));
	region->bfmeGoDCG(reinterpret_cast<BfmeOtherDCG *>(ini));

	LivingWorldRegionStore *self =
		reinterpret_cast<LivingWorldRegionStore *>(instance);
	self->m_regions.push_back(region);
}
