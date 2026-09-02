// ?getTotalDestroyedOfName@ScoreKeeper@@QBEHABVBfmeScoreString@@@Z
// partial score=0.86 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ScoreKeeper per-name destroyed-object total. Walks the 32 STL maps at +0x150.

#include <map>
#include <string.h>

struct BfmeScoreStringData {
	unsigned short references;
	unsigned short allocated;
	unsigned short length;
	unsigned short padding;
	char text[1];
};

class BfmeScoreString {
public:
	bool equals(const BfmeScoreString &other) const;

private:
	BfmeScoreStringData *m_data;
};

bool BfmeScoreString::equals(const BfmeScoreString &other) const
{
	unsigned int leftLength = m_data ? m_data->length : 0;
	const char *left = m_data ? m_data->text : "";
	unsigned int rightLength = other.m_data ? other.m_data->length : 0;
	const char *right = other.m_data ? other.m_data->text : "";
	unsigned int commonLength = leftLength < rightLength ? leftLength : rightLength;
	int comparison = memcmp(right, left, commonLength);
	if (comparison == 0)
		comparison = rightLength - leftLength;
	return comparison == 0;
}

struct BfmeScoreTemplate {
	char padding[0x20];
	BfmeScoreString name;
};

typedef _STL::map<const BfmeScoreTemplate *, int> BfmeScoreMap;

class ScoreKeeper {
public:
	int getTotalDestroyedOfName(const BfmeScoreString &name) const;

private:
	char padding[0x150];
	BfmeScoreMap m_destroyed[32];
};

int ScoreKeeper::getTotalDestroyedOfName(const BfmeScoreString &name) const
{
	int count = 0;
	for (int player = 0; player < 32; ++player) {
		for (BfmeScoreMap::const_iterator it = m_destroyed[player].begin();
		     it != m_destroyed[player].end(); ++it) {
			const BfmeScoreTemplate *thingTemplate = it->first;
			if (thingTemplate && name.equals(thingTemplate->name))
				count += it->second;
		}
	}
	return count;
}
