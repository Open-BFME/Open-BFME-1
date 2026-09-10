// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of the FX particle-info default ctor.
//
// The retail body installs vtable 0x01073878 and initializes the 0x98-byte
// object through scalar stores.  Non-volatile TU-local views preserve the
// compiler's literal-load scheduling; the two barriers preserve the retail
// store groups without embedding retail instructions.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

namespace FXParticleSystem { class ParticleSystemInfo; }
class FXParticleSystem::ParticleSystemInfo
{
public:
	ParticleSystemInfo();
};

// ??0ParticleSystemInfo@FXParticleSystem@@QAE@XZ
FXParticleSystem::ParticleSystemInfo::ParticleSystemInfo()
{
	unsigned int *dwords = reinterpret_cast<unsigned int *>( this );
	unsigned char *bytes = reinterpret_cast<unsigned char *>( this );
	unsigned int zero = 0;

	dwords[0] = 0x01073878;
	dwords[4] = zero;
	dwords[5] = zero;
	dwords[6] = zero;
	dwords[7] = zero;
	dwords[10] = zero;
	dwords[11] = zero;
	dwords[12] = zero;
	dwords[13] = zero;
	dwords[14] = zero;
	dwords[15] = zero;
	dwords[17] = zero;
	dwords[18] = zero;
	dwords[19] = zero;
	dwords[20] = zero;
	dwords[21] = zero;
	dwords[22] = zero;
	dwords[23] = zero;
	dwords[24] = zero;
	dwords[25] = zero;
	dwords[26] = zero;
	dwords[30] = zero;
	_ReadWriteBarrier();
	dwords[31] = 1;
	dwords[3] = 1;
	dwords[2] = 1;

	bytes[0x80] = 0;
	bytes[0x81] = 0;
	bytes[0x82] = 0;
	bytes[0x83] = 0;
	bytes[4] = 0;
	dwords[27] = zero;
	dwords[28] = zero;
	dwords[29] = zero;
	unsigned int unit = 0x3f800000;
	_ReadWriteBarrier();
	dwords[8] = zero;
	dwords[9] = zero;
	dwords[16] = zero;
	dwords[33] = zero;
	dwords[34] = zero;
	dwords[35] = unit;
	dwords[36] = unit;
	dwords[37] = zero;
}
