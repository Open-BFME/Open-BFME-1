// cl: /DNDEBUG /MD /EHsc

// ProductionPrerequisite's copy constructor, retail 0x00783D50.
//
// The whole body is a three-iteration loop moving eight bytes an iteration, so
// the class is an array of three eight-byte entries and nothing else. The loop
// is what says the entry is a CLASS: an array of PODs would be copied
// straight-line, and it is MSVC's elementwise array copy that walks the source
// in edx and the destination in esi with the first dword reached through the
// this-minus-source displacement it computed once.
//
// The constructor itself is not written here. It is the compiler's - a
// user-written one cannot copy an array member at all - so the class declares
// none and a helper below forces it to be emitted.

struct BfmeProductionPrerequisiteEntry
{
	BfmeProductionPrerequisiteEntry( const BfmeProductionPrerequisiteEntry &that )
	{
		m_00 = that.m_00;
		m_04 = that.m_04;
	}

	unsigned int m_00;
	unsigned int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	ProductionPrerequisite();

private:
	BfmeProductionPrerequisiteEntry m_entries[ 3 ];
};

// ??0ProductionPrerequisite@@QAE@ABV0@@Z is the compiler's; this is only here to
// make it emit one.
ProductionPrerequisite bfmeCopyProductionPrerequisite( const ProductionPrerequisite &that )
{
	return that;
}
