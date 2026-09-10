// Open-BFME: the W3D function-lexicon constructor at retail 0x006C05D0.
// The reference class derives directly from FunctionLexicon and adds no
// members; its empty constructor therefore only calls the base constructor
// and installs the W3D vftable.

// Keep this ABI view TU-local.  The W3D header is not on the BFME build
// profile's include path. This partial polymorphic view supplies the base
// constructor and the named W3D vtable needed by this constructor; it does
// not describe the complete virtual interface.
class FunctionLexicon
{
public:

	FunctionLexicon( void );
	virtual ~FunctionLexicon( void );
	virtual void init( void );
	virtual void postProcessLoad( void );
	virtual void reset( void );
	virtual void update( void );
	virtual void draw( void );
};

class W3DFunctionLexicon : public FunctionLexicon
{
public:

	W3DFunctionLexicon( void );
	virtual ~W3DFunctionLexicon( void );
	virtual void init( void );
	virtual void reset( void );
	virtual void update( void );
};

W3DFunctionLexicon::W3DFunctionLexicon( void )
{
}
