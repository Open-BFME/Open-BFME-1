// cl: /DNDEBUG /MD /EHsc

// Slot 1 of the RawFileClass vtable, between the destructor at slot 0 and
// Set_Name at slot 2 -- which is exactly RAWFILE.H's declaration order for
// File_Name. The body is a four-byte getter returning the member at +0x14, and
// the reference implementation is `return(Filename);`. The same address also
// fills slot 1 of BufferedFileClass's vtable, which inherits it.
class RawFileClass
{
public:
	virtual ~RawFileClass();
	virtual const char *File_Name(void) const;

private:
	unsigned char m_head[0x10];
	const char *m_filename;
};

// ?File_Name@RawFileClass@@UBEPBDXZ
const char *RawFileClass::File_Name(void) const
{
	return m_filename;
}
