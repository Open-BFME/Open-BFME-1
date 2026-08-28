// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: _STL::vector<FlightDeckBehavior::RunwayInfo>::_M_insert_overflow,
// retail 0x0039EC70, 287 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// Same 287 bytes as the ModuleInfo::Nugget overflow, and the same reason: an
// element with both a copy constructor and a destructor. The element is
// 136 bytes, which the divide magic 0x78787879 with a shift of six fixes; without
// the destructor the body comes out 338.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h
class FlightDeckBehavior
{
public:
	struct RunwayInfo
	{
		RunwayInfo(const RunwayInfo &other);
		~RunwayInfo(void);

		char m_bfmeBody[136];
	};
};

void BfmeRunwayInfoVectorInsertAnchor(_STL::vector<FlightDeckBehavior::RunwayInfo> &v,
	const FlightDeckBehavior::RunwayInfo &value)
{
	v.insert(v.begin(), value);
}
