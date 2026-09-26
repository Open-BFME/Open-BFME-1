// cl: /DNDEBUG /MD /EHsc

// Slots 17 and 18 of the RawFileClass vtable, between Set_Date_Time at 16 and
// Bias at 19. RAWFILE.H declares Error before Get_File_Handle and leaves Bias
// non-virtual, whereas this build has Bias virtual at slot 19 and these two in
// the opposite order -- so position alone would not settle which is which.
//
// The bodies do. Get_File_Handle is declared inline in the header as
// `{ return Handle; }` and slot 17 is a four-byte getter returning the member at
// +0x10. Error takes three arguments and returns void, and slot 18 is a bare
// ret 0xc -- twelve bytes of arguments popped, no body at all, the release build
// having nothing to report.
class RawFileClass
{
public:
	virtual ~RawFileClass();
	virtual void *Get_File_Handle(void);
	virtual void Error(int error, int canretry, const char *filename);

private:
	unsigned char m_head[0x0C];
	void *m_handle;
};

// ?Get_File_Handle@RawFileClass@@UAEPAXXZ
void *RawFileClass::Get_File_Handle(void)
{
	return m_handle;
}

// ?Error@RawFileClass@@UAEXHHPBD@Z
void RawFileClass::Error(int, int, const char *)
{
}
