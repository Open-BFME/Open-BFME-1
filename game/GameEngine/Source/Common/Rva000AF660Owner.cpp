// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib 
// stlport
// Retail 0x000AF660, 275 bytes through the RET at +0x112. An opaque owner resets
// six name/index/value-list records keyed by water and river texture INI names.
// Each record's value list is cleared with STLport vector::erase, its name is
// set, and its index is stored.
//
// Lever: retail reloads the entry's name from the stack table for the set call
// instead of keeping it in a free register. Reading the name into a local at
// the top of the iteration, across the erase loops, reproduces that reload. A
// bank that forced it with a volatile index read stopped at 277 bytes.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string.h>
#include "ascii_string.h"
#pragma intrinsic(strlen)

// The BFME-retail AsciiString element type (destructor ILT 0x0000D828 ->
// 0x0005EE90), as in CarvedBFMERetailAsciiStringDestructor.cpp.
class BFMERetailAsciiString : public AsciiString
{
public:
	~BFMERetailAsciiString();
};

struct Rva000AF660Record
{
	AsciiString name;
	int index;
	_STL::vector<BFMERetailAsciiString> values;
};

class Rva000AF660Owner
{
public:
	void method();

private:
	char head[8];
	Rva000AF660Record records[6];
};

// ?method@Rva000AF660Owner@@QAEXXZ
void Rva000AF660Owner::method()
{
	struct Entry { int index; const char *name; } entries[6] = {
		{ 0, "RiverTextures" },
		{ 1, "WaterBumpMapTextures" },
		{ 2, "RiverAlphaEdgeTextures" },
		{ 3, "WaterSkyTextures" },
		{ 5, "RiverSparkleTextures" },
		{ 4, "RiverNoiseTextures" }
	};
	for (int i = 0; i < 6; ++i)
	{
		Rva000AF660Record &record = records[entries[i].index];
		const char *name = entries[i].name;
		_STL::vector<BFMERetailAsciiString> &values = record.values;
		values.erase(values.begin(), values.end());
		((StringBase<char> *)&record.name)->set(name, name ? (int)strlen(name) : 0);
		record.index = entries[i].index;
	}
}
