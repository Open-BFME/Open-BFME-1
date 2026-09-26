// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// BFME retail 0x006CB1E0, anonymous 500-record distance scan.

#include <wwmath.h>

typedef float Real;
typedef unsigned char Byte;

struct Rva006CB1E0Value
{
	Real x;
	Real y;
	Real z;
};

struct Rva006CB1E0Record
{
	Real x;
	Real y;
	Real z;
	Real limit;
	Byte padding10[4];
	Byte marked;
	Byte padding15[3];
};

class Rva006CB1E0Owner
{
public:
	void scan(Rva006CB1E0Value value, Real tail);

private:
	Byte padding[0xe4];
	Rva006CB1E0Record records[500];
	int recordCount;
	int resetCount;
};

void Rva006CB1E0Owner::scan(Rva006CB1E0Value value, Real tail)
{
	for (int i = 0; i < recordCount; ++i) {
		Rva006CB1E0Record &record = records[i];
		Rva006CB1E0Value delta = {
			value.x - record.x,
			value.y - record.y,
			value.z - record.z
		};
		Real squared = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
		Real distance = WWMath::Sqrt(squared);
		if (tail + record.limit > distance)
			record.marked = 1;
	}
	resetCount = 0;
}
