// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: Win32LocalFile scalar-deleting destructor at retail RVA
// 0x009D1960.  The matched constructor at 0x009D1930 and complete destructor
// at 0x009D1950 install vtable 0x01143C10, whose LocalFile/File method slots
// and Win32LocalFileSystem::openFile allocation establish the concrete type.

class Win32LocalFile
{
public:
	virtual ~Win32LocalFile();
};

void forceWin32LocalFileDeletingDestructor()
{
	Win32LocalFile value;
}
