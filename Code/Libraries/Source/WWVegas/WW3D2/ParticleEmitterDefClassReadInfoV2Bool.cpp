// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Retail returns Read_InfoV2 as a byte-valued success flag.  Keep that ABI
// view local while the vendored declaration remains WW3DErrorType.

#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "chunkio.h"
#include "v3_rnd.h"
#include "w3d_file.h"
#include <string.h>

// The real class has 73 virtual entries before Create_Randomizer.  These
// declarations preserve that slot without importing the enum-returning view.
#define DECL_RVA_DUMMY(n) virtual void RvaDummy##n(void);
class ParticleEmitterDefClass
{
public:
	virtual ~ParticleEmitterDefClass(void);
	DECL_RVA_DUMMY(01)
	DECL_RVA_DUMMY(02)
	DECL_RVA_DUMMY(03)
	DECL_RVA_DUMMY(04)
	DECL_RVA_DUMMY(05)
	DECL_RVA_DUMMY(06)
	DECL_RVA_DUMMY(07)
	DECL_RVA_DUMMY(08)
	DECL_RVA_DUMMY(09)
	DECL_RVA_DUMMY(10)
	DECL_RVA_DUMMY(11)
	DECL_RVA_DUMMY(12)
	DECL_RVA_DUMMY(13)
	DECL_RVA_DUMMY(14)
	DECL_RVA_DUMMY(15)
	DECL_RVA_DUMMY(16)
	DECL_RVA_DUMMY(17)
	DECL_RVA_DUMMY(18)
	DECL_RVA_DUMMY(19)
	DECL_RVA_DUMMY(20)
	DECL_RVA_DUMMY(21)
	DECL_RVA_DUMMY(22)
	DECL_RVA_DUMMY(23)
	DECL_RVA_DUMMY(24)
	DECL_RVA_DUMMY(25)
	DECL_RVA_DUMMY(26)
	DECL_RVA_DUMMY(27)
	DECL_RVA_DUMMY(28)
	DECL_RVA_DUMMY(29)
	DECL_RVA_DUMMY(30)
	DECL_RVA_DUMMY(31)
	DECL_RVA_DUMMY(32)
	DECL_RVA_DUMMY(33)
	DECL_RVA_DUMMY(34)
	DECL_RVA_DUMMY(35)
	DECL_RVA_DUMMY(36)
	DECL_RVA_DUMMY(37)
	DECL_RVA_DUMMY(38)
	DECL_RVA_DUMMY(39)
	DECL_RVA_DUMMY(40)
	DECL_RVA_DUMMY(41)
	DECL_RVA_DUMMY(42)
	DECL_RVA_DUMMY(43)
	DECL_RVA_DUMMY(44)
	DECL_RVA_DUMMY(45)
	DECL_RVA_DUMMY(46)
	DECL_RVA_DUMMY(47)
	DECL_RVA_DUMMY(48)
	DECL_RVA_DUMMY(49)

protected:
	virtual bool Read_InfoV2(ChunkLoadClass &chunk_load);

public:
	DECL_RVA_DUMMY(51)
	DECL_RVA_DUMMY(52)
	DECL_RVA_DUMMY(53)
	DECL_RVA_DUMMY(54)
	DECL_RVA_DUMMY(55)
	DECL_RVA_DUMMY(56)
	DECL_RVA_DUMMY(57)
	DECL_RVA_DUMMY(58)
	DECL_RVA_DUMMY(59)
	DECL_RVA_DUMMY(60)
	DECL_RVA_DUMMY(61)
	DECL_RVA_DUMMY(62)
	DECL_RVA_DUMMY(63)
	DECL_RVA_DUMMY(64)
	DECL_RVA_DUMMY(65)
	DECL_RVA_DUMMY(66)
	DECL_RVA_DUMMY(67)
	DECL_RVA_DUMMY(68)
	DECL_RVA_DUMMY(69)
	DECL_RVA_DUMMY(70)
	DECL_RVA_DUMMY(71)
	DECL_RVA_DUMMY(72)
	virtual Vector3Randomizer *Create_Randomizer(W3dVolumeRandomizerStruct &info);

	char Pad0[0x160];
	W3dEmitterInfoStructV2 InfoV2;
	char Pad1[0xf4];
	Vector3Randomizer *CreationVolume;
	Vector3Randomizer *VelocityRandomizer;
};
#undef DECL_RVA_DUMMY

bool ParticleEmitterDefClass::Read_InfoV2(ChunkLoadClass &chunk_load)
{
	bool ret_val = false;

	if (chunk_load.Open_Chunk() &&
		(chunk_load.Cur_Chunk_ID() == W3D_CHUNK_EMITTER_INFOV2)) {
		::memset(&InfoV2, 0, sizeof(InfoV2));
		if (chunk_load.Read(&InfoV2, sizeof(InfoV2)) == sizeof(InfoV2)) {
			if (CreationVolume != 0) {
				delete CreationVolume;
				CreationVolume = 0;
			}
			if (VelocityRandomizer != 0) {
				delete VelocityRandomizer;
				VelocityRandomizer = 0;
			}
			CreationVolume = Create_Randomizer(InfoV2.CreationVolume);
			VelocityRandomizer = Create_Randomizer(InfoV2.VelRandom);
			ret_val = true;
		}
		chunk_load.Close_Chunk();
	}

	return ret_val;
}
