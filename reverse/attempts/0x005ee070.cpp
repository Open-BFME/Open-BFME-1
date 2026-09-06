// ?Rva005EE070WriteIndentedLine@@YAXPBDPAVFile@@PAI@Z
// partial score=0.6 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME7: the FX particle INI writer's line emitter at 0x005EE070
// (279 B): an ostringstream on the stack receives one space per indent level
// then the text and a newline; the string is written to the file through its
// fourth virtual slot (data size); the indent grows by two.  STLport
// exceptions off: the string result's inline destructor and the stream
// destructor chain come from the vendor headers.  Address-derived names.

#include <sstream>

typedef int Int;

class File
{
public:
	virtual void slot0( void );
	virtual void slot1( void );
	virtual void slot2( void );
	virtual void slot3( void );
	virtual Int write( const void *data, Int size );
};

// ?Rva005EE070WriteIndentedLine@@YAXPBDPAVFile@@PAI@Z
void Rva005EE070WriteIndentedLine( const char *text, File *file, unsigned int *indent )
{
	_STL::ostringstream os;
	for( unsigned int i = *indent; i > 0; --i )
		os << ' ';
	os << text << '\n';
	{
		_STL::string line = os.str();
		file->write( line.data(), line.size() );
	}
	*indent += 2;
}
