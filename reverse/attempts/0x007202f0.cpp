// ?dispatch@Rva00720BB0Context@@QAEXHPAX@Z
// partial score=0.5292 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// ?dispatch@Rva00720BB0Context@@QAEXHPAX@Z
// partial score=0.45 date=2026-09-14
// BFME's tree-buffer request path.  The surrounding object stores its tree
// records and type table in one large byte layout; these views keep the
// offsets visible without claiming the unrelated parts of the class.

#define Matrix4x4 Matrix4
#define Matrix3x3 Matrix3
#include "matrix4.h"

struct Rva00720BB0DispatchLocals
{
	char m_pad00[12];
	Matrix3D m_transform;
};

class RenderObjClass
{
public:
	virtual void Delete_This( void );
	virtual void slot04( void );
	virtual void slot08( void );
	virtual void slot0c( void );
	virtual void slot10( void );
	virtual void slot14( void );
	virtual void slot18( void );
	virtual void slot1c( void );
	virtual void slot20( void );
	virtual void slot24( void );
	virtual void slot28( void );
	virtual void slot2c( void );
	virtual void slot30( void );
	virtual void slot34( void );
	virtual void slot38( void );
	virtual void slot3c( void );
	virtual void slot40( void );
	virtual void slot44( void );
	virtual void slot48( void );
	virtual void slot4c( void );
	virtual void Validate_Transform( void ) const;
	virtual void Set_Transform( const Matrix3D &transform );

	void Release_Ref( void )
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	const Matrix3D &Get_Transform( void ) const
	{
		Validate_Transform();
		return m_transform;
	}

	int m_refCount;
	char m_pad08[0x18 - 8];
	Matrix3D m_transform;
};

class BfmeGlobPB
{
public:
	virtual void slot00( void );
	virtual void slot04( void );
	virtual void Add_Render_Object( RenderObjClass *object );
};

extern BfmeGlobPB *g_bfmeGlobPB;
RenderObjClass *Create_Render_Obj( const char *name );
void Rva00739B30(RenderObjClass *object, bool geometry);
void Rva00739900Forward(void *object, float value);
struct Coord3D {float x,y,z;};
class FXList {public: static void doFXPos(const FXList *,const Coord3D *,const Matrix3D *,float,const Coord3D *);};

struct Rva00720BB0TreeData
{
	char m_pad00[8];
	void *m_modelName;
	char m_pad0c[0x4c - 0x0c];
	int m_toppleFrames;
	void *m_effect;
	unsigned char m_doShadow;
};

struct Rva00720BB0TreeType
{
	Rva00720BB0TreeData *m_data;
	char m_pad04[0x2c - 4];
	void *m_stumpName;
	char m_pad30[0x38 - 0x30];
	int m_state;
};

struct Rva00720BB0Tree
{
	char m_pad00[0x40];
	int m_treeType;
	char m_pad44[0x44];
	int m_toppleState;
	int m_uprightType;
	int m_toppledType;
	unsigned int m_sinkFrames;
	RenderObjClass *m_toppleObject;
	RenderObjClass *m_pushAsideObject;
	char m_padA0[4];
};

class Rva00720BB0Context
{
public:
	void dispatch( int index, void *request );

	Rva00720BB0TreeType *treeTypeAt( int treeType )
	{
		return reinterpret_cast<Rva00720BB0TreeType *>(
			reinterpret_cast<char *>(this) + (treeType + 0x53cb) * 0x5c);
	}

	public:
	char m_pad00[0x1548];
	Rva00720BB0Tree m_trees[12000];
	int m_entryCount;
	unsigned char m_anythingChanged;
};

void Rva00720BB0Context::dispatch( int index, void *request )
{
	int treeType;
	Rva00720BB0TreeType *type;
	Rva00720BB0TreeType *volatile firstType;
	Rva00720BB0TreeData *data;

	const char *name;
	char * const treeBytes = reinterpret_cast<char *>(this) + index * 0xa4;
 RenderObjClass *&topple = *reinterpret_cast<RenderObjClass **>(treeBytes + 0x15e0);
 RenderObjClass *&pushAside = *reinterpret_cast<RenderObjClass **>(treeBytes + 0x15e4);

	treeType = m_trees[index].m_treeType;
	if (index >= m_entryCount)
		return;
	if (treeType < 0)
		return;

	if (request == reinterpret_cast<void *>(1)) {
		if (treeTypeAt(treeType)->m_data->m_doShadow)
			return;
	} else if (request == reinterpret_cast<void *>(2)) {
		if (!treeTypeAt(treeType)->m_data->m_doShadow)
			return;
	}

	{
	Matrix3D transform;
	type = treeTypeAt(treeType);
	firstType = type;
	data = type->m_data;
	*reinterpret_cast<unsigned int *>(treeBytes + 0x15dc) = data->m_toppleFrames;
	*reinterpret_cast<int *>(treeBytes + 0x15d0) = reinterpret_cast<int>(request);

	if (topple) {
		topple->Release_Ref();
		topple = 0;
	}

	name = *reinterpret_cast<const char **>(reinterpret_cast<char *>(this) + treeType * 0x5c + 0x1e1d20);
	if (name)
		name += 8;
	else
		name = "";
	topple = Create_Render_Obj(name);
	Rva00739B30(topple, false);
	g_bfmeGlobPB->Add_Render_Object(topple);
	transform = topple->Get_Transform();
	transform[0][3] = *reinterpret_cast<float *>(treeBytes + 0x1548);
	transform[1][3] = *reinterpret_cast<float *>(treeBytes + 0x154c);
	transform[2][3] = *reinterpret_cast<float *>(treeBytes + 0x1550);
	Matrix3 rotationValue(*reinterpret_cast<Matrix4 *>(treeBytes + 0x1558));
	transform.Set_Rotation(rotationValue);
	topple->Set_Transform(transform);

	if (pushAside) {
		pushAside->Release_Ref();
		pushAside = 0;
	}

	if (*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + treeType * 0x5c + 0x1e1d2c) != -2) {

	type = treeTypeAt(*reinterpret_cast<int *>(treeBytes + 0x15d8));
	data = type->m_data;
	name = static_cast<const char *>(data->m_modelName);
	if (name)
		name += 8;
	else
		name = "";
	pushAside = Create_Render_Obj(name);
	Rva00739B30(pushAside, false);
	g_bfmeGlobPB->Add_Render_Object(pushAside);
	transform = pushAside->Get_Transform();
	transform[0][3] = *reinterpret_cast<float *>(treeBytes + 0x1548);
	transform[1][3] = *reinterpret_cast<float *>(treeBytes + 0x154c);
	transform[2][3] = *reinterpret_cast<float *>(treeBytes + 0x1550);
	transform.Set_Rotation(rotationValue);
	pushAside->Set_Transform(transform);
 }

	if (topple)
		Rva00739900Forward(topple, 1.0f);
	if (pushAside)
		Rva00739900Forward(pushAside, 0.0f);

	data = firstType->m_data;
 if (data->m_effect) {
 Coord3D position;
 position.x = *reinterpret_cast<float *>(treeBytes + 0x1548);
 position.y = *reinterpret_cast<float *>(treeBytes + 0x154c);
 position.z = *reinterpret_cast<float *>(treeBytes + 0x1550);
 FXList::doFXPos(static_cast<const FXList *>(data->m_effect), &position, 0, 0.0f, 0);
 }

	m_anythingChanged = 1;
	}
}

extern "C" bool __fastcall Rva00720BB0LookupDispatch( Rva00720BB0Context *self, void *, void *owner, void *request )
{
	if ( owner == 0 ) {
		return false;
	}

		int count = self->m_entryCount;
	int i = 0;
	void *payload;
	if ( count > 0 ) {
		char *entry = (char *)self + 0x15DC;
		do {
			if ( *(void **)(entry - 0x38) == owner && *(unsigned int *)entry <= 0 ) {
				payload = *(void **)(entry - 0xC);
				if ( payload == 0 ) {
					goto dispatch;
				}
			}
			++i;
			entry += 0xA4;
		} while ( i < count );
	}
	return false;

dispatch:
	self->dispatch( i, request );
	return true;
}
