// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// The ExperienceLevel field table at 0x010EAB48 sends Upgrades entries to
// this callback at retail RVA 0x0037FBC0. Each token names an UpgradeTemplate.

#define _M_insert_overflow j_00004f8e
#include <vector>
#undef _M_insert_overflow

class BFMERetailAsciiString;

template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;

private:
	StringBase(const T *text);
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *separators = 0);
};

class AsciiString;
class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *j_0002f95a(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class ExperienceLevel
{
public:
	char m_unreconstructed_000[0x44];
	_STL::vector<const UpgradeTemplate *> upgrades;
};

// ?parseExperienceLevelUpgrade@@YAXPAVINI@@PAX1PBX@Z
void parseExperienceLevelUpgrade(INI *ini, void *instance, void *, const void *)
{
	ExperienceLevel *self = (ExperienceLevel *)instance;
	const char *token;
	while ((token = ini->getNextTokenOrNull(0)) != 0)
	{
		const UpgradeTemplate *upgrade;
		{
			BFMERetailAsciiString name(token);
			upgrade = TheUpgradeCenter->j_0002f95a(
				*(const AsciiString *)&name);
		}

		if (upgrade != 0)
			self->upgrades.push_back(upgrade);

	}
}
