// ??0RailedTransportAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.55 date=2026-09-02
// cl: /DNDEBUG /MD
// BFME layout reconstruction of the Zero Hour RailedTransportAIUpdate ctor.

class Thing;
class ModuleData;

class DRB_BodyModule
{
public:
	DRB_BodyModule( Thing *thing, const ModuleData *moduleData );
	virtual void primarySlot();
private:
	char m_primaryPad[ 8 ];
};

class RailedTransportFace1
{
public:
	virtual void face1Slot();
};

class RailedTransportFace2
{
public:
	virtual void face2Slot();
};

class RailedTransportAIUpdate :
	public DRB_BodyModule,
	public RailedTransportFace1,
	public RailedTransportFace2
{
public:
	RailedTransportAIUpdate( Thing *thing, const ModuleData *moduleData );
private:
	char m_unmodelled_014[ 0xe0 - 0x14 ];
	int m_e0;
	int m_e4;
	int m_e8;
};

RailedTransportAIUpdate::RailedTransportAIUpdate(
	Thing *thing,
	const ModuleData *moduleData ) :
	DRB_BodyModule( thing, moduleData )
{
	m_e8 = 0;
	m_e4 = 0;
	m_e0 = 0;
	m_e8 = 0;
}
