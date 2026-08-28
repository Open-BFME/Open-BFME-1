// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?findUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@ABVAsciiString@@@Z: Code/GameEngine/Source/Common/System/Upgrade.cpp

// UpgradeCenter::findUpgrade, retail 0x0010B0E0. A name-to-key call and a
// linked-list walk.
//
// The AsciiString argument goes through str() inlined - `m_data ? m_data+8 : ""'
// - into the name-to-key call on the generator at 0x012ED600. That generator is
// still only known by its address; this file reaches it through the same shim
// class parseInputCallback_Thunk.cpp already uses, so the one global keeps one
// decorated name.
//
// The list head is at +0x08 of the centre and each template carries its key at
// +0x0C and its next at +0x108. No match walks off the end and returns null.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	const char *str( void ) const
	{
		return m_data ? (const char *)( (unsigned char *)m_data + 8 ) : "";
	}

	void *m_data;
};

class NameKeyGeneratorShim
{
public:
	/// address-derived name -- do not treat as an identity.
	Int unidentified_0003ADD7( const char *name );		///< ILT thunk at 0x0003ADD7
};

extern NameKeyGeneratorShim *TheNameKeyGeneratorShim;	///< retail [0x012ED600]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	unsigned char m_unmodelled_00[ 0x0C ];
	Int m_nameKey;							// +0x0C
	unsigned char m_unmodelled_10[ 0x108 - 0x10 ];
	UpgradeTemplate *m_next;				// +0x108
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade( const AsciiString &name ) const;

private:
	unsigned char m_unmodelled_00[8];
	UpgradeTemplate *m_upgradeList;			// +0x08
};

// ?findUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@ABVAsciiString@@@Z
const UpgradeTemplate *UpgradeCenter::findUpgrade( const AsciiString &name ) const
{
	Int key = TheNameKeyGeneratorShim->unidentified_0003ADD7( name.str() );

	for( UpgradeTemplate *upgrade = m_upgradeList; upgrade; upgrade = upgrade->m_next )
		if( upgrade->m_nameKey == key )
			return upgrade;

	return 0;
}
