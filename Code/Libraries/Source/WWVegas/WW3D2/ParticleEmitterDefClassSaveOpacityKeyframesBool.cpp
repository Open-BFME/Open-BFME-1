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
	virtual bool Save_Opacity_Keyframes(ChunkSaveClass &chunk_save);
	char Pad[0x268];
	float OpacityStart;
	float OpacityRand;
	unsigned int OpacityNumKeyFrames;
	float *OpacityKeyTimes;
	float *OpacityValues;
};

bool ParticleEmitterDefClass::Save_Opacity_Keyframes(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;

	W3dEmitterOpacityKeyframeStruct info = { 0 };
	info.Time = 0;
	info.Opacity = OpacityStart;

	if (chunk_save.Write(&info, sizeof(info)) == sizeof(info))
	{
		int count = OpacityNumKeyFrames;
		bool success = true;
		for (int index = 0; (index < count) && success; index++)
		{
			info.Time = OpacityKeyTimes[index];
			info.Opacity = OpacityValues[index];
			success = (chunk_save.Write(&info, sizeof(info)) == sizeof(info));
		}

		ret_val = (success != false);
	}

	return ret_val;
}
