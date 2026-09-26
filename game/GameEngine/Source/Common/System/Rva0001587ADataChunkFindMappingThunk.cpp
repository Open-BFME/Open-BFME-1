// cl: /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// The 5-byte incremental-link thunk at 0x0001587A forwards to the matched
// DataChunkTableOfContents::findMapping body at 0x00103CA0.

#include "ascii_string.h"

class Mapping;

class DataChunkTableOfContentsFindMappingShim
{
public:
	Mapping *find(const AsciiString &name);
};

class Rva0001587ADataChunkFindMappingThunk
{
public:
	Mapping *forward(const AsciiString &name);
};

Mapping *Rva0001587ADataChunkFindMappingThunk::forward(const AsciiString &name)
{
	return ((DataChunkTableOfContentsFindMappingShim *)this)->find(name);
}
