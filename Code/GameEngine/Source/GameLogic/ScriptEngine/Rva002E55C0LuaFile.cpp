// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc
// The Lua host at 0x002E55C0 reads and executes one script file.

typedef int Int;
typedef unsigned int SizeT;

struct lua_State;

extern "C" int lua_dobuffer(lua_State *state, const char *buffer, SizeT size,
	const char *name);
extern "C" void lua_settop(lua_State *state, int index);

extern void *operator new[](unsigned int size);
extern void operator delete[](void *memory);
extern const char g_bfmeEmptyAscii[];

class File
{
public:
	enum Access
	{
		READ = 1,
		BINARY = 0x40
	};

	virtual ~File();
	virtual bool open(const char *filename, Int access);
	virtual void close();
	virtual Int read(void *buffer, Int bytes);
	virtual Int write(const void *buffer, Int bytes);
	virtual Int seek(Int bytes, Int mode);
	virtual void nextLine(char *buffer, Int bufferSize);
	virtual bool scanInt(Int &value);
	virtual bool scanReal(float &value);
	virtual bool scanString(class AsciiString &value);
	virtual bool print(const char *format, ...);
	virtual Int size();
	virtual Int position();
	virtual char *readEntireAndClose();
	virtual File *convertToRAMFile();
	virtual void lock();
	virtual void unlock();
};

class FileSystem
{
public:
	File *openFile(const char *filename, Int access);
};

extern FileSystem *TheFileSystem;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *string);
	~BFMERetailAsciiString() { releaseBuffer(); }

	char *m_data;

private:
	void releaseBuffer();
};

class Rva002E55C0LuaHost
{
public:
	void loadFile(const char *filename);

private:
	char m_unknown[8];
	lua_State *m_state;
};

void Rva002E55C0LuaHost::loadFile(const char *filename)
{
	File *file = TheFileSystem->openFile(filename, File::READ | File::BINARY);
	if (file != 0)
	{
		Int size = file->size();
		char *buffer = (char *)operator new[](size + 10);
		file->read(buffer, size);
		file->close();

		{
			BFMERetailAsciiString name(filename);
			const char *scriptName = name.m_data != 0 ? name.m_data + 8 : g_bfmeEmptyAscii;
			lua_dobuffer(m_state, buffer, size, scriptName);
			lua_settop(m_state, 0);
		}

		operator delete[](buffer);
	}
}
