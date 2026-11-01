// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?findParentTemplate@ParticleSystemManager@FXParticleSystem@@QBEPAVParticleSystemTemplate@2@ABVAsciiString@@H@Z:
// GeneralsMD ParticleSys.cpp (its global-namespace ZH copy stays present-unmatched there).
// Retail 0x005CB600 (230 bytes, through RET 8 at +0xE3); ILT 0x00048220 confirms the
// FXParticleSystem name. The template map sits at +0x9C of the manager (as in
// ParticleSystemManagerWriteINI.cpp) and m_slaveSystemName at +0x68 of the template
// (as in ParticleSystemTemplateCreateSlave.cpp).

#define _STLP_NO_EXCEPTIONS 1
// Keep the disputed retail iterator helper under its address-derived name.
#define _M_skip_to_next Rva003442B0_skipToNext
#include <hash_map>
#undef _M_skip_to_next

#include "ascii_string.h"

// Retail AsciiString::compare shape (repe cmpsb over the shared prefix, then
// the length difference), spelled as the StringBase<char> specialization so
// this TU emits no AsciiString::compare COMDAT of its own. Same spelling as
// game/GameEngine/Source/GameNetwork/Rva00692570KeyLess.cpp.
template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

namespace rts
{
	template <class T>
	struct hash
	{
		unsigned int operator()(T value) const;
	};
}

// Retail tests the name's string header in line (no data, or a zero 16-bit
// length) instead of calling StringBase::isEmpty's out-of-line body.
struct BfmeAsciiHeaderView
{
	int m_refCount;
	unsigned short m_length;
};

inline bool bfmeNameIsEmpty(const AsciiString &name)
{
	const BfmeAsciiHeaderView *data = *(const BfmeAsciiHeaderView *const *)&name;
	return data == 0 || data->m_length == 0;
}

class CommandButton;
// Retail advances through the CommandButton map's iterator helper (0x003442B0);
// both STLport iterators hold the current node and hashtable pointers.
typedef _STL::hash_map<AsciiString, const CommandButton *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > CommandButtonMap;

// Retail calls this map's begin through ILT 0x0003407C -> 0x005C55D0 (not the
// 0x0001ABD1 begin _writeOutINI uses). That byte-identical begin is pinned only
// under the generated int-keyed payload map's name, so the call is spelled through it.
struct Gen_t_005c6b60_m12pod { int a[3]; };
typedef _STL::hash_map<int, Gen_t_005c6b60_m12pod> BfmeBeginRouteMap;

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
	virtual ~ParticleSystemTemplate();

	unsigned char m_pad0[0x64];
	AsciiString m_slaveSystemName;		// +0x68
};

typedef _STL::hash_map<AsciiString, ParticleSystemTemplate *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > TemplateMap;

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findParentTemplate(const AsciiString &name, int parentNum) const;

private:
	unsigned char m_pad[0x9c];
	TemplateMap m_templateMap;			// +0x9C
};

// ?findParentTemplate@ParticleSystemManager@FXParticleSystem@@QBEPAVParticleSystemTemplate@2@ABVAsciiString@@H@Z
ParticleSystemTemplate *ParticleSystemManager::findParentTemplate(const AsciiString &name, int parentNum) const
{
	if (bfmeNameIsEmpty(name)) {
		return NULL;
	}

	BfmeBeginRouteMap::iterator first(((BfmeBeginRouteMap &)m_templateMap).begin());
	TemplateMap::iterator &begin = *(TemplateMap::iterator *)&first;
	TemplateMap::iterator end(const_cast<TemplateMap &>(m_templateMap).end());
	for (; begin != end; ++(*(CommandButtonMap::iterator *)&begin)) {
		ParticleSystemTemplate *sysTemplate = (*begin).second;
		if (name.StringBase<char>::compare(sysTemplate->m_slaveSystemName) == 0) {
			if (! parentNum--) {
				return sysTemplate;
			}
		}
	}

	return NULL;
}

}
