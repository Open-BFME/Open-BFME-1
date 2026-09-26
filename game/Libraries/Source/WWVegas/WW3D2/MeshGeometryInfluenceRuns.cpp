// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Retail RVA 0x00924760, complete 174-byte accessor for compact influence runs.
// The original member name is unknown; Rva00924760InfluenceRuns records the
// recovered address and role. The influence reader at 0x00925380 passes twice
// the run count and writes two unsigned shorts per run through the result.
// This TU models only the pointer at MeshGeometryClass+0x5c, not the full class.

#include "always.h"
#include "sharebuf.h"

class MeshGeometryClass
{
	char _prefix_through_58[0x5c];
	ShareBufferClass<unsigned short> *InfluenceRunBuffer; // retail this+0x5c

protected:
	// Recovered role/address label only; original source name is unknown.
	unsigned short *Rva00924760InfluenceRuns(int count);
};

unsigned short *MeshGeometryClass::Rva00924760InfluenceRuns(int count)
{
	if (count && InfluenceRunBuffer == NULL) {
		InfluenceRunBuffer = NEW_REF(ShareBufferClass<unsigned short>,
			(count, "MeshGeometryClass::InfluenceRunBuffer", 0));
	}

	if (InfluenceRunBuffer != NULL) {
		return InfluenceRunBuffer->Get_Array();
	}
	return NULL;
}
