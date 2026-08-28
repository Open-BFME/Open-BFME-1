// cl: /DNDEBUG /MD /EHsc
// readable body of ?getCommandSetString@Object@@QBEABVAsciiString@@XZ: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// Object::getCommandSetString, retail 0x001C39A0. Three sources tried in order,
// each returned by reference.
//
// The two overrides at +0x32C and +0x328 are AsciiStrings, and "set" means a
// buffer with a non-zero length - the test is a word compare against the length
// in the string header at +0x04, not a null check on the buffer alone.
//
// Failing both, the answer comes from the template at +0x04, walked to its final
// override, at the template's own +0x2C. A null template is not guarded so much
// as returned early: retail materialises 0x2C as a constant, which is that
// member's address computed from a null base. Folding the null case into the
// walk lets the same `add eax,0x2C' serve both and loses those five bytes.

class AsciiStringHeader
{
public:
	int m_refCount;
	unsigned short m_length;				// +0x04
	unsigned short m_capacity;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiStringHeader *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const;

	unsigned char m_unmodelled_00[4];
	Overridable *m_nextOverride;			// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const AsciiString &getCommandSetString( void ) const;

private:
	unsigned char m_unmodelled_00[4];
	Overridable *m_template;				// +0x04
	unsigned char m_unmodelled_08[ 0x328 - 8 ];
	AsciiString m_commandSetFallback;		// +0x328
	AsciiString m_commandSetOverride;		// +0x32C
};

// ?getCommandSetString@Object@@QBEABVAsciiString@@XZ
const AsciiString &Object::getCommandSetString( void ) const
{
	if( m_commandSetOverride.m_data && m_commandSetOverride.m_data->m_length != 0 )
		return m_commandSetOverride;

	if( m_commandSetFallback.m_data && m_commandSetFallback.m_data->m_length != 0 )
		return m_commandSetFallback;

	const Overridable *tmpl = m_template;

	if( tmpl == 0 )
		return *(const AsciiString *)( (const char *)tmpl + 0x2C );

	if( tmpl->m_nextOverride )
		tmpl = tmpl->m_nextOverride->getFinalOverride();

	return *(const AsciiString *)( (const char *)tmpl + 0x2C );
}
