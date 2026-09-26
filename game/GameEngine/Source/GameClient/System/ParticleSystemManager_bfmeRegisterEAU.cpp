// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// The BFME conversion passes a copied particle template to this registration
// method. The manager replaces an existing map value in place or inserts the
// copied object under the supplied name.
// The map stores the copied object pointer without allocating another template.
// stlport

#define _STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_OWN_NAMESPACE 1
#include <hash_map>
#include <new>

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString;

class AsciiStringCompareShim
{
public:
	int compare(const AsciiString &other) const;

private:
	void *m_data;
};

class AsciiString
	: private StringBase<char>
{
public:
	AsciiString(const AsciiString &source) : StringBase<char>(source) {}

	int compare(const AsciiString &other) const
	{
		return ((const AsciiStringCompareShim *)this)->compare(other);
	}
	void set(const AsciiString &source)
	{
		StringBase<char>::set(source);
	}
	~AsciiString() {}
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

class BfmeStrEAU
{
public:
	void *m_bfmeDataEAU;
};

namespace FXParticleSystem
{

class ParticleSystemInfo
{
public:
	virtual ~ParticleSystemInfo();
};

class ParticleSystemTemplate : public ParticleSystemInfo
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &source);
	virtual ~ParticleSystemTemplate();
};

}

class ParticleSystemTemplate : public FXParticleSystem::ParticleSystemTemplate
{
public:
	virtual ~ParticleSystemTemplate();
};

typedef FXParticleSystem::ParticleSystemTemplate BfmeParticleTemplateBase;

class BfmeThingEAU
{
public:
	virtual ~BfmeThingEAU();

private:
	unsigned char m_beforeName[0x94];

public:
	AsciiString m_name;
	int m_slaveTemplate;
	unsigned char m_tail[0x30];
};

namespace rts
{

template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};

}

typedef _STL::hash_map<AsciiString, ParticleSystemTemplate *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > BfmeTemplateMap;

class ParticleSystemManager
{
public:
	void bfmeRegisterEAU(BfmeStrEAU *text, BfmeThingEAU *thing);

private:
	unsigned char m_beforeMap[0x9c];
	BfmeTemplateMap m_templateMap;
};

void ParticleSystemManager::bfmeRegisterEAU(BfmeStrEAU *text, BfmeThingEAU *thing)
{
	if (thing->m_name.compare(*(const AsciiString *)text) != 0)
		thing->m_name.set(*(const AsciiString *)text);

	BfmeTemplateMap::iterator find(m_templateMap.find(*(const AsciiString *)text));
	if (find != m_templateMap.end())
	{
		(*find).second->~ParticleSystemTemplate();
		new ((BfmeParticleTemplateBase *)(*find).second)
			BfmeParticleTemplateBase(
				*(const BfmeParticleTemplateBase *)thing);

		if (thing != NULL)
			delete thing;
		return;
	}

	ParticleSystemTemplate *const &templateThing =
		*(ParticleSystemTemplate *const *)&thing;
	if (!m_templateMap.insert(std::make_pair(*(const AsciiString *)text,
		templateThing)).second)
		delete thing;
}
