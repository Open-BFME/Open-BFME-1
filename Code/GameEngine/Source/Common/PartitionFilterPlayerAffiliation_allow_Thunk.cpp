// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to semantic C++.

class Team;

enum Relationship
{
	ALLIES,
	NEUTRAL,
	ENEMIES
};

class Player
{
public:
	Relationship getRelationship(const Team *) const;
};

class Object
{
	char m_data[0x23c];
	Team *m_team;

public:
	Team *getTeam() const { return m_team; }
};

class PartitionFilterPlayerAffiliation
{
	char m_data[4];
	Player *m_player;
	bool m_match;
	char m_padding[3];
	int m_affiliation;

protected:
	virtual bool allow(Object *);
};

bool PartitionFilterPlayerAffiliation::allow(Object *other)
{
	Relationship relationship = m_player->getRelationship(other->getTeam());
	switch (relationship) {
		case ALLIES:
			if (m_affiliation & 4) {
				return m_match;
			}
			break;
		case NEUTRAL:
			if (m_affiliation & 8) {
				return m_match;
			}
			break;
		case ENEMIES:
			if (m_affiliation & 2) {
				return m_match;
			}
			break;
	}

	return !m_match;
}
