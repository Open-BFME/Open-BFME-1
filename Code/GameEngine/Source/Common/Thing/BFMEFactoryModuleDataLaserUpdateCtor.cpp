// cl: /DNDEBUG /MD /EHsc

// BFMEFactoryModuleData<LaserUpdateModuleData, 0x1C>'s constructor, retail
// 0x00603B90.
//
// ModuleFactory.cpp already carries the template and the size specialisation
// that give this instantiation its name; what it does not carry is a definition
// of the constructor, so the body lands here instead.
//
// The vftable store comes FIRST and only once, ahead of the five zeroes. That
// orders the classes: ModuleData contributes the vftable and the untouched
// +0x04 and nothing else, so its constructor is empty and its own vftable store
// dies, and the fields from +0x08 to +0x18 belong to the wrapper and are
// written by the wrapper's initialiser list. Written the other way round - the
// fields in the base - the base's inits come out ahead of the derived vftable
// store, which is not what retail does.

class LaserUpdateModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	ModuleData()
	{
	}

	virtual void moduleDataAnchor();

private:
	unsigned int m_unmodelled_04;			// +0x04, never written
};

// +0x10 and +0x14 travel together: retail writes the dword at +0x14 BEFORE the
// flag at +0x10, which no single initialiser list can do while the flag lies
// lower. A small member with its dword in the list and its flag assigned in the
// body is what produces that pair in that order.
struct BfmeFactoryDataFlagPair
{
	BfmeFactoryDataFlagPair()
		: m_14( 0 )
	{
		m_10 = false;
	}

	bool m_10;								// +0x10
	unsigned int m_14;						// +0x14
};

template < class T, unsigned int SIZE >
class BFMEFactoryModuleData : public ModuleData
{
public:
	BFMEFactoryModuleData()
		: m_unmodelled_08( 0 ),
			m_unmodelled_0C( 0 ),
			m_flagPair(),
			m_unmodelled_18( 0 )
	{
	}

private:
	unsigned int m_unmodelled_08;			// +0x08
	unsigned int m_unmodelled_0C;			// +0x0C
	BfmeFactoryDataFlagPair m_flagPair;		// +0x10
	unsigned int m_unmodelled_18;			// +0x18
};

// ??0?$BFMEFactoryModuleData@VLaserUpdateModuleData@@$0BM@@@QAE@XZ
template class BFMEFactoryModuleData< LaserUpdateModuleData, 0x1C >;
