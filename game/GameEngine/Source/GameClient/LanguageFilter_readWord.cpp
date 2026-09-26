// cl: /O2 /MD
// BFME LanguageFilter::readWord with the retail File vtable layout.

typedef bool Bool;
typedef unsigned short UnsignedShort;

class File
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual int read(void *, unsigned int);
};

class LanguageFilter
{

protected:
	Bool readWord(File *file1, UnsignedShort *buf);
};

Bool LanguageFilter::readWord(File *file1, UnsignedShort *buf)
{
	int index = 0;
	Bool retval = 1;
	int val = 0;
	UnsignedShort c;

	val = file1->read(&c, sizeof(UnsignedShort));
	if ((val == -1) || (val == 0)) {
		buf[index] = 0;
		return 0;
	}
	buf[index] = c;

	while (buf[index] != ' ') {
		++index;
		val = file1->read(&c, sizeof(UnsignedShort));
		if ((val == -1) || (val == 0)) {
			c = (UnsignedShort)-1;
		}

		if ((c == (UnsignedShort)-1) || (c == ' ')) {
			buf[index] = 0;
			if (c == (UnsignedShort)-1) {
				retval = 0;
			}
			break;
		}
		buf[index] = c;
	}
	return retval;
}
