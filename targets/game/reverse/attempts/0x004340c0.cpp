// ?rva004340C0SubtitleCoordinate@@YAHHPAURva004340C0SubtitleOwner@@MM@Z
// partial score=0.700565 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

#include <math.h>

typedef int Int;
typedef float Real;

struct Rva004340C0SubtitleOwner
{
	unsigned char unknown00[0x60];
	unsigned char alternateMode;
};

Int rva004340C0SubtitleCoordinate(Int index,
	Rva004340C0SubtitleOwner *owner, Real low, Real high)
{
	const Real difference = (Real)fabs(high - low);
	if (owner->alternateMode)
	{
		const Int highCoordinate = (Int)high;
		const Int lowCoordinate = (Int)low;
		const Int *selectedCoordinate = highCoordinate < lowCoordinate ?
			&highCoordinate : &lowCoordinate;
		const Real *coordinates = reinterpret_cast<const Real *>(
			reinterpret_cast<const unsigned char *>(owner) + 0x24);
		return (Int)(difference * coordinates[index]) + *selectedCoordinate;
	}

	const Int highCoordinate = (Int)high;
	const Int lowCoordinate = (Int)low;
	if (index < 15)
	{
		if (index <= 0) index = 0;
	}
	else
	{
		index = 15;
	}
	const Int *selectedCoordinate = highCoordinate < lowCoordinate ?
		&highCoordinate : &lowCoordinate;
	return ((Int)difference / 15) * index + *selectedCoordinate;
}
