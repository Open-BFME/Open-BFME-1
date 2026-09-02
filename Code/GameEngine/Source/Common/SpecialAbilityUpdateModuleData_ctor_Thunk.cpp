// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of the SpecialAbilityUpdateModuleData
// constructor. Retail keeps the four AudioEventRTS members at +0x08, +0x78,
// +0xE8 and +0x158; the remaining module-data fields are represented by their
// recovered ABI-sized tail so this TU does not change shared headers.

__forceinline unsigned int specialAbilityHugeDistanceBits()
{
	return 0x4b189680;
}

__forceinline void specialAbilityStoreZero( volatile unsigned int *address )
{
	*address = 0;
}

class AudioEventRTS
{
public:
	AudioEventRTS( void *allocator, int zero );
	virtual ~AudioEventRTS();

private:
	unsigned char m_data[0x6c];
};

class __declspec(novtable) SpecialAbilityUpdateModuleDataBase
{
public:
	SpecialAbilityUpdateModuleDataBase()
	{
	}
	virtual void specialAbilityUpdateModuleDataBaseAnchor();
	virtual ~SpecialAbilityUpdateModuleDataBase();

private:
	unsigned int m_word04;
};

class SpecialAbilityUpdateModuleData
	: public SpecialAbilityUpdateModuleDataBase
{
public:
	SpecialAbilityUpdateModuleData();
	virtual ~SpecialAbilityUpdateModuleData();

private:
	AudioEventRTS m_packSound;
	AudioEventRTS m_unpackSound;
	AudioEventRTS m_prepSoundLoop;
	AudioEventRTS m_triggerSound;
	unsigned char m_tail[0x8c];
};

// ??0SpecialAbilityUpdateModuleData@@QAE@XZ
SpecialAbilityUpdateModuleData::SpecialAbilityUpdateModuleData()
	: m_packSound( (void *)0x01336e50, 0 ),
	  m_unpackSound( (void *)0x01336e50, 0 ),
	  m_prepSoundLoop( (void *)0x01336e50, 0 ),
	  m_triggerSound( (void *)0x01336e50, 0 )
{
	specialAbilityStoreZero( reinterpret_cast<volatile unsigned int *>( (unsigned char *)this + 0x1d4 ) );
	specialAbilityStoreZero( reinterpret_cast<volatile unsigned int *>( (unsigned char *)this + 0x1e0 ) );
	specialAbilityStoreZero( reinterpret_cast<volatile unsigned int *>( (unsigned char *)this + 0x1e4 ) );
	specialAbilityStoreZero( reinterpret_cast<volatile unsigned int *>( (unsigned char *)this + 0x1e8 ) );
	specialAbilityStoreZero( reinterpret_cast<volatile unsigned int *>( (unsigned char *)this + 0x250 ) );
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x1ec ) = specialAbilityHugeDistanceBits();
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x1f0 ) = specialAbilityHugeDistanceBits();
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x218 ) = 1;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x1fc ) = 1;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x204 ) = 0xffffffff;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x1c8 ) = 0xffffffff;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x1d8 ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x20c ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x210 ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x21c ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x220 ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x1f4 ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x214 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x241 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x242 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x243 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x240 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x244 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x245 ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x1dc ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x1f8 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x247 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x246 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x248 ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x200 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x249 ) = 1;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x224 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x24a ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x208 ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x230 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x24b ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x1cc ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x1d0 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x24c ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x234 ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x24d ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x238 ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x23c ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x228 ) = 0;
	*reinterpret_cast<unsigned int volatile *>( (unsigned char *)this + 0x22c ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x24e ) = 0;
	*reinterpret_cast<unsigned char volatile *>( (unsigned char *)this + 0x24f ) = 0;
}
