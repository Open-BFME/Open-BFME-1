// cl: /DNDEBUG /MD /EHsc
// Address-derived string global already spelled by Rva000623F0CommandLine.cpp
// and recorded in dir32_addresses.csv. Retail VA 0x012F08A8 lies in the
// zero-filled tail of .data. The only reference to it in retail .text is the
// command-line callback 0x000623F0, which calls StringBase<char>::set on it.
// No dynamic initializer or atexit cleanup names it, so this TU defines the
// four-byte string handle with no constructor or destructor. No semantic
// name is proven.
template <class T> class StringBase
{
public:
	void *m_data;
};

StringBase<char> g_012F08A8;
