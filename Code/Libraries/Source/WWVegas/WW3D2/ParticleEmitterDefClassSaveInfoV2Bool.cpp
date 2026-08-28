// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME's emitter save entry points return a one-byte bool. Keep this ABI view
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
	virtual bool Save_InfoV2(ChunkSaveClass &chunk_save);
	char Pad[0x160];
	W3dEmitterInfoStructV2 InfoV2;
};

bool ParticleEmitterDefClass::Save_InfoV2(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;
	if (chunk_save.Begin_Chunk(W3D_CHUNK_EMITTER_INFOV2) == TRUE)
	{
		if (chunk_save.Write(&InfoV2, sizeof(InfoV2)) == sizeof(InfoV2))
		{
			ret_val = true;
		}
		chunk_save.End_Chunk();
	}
	return ret_val;
}
