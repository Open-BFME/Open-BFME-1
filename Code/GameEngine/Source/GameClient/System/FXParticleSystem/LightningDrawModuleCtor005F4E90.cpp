// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /ICode/GameEngine/Source/Common/System

#include "game_client_random_variable.h"

class Rva005F4E90RandomVariable
{
public:
	unsigned int distribution;
	float minimum;
	float maximum;
};

class T1A1_005DD290
{
public:
	T1A1_005DD290( void *first, void *second );
	virtual void primarySlot();
	virtual ~T1A1_005DD290();

private:
	unsigned int m_storage[ 4 ];
};

class ParticleModuleInterface005F2CA0
{
public:
	virtual void interfaceSlot();
};

class __declspec( novtable ) ParticleModule005F2CA0
	: public T1A1_005DD290,
	  public ParticleModuleInterface005F2CA0
{
public:
	ParticleModule005F2CA0( void *first, void *second );
	virtual void moduleSlot();
};

class Xfer;

namespace FXParticleSystem
{

class LightningDrawModuleInfoCleanupBase
{
public:
	LightningDrawModuleInfoCleanupBase() {}
	~LightningDrawModuleInfoCleanupBase();
};

class __declspec( novtable ) LightningDrawModuleInfo
	: public LightningDrawModuleInfoCleanupBase
{
public:
	LightningDrawModuleInfo();
	virtual ~LightningDrawModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer( Xfer &xfer );

	Rva005F4E90RandomVariable m_gcrv1;
	Rva005F4E90RandomVariable m_gcrv2;
	Rva005F4E90RandomVariable m_gcrv3;
	int m_field28;
	bool m_flag;
};

class ParticleSystem;

template <class T>
class TrackingPtr
{
};

class LightningDrawModuleTemplate
{
public:
	unsigned char m_categoryBase[ 0x0c ];
	Rva005F4E90RandomVariable m_gcrv1;
	Rva005F4E90RandomVariable m_gcrv2;
	Rva005F4E90RandomVariable m_gcrv3;
	int m_field30;
	bool m_flag34;
};

class __declspec( novtable ) Rva005F4E90LightningDrawModule
	: public ParticleModule005F2CA0,
	  public LightningDrawModuleInfo
{
public:
	Rva005F4E90LightningDrawModule(
		TrackingPtr<ParticleSystem> &system,
		const LightningDrawModuleTemplate *source );

private:
	unsigned char m_padding[ 0x870 ];
	int m_field8b8;
	float m_field8bc;
	int m_field8c0;
	int m_field8c4;
	int m_field8c8;
	float m_field8cc;
	int m_field8d0;
	int m_field8d4;
	float m_field8d8;
	int m_field8dc;
	int m_field8e0;
};

// ??0LightningDrawModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@PBVLightningDrawModuleTemplate@1@@Z
Rva005F4E90LightningDrawModule::Rva005F4E90LightningDrawModule(
	TrackingPtr<ParticleSystem> &system,
	const LightningDrawModuleTemplate *source )
	: ParticleModule005F2CA0( &system,
		const_cast<LightningDrawModuleTemplate *>( source ) ),
	  LightningDrawModuleInfo()
{
	unsigned char *destination = reinterpret_cast<unsigned char *>( this );

	*(volatile unsigned int *)destination = 0x01112fd0;
	*(volatile unsigned int *)( destination + 0x14 ) = 0x01112fcc;
	*(volatile unsigned int *)( destination + 0x18 ) = 0x01112ff4;

	m_gcrv1 = source->m_gcrv1;
	m_gcrv2 = source->m_gcrv2;
	m_gcrv3 = source->m_gcrv3;
	m_field28 = source->m_field30;
	*(volatile unsigned char *)( destination + 0x44 ) = source->m_flag34;

	*(volatile unsigned int *)( destination + 0x8b8 ) = 1;
	*(volatile unsigned int *)( destination + 0x8c0 ) = 0;
	unsigned int *field8c4 = reinterpret_cast<unsigned int *>( destination + 0x8c4 );
	*field8c4 = 0;
	*(volatile float *)( destination + 0x8bc ) = 1.0f;
	*(volatile unsigned int *)( destination + 0x8c8 ) = 0;
	*(volatile float *)( destination + 0x8cc ) = 1.0f;
	*(volatile unsigned int *)( destination + 0x8d0 ) = 0;
	*(volatile unsigned int *)( destination + 0x8d4 ) = 0;
	*(volatile float *)( destination + 0x8d8 ) = 1.0f;
	*(volatile unsigned int *)( destination + 0x8dc ) = 0;
	*(volatile unsigned int *)( destination + 0x8e0 ) = 0;
}

}
