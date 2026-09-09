// cl: /DNDEBUG /MD /EHsc
// Real Script::duplicate body at RVA 0x0035B680.
//
// Identity is established independently by the named Script::duplicate ILT at
// 0x0004589F, which is called by TeamPrototype::getGenericScript at
// 0x000ED6F0.  Retail allocates the 0x40-byte Script and invokes the matched
// Script copy constructor at 0x0035B550 through its ILT.

class Script
{
public:
	Script( const Script &other );
	virtual ~Script();
	Script *duplicate() const;

private:
	int m_fields[ 15 ];
};

// ?duplicate@Script@@QBEPAV1@XZ
Script *Script::duplicate() const
{
	return new Script( *this );
}
