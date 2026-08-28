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
public:
	virtual bool Save_W3D(ChunkSaveClass &chunk_save);
	virtual void Dummy01(); virtual void Dummy02(); virtual void Dummy03();
	virtual void Dummy04(); virtual void Dummy05(); virtual void Dummy06();
	virtual void Dummy07(); virtual void Dummy08(); virtual void Dummy09();
	virtual void Dummy10(); virtual void Dummy11(); virtual void Dummy12();
	virtual void Dummy13(); virtual void Dummy14(); virtual void Dummy15();
	virtual void Dummy16(); virtual void Dummy17(); virtual void Dummy18();
	virtual void Dummy19(); virtual void Dummy20(); virtual void Dummy21();
	virtual void Dummy22(); virtual void Dummy23(); virtual void Dummy24();
	virtual void Dummy25(); virtual void Dummy26(); virtual void Dummy27();
	virtual void Dummy28(); virtual void Dummy29(); virtual void Dummy30();
	virtual void Dummy31(); virtual void Dummy32(); virtual void Dummy33();
	virtual void Dummy34(); virtual void Dummy35(); virtual void Dummy36();
	virtual void Dummy37(); virtual void Dummy38(); virtual void Dummy39();
	virtual void Dummy40(); virtual void Dummy41(); virtual void Dummy42();
	virtual void Dummy43(); virtual void Dummy44(); virtual void Dummy45();
	virtual void Dummy46(); virtual void Dummy47(); virtual void Dummy48();
	virtual void Dummy49(); virtual void Dummy50(); virtual void Dummy51();
	virtual void Dummy52(); virtual void Dummy53(); virtual void Dummy54();
	virtual void Dummy55(); virtual void Dummy56(); virtual void Dummy57();
	virtual void Dummy58(); virtual void Dummy59();

protected:
	virtual bool Save_Header(ChunkSaveClass &chunk_save);
	virtual bool Save_User_Data(ChunkSaveClass &chunk_save);
	virtual bool Save_Info(ChunkSaveClass &chunk_save);
	virtual bool Save_InfoV2(ChunkSaveClass &chunk_save);
	virtual bool Save_Props(ChunkSaveClass &chunk_save);
	virtual bool Save_Line_Properties(ChunkSaveClass &chunk_save);
	virtual bool Save_Frame_Keyframes(ChunkSaveClass &chunk_save);
	virtual bool Save_Rotation_Keyframes(ChunkSaveClass &chunk_save);
	virtual bool Save_Blur_Time_Keyframes(ChunkSaveClass &chunk_save);
	virtual bool Save_Extra_Info(ChunkSaveClass &chunk_save);
};

bool ParticleEmitterDefClass::Save_W3D(ChunkSaveClass &chunk_save)
{
	bool success = false;

	if (chunk_save.Begin_Chunk(W3D_CHUNK_EMITTER) == true)
	{
		if ((Save_Header(chunk_save) == true) &&
			(Save_User_Data(chunk_save) == true) &&
			(Save_Info(chunk_save) == true) &&
			(Save_InfoV2(chunk_save) == true) &&
			(Save_Props(chunk_save) == true) &&
			(Save_Line_Properties(chunk_save) == true) &&
			(Save_Rotation_Keyframes(chunk_save) == true) &&
			(Save_Frame_Keyframes(chunk_save) == true) &&
			(Save_Blur_Time_Keyframes(chunk_save) == true) &&
			(Save_Extra_Info(chunk_save) == true))
		{
			success = true;
		}

		chunk_save.End_Chunk();
	}

	return success;
}
