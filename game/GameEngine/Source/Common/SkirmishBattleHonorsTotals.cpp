// cl: /DNDEBUG /MD /EHsc

// SkirmishBattleHonors totals across the four BFME factions.

#include "../../Include/Common/ScalarTypes.h"


#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class SkirmishBattleHonors
{
public:
	Int getWins(AsciiString side) const;
	Int getLosses(AsciiString side) const;
	Int getLosses(void) const;
};

Int SkirmishBattleHonors::getLosses(void) const
{
	AsciiString side;
	Int total = 0;
	side.StringBase<char>::set("Gondor", 6);
	total += getLosses(side);

	side.StringBase<char>::set("Rohan", 5);
	total += getLosses(side);
	side.StringBase<char>::set("Isengard", 8);
	total += getLosses(side);
	side.StringBase<char>::set("Mordor", 6);
	total += getLosses(side);

	return total;
}
