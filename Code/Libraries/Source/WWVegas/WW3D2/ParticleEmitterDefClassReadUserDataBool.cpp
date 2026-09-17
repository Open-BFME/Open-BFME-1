// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME's emitter read entry points return a one-byte bool. Keep this ABI view
// local because the later vendored declaration returns WW3DErrorType.

#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "chunkio.h"
#include "w3d_file.h"
#include <stdlib.h>

#define DECL_DUMMY(n) virtual void Dummy##n();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_ldr.h
class ParticleEmitterDefClass
{
public:
	virtual ~ParticleEmitterDefClass(void);

protected:
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
	virtual bool Read_User_Data(ChunkLoadClass &chunk_load);
	DECL_DUMMY(49)
	DECL_DUMMY(50)
	DECL_DUMMY(51)
	DECL_DUMMY(52)
	DECL_DUMMY(53)
	DECL_DUMMY(54)
	DECL_DUMMY(55)
	DECL_DUMMY(56)
	DECL_DUMMY(57)
	DECL_DUMMY(58)
	DECL_DUMMY(59)
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

private:
	char *Name;
	char *UserString;
	int UserType;
	unsigned int Version;
};
#undef DECL_DUMMY

bool ParticleEmitterDefClass::Read_User_Data(ChunkLoadClass &chunk_load)
{
	bool ret_val = false;

	if (chunk_load.Open_Chunk() &&
		(chunk_load.Cur_Chunk_ID() == W3D_CHUNK_EMITTER_USER_DATA)) {

		W3dEmitterUserInfoStruct user_info = { 0 };
		if (chunk_load.Read(&user_info, sizeof(user_info)) == sizeof(user_info)) {
			ret_val = true;
			UserType = user_info.Type;

			if (user_info.SizeofStringParam > 0) {
				UserString = (char *)::malloc(sizeof(char) * (user_info.SizeofStringParam + 1));
				UserString[0] = 0;

				if (chunk_load.Read(UserString, user_info.SizeofStringParam) != user_info.SizeofStringParam) {
					ret_val = false;
				}
			}
		}

		chunk_load.Close_Chunk();
	}

	return ret_val;
}
