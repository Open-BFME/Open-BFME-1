// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME's emitter read entry points return a one-byte bool.  Keep this ABI view
// local because the later vendored declaration returns WW3DErrorType.

#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "chunkio.h"
#include "w3d_file.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_ldr.h
class ParticleEmitterDefClass
{
protected:
	virtual bool Read_Line_Properties(ChunkLoadClass &chunk_load);
	char Pad[0x204];
	W3dEmitterLinePropertiesStruct LineProperties;
};

bool ParticleEmitterDefClass::Read_Line_Properties(ChunkLoadClass &chunk_load)
{
	bool success = false;

	if (chunk_load.Cur_Chunk_ID() == W3D_CHUNK_EMITTER_LINE_PROPERTIES)
	{
		if (chunk_load.Read(&LineProperties, sizeof(LineProperties)) == sizeof(LineProperties))
			success = true;
	}

	return success;
}
