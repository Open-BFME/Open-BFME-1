// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME5: the out-of-line assignment used by Eva's message table.
// Retail 0x004263D0 is entered through ILT 0x00031DBD, which the matched
// Eva::init and Eva::reset bodies use for message-table assignment.  The body
// proves a 0x1C value stride and STLport vector assignment control flow.
// EvaInit.cpp already owns the TU-local EvaMessageVector ABI declaration; this
// file owns only the concrete STLport template instantiation that supplies the
// retail body.  The 28-byte element remains opaque because the retail bytes
// expose only its width and its out-of-line helper calls.

#include <vector>

struct EvaMessageInfo
{
	char m_unported[ 28 ];
	EvaMessageInfo();
	EvaMessageInfo( const EvaMessageInfo & );
	~EvaMessageInfo();
	EvaMessageInfo &operator=( const EvaMessageInfo & );
};

template class _STL::vector<EvaMessageInfo>;
