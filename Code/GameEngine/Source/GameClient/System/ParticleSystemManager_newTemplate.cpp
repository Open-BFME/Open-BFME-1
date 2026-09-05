// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef bool Bool;
typedef int Int;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_string.m_data ? str.m_string.m_data->length : 0;
		const char *data = str.m_string.m_data ? &str.m_string.m_data->data[0] : "";
		const int myLen = m_string.m_data ? m_string.m_data->length : 0;
		const char *myData = m_string.m_data ? &m_string.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0) {
			return result;
		}
		return myLen - len;
	}

	StringBase<char> m_string;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

class ParticleSystemInfo
{
public:
	virtual ~ParticleSystemInfo();

private:
	unsigned char m_pad[0x94];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystemTemplate : public ParticleSystemInfo
{
public:
	ParticleSystemTemplate(const AsciiString &name);
	virtual ~ParticleSystemTemplate();

	void deleteInstance()
	{
		delete this;
	}

private:
	AsciiString m_name;
	Int m_slaveTemplate;
	void *m_a0[11];
	unsigned char m_tail[4];
};

typedef _STL::hash_map<AsciiString, ParticleSystemTemplate *, rts::hash<AsciiString>, _STL::equal_to<AsciiString> > TemplateMap;

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	ParticleSystemTemplate *newTemplate(const AsciiString &name);

private:
	unsigned char m_prefix[0x9c];
	TemplateMap m_templateMap;
};

ParticleSystemTemplate *ParticleSystemManager::findTemplate( const AsciiString &name ) const
{
	ParticleSystemTemplate *sysTemplate = NULL;
	TemplateMap::const_iterator find(m_templateMap.find(name));
	if (find != m_templateMap.end()) {
		sysTemplate = (*find).second;
	}
	return sysTemplate;
}

// ?newTemplate@ParticleSystemManager@@QAEPAVParticleSystemTemplate@@ABVAsciiString@@@Z
ParticleSystemTemplate *ParticleSystemManager::newTemplate( const AsciiString &name )
{
	ParticleSystemTemplate *sysTemplate = findTemplate(name);
	if (sysTemplate == NULL) {
		sysTemplate = new ParticleSystemTemplate( name );

		if (! m_templateMap.insert(std::make_pair(name, sysTemplate)).second) {
			sysTemplate->deleteInstance();
			sysTemplate = NULL;
		}
	}

	return sysTemplate;
}
