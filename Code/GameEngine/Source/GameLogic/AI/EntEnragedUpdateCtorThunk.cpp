// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EntEnragedUpdate retail constructor expressed as C++.

class Thing;
class ModuleData;
class Object;

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class EntEnragedIface1 { public: virtual void slot(); };
class EntEnragedIface2 { public: virtual void slot(); };

class UpdateModule : public PB_DeepBase, public EntEnragedIface1,
	public EntEnragedIface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

struct EntEnragedModuleDataView
{
	unsigned char m_pad[8];
	unsigned int m_initialValue;
};

int __cdecl entEnragedInitialValue(int, unsigned int, const void *, int);

class EntEnragedUpdate : public UpdateModule
{
public:
	EntEnragedUpdate(Thing *, const ModuleData *);

private:
	unsigned int m_f20;
	unsigned int m_f24;
	unsigned int m_f28;
	bool m_f2c;
	bool m_f2d;
	bool m_f2e;
	bool m_f2f;
	bool m_f30;
};

// ??0EntEnragedUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
EntEnragedUpdate::EntEnragedUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), m_f20(0)
{
	const EntEnragedModuleDataView *data =
		reinterpret_cast<const EntEnragedModuleDataView *>(m_moduleData);
	m_f20 += entEnragedInitialValue(0, data->m_initialValue,
		reinterpret_cast<const void *>(0x010be788), 0x4c);
	m_f2c = false;
	m_f2e = false;
	m_f2f = false;
	m_f2d = false;
	m_f28 = 0;
	m_f30 = false;
	m_f24 = 0x3fffffff;
}
