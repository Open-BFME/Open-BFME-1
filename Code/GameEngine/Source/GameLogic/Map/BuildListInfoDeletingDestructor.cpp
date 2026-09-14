// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BuildListInfo scalar-deleting destructor at retail RVA
// 0x00195550 (30 bytes).  The canonical constructor at 0x00194210 installs
// the BuildListInfo vtable, and the matched protected complete destructor at
// 0x00194320 owns the linked BuildListInfo chain; the SidesList methods and
// pool entry provide additional class identity.

class BuildListInfo
{
    friend void Force_BuildListInfo_Deleting_Destructor(BuildListInfo *value);

protected:
	__declspec(noinline) virtual ~BuildListInfo();
};

BuildListInfo::~BuildListInfo()
{
}

void Force_BuildListInfo_Deleting_Destructor(BuildListInfo *value)
{
	delete value;
}
