// ?rebuildPathFromStatePoints@Rva00270DF0AIUpdate@@IAEXXZ
// partial score=0.3 date=2026-09-20
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(this) + 0x38);
	}
};

class Thing
{
public:
	void getUnitDirectionVector2D(Coord3D &direction) const;
};

class PathNode
{
};

class Path
{
public:
	Path();
	void appendNode(const Coord3D *position, PathfindLayerEnum layer);
	void optimize(const Object *object, Int surfaces, Bool blocked);
	void bfmeOptimizeDir(const Object *object, const Coord3D *direction,
		Int surfaces, Bool blocked);

private:
	char m_slicePad[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
	char m_tailPad[0x24 - 0x10];
};

class Rva00270DF0LocomotorTemplate
{
public:
	Rva00270DF0LocomotorTemplate *getFinalOverride() const;

	void *m_vtable;
	Rva00270DF0LocomotorTemplate *m_next;
	char m_pad[8];
	Int m_surfaces;
};

class Rva00270DF0Locomotor
{
public:
	char m_pad[4];
	Rva00270DF0LocomotorTemplate *m_template;
};

struct Rva0016F770Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva0016F770Path
{
	char m_pad[0x44];
	Rva0016F770Coord3D *m_begin;
	Rva0016F770Coord3D *m_end;

	Rva0016F770Coord3D *getPoint(Int index);
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};

class Pathfinder
{
public:
	void setDebugPath(Path *path);
};

class AI
{
public:
	char m_pad[0x0C];
	Pathfinder *m_pathfinder;
};

class GameLogic
{
public:
	char m_pad[0x3C];
	UnsignedInt m_frame;
};

struct GlobalData
{
	char m_pad[0xA88];
	Int m_debugAI;
};

class Rva00270DF0VirtualSlots
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual void slot096();
	virtual void slot097();
	virtual void slot098();
	virtual void slot099();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
};

class Rva00270DF0AIUpdate : public Rva00270DF0VirtualSlots
{
protected:
	virtual void postPath();
	void rebuildPathFromStatePoints();

	char m_pad000[4];
	Object *m_object;
	char m_pad00C[0x30 - 0x0C];
	Rva0016F770Path *m_stateMachine;
	char m_pad034[0x140 - 0x34];
	Path *m_path;
	char m_pad144[0x160 - 0x144];
	UnsignedInt m_pathTimestamp;
	char m_pad164[0x16C - 0x164];
	Int m_blockedFrames;
	char m_pad170[0x1CC - 0x170];
	Rva00270DF0Locomotor *m_curLocomotor;
	char m_pad1D0[0x326 - 0x1D0];
	Bool m_isBlockedAndStuck;
};

extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;
extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheBfmeGameLogic;

void Rva00270DF0AIUpdate::rebuildPathFromStatePoints()
{
	Rva00270DF0LocomotorTemplate *locomotor = m_curLocomotor->m_template;
	Path *path = new Path;
	m_path = path;
	path->appendNode(m_object->getPosition(), LAYER_GROUND);

	if (locomotor->m_next)
		locomotor = locomotor->getFinalOverride();
	path->optimize(m_object, locomotor->m_surfaces, false);

	for (Int index = 0; index < (Int)(m_stateMachine->m_end - m_stateMachine->m_begin);
		++index)
	{
		Rva0016F770Coord3D *source = m_stateMachine->getPoint(index);
		Coord3D point = *reinterpret_cast<Coord3D *>(source);
		PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(
			m_object, &point);
		path->appendNode(&point, layer);
	}

	if (TheWritableGlobalData->m_debugAI == 1)
		TheAI->m_pathfinder->setDebugPath(m_path);

	Coord3D direction;
	reinterpret_cast<const Thing *>(m_object)->getUnitDirectionVector2D(direction);
	locomotor = m_curLocomotor->m_template;
	if (locomotor && locomotor->m_next)
		locomotor = locomotor->getFinalOverride();
	path->bfmeOptimizeDir(m_object, &direction, locomotor->m_surfaces, false);

	m_pathTimestamp = TheBfmeGameLogic->m_frame;
	postPath();
	m_blockedFrames = 0;
	m_isBlockedAndStuck = false;
}
