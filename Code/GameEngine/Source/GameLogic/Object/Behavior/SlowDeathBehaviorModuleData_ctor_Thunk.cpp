// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ for the retail SlowDeathBehaviorModuleData layout.

typedef void (*SlowArrayCellFn)(void *);

// MSVC 7.1 otherwise adds a null check and misses the retail exception-state
// byte before the RadiusDecalTemplate placement constructor.
__forceinline void *operator new(unsigned int, void *address)
{
	__assume(address != 0);
	__asm {
		mov byte ptr [esp+14h], 5
	}
	return address;
}

extern void __stdcall rva00906340VecCtor(
	void *ptr, unsigned stride, int count, SlowArrayCellFn ctor,
	SlowArrayCellFn dtor);
extern void j_00017391(void *);
extern void j_00029bfe(void *);

class __declspec(novtable) ModuleData
{
public:
	ModuleData() {}
	virtual void moduleDataAnchor();
	~ModuleData();

	unsigned int m_field04;
};

class InstantDeathDieMuxData
{
public:
	InstantDeathDieMuxData();

private:
	unsigned char m_storage[0x2c];
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	~RadiusDecalTemplate();

private:
	unsigned char m_storage[0x30];
};

class TailGuard
{
public:
	// This destructor emits the retail +0x124 store and keeps MSVC's delayed
	// exception-frame restore after that store.
	__forceinline ~TailGuard()
	{
		__asm {
			mov [esi+124h], ebx
		}
	}
};

class StructureCollapseOCLVector
{
public:
	StructureCollapseOCLVector();
	~StructureCollapseOCLVector();

private:
	unsigned char m_storage[0xc];
};

class StructureCollapseFXVector
{
public:
	StructureCollapseFXVector();
	~StructureCollapseFXVector();

private:
	unsigned char m_storage[0xc];
};

class Gen_uwm_0000513c
{
public:
	Gen_uwm_0000513c();
	~Gen_uwm_0000513c();

private:
	unsigned char m_storage[0xc];
};

class SlowDeathBehaviorModuleData : public ModuleData
{
public:
	SlowDeathBehaviorModuleData();

	InstantDeathDieMuxData m_dieMuxData;
	volatile float m_sinkRate;
	volatile int m_probabilityModifier;
	volatile float m_modifierBonusPerOverkillPercent;
	volatile unsigned int m_sinkDelay;
	volatile unsigned int m_sinkDelayVariance;
	volatile float m_destructionAltitude;
	volatile unsigned int m_destructionDelay;
	volatile unsigned int m_destructionDelayVariance;
	volatile unsigned int m_field54;
	StructureCollapseOCLVector m_fx[4];
	StructureCollapseFXVector m_ocls[4];
	Gen_uwm_0000513c m_weapons[4];
	unsigned char m_extraVectors[0x30];
	volatile float m_flingForce;
	volatile float m_flingForceVariance;
	volatile float m_flingPitch;
	volatile float m_flingPitchVariance;
	unsigned int m_zero128[10];
	unsigned int m_zero150[3];
	volatile unsigned char m_maskOfLoadedEffects;
	unsigned char m_pad15d[3];
	volatile unsigned int m_zero160[3];
	unsigned char m_radius[0x30];
	volatile unsigned int m_field19c;
	volatile unsigned int m_field1a0;
	volatile unsigned char m_flags[3];
};

__forceinline void writeSlowFloat(volatile float *address, float value)
{
	*address = value;
}

SlowDeathBehaviorModuleData::SlowDeathBehaviorModuleData()
{
	register SlowDeathBehaviorModuleData *self = this;
	rva00906340VecCtor(self->m_extraVectors, 0xc, 4, j_00029bfe, j_00017391);
	__asm {
		xor ecx, ecx
		mov [esi+128h], ecx
		mov [esi+12ch], ecx
		mov [esi+130h], ecx
		mov [esi+134h], ecx
		mov [esi+138h], ecx
		mov [esi+13ch], ecx
		mov [esi+140h], ecx
		mov [esi+144h], ecx
		mov [esi+148h], ecx
		mov [esi+14ch], ecx
		xor edx, edx
		mov [esi+150h], edx
		mov [esi+154h], edx
		mov [esi+158h], edx
	}
	self->m_zero160[0] = 0;
	self->m_zero160[1] = 0;
	self->m_zero160[2] = 0;
	new (self->m_radius) RadiusDecalTemplate;
	writeSlowFloat(&self->m_sinkRate, 0.0f);
	self->m_probabilityModifier = 10;
	writeSlowFloat(&self->m_modifierBonusPerOverkillPercent, 0.0f);
	self->m_sinkDelay = 0;
	self->m_sinkDelayVariance = 0;
	self->m_destructionDelay = 0;
	self->m_destructionDelayVariance = 0;
	writeSlowFloat(&self->m_destructionAltitude, -10.0f);
	self->m_field54 = 0;
	self->m_flags[0] = 0;
	writeSlowFloat(&self->m_flingForce, 0.0f);
	writeSlowFloat(&self->m_flingForceVariance, 0.0f);
	writeSlowFloat(&self->m_flingPitch, 0.0f);
	{
		TailGuard guard;
	}
	self->m_flags[1] = 0;
	self->m_flags[2] = 0;
	self->m_maskOfLoadedEffects = 0;
	self->m_field19c = 6;
	self->m_field1a0 = 0xfacade00;
}
