// cl: /DNDEBUG /MD /EHsc
// readable body of ??1SidesInfo@@QAE@XZ: Code/GameEngine/Source/GameLogic/Map/SidesList.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h
class BuildListInfo
{
public:
	virtual ~BuildListInfo();
	void deleteInstance() { if (this) delete this; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
	public:
	void clear();
	~Dict() { releaseData(); }

private:
	void releaseData();
	void *m_data;
};

class SidesInfoSegmentShim
{
public:
	void finish(void *, void *);
};

class MemberA
{
public:
	~MemberA();
	unsigned char m_pad[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptList
{
public:
	virtual ~ScriptList();
	void deleteInstance() { if (this) delete this; }
};

class __declspec(novtable) SidesInfo
{
public:
	~SidesInfo();

private:
	BuildListInfo *m_pBuildList;
	Dict m_dict;
	ScriptList *m_scripts;
	MemberA m_segment;
};

// ??1SidesInfo@@QAE@XZ
SidesInfo::~SidesInfo()
{
	SidesInfo *self = this;
	m_pBuildList->deleteInstance();
	m_pBuildList = 0;
	m_dict.clear();
	m_scripts->deleteInstance();
	m_scripts = 0;
	self = (SidesInfo *)((unsigned char *)self + 0xc);
	((SidesInfoSegmentShim *)self)->finish(
		*(void **)((unsigned char *)self + 0),
		*(void **)((unsigned char *)self + 4));
}
