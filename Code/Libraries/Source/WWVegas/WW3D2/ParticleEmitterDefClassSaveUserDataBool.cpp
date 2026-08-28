// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME's emitter save entry points return a one-byte bool.  Keep this ABI view
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
