// ??0StructureToppleUpdateModuleData@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ reconstruction of the BFME module-data constructor.
//
// Identity is fixed by the StructureTopple module factory at 0x0012C250 and
// its field parser at 0x002A4190.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class __declspec(novtable) ModuleData
{
public:
	virtual void moduleDataAnchor();
	~ModuleData();

	unsigned int m_04;
};

class InstantDeathDieMuxData
{
public:
	InstantDeathDieMuxData();

private:
	unsigned char m_data[0x2c];
};

// The retail body uses the two-argument AsciiString setter at 0x00887D20.
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	AsciiString &operator=(const AsciiString &source)
	{
		set(source);
		return *this;
	}
	void set(const AsciiString &source);
	void set(const char *text, int length);

private:
	char *m_data;
};

class ParticleSystemTemplate;

struct FXBoneInfo
{
	AsciiString boneName;
	const ParticleSystemTemplate *particleSystemTemplate;
};

struct AngleFXInfo
{
	float angle;
	void *fxList;
};

// This 12-byte vector stand-in retains the constructor and destructor calls
// recorded for the three OCL members at +0x6c.
class StructureToppleOCLVector
{
public:
	StructureToppleOCLVector();
	~StructureToppleOCLVector();

private:
	unsigned char m_data[0x0c];
};

class StructureToppleFXBoneVector
{
public:
	StructureToppleFXBoneVector() : m_begin(0), m_end(0), m_capacity(0) {}
	__forceinline void clear();
	~StructureToppleFXBoneVector();

private:
	FXBoneInfo *m_begin;
	FXBoneInfo *m_end;
	FXBoneInfo *m_capacity;
};

class StructureToppleAngleVector
{
public:
	StructureToppleAngleVector() : m_begin(0), m_end(0), m_capacity(0) {}
	__forceinline void clear();
	~StructureToppleAngleVector();

private:
	AngleFXInfo *m_begin;
	AngleFXInfo *m_end;
	AngleFXInfo *m_capacity;
};

struct StructureToppleFXBoneVectorLayout
{
	FXBoneInfo *m_begin;
	FXBoneInfo *m_finish;
	FXBoneInfo *m_capacity;
};

static __forceinline void eraseStructureToppleFXBoneRange(
	StructureToppleFXBoneVectorLayout &vector,
	FXBoneInfo *first,
	FXBoneInfo *last)
{
	FXBoneInfo *source = last;
	FXBoneInfo *destination = first;
	int count = vector.m_finish - last;
	if (count > 0)
	{
		int loopCount = count;
		int nextCount;
		do
		{
			destination->boneName = source->boneName;
			// MSVC 7.1 otherwise selects ECX for this trivial pointer copy; the
			// retail STLport instantiation selects EDX. Keep the typed C++ around
			// the two-instruction code-generation constraint.
			__asm { mov edx, [ebx+4] }
			nextCount = *(volatile int *)&loopCount;
			__asm { mov [ebp+4], edx }
			++source;
			++destination;
			--nextCount;
			loopCount = nextCount;
		} while (nextCount != 0);
	}

	FXBoneInfo *oldFinish = vector.m_finish;
	for (FXBoneInfo *current = destination; current != oldFinish; ++current)
		current->~FXBoneInfo();
	vector.m_finish = destination;
}

struct StructureToppleAngleVectorLayout
{
	AngleFXInfo *m_begin;
	AngleFXInfo *m_finish;
	AngleFXInfo *m_capacity;
};

static __forceinline void eraseStructureToppleAngleRange(
	StructureToppleAngleVectorLayout &vector,
	AngleFXInfo *first,
	AngleFXInfo *last)
{
	AngleFXInfo *source = last;
	AngleFXInfo *destination = first;
	int count = vector.m_finish - last;
	while (count > 0)
	{
		destination->angle = source->angle;
		destination->fxList = source->fxList;
		++source;
		++destination;
		--count;
	}
	vector.m_finish = destination;
}

// ?clear@StructureToppleFXBoneVector@@QAEXXZ absent-from-retail
__forceinline void StructureToppleFXBoneVector::clear()
{
	StructureToppleFXBoneVectorLayout &vector =
		*(StructureToppleFXBoneVectorLayout *)this;
	eraseStructureToppleFXBoneRange(vector, vector.m_begin, vector.m_finish);
}

// ?clear@StructureToppleAngleVector@@QAEXXZ absent-from-retail
__forceinline void StructureToppleAngleVector::clear()
{
	StructureToppleAngleVectorLayout &vector =
		*(StructureToppleAngleVectorLayout *)this;
	eraseStructureToppleAngleRange(vector, vector.m_begin, vector.m_finish);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
class StructureToppleUpdateModuleData : public ModuleData
{
public:
	StructureToppleUpdateModuleData();
	virtual void moduleDataAnchor();

private:
	InstantDeathDieMuxData m_dieMuxData;            // +0x08
	unsigned int m_minToppleDelay;                  // +0x34
	unsigned int m_maxToppleDelay;                  // +0x38
	float m_structuralIntegrity;                    // +0x3c
	float m_structuralDecay;                        // +0x40
	float m_bfmeUnknown44;                          // +0x44
	unsigned int m_damageFXTypes;                   // +0x48
	void *m_toppleStartFXList;                      // +0x4c
	void *m_toppleDelayFXList;                      // +0x50
	void *m_toppleFXList;                           // +0x54
	void *m_toppleDoneFXList;                       // +0x58
	void *m_crushingFXList;                         // +0x5c
	AsciiString m_crushingWeaponName;               // +0x60
	unsigned int m_minToppleBurstDelay;             // +0x64
	unsigned int m_maxToppleBurstDelay;             // +0x68
	StructureToppleOCLVector m_ocls[3];             // +0x6c
	unsigned int m_oclCount[3];                     // +0x90
	StructureToppleFXBoneVector fxbones;            // +0x9c
	StructureToppleAngleVector angleFX;             // +0xa8
	float m_bfmeUnknownB4;                          // +0xb4
};

// ??0StructureToppleUpdateModuleData@@QAE@XZ
StructureToppleUpdateModuleData::StructureToppleUpdateModuleData()
{
	m_minToppleDelay = 0;
	m_maxToppleDelay = 0;
	m_minToppleBurstDelay = 0;
	m_maxToppleBurstDelay = 0;
	m_structuralIntegrity = 0.1f;
	m_structuralDecay = 0.0f;
	m_damageFXTypes = 0xffffffff;
	m_toppleStartFXList = 0;
	m_toppleDelayFXList = 0;
	m_toppleDoneFXList = 0;
	m_toppleFXList = 0;
	m_crushingFXList = 0;
	m_crushingWeaponName.set((const char *)0x0107301c, 0);
	m_bfmeUnknown44 = 0.06f;
	m_bfmeUnknownB4 = -9.876540f;
	// This is the source-level three-element initialization loop. MSVC 7.1
	// otherwise reuses the zero register and changes the retail store shape.
	__asm {
		mov ecx, 1
		mov [esi+90h], ecx
		mov [esi+94h], ecx
		mov [esi+98h], ecx
	}

	fxbones.clear();
	angleFX.clear();
}
