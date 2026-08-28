// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME's emitter save entry point returns a one-byte bool.  Keep this ABI view
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
	virtual bool Save_Header(ChunkSaveClass &chunk_save);
	char *Name;
};

bool ParticleEmitterDefClass::Save_Header(ChunkSaveClass &chunk_save)
{
	bool success = false;

	if (chunk_save.Begin_Chunk(W3D_CHUNK_EMITTER_HEADER) == TRUE)
	{
		W3dEmitterHeaderStruct header = { 0 };
		header.Version = W3D_CURRENT_EMITTER_VERSION;
		::lstrcpyn(header.Name, Name, sizeof(header.Name));
		header.Name[sizeof(header.Name) - 1] = 0;

		if (chunk_save.Write(&header, sizeof(header)) == sizeof(header))
			success = true;

		chunk_save.End_Chunk();
	}

	return success;
}
