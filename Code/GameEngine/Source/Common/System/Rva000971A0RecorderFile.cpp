// cl: /O2
//
// Retail 0x000971A0 returns the pointer stored at this-relative offset 0x0C.
// The nearby recorder methods support a file-pointer interpretation, but no
// caller proves the accessor's semantic name, so the owner keeps the RVA.

class Rva000971A0Recorder
{
	char m_lead[0x0C];
	void *m_file;

public:
	void *getFile() const;
};

void *Rva000971A0Recorder::getFile() const
{
	return m_file;
}
