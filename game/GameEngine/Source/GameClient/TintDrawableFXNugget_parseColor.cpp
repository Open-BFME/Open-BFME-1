// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TintDrawableFXNugget color field parser at retail 0x004276A0.

typedef float Real;
typedef int Int;

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

class INI
{
public:
	const char *getNextSubToken(const char *name);
	static Int scanInt(const char *token);
};

class INIException
{
public:
	INIException(Int error, const char *format, ...);
	INIException(const INIException &other);

private:
	Int m_error;
	const char *m_format;
};

extern const Real g_0107C64C;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);

class TintDrawableFXNugget
{
public:
	static void parseColor(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseColor@TintDrawableFXNugget@@SAXPAVINI@@PAX1PBX@Z
void TintDrawableFXNugget::parseColor(INI *ini, void *, void *store, const void *)
{
	const char *names[3] = { "R", "G", "B" };
	Int colors[3];
	for (Int i = 0; i < 3; i++) {
		colors[i] = INI::scanInt(ini->getNextSubToken(names[i]));
		if (colors[i] < -255 || colors[i] > 255) {
			INIException error(3, "color value %s=%i out of range (0..255)", names[i], colors[i]);
			_CxxThrowException(&error, (void *)0x011DFC30);
		}
	}

	RGBColor *theColor = (RGBColor *)store;
	theColor->red = (Real)colors[0] * g_0107C64C;
	theColor->green = (Real)colors[1] * g_0107C64C;
	theColor->blue = (Real)colors[2] * g_0107C64C;
}
