// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00133770Record
{
	unsigned int m_words[59];
};

extern "C" void Rva00133770CopyRecord(
	Rva00133770Record *destination, const Rva00133770Record *source )
{
	if ( destination != 0 ) {
		*destination = *source;
	}
}
