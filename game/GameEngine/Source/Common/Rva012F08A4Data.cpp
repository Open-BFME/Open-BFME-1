// cl: /DNDEBUG /MD /EHsc
// Address-derived string global already spelled by Rva00062330CommandLine.cpp
// and recorded in dir32_addresses.csv. Retail VA 0x012F08A4 lies in the
// zero-filled tail of .data. The only reference to it in retail .text is the
// command-line callback 0x00062330, which calls StringBase<char>::set on it.
// No dynamic initializer or atexit cleanup names it, so this TU defines the
// four-byte string handle with no constructor or destructor (as
// Rva012F08A8Data.cpp does for its neighbour). No semantic name is proven.
template <class T> class StringBase
{
public:
	void *m_data;
};

StringBase<char> g_012F08A4;
