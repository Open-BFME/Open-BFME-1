// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME W3D file open helper -- retail 0x006F6BA0, size 204.
//
// The callers pass the filename first, followed by two 32-bit words which the
// wide FileSystem::openFile form receives as its offset and size arguments.
// The parameter types below preserve the established exported ABI used by the
// existing loader objects; the names and casts describe the actual roles.

class File;

class GameFileClass
{
public:
	GameFileClass( char const *filename );
	virtual ~GameFileClass();

	void   *m_theFile;
	char    m_fileExists;
	char    m_filePath[260];
	char    m_filename[260];
};

class FileSystem
{
public:
	File *openFile( const char *filename, int access, int offset, int size );
};

extern int *g_012F8228;
extern FileSystem *TheFileSystem;

// ?Open_W3D_File@@YAPAXPAX0PBD@Z
void *Open_W3D_File( void *filename_arg, void *offset_arg, const char *size_arg )
{
	if ( !g_012F8228 || !TheFileSystem )
		return 0;

	GameFileClass file( (const char *)filename_arg );

	if ( !file.m_fileExists )
		return 0;

	File *result = TheFileSystem->openFile(
		file.m_filePath, 0x41, (int)offset_arg, (int)size_arg );
	return (void *)result;
}
