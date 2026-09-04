// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
//
// Convert of gen-dump ?d_002f5180@@YAXXZ at 0x002F5180 (63 bytes).
// By-value name through the 0x012EF4CC singleton vslot 26 then vslot 28
// with the second argument plus the immediates 0x497423FE and 1.

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
	virtual void applyNamed(void *item, void *arg, int imm, int flag);
};

extern TerrainLogic *TheTerrainLogic;

void __stdcall d_002f5180(const AsciiString &name, void *arg)
{
	void *item = TheTerrainLogic->lookupByValue(name);
	if (item)
		TheTerrainLogic->applyNamed(item, arg, 0x497423FE, 1);
}
