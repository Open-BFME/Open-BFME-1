// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME's emitter read entry points return a one-byte bool. Keep this ABI view
// local because the later vendored declaration returns WW3DErrorType.

#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "chunkio.h"
#include "w3d_file.h"
#include "vector3.h"

#define BYTE_TO_FLOAT(byte) (((float)(byte)) / 255.0F)
#define RGBA_TO_VECTOR3(rgba) Vector3(BYTE_TO_FLOAT((rgba).R), BYTE_TO_FLOAT((rgba).G), BYTE_TO_FLOAT((rgba).B))

template <class T> struct ParticlePropertyStruct
{
	T Start;
	T Rand;
	unsigned int NumKeyFrames;
	float *KeyTimes;
	T *Values;
};

#define DECL_DUMMY(n) virtual void Dummy##n();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_ldr.h
class ParticleEmitterDefClass
{
protected:
	virtual bool Read_Props(ChunkLoadClass &chunk_load);
	DECL_DUMMY(1)
	DECL_DUMMY(2)
	DECL_DUMMY(3)
	DECL_DUMMY(4)
	DECL_DUMMY(5)
	DECL_DUMMY(6)
	DECL_DUMMY(7)
	DECL_DUMMY(8)
	DECL_DUMMY(9)
	DECL_DUMMY(10)
	DECL_DUMMY(11)
	DECL_DUMMY(12)
	DECL_DUMMY(13)
	DECL_DUMMY(14)
	DECL_DUMMY(15)
	DECL_DUMMY(16)
	DECL_DUMMY(17)
	DECL_DUMMY(18)
	DECL_DUMMY(19)
	DECL_DUMMY(20)
	DECL_DUMMY(21)
	DECL_DUMMY(22)
	DECL_DUMMY(23)
	DECL_DUMMY(24)
	DECL_DUMMY(25)
	DECL_DUMMY(26)
	DECL_DUMMY(27)
	DECL_DUMMY(28)
	DECL_DUMMY(29)
	DECL_DUMMY(30)
	DECL_DUMMY(31)
	DECL_DUMMY(32)
	DECL_DUMMY(33)
	DECL_DUMMY(34)
	DECL_DUMMY(35)
	DECL_DUMMY(36)
	DECL_DUMMY(37)
	DECL_DUMMY(38)
	DECL_DUMMY(39)
	DECL_DUMMY(40)
	DECL_DUMMY(41)
	DECL_DUMMY(42)
	DECL_DUMMY(43)
	DECL_DUMMY(44)
	DECL_DUMMY(45)
	DECL_DUMMY(46)
	DECL_DUMMY(47)
	DECL_DUMMY(48)
	DECL_DUMMY(49)
	DECL_DUMMY(50)
	DECL_DUMMY(51)
	DECL_DUMMY(52)
	DECL_DUMMY(53)
	DECL_DUMMY(54)
	DECL_DUMMY(55)
	DECL_DUMMY(56)
	virtual bool Read_Color_Keyframe(ChunkLoadClass &chunk_load, float *key_time, Vector3 *value);
	virtual bool Read_Opacity_Keyframe(ChunkLoadClass &chunk_load, float *key_time, float *value);
	virtual bool Read_Size_Keyframe(ChunkLoadClass &chunk_load, float *key_time, float *value);
	DECL_DUMMY(60)
	DECL_DUMMY(61)
	DECL_DUMMY(62)
	DECL_DUMMY(63)
	DECL_DUMMY(64)
	DECL_DUMMY(65)
	DECL_DUMMY(66)
	DECL_DUMMY(67)
	DECL_DUMMY(68)
	DECL_DUMMY(69)
	DECL_DUMMY(70)
	DECL_DUMMY(71)
	DECL_DUMMY(72)
	DECL_DUMMY(73)
	DECL_DUMMY(74)
	DECL_DUMMY(75)
	DECL_DUMMY(76)
	DECL_DUMMY(77)
	virtual void Free_Props();

private:
	char Pad[0x244];
	ParticlePropertyStruct<Vector3> ColorKeyframes;
	ParticlePropertyStruct<float> OpacityKeyframes;
	ParticlePropertyStruct<float> SizeKeyframes;
};

bool ParticleEmitterDefClass::Read_Props(ChunkLoadClass &chunk_load)
{
	bool ret_val = false;
	Free_Props();

	if (chunk_load.Open_Chunk() && chunk_load.Cur_Chunk_ID() == W3D_CHUNK_EMITTER_PROPS)
	{
		W3dEmitterPropertyStruct info = { 0 };
		if (chunk_load.Read(&info, sizeof(info)) == sizeof(info))
		{
			unsigned int index = 0;

			ColorKeyframes.NumKeyFrames = info.ColorKeyframes - 1;
			OpacityKeyframes.NumKeyFrames = info.OpacityKeyframes - 1;
			SizeKeyframes.NumKeyFrames = info.SizeKeyframes - 1;
			ColorKeyframes.Rand = RGBA_TO_VECTOR3(info.ColorRandom);
			OpacityKeyframes.Rand = info.OpacityRandom;
			SizeKeyframes.Rand = info.SizeRandom;

			if (ColorKeyframes.NumKeyFrames > 0)
			{
				ColorKeyframes.KeyTimes = new float[ColorKeyframes.NumKeyFrames];
				ColorKeyframes.Values = new Vector3[ColorKeyframes.NumKeyFrames];
			}

			if (OpacityKeyframes.NumKeyFrames > 0)
			{
				OpacityKeyframes.KeyTimes = new float[OpacityKeyframes.NumKeyFrames];
				OpacityKeyframes.Values = new float[OpacityKeyframes.NumKeyFrames];
			}

			if (SizeKeyframes.NumKeyFrames > 0)
			{
				SizeKeyframes.KeyTimes = new float[SizeKeyframes.NumKeyFrames];
				SizeKeyframes.Values = new float[SizeKeyframes.NumKeyFrames];
			}

			Read_Color_Keyframe(chunk_load, NULL, &ColorKeyframes.Start);
			for (index = 0; index < ColorKeyframes.NumKeyFrames; ++index)
			{
				Read_Color_Keyframe(chunk_load, &ColorKeyframes.KeyTimes[index], &ColorKeyframes.Values[index]);
			}

			int last_keyframe = ColorKeyframes.NumKeyFrames - 1;
			if (last_keyframe > 0 &&
				ColorKeyframes.Values[last_keyframe].X == 0 &&
				ColorKeyframes.Values[last_keyframe].Y == 0 &&
				ColorKeyframes.Values[last_keyframe].Z == 0 &&
				(ColorKeyframes.Rand.X > 0 || ColorKeyframes.Rand.Y > 0 || ColorKeyframes.Rand.Z > 0))
			{
				ColorKeyframes.Values[last_keyframe].X = -ColorKeyframes.Rand.X;
				ColorKeyframes.Values[last_keyframe].Y = -ColorKeyframes.Rand.Y;
				ColorKeyframes.Values[last_keyframe].Z = -ColorKeyframes.Rand.Z;
			}

			Read_Opacity_Keyframe(chunk_load, NULL, &OpacityKeyframes.Start);
			for (index = 0; index < OpacityKeyframes.NumKeyFrames; ++index)
			{
				Read_Opacity_Keyframe(chunk_load, &OpacityKeyframes.KeyTimes[index], &OpacityKeyframes.Values[index]);
			}

			Read_Size_Keyframe(chunk_load, NULL, &SizeKeyframes.Start);
			for (index = 0; index < SizeKeyframes.NumKeyFrames; ++index)
			{
				Read_Size_Keyframe(chunk_load, &SizeKeyframes.KeyTimes[index], &SizeKeyframes.Values[index]);
			}

			ret_val = true;
		}

		chunk_load.Close_Chunk();
	}

	return ret_val;
}
