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
	virtual bool Read_Frame_Keyframes(ChunkLoadClass &chunk_load);
	char Pad[0x2A8];
	float FrameStart;
	float FrameRand;
	unsigned int FrameNumKeyFrames;
	float *FrameKeyTimes;
	float *FrameValues;
};

bool ParticleEmitterDefClass::Read_Frame_Keyframes(ChunkLoadClass &chunk_load)
{
	bool success = true;

	W3dEmitterFrameHeaderStruct header;
	if (chunk_load.Read(&header, sizeof(header)) != sizeof(header))
		success = false;

	W3dEmitterFrameKeyframeStruct key;
	if (chunk_load.Read(&key, sizeof(key)) == sizeof(key))
		FrameStart = key.Frame;

	FrameNumKeyFrames = header.KeyframeCount;
	FrameRand = header.Random;

	if (FrameNumKeyFrames > 0)
	{
		FrameKeyTimes = new float[FrameNumKeyFrames];
		FrameValues = new float[FrameNumKeyFrames];
	}

	for (unsigned int i = 0; (i < header.KeyframeCount) && (success == true); ++i)
	{
		W3dEmitterFrameKeyframeStruct key;
		if (chunk_load.Read(&key, sizeof(key)) != sizeof(key))
			success = false;
		FrameKeyTimes[i] = key.Time;
		FrameValues[i] = key.Frame;
	}

	return success;
}
