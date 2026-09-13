// cl: /DNDEBUG /MD /EHsc

// W3DFloorDraw's constructor, retail 0x007517A0.
//
// The base constructor it forwards to is 0x007592C0, which the ledger already
// carries as W3DPropDraw's - the two are byte-identical and the linker folded
// them, so the address cannot say which draw class W3DFloorDraw actually
// derives from. This file gives that base a stand-in name and pins the address
// under it; the name is this tree's, not the image's.
//
// What the bytes do fix: the base runs to +0x10, the flag W3DFloorDraw adds
// sits there, and it is set from a byte at +0x0E of the module data - which the
// base left at this+0x04. Retail zeroes the flag first and only overwrites it
// on the true side, which is a member-init plus an `if', not an assignment of
// the module-data byte.

class Thing;
class ModuleData;

// Only the one field this constructor reads.
struct W3DFloorDrawModuleData
{
	unsigned char m_unmodelled_00[0x0E];
	bool m_unmodelled_0E;					// +0x0E
};

class W3DFloorDrawBase
{
public:
	W3DFloorDrawBase( Thing *thing, const ModuleData *moduleData );

	virtual void drawModuleAnchor();

protected:
	const ModuleData *getModuleData() const { return m_moduleData; }

private:
	const ModuleData *m_moduleData;			// +0x04
	unsigned char m_unmodelled_08[8];
};

class W3DFloorDraw : public W3DFloorDrawBase
{
public:
	W3DFloorDraw( Thing *thing, const ModuleData *moduleData );

private:
	bool m_unmodelled_10;					// +0x10
};

W3DFloorDraw::W3DFloorDraw( Thing *thing, const ModuleData *moduleData )
	: W3DFloorDrawBase( thing, moduleData ), m_unmodelled_10( false )
{
	if( ((const W3DFloorDrawModuleData *)getModuleData())->m_unmodelled_0E )
		m_unmodelled_10 = true;
}
