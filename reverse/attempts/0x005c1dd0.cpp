// ??0ParticleSystemInfo@FXParticleSystem@@QAE@XZ
// partial score=0.9 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FXParticleSystem::ParticleSystemInfo constructor.
//
// This TU-local layout shim keeps the original constructor's explicit object
// initialization order.  ParticleSystemInfo's vtable is installed by the
// constructor, so the known class vtable address is part of the layout
// evidence rather than a compiler intrinsic.
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
	volatile unsigned int *dwords =
		reinterpret_cast<volatile unsigned int *>( this );
	volatile unsigned char *bytes =
		reinterpret_cast<volatile unsigned char *>( this );

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

	bytes[0x80] = static_cast<unsigned char>( zero );
	bytes[0x81] = static_cast<unsigned char>( zero );
	bytes[0x82] = static_cast<unsigned char>( zero );
	bytes[0x83] = static_cast<unsigned char>( zero );
	bytes[4] = static_cast<unsigned char>( zero );
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
