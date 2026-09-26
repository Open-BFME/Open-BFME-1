// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// BFME's emitter save entry points return a one-byte bool. Keep this ABI view
// local because the later vendored declaration returns WW3DErrorType.

#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "chunkio.h"
#include "w3d_file.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_ldr.h
class ParticleEmitterDefClass
{
protected:
	virtual bool Save_Info(ChunkSaveClass &chunk_save);
	virtual bool Save_InfoV2(ChunkSaveClass &chunk_save);
	virtual bool Save_Line_Properties(ChunkSaveClass &chunk_save);
	char Pad[0x14];
	W3dEmitterInfoStruct Info;
	W3dEmitterInfoStructV2 InfoV2;
	char PadToLineProperties[0x204 - 0x14 - sizeof(W3dEmitterInfoStruct) - sizeof(W3dEmitterInfoStructV2)];
	W3dEmitterLinePropertiesStruct LineProperties;
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

bool ParticleEmitterDefClass::Save_Line_Properties(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;
	if (chunk_save.Begin_Chunk(W3D_CHUNK_EMITTER_LINE_PROPERTIES) == TRUE)
	{
		if (chunk_save.Write(&LineProperties, sizeof(LineProperties)) == sizeof(LineProperties))
		{
			ret_val = true;
		}
		chunk_save.End_Chunk();
	}
	return ret_val;
}
