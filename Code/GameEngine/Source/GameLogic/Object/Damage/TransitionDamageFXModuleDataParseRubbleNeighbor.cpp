// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Include /Ireference/shims/ini_noinline /Ireference/shims/iniexception /Ireference/shims/asciistring_outofline
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "basetype.h"
#include "ascii_string.h"

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getNextSubToken(const char *expected);
	const char *getSepsColon() const { return m_sepsColon; }
	static Real scanReal(const char *token);
	static void parseObjectCreationList(INI *ini, void *instance, void *store,
		const void *userData);

private:
	char m_unreconstructed[0x41c];
	const char *m_sepsColon;
};

class INIException
{
public:
	INIException(Int code, const char *format, ...);
	INIException(const INIException &other);
	~INIException();

private:
	char *m_failureMessage;
	Int m_argCount;
};

class ObjectCreationList;

typedef Int ObjectID;

class Gen00252A50
{
public:
	Gen00252A50() {}
	__forceinline Gen00252A50(const Gen00252A50 &other)
		: m_objectID(other.m_objectID), m_subObjects(other.m_subObjects),
		  m_ocl(other.m_ocl)
	{
		m_neighborOffset.x = other.m_neighborOffset.x;
		m_neighborOffset.y = other.m_neighborOffset.y;
		m_neighborOffset.z = other.m_neighborOffset.z;
		m_oclOffset.x = other.m_oclOffset.x;
		m_oclOffset.y = other.m_oclOffset.y;
		m_oclOffset.z = other.m_oclOffset.z;
	}

	ObjectID m_objectID;
	std::vector<AsciiString> m_subObjects;
	const ObjectCreationList *m_ocl;
	Coord3D m_neighborOffset;
	Coord3D m_oclOffset;
};

class Gen00252A50Vector : public std::vector<Gen00252A50>
{
public:
	__forceinline void append(const Gen00252A50 &value)
	{
		if (this->_M_finish != this->_M_end_of_storage._M_data)
		{
			Gen00252A50 *finish = this->_M_finish;
			new (finish) Gen00252A50(value);
			++this->_M_finish;
		}
		else
			this->_M_insert_overflow(this->_M_finish, value, _IsPODType(),
				1UL, true);
	}
};

class TransitionDamageFXModuleData
{
public:
	static void NeighborIDSubobjectNameDataAppend(INI *ini, void *instance,
		void *store, const void *userData);
};

typedef void *(__cdecl *LookupFn)(void *, void *);
extern LookupFn g_lookup;

// The FieldParse row at VA 0x0108DBF0 registers the RubbleNeighbor token here.
// The parser's error string names TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend.
void TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend(
	INI *ini, void *instance, void *store, const void *)
{
	Gen00252A50 neighbor;
	neighbor.m_objectID = 0;
	neighbor.m_ocl = 0;
	neighbor.m_neighborOffset.z = 0.0f;
	neighbor.m_neighborOffset.y = 0.0f;
	neighbor.m_neighborOffset.x = 0.0f;
	neighbor.m_oclOffset.z = 0.0f;
	neighbor.m_oclOffset.y = 0.0f;
	neighbor.m_oclOffset.x = 0.0f;

	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token != 0)
	{
		LookupFn compare = g_lookup;
		do
		{
			if (compare((void *)token, (void *)"NeighborOffset") == 0)
			{
				neighbor.m_neighborOffset.x =
					INI::scanReal(ini->getNextSubToken("X"));
				neighbor.m_neighborOffset.y =
					INI::scanReal(ini->getNextSubToken("Y"));
				neighbor.m_neighborOffset.z =
					INI::scanReal(ini->getNextSubToken("Z"));
			}
			else if (compare((void *)token, (void *)"OCLOffset") == 0)
			{
				neighbor.m_oclOffset.x =
					INI::scanReal(ini->getNextSubToken("X"));
				neighbor.m_oclOffset.y =
					INI::scanReal(ini->getNextSubToken("Y"));
				neighbor.m_oclOffset.z =
					INI::scanReal(ini->getNextSubToken("Z"));
			}
			else if (compare((void *)token, (void *)"OCL") == 0)
				INI::parseObjectCreationList(ini, instance, &neighbor.m_ocl, 0);
			else if (compare((void *)token, (void *)"SubObject") == 0)
			{
				AsciiString subObject(ini->getNextToken(0));
				neighbor.m_subObjects.push_back(subObject);
			}
			else
				throw INIException(3,
					"bad colon spacing, or unexpected token in TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend");

			token = ini->getNextTokenOrNull(ini->getSepsColon());
		} while (token != 0);
	}

	((Gen00252A50Vector *)store)->append(neighbor);
}
