// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The t-grid record at 0x00776240 is an anonymous 0xbc-byte value type.  Its
// assignment is used by vector insert at 0x0077CC60.  The surrounding fields
// are the original string, vector, tree, and array members; the helper calls
// are the already-ledgered incremental-link thunks for those member types.

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	char *m_data;
};

struct Raw10
{
	unsigned int words[10];
};

struct Vec12
{
	void *start;
	void *finish;
	void *endOfStorage;
};

struct List4
{
	void *head;
};

class BfmeCopyReceiver
{
};

union BfmeCopyCall
{
	void (*freeFunction)();
	void (BfmeCopyReceiver::*memberFunction)(const void *);
};

#define BFME_COPY_THUNK(thunk, target, source) do { \
	BfmeCopyCall _call; \
	_call.freeFunction = (thunk); \
	(((BfmeCopyReceiver *)(target))->*_call.memberFunction)((source)); \
} while (0)

extern void j_00030d5a();
extern void j_0000583f();
extern void j_0002c719();
extern void j_00010feb();
extern void j_000063d4();
extern void j_0001c288();

struct Gen_t_00776240_p128pod : public AsciiString
{
	Raw10 raw;
	Vec12 vector2c;
	unsigned int dword38;
	unsigned int dword3c;
	unsigned char byte40;
	unsigned int dword44;
	AsciiString string48;
	unsigned int dword4c;
	List4 vector50;
	Vec12 vector54;
	Vec12 vector60;
	unsigned char byte6c;
	Vec12 vector70;
	Vec12 vector7c[4];
	unsigned char byteac;

	Gen_t_00776240_p128pod &operator=(
		const Gen_t_00776240_p128pod &other);
};

Gen_t_00776240_p128pod &Gen_t_00776240_p128pod::operator=(
	const Gen_t_00776240_p128pod &other)
{
	if (this != &other)
	{
		AsciiString::operator=(other);
		raw = other.raw;
		BFME_COPY_THUNK(j_00030d5a, &vector2c, &other.vector2c);
		dword38 = other.dword38;
		byte40 = other.byte40;
		dword44 = other.dword44;
		dword3c = other.dword3c;
		string48 = other.string48;
		BFME_COPY_THUNK(j_0000583f, &vector50, &other.vector50);
		dword4c = other.dword4c;
		BFME_COPY_THUNK(j_0002c719, &vector70, &other.vector70);
		BFME_COPY_THUNK(j_00010feb, &vector54, &other.vector54);
		BFME_COPY_THUNK(j_000063d4, &vector60, &other.vector60);
		byteac = other.byteac;
		byte6c = other.byte6c;
		for (int i = 0; i < 4; ++i)
		{
			BFME_COPY_THUNK(j_0001c288, &vector7c[i],
				&other.vector7c[i]);
		}
	}
	return *this;
}
