// cl: /DNDEBUG /MD /EHsc
//
// Six more instances of the BitFlags token loop already landed at 0x001EB490
// (Code/GameEngine/Source/Common/BitFlagsParseFromINI.cpp).  All seven bodies
// normalise identically once relocation slots are blanked, and the only slot
// that differs is the per-instantiation routine each one hands its token to --
// 0x00049A2B for the landed one, and the six below.  Everything else, the
// token loop, the description building and the early exit, is the same code.
//
// The bit COUNT is not recoverable from these bytes -- the flag array is never
// touched here -- so each instantiation is named after its address rather than
// given an invented width.

typedef int Int;
typedef bool Bool;

extern "C" unsigned int __cdecl strlen( const char *text );
#pragma intrinsic(strlen)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void clear();
	void concat( const char *text, Int length );
	void concat( const char *text )
	{
		concat( text, text ? strlen( text ) : 0 );
	}

	Bool isNotEmpty() const
	{
		return m_data != 0 && m_data->length != 0;
	}

private:
	struct Data
	{
		Int referenceCount;
		unsigned short length;
		unsigned short capacity;
	};

	Data *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextTokenOrNull( const char *seps = 0 );	// retail 0x008509C0
};

class GenItem;

// ---------------------------------------------------------------------------
// 0x001292C0 -- token loop over the routine at ILT 0x0003D3B1.

class Open2Handler1292C0
{
public:
	Bool handle( GenItem *item, Bool *foundNormal, Bool *foundAddOrSub );
};

class Open2Flags1292C0
{
public:
	void parse( INI *ini, AsciiString *description );

private:
	unsigned int m_bits[ 1 ];
};

// @?parse@Open2Flags1292C0@@QAEXPAVINI@@PAVAsciiString@@@Z 0x001292C0
void Open2Flags1292C0::parse( INI *ini, AsciiString *description )
{
	if( description )
		description->clear();

	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	for( const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull() )
	{
		if( description )
		{
			if( description->isNotEmpty() )
				description->concat( " ", 1 );
			description->concat( token );
		}

		if( !( (Open2Handler1292C0 *)this )->handle( (GenItem *)token, &foundNormal, &foundAddOrSub ) )
			break;
	}
}

// ---------------------------------------------------------------------------
// 0x00142D20 -- token loop over the routine at ILT 0x0004A7AF.

class Open2Handler142D20
{
public:
	Bool handle( GenItem *item, Bool *foundNormal, Bool *foundAddOrSub );
};

class Open2Flags142D20
{
public:
	void parse( INI *ini, AsciiString *description );

private:
	unsigned int m_bits[ 1 ];
};

// @?parse@Open2Flags142D20@@QAEXPAVINI@@PAVAsciiString@@@Z 0x00142D20
void Open2Flags142D20::parse( INI *ini, AsciiString *description )
{
	if( description )
		description->clear();

	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	for( const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull() )
	{
		if( description )
		{
			if( description->isNotEmpty() )
				description->concat( " ", 1 );
			description->concat( token );
		}

		if( !( (Open2Handler142D20 *)this )->handle( (GenItem *)token, &foundNormal, &foundAddOrSub ) )
			break;
	}
}

// ---------------------------------------------------------------------------
// 0x00204A80 -- token loop over the routine at ILT 0x0003D68B.

class Open2Handler204A80
{
public:
	Bool handle( GenItem *item, Bool *foundNormal, Bool *foundAddOrSub );
};

class Open2Flags204A80
{
public:
	void parse( INI *ini, AsciiString *description );

private:
	unsigned int m_bits[ 1 ];
};

// @?parse@Open2Flags204A80@@QAEXPAVINI@@PAVAsciiString@@@Z 0x00204A80
void Open2Flags204A80::parse( INI *ini, AsciiString *description )
{
	if( description )
		description->clear();

	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	for( const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull() )
	{
		if( description )
		{
			if( description->isNotEmpty() )
				description->concat( " ", 1 );
			description->concat( token );
		}

		if( !( (Open2Handler204A80 *)this )->handle( (GenItem *)token, &foundNormal, &foundAddOrSub ) )
			break;
	}
}

// ---------------------------------------------------------------------------
// 0x0029CE10 -- token loop over the routine at ILT 0x00006F78.

class Open2Handler29CE10
{
public:
	Bool handle( GenItem *item, Bool *foundNormal, Bool *foundAddOrSub );
};

class Open2Flags29CE10
{
public:
	void parse( INI *ini, AsciiString *description );

private:
	unsigned int m_bits[ 1 ];
};

// @?parse@Open2Flags29CE10@@QAEXPAVINI@@PAVAsciiString@@@Z 0x0029CE10
void Open2Flags29CE10::parse( INI *ini, AsciiString *description )
{
	if( description )
		description->clear();

	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	for( const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull() )
	{
		if( description )
		{
			if( description->isNotEmpty() )
				description->concat( " ", 1 );
			description->concat( token );
		}

		if( !( (Open2Handler29CE10 *)this )->handle( (GenItem *)token, &foundNormal, &foundAddOrSub ) )
			break;
	}
}

// ---------------------------------------------------------------------------
// 0x00369790 -- token loop over the routine at ILT 0x0002E893.

class Open2Handler369790
{
public:
	Bool handle( GenItem *item, Bool *foundNormal, Bool *foundAddOrSub );
};

class Open2Flags369790
{
public:
	void parse( INI *ini, AsciiString *description );

private:
	unsigned int m_bits[ 1 ];
};

// @?parse@Open2Flags369790@@QAEXPAVINI@@PAVAsciiString@@@Z 0x00369790
void Open2Flags369790::parse( INI *ini, AsciiString *description )
{
	if( description )
		description->clear();

	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	for( const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull() )
	{
		if( description )
		{
			if( description->isNotEmpty() )
				description->concat( " ", 1 );
			description->concat( token );
		}

		if( !( (Open2Handler369790 *)this )->handle( (GenItem *)token, &foundNormal, &foundAddOrSub ) )
			break;
	}
}

// ---------------------------------------------------------------------------
// 0x0061CC40 -- token loop over the routine at ILT 0x000341FD.

class Open2Handler61CC40
{
public:
	Bool handle( GenItem *item, Bool *foundNormal, Bool *foundAddOrSub );
};

class Open2Flags61CC40
{
public:
	void parse( INI *ini, AsciiString *description );

private:
	unsigned int m_bits[ 1 ];
};

// @?parse@Open2Flags61CC40@@QAEXPAVINI@@PAVAsciiString@@@Z 0x0061CC40
void Open2Flags61CC40::parse( INI *ini, AsciiString *description )
{
	if( description )
		description->clear();

	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	for( const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull() )
	{
		if( description )
		{
			if( description->isNotEmpty() )
				description->concat( " ", 1 );
			description->concat( token );
		}

		if( !( (Open2Handler61CC40 *)this )->handle( (GenItem *)token, &foundNormal, &foundAddOrSub ) )
			break;
	}
}
