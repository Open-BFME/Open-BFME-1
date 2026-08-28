// cl: /DNDEBUG /MD /EHs-c-

// FILE: ShdDefFactoryClassDelete.cpp /////////////////////////////////////////
//
// ShdDefFactoryClass' scalar deleting destructor, retail 0x009EB910.
//
// The reference wwshade/shddeffactory.h gives this class NextFactory and
// PrevFactory and a destructor that unregisters itself from
// ShdDefManagerClass.  Retail's destructor does something else entirely: it
// stores the vtable pointer and then array-deletes a member at +0xc.  The
// callee is 0x00881EF0, which the ledger names ??_V@YAXPAX@Z -- operator
// delete[], not operator delete -- and there is no element loop ahead of it, so
// the array is of a type with no destructor.  The this-delete that follows,
// behind the usual flags & 1 test, goes to 0x00881EB0, the scalar
// ??3@YAXPAX@Z.
//
// What sits at +0x4 and +0x8 this body does not say; only that the owned array
// is the third pointer.  Spelled here rather than in shddeffactory.h so the
// rest of wwshade is untouched.
//
///////////////////////////////////////////////////////////////////////////////

// Declared so MSVC lowers the array delete to ??_V@YAXPAX@Z instead of folding
// it to the scalar form.
void operator delete[]( void *block );

class ShdDefClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/wwshade/shddeffactory.h
class ShdDefFactoryClass
{
public:

	virtual ~ShdDefFactoryClass( void );

	virtual ShdDefClass *Create( void ) const = 0;
	virtual const char *Get_Name( void ) const = 0;
	virtual unsigned int Get_Class_ID( void ) const = 0;

protected:

	// vptr @0x0
	ShdDefFactoryClass *NextFactory;				// @0x4
	ShdDefFactoryClass *PrevFactory;				// @0x8
	char *m_bfmeOwnedArray;									// @0xc

};

// The destructor MSVC inlines into the deleting one above is also emitted as
// its own COMDAT. Not claimed here: no address is proved for it.
// ??1ShdDefFactoryClass@@UAE@XZ present-unmatched
ShdDefFactoryClass::~ShdDefFactoryClass( void )
{
	delete [] m_bfmeOwnedArray;
}
