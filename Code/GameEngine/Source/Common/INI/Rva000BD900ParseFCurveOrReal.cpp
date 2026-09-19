// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc
// BFME function-curve field parser at retail RVA 0x000BD900.

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl sscanf(const char *, const char *, ...);
extern "C" int __cdecl strcmp(const char *, const char *);

namespace _STL
{
struct random_access_iterator_tag
{
};

char *__cdecl __copy(char *, char *, char *, const random_access_iterator_tag &, int *);
}

class INIException
{
public:
	INIException(Int argCount, const char *format, ...);
	INIException(const INIException &other);

private:
	char *m_failureMessage;
	Int m_argCount;
};

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
};

class Rva0006AB10Curve
{
public:
	void set(Real time, Real value, Int inTangent, Int outTangent);

	void clear()
	{
		_STL::random_access_iterator_tag tag;
		Int *none = 0;
		char *result = m_start;
		m_finish = _STL::__copy(m_finish, m_finish, result, tag, none);
		m_field0 = 0;
		m_field4 = 0;
	}

private:
	Int m_field0;
	Int m_field4;
	char *m_start;
	char *m_finish;
	char *m_end;
};

class Rva0006AF00FunctionCurve
{
public:
	void parse(INI *ini);
};

class Rva000BD900
{
public:
	static void parseFCurveOrReal(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseFCurveOrReal@Rva000BD900@@SAXPAVINI@@PAX1PBX@Z
void Rva000BD900::parseFCurveOrReal(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken();
	Rva0006AB10Curve *curve = (Rva0006AB10Curve *)store;
	curve->clear();

	Real value;
	if (sscanf(token, "%f", &value) == 1)
	{
		curve->set(0.0f, value, 0, 0);
		return;
	}

	if (strcmp(token, "FCurve") == 0)
	{
		((Rva0006AF00FunctionCurve *)curve)->parse(ini);
		return;
	}

	throw INIException(5, "'FCurve' expected");
}
