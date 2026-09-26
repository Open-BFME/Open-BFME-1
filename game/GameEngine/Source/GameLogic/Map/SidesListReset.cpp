// cl: /DNDEBUG /MD /EHsc
// The reset role is proven by subsystem dispatch; original method spellings remain unresolved.
class Rva0019BE80TeamRec
{
public:
    void clear();

private:
    unsigned char m_storage[0x1c];
};

class Rva0019BE80SidesList
{
public:
    void reset();
    void clearSidesAndTeamsAt0019BE50();

private:
    void clearSideStorageAt0019B4C0();
    unsigned char m_prefix[0x630];
    Rva0019BE80TeamRec m_teams;
    Rva0019BE80TeamRec m_skirmishTeams;
    char m_flag668;
};

void Rva0019BE80SidesList::reset()
{
    clearSideStorageAt0019B4C0();
    m_teams.clear();
    m_skirmishTeams.clear();
    m_flag668 = 1;
}

void Rva0019BE80SidesList::clearSidesAndTeamsAt0019BE50()
{
    clearSideStorageAt0019B4C0();
    m_teams.clear();
    m_skirmishTeams.clear();
    m_flag668 = 1;
}
