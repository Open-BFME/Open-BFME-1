// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// The data table at 0x012B4040 starts with ATTRIBUTE_NONE, then ARMOR and the
// remaining attribute names, and ends with a null pointer.  The body performs
// a case-sensitive scan and returns the zero-based entry, falling back to the
// ATTRIBUTE_NONE value.  The owner and method name remain descriptive because
// no trustworthy class identity is available.

#include <string.h>

extern const char *Rva003678E0AttributeNames[];

class Rva003678E0AttributeLookup
{
public:
	int find( const char *name ) const;
};

int Rva003678E0AttributeLookup::find( const char *name ) const
{
	for( int attribute = 0; Rva003678E0AttributeNames[ attribute ]; ++attribute )
	{
		if( strcmp( Rva003678E0AttributeNames[ attribute ], name ) == 0 )
			return attribute;
	}

	return 0;
}
