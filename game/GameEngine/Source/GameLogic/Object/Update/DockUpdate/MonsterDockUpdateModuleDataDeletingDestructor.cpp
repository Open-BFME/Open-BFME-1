// cl: /O2 /Ob0

class MonsterDockUpdateModuleData
{
public:
	virtual ~MonsterDockUpdateModuleData();
};

// ~MonsterDockUpdateModuleData is matched out of line (MonsterDockUpdateModuleDataCtorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceMonsterDockUpdateModuleDataDeletingDestructorCopy(const MonsterDockUpdateModuleData &that)
{
	MonsterDockUpdateModuleData value(that);
}
