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
	virtual bool Read_Rotation_Keyframes(ChunkLoadClass &chunk_load);
	char Pad[0x290];
	float RotationStart;
	float RotationRand;
	unsigned int RotationNumKeyFrames;
	float *RotationKeyTimes;
	float *RotationValues;
	float InitialOrientationRandom;
};

bool ParticleEmitterDefClass::Read_Rotation_Keyframes(ChunkLoadClass &chunk_load)
{
	bool success = true;

	W3dEmitterRotationHeaderStruct header;
	if (chunk_load.Read(&header, sizeof(header)) != sizeof(header))
		success = false;
	RotationNumKeyFrames = header.KeyframeCount;
	RotationRand = header.Random;
	InitialOrientationRandom = header.OrientationRandom;

	W3dEmitterRotationKeyframeStruct key;
	if (chunk_load.Read(&key, sizeof(key)) == sizeof(key))
		RotationStart = key.Rotation;

	if (RotationNumKeyFrames > 0)
	{
		RotationKeyTimes = new float[RotationNumKeyFrames];
		RotationValues = new float[RotationNumKeyFrames];
	}

	for (unsigned int i = 0; (i < header.KeyframeCount) && (success == true); ++i)
	{
		W3dEmitterRotationKeyframeStruct key;
		if (chunk_load.Read(&key, sizeof(key)) == sizeof(key))
		{
			RotationKeyTimes[i] = key.Time;
			RotationValues[i] = key.Rotation;
		}
		else
		{
			RotationKeyTimes[i] = 0.0f;
			RotationValues[i] = 0.0f;
			success = false;
		}
	}

	return success;
}
