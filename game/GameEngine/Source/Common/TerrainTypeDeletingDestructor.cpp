// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: TerrainType scalar-deleting destructor at retail RVA 0x000A8650
// (30 bytes). The exact constructor at 0x000A82F0 installs vtable 0x01080F0C,
// whose slot zero routes through ILT 0x000209D2 to this wrapper. The complete
// destructor is the matched 0x000A83D0 body reached through ILT 0x00024442.

class TerrainType
{
public:
	virtual ~TerrainType();
};

void forceTerrainTypeDeletingDestructor()
{
	TerrainType value;
}
