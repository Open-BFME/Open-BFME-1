class LocalFileSystem
{
public:
	LocalFileSystem();

	virtual void bfmeSlot00EBB();
	virtual void bfmeInitEBB();
	virtual void bfmeSlot02EBB();
	virtual void bfmeSlot03EBB();
	virtual char bfmeExistsEBB(const char *name);
};

class ArchiveFileSystem
{
public:
	ArchiveFileSystem();

	virtual void bfmeSlot00EBB();
	virtual void bfmeInitEBB();

	unsigned char m_bfmeBodyEBB[0x28];
};

extern LocalFileSystem *TheLocalFileSystem;
extern ArchiveFileSystem *TheArchiveFileSystem;
extern char g_bfmeShaderFlagEBB;

void bfmeInitFileSystemsEBB()
{
	TheLocalFileSystem = new LocalFileSystem();
	TheArchiveFileSystem = new ArchiveFileSystem();

	TheLocalFileSystem->bfmeInitEBB();
	TheArchiveFileSystem->bfmeInitEBB();

	if (!TheLocalFileSystem->bfmeExistsEBB("shaders.big"))
		g_bfmeShaderFlagEBB = 1;
}
