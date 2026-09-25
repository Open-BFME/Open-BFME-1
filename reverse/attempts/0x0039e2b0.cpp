// ?Rva0039E2B0AttributeNameResolution@@YAXPAUAttributeEntryNameLists@@@Z
// partial score=0.264609 date=2026-09-25
// cl: /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/shims/iniexception /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define ASCIISTRING_H
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "PreRTS.h"
#include <vector>
#include "Common/INIException.h"

template <>
inline int StringBase<char>::getLength() const
{
	return m_data ? m_data->length : 0;
}

template <>
inline const char *StringBase<char>::str() const
{
	return m_data ? m_data->data : "";
}

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

typedef _STL::vector<AsciiString> AttributeNameVector;
typedef _STL::vector<const ThingTemplate *> AttributeTemplateVector;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern BfmeThingFactory *TheThingFactory;

struct AttributeEntryNameLists
{
	AttributeNameVector names0;
	AttributeNameVector names1;
	AttributeTemplateVector special0;
	AttributeTemplateVector special1;
	AttributeTemplateVector ordinary0;
	AttributeTemplateVector ordinary1;
	char tail[64];
};


void Rva0039E2B0AttributeNameResolution(
	AttributeEntryNameLists *entry)
{
	{
	int count = (int)(entry->names0.end() - entry->names0.begin());
	for (int index = 0; index < count; ++index)
	{
		AsciiString &original = entry->names0[index];
		StringBase<char> *base = (StringBase<char> *)&original;
		if (base->startsWith("S:", 2) && (unsigned int)original.getLength() >= 3u)
		{
			const char *suffix = base->str() + 2;
			const ThingTemplate *value = TheThingFactory->findTemplate(AsciiString(suffix));
			if (!value)
			{
				throw INIException(3, "ObjectFilter::resolveNames() specified -S:%s but template %s doesn't exist! Typo?", suffix, suffix);
			}
			entry->special0.push_back(value);
		}
		else
		{
			const ThingTemplate *value = TheThingFactory->findTemplate(original);
			if (!value)
			{
				throw INIException(3, "ObjectFilter::resolveNames() specified -%s but this template doesn't exist! Typo?", original.str());
			}
			entry->ordinary0.push_back(value);
		}
	}
	entry->names0.erase(entry->names0.begin(), entry->names0.end());
	}

	{
	int count = (int)(entry->names1.end() - entry->names1.begin());
	for (int index = 0; index < count; ++index)
	{
		AsciiString &original = entry->names1[index];
		StringBase<char> *base = (StringBase<char> *)&original;
		if (base->startsWith("S:", 2) && (unsigned int)original.getLength() >= 3u)
		{
			const char *suffix = base->str() + 2;
			const ThingTemplate *value = TheThingFactory->findTemplate(AsciiString(suffix));
			if (!value)
			{
				throw INIException(3, "ObjectFilter::resolveNames() specified +S:%s but template %s doesn't exist! Typo?", suffix, suffix);
			}
			entry->special1.push_back(value);
		}
		else
		{
			const ThingTemplate *value = TheThingFactory->findTemplate(original);
			if (!value)
			{
				throw INIException(3, "ObjectFilter::resolveNames() specified +%s but this template doesn't exist! Typo?", original.str());
			}
			entry->ordinary1.push_back(value);
		}
	}
	entry->names1.erase(entry->names1.begin(), entry->names1.end());
	}
}
