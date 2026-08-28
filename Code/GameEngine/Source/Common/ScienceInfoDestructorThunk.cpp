// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
    ~UnicodeString();

private:
    void *m_data;
};

class ScienceVecStandIn
{
public:
    ~ScienceVecStandIn();

private:
    void *m_begin;
    void *m_end;
    void *m_capacity;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
    virtual ~Overridable()
    {
        if (m_nextOverride)
            delete m_nextOverride;
        m_nextOverride = 0;
    }

private:
    Overridable *m_nextOverride;
    bool m_isOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Science.h
class ScienceInfo : public Overridable
{
protected:
    virtual ~ScienceInfo();

private:
    int m_science;
    UnicodeString m_name;
    UnicodeString m_description;
    ScienceVecStandIn m_rootSciences;
    int m_sciencePurchasePointCost;
    bool m_grantable;
};

ScienceInfo::~ScienceInfo()
{
}
