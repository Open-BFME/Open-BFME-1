// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00696370: open a file with access 0x141 and return success.
class File;
class FileSystem
{
public:
	File *openFile(const char *path, int access);
};
extern FileSystem *TheFileSystem;

int __stdcall rva00696370OpenFile(const char *path, File **out)
{
	File *file = TheFileSystem->openFile(path, 0x141);
	*out = file;
	return file != 0;
}
