// cl: /DNDEBUG /MD /EHsc

// HordeMemberCollideModuleData's constructor, retail 0x00216790. Nine bytes:
// no base constructor call, no members, just this class's own vftable pointer
// at +0x00. The base's word at +0x04 is left alone, which is what an implicit
// base constructor looks like.

class HordeMemberCollideModuleDataBase
{
public:
	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[4];
};

class HordeMemberCollideModuleData : public HordeMemberCollideModuleDataBase
{
public:
	HordeMemberCollideModuleData();
};

HordeMemberCollideModuleData::HordeMemberCollideModuleData()
{
}
