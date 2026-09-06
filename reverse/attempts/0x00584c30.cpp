// ?parseUnitPrereq@Rva00584C30@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.25 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME7: INI field parser at 0x00584C30 (192 B): zero-constructs a
// twelve-byte ProductionPrerequisite::PrereqUnitRec (unit/flags/name -- the
// generic trivial-member-ctor pin ??0HRBMD_Buffer@@QAE@XZ at 0x0003747A
// used here as one more alias of that shared ICF-folded zero-init body),
// runs ini->initFromINI() against the field table at VA 0x110B918, and
// pushes the finished record onto the instance's vector<PrereqUnitRec> --
// the exact _M_insert_overflow already matched at 0x0040F277. The nested
// struct name is redeclared locally (the real one is private in
// reference/CnC_Generals_Zero_Hour's ProductionPrerequisite.h) to link
// against that mangled symbol. BFME parses each unit prerequisite as its
// own INI sub-block, unlike Zero Hour's addUnitPrereq(AsciiString, Bool);
// not yet byte-verified.

inline void *operator new( unsigned int, void *p ) { return p; }

class AsciiString
{
public:
	AsciiString();
	~AsciiString();
};

class ThingTemplate;
struct FieldParse;

class INI
{
public:
	void initFromINI( void *instance, const FieldParse *table );
};

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		const ThingTemplate *unit;
		int flags;
		AsciiString name;
	};
};

class HRBMD_Buffer
{
public:
	HRBMD_Buffer();
};

extern const FieldParse Rva00584C30FieldParseTable[];

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type>
void __cdecl _Construct(Type *destination, const Type &value);

template <class Type, class Allocator>
class vector
{
public:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;

	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );
};
}

class Rva00584C30Store
{
public:
	char m_bfmeHead[ 4 ];
	_STL::vector<ProductionPrerequisite::PrereqUnitRec, _STL::allocator<ProductionPrerequisite::PrereqUnitRec> > m_prereqUnits;
};

class Rva00584C30
{
public:
	static void parseUnitPrereq( INI *ini, void *instance, void *, const void * );
};

// ?parseUnitPrereq@Rva00584C30@@SAXPAVINI@@PAX1PBX@Z
void Rva00584C30::parseUnitPrereq( INI *ini, void *instance, void *, const void * )
{
	ProductionPrerequisite::PrereqUnitRec entry;
	::new ( &entry ) HRBMD_Buffer();

	ini->initFromINI( &entry, Rva00584C30FieldParseTable );

	Rva00584C30Store *self = (Rva00584C30Store *)instance;
	_STL::vector<ProductionPrerequisite::PrereqUnitRec, _STL::allocator<ProductionPrerequisite::PrereqUnitRec> > &items = self->m_prereqUnits;

	if( items._M_finish != items._M_end_of_storage )
	{
		_STL::_Construct( items._M_finish, entry );
		++items._M_finish;
	}
	else
	{
		items._M_insert_overflow( items._M_finish, entry,
			_STL::__false_type(), 1, true );
	}
}
