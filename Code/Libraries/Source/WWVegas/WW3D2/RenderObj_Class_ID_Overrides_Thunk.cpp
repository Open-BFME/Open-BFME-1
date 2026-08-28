// cl: /DNDEBUG /MD /EHsc

// Three Class_ID overrides, each carrying the two independent witnesses this
// identification needs.
//
// Position: every one sits directly after that class's destructor and its
// Clone override, which is exactly rendobj.h's declaration order -- destructor,
// Clone, Class_ID.
//
// Value: each returns the number rendobj.h's ClassID enum assigns to that class,
// counting from CLASSID_MESH = 0. CLASSID_PARTICLEEMITTER is 15,
// CLASSID_PARTICLEBUFFER is 16, CLASSID_NULL is 22.
//
// Neither witness is sufficient alone. Vtable position is corrupted by ICF
// folding and by this build's additions to the declaration lists, and a body
// returning a small constant is common enough that forty of them in this image
// return a value that happens to land inside the enum. They fail independently,
// so their agreement is what carries the claim.
class RenderObjClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_emt.h
class ParticleEmitterClass
{
public:
	virtual ~ParticleEmitterClass();
	virtual RenderObjClass *Clone(void) const;
	virtual int Class_ID(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_buf.h
class ParticleBufferClass
{
public:
	virtual ~ParticleBufferClass();
	virtual RenderObjClass *Clone(void) const;
	virtual int Class_ID(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/nullrobj.h
class Null3DObjClass
{
public:
	virtual ~Null3DObjClass();
	virtual RenderObjClass *Clone(void) const;
	virtual int Class_ID(void) const;
};

// ?Class_ID@ParticleEmitterClass@@UBEHXZ
int ParticleEmitterClass::Class_ID(void) const
{
	return 15;
}

// ?Class_ID@ParticleBufferClass@@UBEHXZ
int ParticleBufferClass::Class_ID(void) const
{
	return 16;
}

// ?Class_ID@Null3DObjClass@@UBEHXZ
int Null3DObjClass::Class_ID(void) const
{
	return 22;
}
