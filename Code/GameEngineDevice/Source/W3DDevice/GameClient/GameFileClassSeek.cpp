// cl: /DNDEBUG /MD /EHsc
// readable body of ?Seek@GameFileClass@@UAEHHH@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DFileSystem.cpp

class File
{
public:
	enum seekMode
	{
		START,
		CURRENT,
		END
	};

	virtual ~File();
	virtual int open(const char *filename, int access);
	virtual void close();
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);
	virtual int seek(int bytes, seekMode mode);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DFileSystem.h
class GameFileClass
{
public:
	virtual int Seek(int position, int direction);

private:
	File *m_file;
};

int GameFileClass::Seek(int position, int direction)
{
	File::seekMode mode = File::CURRENT;
	switch (direction) {
	default:
	case 1:
		mode = File::CURRENT;
		break;
	case 0:
		mode = File::START;
		break;
	case 2:
		mode = File::END;
		break;
	}
	if (m_file) {
		return m_file->seek(position, mode);
	}
	return -1;
}
