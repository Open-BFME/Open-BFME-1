// cl: /DNDEBUG /MD /EHsc
// RVA-derived names: owning class is the ScriptEngine flag-lookup view
// (canonicalFlagName is a member of this object). Identity of the two
// table getters is the ILT thunks 0x000323F8 -> 0x00359D40 and
// 0x0000A592 -> 0x00359DC0; the container probe is 0x000485BD -> 0x0033C290.
//
// The two named-item lookups, 0x0033C340 and 0x0033C450, which are the same
// body reaching two different table getters -- findByNameA through the ILT at
// 0x000323F8 and findByNameB through 0x0000A592. Both files already declared
// both getters and both lookups; only the definition differed, so the two files
// were one head written twice.

class AsciiString;

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class BfmeNamedItem0033c340;

class BfmeNamedContainer0033c340
{
public:
	BfmeNamedItem0033c340 *findByNameA(const AsciiString &name);
	BfmeNamedItem0033c340 *findByNameB(const AsciiString &name);
};

class BFMEScriptEngineFlagLookup
{
public:
	BfmeNamedItem0033c340 *lookupNamedItemA(AsciiString name, AsciiString *outCanonical);
	BfmeNamedItem0033c340 *lookupNamedItemB(AsciiString name, AsciiString *outCanonical);

private:
	AsciiString canonicalFlagName(const AsciiString &name);
	BfmeNamedContainer0033c340 *findNamedContainer(const AsciiString &canonical);
};

// ?lookupNamedItemA@BFMEScriptEngineFlagLookup@@QAEPAVBfmeNamedItem0033c340@@VAsciiString@@PAV3@@Z
BfmeNamedItem0033c340 *BFMEScriptEngineFlagLookup::lookupNamedItemA(
	AsciiString name, AsciiString *outCanonical)
{
	AsciiString canonical = canonicalFlagName(name);
	BfmeNamedContainer0033c340 *container = findNamedContainer(canonical);
	if (container) {
		BfmeNamedItem0033c340 *item = container->findByNameA(name);
		if (item) {
			if (outCanonical)
				outCanonical->set(canonical);
		}
		return item;
	}
	return 0;
}


// ?lookupNamedItemB@BFMEScriptEngineFlagLookup@@QAEPAVBfmeNamedItem0033c340@@VAsciiString@@PAV3@@Z
BfmeNamedItem0033c340 *BFMEScriptEngineFlagLookup::lookupNamedItemB(
	AsciiString name, AsciiString *outCanonical)
{
	AsciiString canonical = canonicalFlagName(name);
	BfmeNamedContainer0033c340 *container = findNamedContainer(canonical);
	if (container) {
		BfmeNamedItem0033c340 *item = container->findByNameB(name);
		if (item) {
			if (outCanonical)
				outCanonical->set(canonical);
		}
		return item;
	}
	return 0;
}
