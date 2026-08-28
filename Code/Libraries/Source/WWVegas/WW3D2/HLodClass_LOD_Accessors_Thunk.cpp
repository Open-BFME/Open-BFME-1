// cl: /DNDEBUG /MD /EHsc

// Slots 100 and 101 of the HLodClass vtable, bounded by Set_LOD_Level below and
// Set_LOD_Bias above. hlod.h declares exactly two virtuals in that gap and in
// this order:
//
//     virtual void Set_LOD_Level(int lod);
//     virtual int  Get_LOD_Level(void) const;
//     virtual int  Get_LOD_Count(void) const;
//     virtual void Set_LOD_Bias(float bias);
//
// Both bodies are seven-byte int getters taking no arguments, which is what both
// declarations call for. These are distinct names rather than an overload group,
// so the vtable keeps declaration order -- unlike the Collect_Objects and Scale
// overload sets, which appear reversed.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hlod.h
class HLodClass
{
public:
	virtual ~HLodClass();
	virtual void Set_LOD_Level(int lod);
	virtual int Get_LOD_Level(void) const;
	virtual int Get_LOD_Count(void) const;
	virtual void Set_LOD_Bias(float bias);

private:
	unsigned char m_head[0x120];
	int m_lodCount;
	int m_lodLevel;
};

// ?Get_LOD_Level@HLodClass@@UBEHXZ
int HLodClass::Get_LOD_Level(void) const
{
	return m_lodLevel;
}

// ?Get_LOD_Count@HLodClass@@UBEHXZ
int HLodClass::Get_LOD_Count(void) const
{
	return m_lodCount;
}
