// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// BFME's emitter keyframe entry points return a one-byte bool. Keep this ABI
// view local because the later vendored declaration returns WW3DErrorType.

// The nine ParticleEmitterDefClass chunk bodies that read or write a keyframe
// track. They sat in nine files, and every one of them declared the whole class
// from scratch as a single virtual followed by `char Pad[N]` and just the block
// it touched -- nine pads, nine partial classes, one real layout.
//
// Put side by side the pads tile that layout exactly, with no gap and no overlap.
// Members start at +0x04 because the vptr is at 0, so each file's Pad[N] puts its
// block at N+4:
//
//   +0x248  Color     Vector3 start and rand, count, times, Vector3 values   0x24
//   +0x26C  Opacity   float start and rand, count, times, values             0x14
//   +0x280  Size      as opacity                                             0x14
//   +0x294  Rotation  as opacity, plus InitialOrientationRandom              0x18
//   +0x2AC  Frame     as opacity                                             0x14
//   +0x2C0  Blur      as opacity                                             0x14
//
// Each block ends exactly where the next begins -- 0x248+0x24 = 0x26C,
// 0x26C+0x14 = 0x280, 0x280+0x14 = 0x294, 0x294+0x18 = 0x2AC, 0x2AC+0x14 = 0x2C0
// -- so the six accounts corroborate one another rather than merely coexisting.
// Three of the blocks are pinned twice over, by a reader and a writer written in
// different files that never saw each other: Rotation at 0x290, Frame at 0x2A8
// and Blur at 0x2BC each carry the same pad in their Read_ and their Save_ file.
//
// Declaring all nine virtuals together does not move anything: they share one
// vptr, so the members still start at +0x04 exactly as they did when each file
// declared one virtual.
//
// All nine are protected virtuals (MAE) and share one section. All nine carried a
// byte-identical `// cl:` line, so no flag was probed or changed.

#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "chunkio.h"
#include "w3d_file.h"
#include "vector3.h"

// Used by Save_Color_Keyframes only.
#define FLOAT_TO_BYTE(fval) ((unsigned char)(max((fval), 0.0F) * 255.0F))
#define VECTOR3_TO_RGBA(vector3, rgba) \
	rgba.R = FLOAT_TO_BYTE((vector3).X); \
	rgba.G = FLOAT_TO_BYTE((vector3).Y); \
	rgba.B = FLOAT_TO_BYTE((vector3).Z);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_ldr.h
class ParticleEmitterDefClass
{
protected:
	virtual bool Read_Rotation_Keyframes(ChunkLoadClass &chunk_load);
	virtual bool Read_Frame_Keyframes(ChunkLoadClass &chunk_load);
	virtual bool Read_Blur_Time_Keyframes(ChunkLoadClass &chunk_load);
	virtual bool Save_Opacity_Keyframes(ChunkSaveClass &chunk_save);
	virtual bool Save_Size_Keyframes(ChunkSaveClass &chunk_save);
	virtual bool Save_Rotation_Keyframes(ChunkSaveClass &chunk_save);
	virtual bool Save_Frame_Keyframes(ChunkSaveClass &chunk_save);
	virtual bool Save_Blur_Time_Keyframes(ChunkSaveClass &chunk_save);
	virtual bool Save_Color_Keyframes(ChunkSaveClass &chunk_save);

	char Pad[0x244];

	Vector3 ColorStart;				// +0x248
	Vector3 ColorRand;
	unsigned int ColorNumKeyFrames;
	float *ColorKeyTimes;
	Vector3 *ColorValues;

	float OpacityStart;				// +0x26C
	float OpacityRand;
	unsigned int OpacityNumKeyFrames;
	float *OpacityKeyTimes;
	float *OpacityValues;

	float SizeStart;				// +0x280
	float SizeRand;
	unsigned int SizeNumKeyFrames;
	float *SizeKeyTimes;
	float *SizeValues;

	float RotationStart;				// +0x294
	float RotationRand;
	unsigned int RotationNumKeyFrames;
	float *RotationKeyTimes;
	float *RotationValues;
	float InitialOrientationRandom;

	float FrameStart;				// +0x2AC
	float FrameRand;
	unsigned int FrameNumKeyFrames;
	float *FrameKeyTimes;
	float *FrameValues;

	float BlurStart;				// +0x2C0
	float BlurRand;
	unsigned int BlurNumKeyFrames;
	float *BlurKeyTimes;
	float *BlurValues;
};

// ?Read_Rotation_Keyframes@ParticleEmitterDefClass@@MAE_NAAVChunkLoadClass@@@Z  retail 0x0098C6D0
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

// ?Read_Frame_Keyframes@ParticleEmitterDefClass@@MAE_NAAVChunkLoadClass@@@Z  retail 0x0098C7E0
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

// ?Read_Blur_Time_Keyframes@ParticleEmitterDefClass@@MAE_NAAVChunkLoadClass@@@Z  retail 0x0098C8C0
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

// ?Save_Opacity_Keyframes@ParticleEmitterDefClass@@MAE_NAAVChunkSaveClass@@@Z  retail 0x0098CC70
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

// ?Save_Size_Keyframes@ParticleEmitterDefClass@@MAE_NAAVChunkSaveClass@@@Z  retail 0x0098CD10
bool ParticleEmitterDefClass::Save_Size_Keyframes(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;

	W3dEmitterSizeKeyframeStruct info = { 0 };
	info.Time = 0;
	info.Size = SizeStart;

	if (chunk_save.Write(&info, sizeof(info)) == sizeof(info))
	{
		int count = SizeNumKeyFrames;
		bool success = true;
		for (int index = 0; (index < count) && success; index++)
		{
			info.Time = SizeKeyTimes[index];
			info.Size = SizeValues[index];
			success = (chunk_save.Write(&info, sizeof(info)) == sizeof(info));
		}

		ret_val = (success != false);
	}

	return ret_val;
}

// ?Save_Rotation_Keyframes@ParticleEmitterDefClass@@MAE_NAAVChunkSaveClass@@@Z  retail 0x0098CE00
bool ParticleEmitterDefClass::Save_Rotation_Keyframes(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;

	if (chunk_save.Begin_Chunk(W3D_CHUNK_EMITTER_ROTATION_KEYFRAMES) == TRUE)
	{
		W3dEmitterRotationHeaderStruct header;
		header.KeyframeCount = RotationNumKeyFrames;
		header.Random = RotationRand;
		header.OrientationRandom = InitialOrientationRandom;
		chunk_save.Write(&header, sizeof(W3dEmitterRotationHeaderStruct));

		bool success = true;
		W3dEmitterRotationKeyframeStruct key;
		key.Time = 0;
		key.Rotation = RotationStart;
		chunk_save.Write(&key, sizeof(key));

		for (unsigned int index = 0; (index < header.KeyframeCount) && success; index++)
		{
			key.Time = RotationKeyTimes[index];
			key.Rotation = RotationValues[index];
			success = (chunk_save.Write(&key, sizeof(key)) == sizeof(key));
		}

		ret_val = (success != false);
		chunk_save.End_Chunk();
	}

	return ret_val;
}

// ?Save_Frame_Keyframes@ParticleEmitterDefClass@@MAE_NAAVChunkSaveClass@@@Z  retail 0x0098CEE0
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

// ?Save_Blur_Time_Keyframes@ParticleEmitterDefClass@@MAE_NAAVChunkSaveClass@@@Z  retail 0x0098CFB0
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

// ?Save_Color_Keyframes@ParticleEmitterDefClass@@MAE_NAAVChunkSaveClass@@@Z  retail 0x0098E140
bool ParticleEmitterDefClass::Save_Color_Keyframes(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;

	W3dEmitterColorKeyframeStruct info = { 0 };
	info.Time = 0;
	VECTOR3_TO_RGBA(ColorStart, info.Color);

	if (chunk_save.Write(&info, sizeof(info)) == sizeof(info))
	{
		int count = ColorNumKeyFrames;
		bool success = true;
		for (int index = 0; (index < count) && success; index++)
		{
			info.Time = ColorKeyTimes[index];
			VECTOR3_TO_RGBA(ColorValues[index], info.Color);
			success = (chunk_save.Write(&info, sizeof(info)) == sizeof(info));
		}

		ret_val = (success != false);
	}

	return ret_val;
}
