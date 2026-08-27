// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME's emitter save entry points return a one-byte bool. Keep this ABI view
// local because the later vendored declaration returns WW3DErrorType.

#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "chunkio.h"
#include "w3d_file.h"

class ParticleEmitterDefClass
{
protected:
	virtual bool Save_Info(ChunkSaveClass &chunk_save);
	char Pad[0x14];
	W3dEmitterInfoStruct Info;
};

bool ParticleEmitterDefClass::Save_Info(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;
	if (chunk_save.Begin_Chunk(W3D_CHUNK_EMITTER_INFO) == TRUE)
	{
		if (chunk_save.Write(&Info, sizeof(Info)) == sizeof(Info))
		{
			ret_val = true;
		}
		chunk_save.End_Chunk();
	}
	return ret_val;
}
