// ?d_003d0c40@@YAXXZ
// partial score=0.9 date=2026-09-06
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
	bool hasSameKeyList( const SoundKeyPair *other ) const;

private:
	char m_unmodelled[ 0x3C ];
};

#pragma comment(linker, "/alternatename:??0SoundKeyPair@@QAE@PAVLargeGroupAudioMap@@@Z=?j_00044463@@YAXXZ")
#pragma comment(linker, "/alternatename:?hasSameKeyList@SoundKeyPair@@QBE_NPBV1@@Z=?j_00028b37@@YAXXZ")

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

// ?parseSound@LargeGroupAudioMap@@SAXPAVINI@@PAX1PBX@Z
void __cdecl LargeGroupAudioMap::parseSound(
	INI *ini, void *instance, void *, const void * )
{
	SoundKeyPair *sound;
	volatile LargeGroupAudioMap *map = static_cast<LargeGroupAudioMap *>( instance );
	std::vector<SoundKeyPair *> &sounds =
		((LargeGroupAudioMap *)map)->m_sounds;
	sound = new SoundKeyPair( (LargeGroupAudioMap *)map );
	sounds.push_back( sound );
	ini->initFromINI( sound, (const FieldParse *)0x010EE088 );

	std::vector<SoundKeyPair *>::iterator it = sounds.begin();
	std::vector<SoundKeyPair *>::iterator end = sounds.end();
	for ( ; it != end; ++it )
	{
		if ( sound == *it )
			continue;
		if ( sound->hasSameKeyList( *it ) )
		{
			INIException error( 3, (const char *)0x010EE190 );
			extern void __declspec( noreturn ) __stdcall _CxxThrowException(
				void *, void * );
			_CxxThrowException( &error, (void *)0x011DFC30 );
		}
	}
}
