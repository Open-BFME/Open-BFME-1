// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the ParticleEmitterClass::Scale naked dump to clean C++.
//
// Zero Hour's part_emt.cpp body. Retail reads the layout out plainly: PosRand
// at this+0xD8 and VelRand at this+0xE8 are both null-checked before a virtual
// call at vtable +0x10, BaseVel is a Vector3 at this+0xDC (three consecutive
// scalings), OutwardVel is a single float at this+0xEC, and Buffer at
// this+0x130 is called without a null check through vtable +0x16C.
//
// Only the two virtual slots are reconstructed; the entries ahead of them are
// declared to place them and are never defined or called. Vector3 is copied
// from the reference WWMath header rather than hand-rolled, for the reason
// recorded in docs/lessons.md -- an equivalent-looking class makes MSVC route
// the temporaries through memory.

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) {};
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }

	Vector3 &operator = (const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Vector3 &operator *= (float k) { X = X * k; Y = Y * k; Z = Z * k; return *this; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/v3_rnd.h
class Vector3Randomizer
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();

	virtual void Scale(float scale);					///< vtable +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_buf.h
class ParticleBufferClass
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void unused62();
	virtual void unused63();
	virtual void unused64();
	virtual void unused65();
	virtual void unused66();
	virtual void unused67();
	virtual void unused68();
	virtual void unused69();
	virtual void unused70();
	virtual void unused71();
	virtual void unused72();
	virtual void unused73();
	virtual void unused74();
	virtual void unused75();
	virtual void unused76();
	virtual void unused77();
	virtual void unused78();
	virtual void unused79();
	virtual void unused80();
	virtual void unused81();
	virtual void unused82();
	virtual void unused83();
	virtual void unused84();
	virtual void unused85();
	virtual void unused86();
	virtual void unused87();
	virtual void unused88();
	virtual void unused89();
	virtual void unused90();

	virtual void Scale(float scale);					///< vtable +0x16C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_emt.h
class ParticleEmitterClass
{
public:
	virtual void Scale(float scale);

private:
	// the vtable pointer occupies +0x00
	unsigned char m_unreconstructed_04[0xD8 - 4];
	Vector3Randomizer *PosRand;							///< retail this+0xD8
	Vector3 BaseVel;									///< retail this+0xDC
	Vector3Randomizer *VelRand;							///< retail this+0xE8
	float OutwardVel;									///< retail this+0xEC
	unsigned char m_unreconstructed_F0[0x130 - 0xF0];
	ParticleBufferClass *Buffer;						///< retail this+0x130
};

// ?Scale@ParticleEmitterClass@@UAEXM@Z
void ParticleEmitterClass::Scale(float scale)
{
	// Scale all velosity and position parameters
	if (PosRand) PosRand->Scale(scale);
	BaseVel *= scale;
	if (VelRand) VelRand->Scale(scale);
	OutwardVel *= scale;

	// Scale sizes of all particles
	Buffer->Scale(scale);
}
