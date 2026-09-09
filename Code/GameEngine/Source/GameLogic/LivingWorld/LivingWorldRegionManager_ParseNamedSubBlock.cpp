// cl: /DNDEBUG /MD /EHsc
// stlport
//
// The Region field table registers this callback for LivingWorldRegion.  The
// parser allocates the 0xF4-byte region whose constructor installs vtable
// 0x01117258, calls BfmeThingDCG::bfmeGoDCG, then appends the pointer to the
// campaign vector at instance+0x30.

template <typename Type>
class StringBase
{
	friend class AsciiString;

	StringBase(const Type *text);
	void releaseBuffer();

private:
	void *m_data;
};

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

class Rva0061AF80Region : public BfmeThingDCG
{
public:
	Rva0061AF80Region(const AsciiString &name);

private:
	char m_body[0xF0];
};

#pragma comment(linker, "/alternatename:??0Rva0061AF80Region@@QAE@ABVAsciiString@@@Z=?d_0061af80@@YAXXZ")

#include <vector>

class LivingWorldRegionManager
{
public:
	static void parseNamedSubBlock(INI *ini, void *instance, void *, const void *);
};

class LivingWorldRegionStore
{
public:
	char m_pad[0x30];
	std::vector<Rva0061AF80Region *> m_regions;
};

// ?parseNamedSubBlock@LivingWorldRegionManager@@SAXPAVINI@@PAX1PBX@Z
void LivingWorldRegionManager::parseNamedSubBlock(
	INI *ini, void *instance, void *, const void *)
{
	Rva0061AF80Region *region = 0;
	const char *token = ini->getNextToken();
	region = new Rva0061AF80Region(AsciiString(token));
	region->bfmeGoDCG(reinterpret_cast<BfmeOtherDCG *>(ini));

	LivingWorldRegionStore *store =
		reinterpret_cast<LivingWorldRegionStore *>(instance);
	store->m_regions.push_back(region);
}
