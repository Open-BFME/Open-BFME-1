// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME's emitter read entry points return a one-byte bool.  Keep this ABI view
// local because the later vendored declaration returns WW3DErrorType.

#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "chunkio.h"
#include "w3d_file.h"

class ParticleEmitterDefClass
{
protected:
	virtual bool Read_Blur_Time_Keyframes(ChunkLoadClass &chunk_load);
	char Pad[0x2BC];
	float BlurStart;
	float BlurRand;
	unsigned int BlurNumKeyFrames;
	float *BlurKeyTimes;
	float *BlurValues;
};

bool ParticleEmitterDefClass::Read_Blur_Time_Keyframes(ChunkLoadClass &chunk_load)
{
	bool success = true;

	W3dEmitterBlurTimeHeaderStruct header;
	if (chunk_load.Read(&header, sizeof(header)) != sizeof(header))
		success = false;

	W3dEmitterBlurTimeKeyframeStruct key;
	if (chunk_load.Read(&key, sizeof(key)) == sizeof(key))
		BlurStart = key.BlurTime;

	BlurNumKeyFrames = header.KeyframeCount;
	BlurRand = header.Random;

	if (BlurNumKeyFrames > 0)
	{
		BlurKeyTimes = new float[BlurNumKeyFrames];
		BlurValues = new float[BlurNumKeyFrames];
	}

	for (unsigned int i = 0; (i < header.KeyframeCount) && (success == true); ++i)
	{
		W3dEmitterBlurTimeKeyframeStruct key;
		if (chunk_load.Read(&key, sizeof(key)) != sizeof(key))
			success = false;
		BlurKeyTimes[i] = key.Time;
		BlurValues[i] = key.BlurTime;
	}

	return success;
}
