// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

// ?bfmeSetupAPB@@YAHXZ 0x00061380
// The retail body updates g_bfmeFlagsAPB at 0x012A6FA0, marks the second CRC
// mode at 0x012ED4E6, and rejects the mode pair through the shared INIException
// text at 0x01075230 when g_bfmeOnAPB at 0x012ED4E5 is already set.

typedef unsigned int UnsignedInt;

extern UnsignedInt g_bfmeFlagsAPB;
extern bool g_bfmeOnAPB;
extern bool g_bfmeDoneAPB;
extern "C" char _bfmeTagAPB;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);

class INIException
{
public:
	INIException(int code, const char *message, ...);
	INIException(const INIException &other);

private:
	int m_code;
	const char *m_message;
};

int bfmeSetupAPB(void)
{
	g_bfmeDoneAPB = true;
	g_bfmeFlagsAPB |= 0x20000;
	if (g_bfmeOnAPB)
	{
		INIException error(3, "Do not specify both -deepCRC and -liteCRC in your commandline arguments.");
		_CxxThrowException(&error, &_bfmeTagAPB);
	}
	return 1;
}
