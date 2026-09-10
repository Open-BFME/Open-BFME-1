// cl: /DNDEBUG /MD /EHsc /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"
#include <vector>

class LargeGroupAudioMap;
class SoundKeyPair;

class SoundKeyPair
{
public:
	SoundKeyPair( LargeGroupAudioMap *owner );

private:
	char m_unmodelled[ 0x3C ];
};

// The comparison at RVA 0x00028B37 is the landed address-derived
// Rva003D3250::equals (Y1IntRangeEquals.cpp): reinterpreting the SoundKeyPair
// pointers reproduces retail's exact call, no invented member name needed.
class Rva003D3250
{
public:
	int *m_begin;
	int *m_end;

	bool equals( const Rva003D3250 *other ) const;
};

// upstream layout: LargeGroupAudioMapDestructor.cpp (BfmeBaseVUH vtable(0),
// m_owner(4), m_isOverride(8) + pad = size 0xc; +8 padding, +4 AsciiString =
// m_sound at 0x18, matching this function's `[instance + 0x18]` access.
class LargeGroupAudioMapBase
{
protected:
	char m_unmodelled[ 0x18 ];
};

class LargeGroupAudioMap : public LargeGroupAudioMapBase
{
public:
	static void __cdecl parseSound( INI *ini, void *instance, void *, const void * );

private:
	std::vector<SoundKeyPair *> m_sounds;
};

extern void __declspec( noreturn ) __stdcall _CxxThrowException(
	void *, void * ) throw();

// ?parseSound@LargeGroupAudioMap@@SAXPAVINI@@PAX1PBX@Z
void __cdecl LargeGroupAudioMap::parseSound(
	INI *ini, void *instance, void *, const void * )
{
	SoundKeyPair *sound;
	LargeGroupAudioMap *map = static_cast<LargeGroupAudioMap *>( instance );
	std::vector<SoundKeyPair *> &sounds = map->m_sounds;
	sound = new SoundKeyPair( map );
	sounds.push_back( sound );
	ini->initFromINI( sound, (const FieldParse *)0x010EE088 );

	std::vector<SoundKeyPair *>::iterator it = sounds.begin();
	std::vector<SoundKeyPair *>::iterator end = sounds.end();
	for ( ; it != end; ++it )
	{
		if ( sound == *it )
			continue;
		if ( ( (const Rva003D3250 *)sound )->equals( (const Rva003D3250 *)*it ) )
		{
			INIException error( 3, (const char *)0x010EE190 );
			_CxxThrowException( &error, (void *)0x011DFC30 );
		}
	}
}
