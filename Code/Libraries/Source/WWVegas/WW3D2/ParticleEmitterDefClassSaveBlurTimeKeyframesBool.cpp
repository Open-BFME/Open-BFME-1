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
	virtual bool Save_Blur_Time_Keyframes(ChunkSaveClass &chunk_save);
	char Pad[0x2BC];
	float BlurStart;
	float BlurRand;
	unsigned int BlurNumKeyFrames;
	float *BlurKeyTimes;
	float *BlurValues;
};

bool ParticleEmitterDefClass::Save_Blur_Time_Keyframes(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;

	if (chunk_save.Begin_Chunk(W3D_CHUNK_EMITTER_BLUR_TIME_KEYFRAMES) == TRUE)
	{
		W3dEmitterBlurTimeHeaderStruct header;
		header.KeyframeCount = BlurNumKeyFrames;
		header.Random = BlurRand;
		chunk_save.Write(&header, sizeof(W3dEmitterBlurTimeHeaderStruct));

		bool success = true;
		W3dEmitterBlurTimeKeyframeStruct key;
		key.Time = 0;
		key.BlurTime = BlurStart;
		chunk_save.Write(&key, sizeof(key));

		for (unsigned int index = 0; (index < header.KeyframeCount) && success; index++)
		{
			key.Time = BlurKeyTimes[index];
			key.BlurTime = BlurValues[index];
			success = (chunk_save.Write(&key, sizeof(key)) == sizeof(key));
		}

		ret_val = (success != false);
		chunk_save.End_Chunk();
	}

	return ret_val;
}
