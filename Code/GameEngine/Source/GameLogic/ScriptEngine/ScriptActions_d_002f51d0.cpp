// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
//
// Convert of gen-dump ?d_002f51d0@@YAXXZ at 0x002F51D0 (66 bytes).
// Same 0x012EF4CC vslot 26 lookup as 0x002F5180 then vslot 29 with
// three extra stack arguments (ret 0x10).

#include "StringInline.h"

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual void *lookupByValue(AsciiString name);
	virtual void slot27();
	virtual void slot28();
	virtual void applyNamed(void *item, void *a, void *b, void *c);
};

extern TerrainLogic *TheTerrainLogic;

void __stdcall d_002f51d0(const AsciiString &name, void *a, void *b, void *c)
{
	void *item = TheTerrainLogic->lookupByValue(name);
	if (item)
		TheTerrainLogic->applyNamed(item, a, b, c);
}
