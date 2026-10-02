// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// BFME's emitter save entry points return a one-byte bool.  Keep this ABI view
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
	virtual bool Save_Header(ChunkSaveClass &chunk_save);
	virtual bool Save_User_Data(ChunkSaveClass &chunk_save);
	char *Name;
	char *UserString;
	int UserType;
};

bool ParticleEmitterDefClass::Save_User_Data(ChunkSaveClass &chunk_save)
{
	bool success = false;

	if (chunk_save.Begin_Chunk(W3D_CHUNK_EMITTER_USER_DATA) == TRUE)
	{
		DWORD stringLength = UserString ? (::lstrlen(UserString) + 1) : 0;

		W3dEmitterUserInfoStruct userInfo = { 0 };
		userInfo.Type = UserType;
		userInfo.SizeofStringParam = stringLength;

		if (chunk_save.Write(&userInfo, sizeof(userInfo)) == sizeof(userInfo))
		{
			success = true;
			if (UserString != 0 &&
				chunk_save.Write(UserString, stringLength) != stringLength)
			{
				success = false;
			}
		}
		chunk_save.End_Chunk();
	}

	return success;
}

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
