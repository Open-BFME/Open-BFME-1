// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the nonvirtual save-header reader at retail RVA
// 0x009D89E0.  The caller at GameState::getSaveGameInfoFromFile constructs
// Gen009D8CA0 immediately before calling this method, proving the owner.  Its
// File argument is the BFME File family: read is virtual slot 3 (+0x0C).
//
// The method name is deliberately neutral.  The owner, boundary, ABI and
// behavior are proven by the constructor/caller pair and the retail body, but
// no surviving public declaration names this private helper.

typedef int Int;
typedef bool Bool;

class File
{
public:
	virtual ~File();
	virtual Bool open(const char *, Int);
	virtual void close();
	virtual Int read(void *, Int);
	virtual Int write(const void *, Int);
	virtual Int seek(Int, Int);
	virtual void nextLine(char *, Int);
	virtual Bool scanInt(Int &);
	virtual Bool scanReal(float &);
	virtual Bool scanString(void *);
	virtual Bool print(const char *, ...);
	virtual Int size();
	virtual Int position();
	virtual char *readEntireAndClose();
	virtual File *convertToRAMFile();
	virtual void lock();
	virtual void unlock();
};

class Gen009D8CA0
{
public:
	virtual void slot0();
	Bool readAt009D89E0(File *file, void *output);

private:
	int m_first;
	int m_third;
	int m_second;
	Bool m_flag;
	unsigned char m_pad[3];
	File *m_valueA;
	int m_valueB;
	int m_index;
};

Bool Gen009D8CA0::readAt009D89E0(File *file, void *output)
{
	if (m_valueA != 0)
		return false;

	int first;
	int second;
	int value;
	if (file->read(&first, 4) != 4)
		goto failure;
	if (file->read(&second, 4) != 4)
		goto failure;
	if (first != 0x45414c41)
		goto failure;
	if (second != 0x52545331)
	{
		if (second != 0x52545332)
			goto failure;
	}

	*(int *)output = 0;
	if (second != 0x52545331)
		file->read(output, 4);
	if (file->read(&value, 4) == 4)
	{
		m_valueA = file;
		m_flag = value != 0;
		m_valueB = 0;
		return true;
	}

failure:
	return false;
}
