// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the five MultiPlay*Mult INI parse callbacks and the five setters
// they call.  Retail, per callback:
//
//     token = ini->getNextTokenOrNull( ini->getSepsColon() )   ; [ini+0x41C]
//     while token:
//         v = ini->getNextToken( ini->getSepsColon() )
//         if v:
//             value = INI::scanReal( v )
//             eight `push "MPn" / push token / call [__imp__strcmpi]` tests,
//             each storing value through the setter
//             token = ini->getNextTokenOrNull( ini->getSepsColon() )
//
// THE KEYWORDS AND THE OFFSET COME FROM THE SAME TABLE ROW.  All five appear in
// the GlobalData FieldParse table -- the block that also carries TutorialMap,
// ShrubBrightnessScale and the GoodCommandPointsMP* rows -- at 0x00C78A08..48,
// every one with offset 0xEE0.  So `store` is one sub-object of GlobalData and
// the five arrays are laid out inside it at 0x00, 0x80, 0x100, 0x180 and 0x200,
// which is exactly the five bases the bodies write.
//
// THE SETTERS ARE REAL FUNCTIONS AND THE BODIES PROVE IT TWICE.  Each is
// `index = slot - 1; if ( index >= 0 && index < 32 ) m_array[index] = value;`
// -- a signed test, a 32-entry bound, `ret 8` -- and each is reached by the MP7
// and MP8 cases of its own callback.  MP1 through MP6 are inlined and folded to
// a direct store, MP7 and MP8 are calls: MSVC's inline budget for one function
// body runs out after six expansions of the same callee.  Writing all eight as
// calls reproduces that split exactly; writing the store by hand does not
// produce the out-of-line copy at all.
//
// THE NULL VALUE-TOKEN PATH DOES NOT ADVANCE.  `je` on a null getNextToken
// result jumps PAST the re-read of `token`, straight to the while test, with
// `token` unchanged -- so the re-read sits INSIDE the `if ( v )` block in the
// source, not after it.  Spelling it as `if (!v) break;` or putting the re-read
// after the block moves the jump.
//
// stricmp IS AN IMPORT, and it is loaded once into edi and called eight times,
// which is what `__declspec(dllimport)` gives.  The IAT slot 0x0135933C is
// `_strcmpi` -- the C name, so the declaration has to be extern "C" or the
// relocation names a C++ symbol that does not exist in retail.
//
// The struct name and the setter names are this file's; the keywords, the
// offsets, the bound and the array bases are the binary's.

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl _strcmpi( const char *, const char * );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps );
	const char *getNextTokenOrNull( const char *seps );
	const char *getSepsColon( void ) const { return m_sepsColon; }
	static Real scanReal( const char *token );

	char m_unreconstructed_000[ 0x41c ];
	const char *m_sepsColon;
};

class MultiPlayMults
{
public:
	void setMoneyMult( Int slot, Real value )
	{
		Int index = slot - 1;
		if ( index >= 0 && index < 32 )
			m_money[ index ] = value;
	}

	void setUnitXPMult( Int slot, Real value )
	{
		Int index = slot - 1;
		if ( index >= 0 && index < 32 )
			m_unitXP[ index ] = value;
	}

	void setBuildingXPMult( Int slot, Real value )
	{
		Int index = slot - 1;
		if ( index >= 0 && index < 32 )
			m_buildingXP[ index ] = value;
	}

	void setUnitSpeedMult( Int slot, Real value )
	{
		Int index = slot - 1;
		if ( index >= 0 && index < 32 )
			m_unitSpeed[ index ] = value;
	}

	void setBuildingSpeedMult( Int slot, Real value )
	{
		Int index = slot - 1;
		if ( index >= 0 && index < 32 )
			m_buildingSpeed[ index ] = value;
	}

	// 0x00, 0x80, 0x100, 0x180, 0x200 inside GlobalData+0xEE0
	Real m_money[ 32 ];
	Real m_unitXP[ 32 ];
	Real m_buildingXP[ 32 ];
	Real m_unitSpeed[ 32 ];
	Real m_buildingSpeed[ 32 ];
};

// GlobalData keyword "MultiPlayMoneyMult", offset 0xEE0
void parseMultiPlayMoneyMult( INI *ini, void *, void *store, const void * )
{
	MultiPlayMults *mults = (MultiPlayMults *)store;
	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	while ( token )
	{
		const char *valueToken = ini->getNextToken( ini->getSepsColon() );
		if ( valueToken )
		{
			Real value = INI::scanReal( valueToken );
			if ( !_strcmpi( token, "MP1" ) )
				mults->setMoneyMult( 1, value );
			else if ( !_strcmpi( token, "MP2" ) )
				mults->setMoneyMult( 2, value );
			else if ( !_strcmpi( token, "MP3" ) )
				mults->setMoneyMult( 3, value );
			else if ( !_strcmpi( token, "MP4" ) )
				mults->setMoneyMult( 4, value );
			else if ( !_strcmpi( token, "MP5" ) )
				mults->setMoneyMult( 5, value );
			else if ( !_strcmpi( token, "MP6" ) )
				mults->setMoneyMult( 6, value );
			else if ( !_strcmpi( token, "MP7" ) )
				mults->setMoneyMult( 7, value );
			else if ( !_strcmpi( token, "MP8" ) )
				mults->setMoneyMult( 8, value );

			token = ini->getNextTokenOrNull( ini->getSepsColon() );
		}
	}
}

// GlobalData keyword "MultiPlayUnitXPMult", offset 0xEE0
void parseMultiPlayUnitXPMult( INI *ini, void *, void *store, const void * )
{
	MultiPlayMults *mults = (MultiPlayMults *)store;
	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	while ( token )
	{
		const char *valueToken = ini->getNextToken( ini->getSepsColon() );
		if ( valueToken )
		{
			Real value = INI::scanReal( valueToken );
			if ( !_strcmpi( token, "MP1" ) )
				mults->setUnitXPMult( 1, value );
			else if ( !_strcmpi( token, "MP2" ) )
				mults->setUnitXPMult( 2, value );
			else if ( !_strcmpi( token, "MP3" ) )
				mults->setUnitXPMult( 3, value );
			else if ( !_strcmpi( token, "MP4" ) )
				mults->setUnitXPMult( 4, value );
			else if ( !_strcmpi( token, "MP5" ) )
				mults->setUnitXPMult( 5, value );
			else if ( !_strcmpi( token, "MP6" ) )
				mults->setUnitXPMult( 6, value );
			else if ( !_strcmpi( token, "MP7" ) )
				mults->setUnitXPMult( 7, value );
			else if ( !_strcmpi( token, "MP8" ) )
				mults->setUnitXPMult( 8, value );

			token = ini->getNextTokenOrNull( ini->getSepsColon() );
		}
	}
}

// GlobalData keyword "MultiPlayBuildingXPMult", offset 0xEE0
void parseMultiPlayBuildingXPMult( INI *ini, void *, void *store, const void * )
{
	MultiPlayMults *mults = (MultiPlayMults *)store;
	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	while ( token )
	{
		const char *valueToken = ini->getNextToken( ini->getSepsColon() );
		if ( valueToken )
		{
			Real value = INI::scanReal( valueToken );
			if ( !_strcmpi( token, "MP1" ) )
				mults->setBuildingXPMult( 1, value );
			else if ( !_strcmpi( token, "MP2" ) )
				mults->setBuildingXPMult( 2, value );
			else if ( !_strcmpi( token, "MP3" ) )
				mults->setBuildingXPMult( 3, value );
			else if ( !_strcmpi( token, "MP4" ) )
				mults->setBuildingXPMult( 4, value );
			else if ( !_strcmpi( token, "MP5" ) )
				mults->setBuildingXPMult( 5, value );
			else if ( !_strcmpi( token, "MP6" ) )
				mults->setBuildingXPMult( 6, value );
			else if ( !_strcmpi( token, "MP7" ) )
				mults->setBuildingXPMult( 7, value );
			else if ( !_strcmpi( token, "MP8" ) )
				mults->setBuildingXPMult( 8, value );

			token = ini->getNextTokenOrNull( ini->getSepsColon() );
		}
	}
}

// GlobalData keyword "MultiPlayUnitSpeedMult", offset 0xEE0
void parseMultiPlayUnitSpeedMult( INI *ini, void *, void *store, const void * )
{
	MultiPlayMults *mults = (MultiPlayMults *)store;
	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	while ( token )
	{
		const char *valueToken = ini->getNextToken( ini->getSepsColon() );
		if ( valueToken )
		{
			Real value = INI::scanReal( valueToken );
			if ( !_strcmpi( token, "MP1" ) )
				mults->setUnitSpeedMult( 1, value );
			else if ( !_strcmpi( token, "MP2" ) )
				mults->setUnitSpeedMult( 2, value );
			else if ( !_strcmpi( token, "MP3" ) )
				mults->setUnitSpeedMult( 3, value );
			else if ( !_strcmpi( token, "MP4" ) )
				mults->setUnitSpeedMult( 4, value );
			else if ( !_strcmpi( token, "MP5" ) )
				mults->setUnitSpeedMult( 5, value );
			else if ( !_strcmpi( token, "MP6" ) )
				mults->setUnitSpeedMult( 6, value );
			else if ( !_strcmpi( token, "MP7" ) )
				mults->setUnitSpeedMult( 7, value );
			else if ( !_strcmpi( token, "MP8" ) )
				mults->setUnitSpeedMult( 8, value );

			token = ini->getNextTokenOrNull( ini->getSepsColon() );
		}
	}
}

// GlobalData keyword "MultiPlayBuildingSpeedMult", offset 0xEE0
void parseMultiPlayBuildingSpeedMult( INI *ini, void *, void *store, const void * )
{
	MultiPlayMults *mults = (MultiPlayMults *)store;
	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	while ( token )
	{
		const char *valueToken = ini->getNextToken( ini->getSepsColon() );
		if ( valueToken )
		{
			Real value = INI::scanReal( valueToken );
			if ( !_strcmpi( token, "MP1" ) )
				mults->setBuildingSpeedMult( 1, value );
			else if ( !_strcmpi( token, "MP2" ) )
				mults->setBuildingSpeedMult( 2, value );
			else if ( !_strcmpi( token, "MP3" ) )
				mults->setBuildingSpeedMult( 3, value );
			else if ( !_strcmpi( token, "MP4" ) )
				mults->setBuildingSpeedMult( 4, value );
			else if ( !_strcmpi( token, "MP5" ) )
				mults->setBuildingSpeedMult( 5, value );
			else if ( !_strcmpi( token, "MP6" ) )
				mults->setBuildingSpeedMult( 6, value );
			else if ( !_strcmpi( token, "MP7" ) )
				mults->setBuildingSpeedMult( 7, value );
			else if ( !_strcmpi( token, "MP8" ) )
				mults->setBuildingSpeedMult( 8, value );

			token = ini->getNextTokenOrNull( ini->getSepsColon() );
		}
	}
}

