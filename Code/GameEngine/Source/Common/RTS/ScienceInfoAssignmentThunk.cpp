// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ScienceInfo assignment in the retail 0x30-byte layout.

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &);
private:
	unsigned char m_data[0x0c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString &operator=(const UnicodeString &);
private:
	void *m_data;
};

class ScienceVecStorage
{
public:
	ScienceVecStorage &operator=(const ScienceVecStorage &);
private:
	void *m_first;
	void *m_last;
	void *m_end;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Science.h
class ScienceInfo : public ScienceInfoBase
{
public:
	ScienceInfo &operator=(const ScienceInfo &);
private:
	unsigned int m_science;
	UnicodeString m_name;
	UnicodeString m_description;
	ScienceVecStorage m_prerequisiteSciences;
	int m_sciencePurchasePointCost;
	int m_sciencePurchasePointCostMP;
	bool m_grantable;
};

// ??4ScienceInfo@@QAEAAV0@ABV0@@Z
ScienceInfo &ScienceInfo::operator=(const ScienceInfo &other)
{
	ScienceInfoBase::operator=(other);
	m_science = other.m_science;
	m_name = other.m_name;
	m_description = other.m_description;
	m_prerequisiteSciences = other.m_prerequisiteSciences;
	m_sciencePurchasePointCost = other.m_sciencePurchasePointCost;
	m_sciencePurchasePointCostMP = other.m_sciencePurchasePointCostMP;
	m_grantable = other.m_grantable;
	return *this;
}
