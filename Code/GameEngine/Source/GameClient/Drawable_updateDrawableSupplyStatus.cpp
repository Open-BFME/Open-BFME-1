// cl: /DNDEBUG /MD /EHsc
// readable body of ?updateDrawableSupplyStatus@Drawable@@QAEXHH@Z: Code/GameEngine/Source/GameClient/Drawable.cpp

// Drawable::updateDrawableSupplyStatus, retail 0x00411E50. Zero Hour's loop
// unchanged: walk the draw modules, ask each for its object draw interface and
// pass the two counts on to any that has one.
//
// The module array is at +0x150 and the loop is the null-terminated walk
// getDrawModules() returns, so the terminator test is on the pointer the array
// holds rather than on a count. The two interfaces are spelled out to their
// slots - getObjectDrawInterface at +0x9C of the draw module and
// updateDrawModuleSupplyStatus at +0x20 of the interface - with anchors ahead
// of them standing in for methods this translation unit has no business naming.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class ObjectDrawInterface
{
public:
	virtual void objectDrawAnchor00();
	virtual void objectDrawAnchor04();
	virtual void objectDrawAnchor08();
	virtual void objectDrawAnchor0C();
	virtual void objectDrawAnchor10();
	virtual void objectDrawAnchor14();
	virtual void objectDrawAnchor18();
	virtual void objectDrawAnchor1C();
	virtual void updateDrawModuleSupplyStatus( Int maxSupply, Int currentSupply );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	virtual void drawModuleAnchor00();
	virtual void drawModuleAnchor04();
	virtual void drawModuleAnchor08();
	virtual void drawModuleAnchor0C();
	virtual void drawModuleAnchor10();
	virtual void drawModuleAnchor14();
	virtual void drawModuleAnchor18();
	virtual void drawModuleAnchor1C();
	virtual void drawModuleAnchor20();
	virtual void drawModuleAnchor24();
	virtual void drawModuleAnchor28();
	virtual void drawModuleAnchor2C();
	virtual void drawModuleAnchor30();
	virtual void drawModuleAnchor34();
	virtual void drawModuleAnchor38();
	virtual void drawModuleAnchor3C();
	virtual void drawModuleAnchor40();
	virtual void drawModuleAnchor44();
	virtual void drawModuleAnchor48();
	virtual void drawModuleAnchor4C();
	virtual void drawModuleAnchor50();
	virtual void drawModuleAnchor54();
	virtual void drawModuleAnchor58();
	virtual void drawModuleAnchor5C();
	virtual void drawModuleAnchor60();
	virtual void drawModuleAnchor64();
	virtual void drawModuleAnchor68();
	virtual void drawModuleAnchor6C();
	virtual void drawModuleAnchor70();
	virtual void drawModuleAnchor74();
	virtual void drawModuleAnchor78();
	virtual void drawModuleAnchor7C();
	virtual void drawModuleAnchor80();
	virtual void drawModuleAnchor84();
	virtual void drawModuleAnchor88();
	virtual void drawModuleAnchor8C();
	virtual void drawModuleAnchor90();
	virtual void drawModuleAnchor94();
	virtual void drawModuleAnchor98();
	virtual ObjectDrawInterface *getObjectDrawInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void updateDrawableSupplyStatus( Int maxSupply, Int currentSupply );

private:
	DrawModule **getDrawModules()
	{
		return m_drawModules;
	}

	unsigned char m_unmodelled_000[ 0x150 ];
	DrawModule **m_drawModules;				// +0x150
};

// ?updateDrawableSupplyStatus@Drawable@@QAEXHH@Z
void Drawable::updateDrawableSupplyStatus( Int maxSupply, Int currentSupply )
{
	for( DrawModule **dm = getDrawModules(); *dm; ++dm )
	{
		ObjectDrawInterface *di = (*dm)->getObjectDrawInterface();

		if( di )
			di->updateDrawModuleSupplyStatus( maxSupply, currentSupply );
	}
}
