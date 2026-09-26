// cl: /DNDEBUG /MD /EHsc
// Open-BFME: the bone-name-key INI field parser, retail 0x00773270, 180 bytes.
//
// The W3DModelDraw FieldParse table at 0x01124718 pairs four strings with this
// one body: Turret at row 0x011248C8, TurretPitch at 0x011248E8, AltTurret at
// 0x01124908 and AltTurretPitch at 0x01124928. Zero Hour's W3DModelDraw.cpp
// registers its own Turret, TurretPitch, AltTurret and AltTurretPitch rows
// against a static called parseBoneNameKey, and that function reads the same
// four steps in the same order, so the name carries over.
//
// The body lowercases the token, hands it to
// ModelConditionInfo::addPublicBone at 0x00772BF0 when the instance pointer is
// not null, and stores either NAMEKEY_INVALID or the key from
// NameKeyGenerator::nameToKey at 0x0008FFC0. The string header is the
// four-short one, which is why the emptiness test reads a word at m_data + 4.
struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_length;
	unsigned short m_pad;
	char m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	BfmeAsciiStringData *m_data;

public:
	// Retail spells both of these public: the calls at 0x00887DA0 and
	// 0x008881A0 carry the QAE and QBE decorations.
	void toLower();
	bool isNone() const;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void toLower( void ) { StringBase<char>::toLower(); }
	bool isNone( void ) const { return StringBase<char>::isNone(); }
	bool isEmpty( void ) const { return m_data == 0 || m_data->m_length == 0; }
	const char *str( void ) const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class ModelConditionInfo
{
public:
	void addPublicBone( const AsciiString &boneName ) const;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

// ?parseBoneNameKey@@YAXPAVINI@@PAX1PBX@Z
void parseBoneNameKey( INI *ini, void *instance, void *store, const void *userData )
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;
	NameKeyType *key = (NameKeyType *)store;

	AsciiString tmp = ini->getNextToken();
	tmp.toLower();

	if( self )
		self->addPublicBone( tmp );

	if( tmp.isEmpty() || tmp.isNone() )
		*key = NAMEKEY_INVALID;
	else
		*key = TheNameKeyGenerator->nameToKey( tmp.str() );
}
