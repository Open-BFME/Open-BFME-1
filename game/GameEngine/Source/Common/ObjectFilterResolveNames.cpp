// cl: /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/iniexception /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BFME's AsciiString (WWLib ascii_string.h) stands in for the ZH header that
// PreRTS.h would pull in; getLength and str are inline at retail call sites.
#define ASCIISTRING_H
#include "ascii_string.h"
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


// ObjectFilter's name resolution, retail 0x0039E2B0 (907 bytes).
//
// Identity: its four INIException messages name it --
// "ObjectFilter::resolveNames() specified +S:%s but template %s doesn't exist!
// Typo?" and the -S:, + and - variants -- and the 0x88-byte object it walks
// is the filter: the inclusion names at +0x00 feed the "+" messages, the
// exclusion names at +0x0C the "-" ones. It is a cdecl helper taking the
// filter (the loop at 0x0039E720 calls it once per 0x88-byte element), so it
// keeps its address in the name rather than claim the member's signature.
// Each name either starts "S:" (the rest names a template kept in its own
// list) or is a template name; both must resolve or the INI load throws. The
// name lists are cleared afterwards.

typedef _STL::vector<AsciiString> ObjectFilterNameVector;
typedef _STL::vector<const ThingTemplate *> ObjectFilterTemplateVector;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern BfmeThingFactory *TheThingFactory;

class ObjectFilter
{
public:
	static void rva0039E2B0ResolveNames(ObjectFilter *filter);

	ObjectFilterNameVector m_inclusionNames;			// +0x00
	ObjectFilterNameVector m_exclusionNames;			// +0x0C
	ObjectFilterTemplateVector m_inclusionSTemplates;		// +0x18
	ObjectFilterTemplateVector m_exclusionSTemplates;		// +0x24
	ObjectFilterTemplateVector m_inclusionTemplates;		// +0x30
	ObjectFilterTemplateVector m_exclusionTemplates;		// +0x3C
	char m_tail[0x88 - 0x48];				// +0x48
};

// ?rva0039E2B0ResolveNames@ObjectFilter@@SAXPAV1@@Z
void ObjectFilter::rva0039E2B0ResolveNames(ObjectFilter *filter)
{
	int i;
	int count = filter->m_inclusionNames.size();
	for (i = 0; i < count; ++i)
	{
		AsciiString &name = filter->m_inclusionNames[i];
		if (((StringBase<char> *)&name)->startsWith("S:", 2) && (unsigned)name.getLength() >= 3)
		{
			const char *templateName = name.str();
			templateName += 2;
			const ThingTemplate *tmpl = TheThingFactory->findTemplate(AsciiString(templateName));
			if (!tmpl)
				throw INIException(3, "ObjectFilter::resolveNames() specified +S:%s but template %s doesn't exist! Typo?", templateName, templateName);
			filter->m_inclusionSTemplates.push_back(tmpl);
		}
		else
		{
			const ThingTemplate *tmpl = TheThingFactory->findTemplate(name);
			if (!tmpl)
				throw INIException(3, "ObjectFilter::resolveNames() specified +%s but this template doesn't exist! Typo?", name.str());
			filter->m_inclusionTemplates.push_back(tmpl);
		}
	}
	filter->m_inclusionNames.clear();

	count = filter->m_exclusionNames.size();
	for (i = 0; i < count; ++i)
	{
		AsciiString &name = filter->m_exclusionNames[i];
		if (((StringBase<char> *)&name)->startsWith("S:", 2) && (unsigned)name.getLength() >= 3)
		{
			const char *templateName = name.str();
			templateName += 2;
			const ThingTemplate *tmpl = TheThingFactory->findTemplate(AsciiString(templateName));
			if (!tmpl)
				throw INIException(3, "ObjectFilter::resolveNames() specified -S:%s but template %s doesn't exist! Typo?", templateName, templateName);
			filter->m_exclusionSTemplates.push_back(tmpl);
		}
		else
		{
			const ThingTemplate *tmpl = TheThingFactory->findTemplate(name);
			if (!tmpl)
				throw INIException(3, "ObjectFilter::resolveNames() specified -%s but this template doesn't exist! Typo?", name.str());
			filter->m_exclusionTemplates.push_back(tmpl);
		}
	}
	filter->m_exclusionNames.clear();
}
