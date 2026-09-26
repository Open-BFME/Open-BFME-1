// Opaque 16-byte record copied at retail 0x000FCF30.
// The copy body preserves three DWORDs and constructs the trailing
// StringBase<char> subobject at +0x0C through its copy constructor.
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct Rva000FCF30Record
{
	unsigned long word00;
	unsigned long word04;
	unsigned long word08;
	AsciiString text0C;

	Rva000FCF30Record( const Rva000FCF30Record &that );
};

Rva000FCF30Record::Rva000FCF30Record( const Rva000FCF30Record &that )
	: word00( that.word00 ),
	  word04( that.word04 ),
	  word08( that.word08 ),
	  text0C( that.text0C )
{
}
