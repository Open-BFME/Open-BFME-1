// ?parseBannerCarrierPosition@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.97 date=2026-08-31
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <string.h>
#include <vector>

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
	AsciiString &operator=(const char *text);

private:
	void *m_data;
};

struct Coord2D
{
	Real x;
	Real y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException(int code, const char *message, ...);
	INIException(const INIException &other);
	~INIException();

private:
	char *m_failureMessage;
	int m_argCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getSepsColon() const { return m_sepsColon; }

	static void parseCoord2D(INI *, void *, void *, const void *);

private:
	char m_prefix[0x41c];
	const char *m_sepsColon;
};

struct BannerCarrierPosition
{
	BannerCarrierPosition() : m_unitType("")
	{
		m_position.x = 0;
		m_position.y = 0;
	}

	AsciiString m_unitType;
	Coord2D m_position;
};

typedef std::vector<BannerCarrierPosition *> BannerCarrierPositions;

void parseBannerCarrierPosition(INI *ini, void *, void *store, const void *)
{
	BannerCarrierPosition *position = new BannerCarrierPosition;
	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (!token || strcmp(token, "UnitType") != 0)
		throw INIException(3, "UnitType expected");

	{
		Coord2D parsedPosition;
		position->m_unitType = ini->getNextToken(ini->getSepsColon());
		token = ini->getNextTokenOrNull(ini->getSepsColon());
		if (!token || strcmp(token, "Pos") != 0)
			throw INIException(3, "'Pos' expected");

		INI::parseCoord2D(ini, 0, &parsedPosition, 0);
		position->m_position = parsedPosition;
	}
	static_cast<BannerCarrierPositions *>(store)->push_back(position);
}
