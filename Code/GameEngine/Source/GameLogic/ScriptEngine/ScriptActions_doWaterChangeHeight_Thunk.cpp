// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
//
// ?doWaterChangeHeight@ScriptActions@@IAEXABVAsciiString@@M@Z
//
// The DISPLAY_COUNTER dispatcher family identifies this as action 201,
// WATER_CHANGE_HEIGHT.  The TerrainLogic calls use vslots 26 and 28; the
// first takes its AsciiString by value and the second receives the height,
// 999999.9f damage, and TRUE.

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
	virtual void *getWaterHandleByName(AsciiString name);
	virtual void slot27();
	virtual void setWaterHeight(void *water, float height, float damage, int flag);
};

extern TerrainLogic *TheTerrainLogic;

class ScriptActions
{
protected:
	void doWaterChangeHeight(const AsciiString &waterName, float newHeight);
};

void ScriptActions::doWaterChangeHeight(const AsciiString &waterName, float newHeight)
{
	void *water = TheTerrainLogic->getWaterHandleByName(waterName);
	if (water)
		TheTerrainLogic->setWaterHeight(water, newHeight, 999999.9f, 1);
}
