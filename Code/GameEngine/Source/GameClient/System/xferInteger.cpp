// cl: /DNDEBUG /MD /EHsc

// xferInteger, retail 0x0010C300. Four instructions of setup and one virtual
// call: Xfer's slot at +0x90 takes a name, an address and a size, and this
// helper always passes four bytes.
//
// The name it passes is the literal "ParticleType", which is not generic - the
// helper is one the particle-system bulk file uses for that one field, and the
// decorated name reloc_names recovered says only that its parameters are an
// Xfer and an Int.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h
class Xfer
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_0C() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_1C() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _bfme_pad_28() = 0;
	virtual void _bfme_pad_2C() = 0;
	virtual void _bfme_pad_30() = 0;
	virtual void _bfme_pad_34() = 0;
	virtual void _bfme_pad_38() = 0;
	virtual void _bfme_pad_3C() = 0;
	virtual void _bfme_pad_40() = 0;
	virtual void _bfme_pad_44() = 0;
	virtual void _bfme_pad_48() = 0;
	virtual void _bfme_pad_4C() = 0;
	virtual void _bfme_pad_50() = 0;
	virtual void _bfme_pad_54() = 0;
	virtual void _bfme_pad_58() = 0;
	virtual void _bfme_pad_5C() = 0;
	virtual void _bfme_pad_60() = 0;
	virtual void _bfme_pad_64() = 0;
	virtual void _bfme_pad_68() = 0;
	virtual void _bfme_pad_6C() = 0;
	virtual void _bfme_pad_70() = 0;
	virtual void _bfme_pad_74() = 0;
	virtual void _bfme_pad_78() = 0;
	virtual void _bfme_pad_7C() = 0;
	virtual void _bfme_pad_80() = 0;
	virtual void _bfme_pad_84() = 0;
	virtual void _bfme_pad_88() = 0;
	virtual void _bfme_pad_8C() = 0;
	virtual void xferUser( const char *name, void *data, Int size ) = 0;	// +0x90
};

// ?xferInteger@@YAXAAVXfer@@AAH@Z
void xferInteger( Xfer &xfer, Int &value )
{
	xfer.xferUser( "ParticleType", &value, 4 );
}

// This copy is emitted by the particle-system TU for the enum field with its
// own retail name.  It has the same call shape as xferInteger, but the string
// literal is part of the byte-true identity.
void xferIntegerParticlePriority( Xfer &xfer, Int &value )
{
	xfer.xferUser( "ParticlePriorityType", &value, 4 );
}
