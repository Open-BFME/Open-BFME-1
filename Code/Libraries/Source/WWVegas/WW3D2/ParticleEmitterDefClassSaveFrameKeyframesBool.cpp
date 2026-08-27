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
	virtual bool Save_Frame_Keyframes(ChunkSaveClass &chunk_save);
	char Pad[0x2A8];
	float FrameStart;
	float FrameRand;
	unsigned int FrameNumKeyFrames;
	float *FrameKeyTimes;
	float *FrameValues;
};

bool ParticleEmitterDefClass::Save_Frame_Keyframes(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;

	if (chunk_save.Begin_Chunk(W3D_CHUNK_EMITTER_FRAME_KEYFRAMES) == TRUE)
	{
		W3dEmitterFrameHeaderStruct header;
		header.KeyframeCount = FrameNumKeyFrames;
		header.Random = FrameRand;
		chunk_save.Write(&header, sizeof(W3dEmitterFrameHeaderStruct));

		bool success = true;
		W3dEmitterFrameKeyframeStruct key;
		key.Time = 0;
		key.Frame = FrameStart;
		chunk_save.Write(&key, sizeof(key));

		for (unsigned int index = 0; (index < header.KeyframeCount) && success; index++)
		{
			key.Time = FrameKeyTimes[index];
			key.Frame = FrameValues[index];
			success = (chunk_save.Write(&key, sizeof(key)) == sizeof(key));
		}

		ret_val = (success != false);
		chunk_save.End_Chunk();
	}

	return ret_val;
}
