// BFME's tree-buffer request path.  The surrounding object stores its tree
// records and type table in one large byte layout; these views keep the
// offsets visible without claiming the unrelated parts of the class.

class Matrix4
{
	float m_values[16];
};

class Matrix3
{
public:
	Matrix3( const Matrix4 &source );

	public:
	float m_values[9];
};

class Matrix3D
{
public:
	void Set_Rotation( const Matrix3 &rotation );

	float m_values[12];
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
extern "C" void Rva00739900Forward( void *object, float value );
extern "C" void j_00018fc0( RenderObjClass *object, int geometry, const char *colors );
extern "C" void j_0001593d( void *effect, const void *position, int a, int b, int c );

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

class Rva00720BB0Context
{
public:
	void dispatch( int index, void *request );

	public:
	char m_unknown0000[0x1E1CC8];
	int m_entryCount;
};

static Rva00720BB0TreeType *treeTypeAt( Rva00720BB0Context *self, int treeType )
{
	return reinterpret_cast<Rva00720BB0TreeType *>(
		reinterpret_cast<char *>(self) + (treeType + 0x53cb) * 0x5c);
}

void Rva00720BB0Context::dispatch( int index, void *request )
{
	char *record = reinterpret_cast<char *>(this) + index * 0xa4;
	int treeType = *reinterpret_cast<int *>(record + 0x1588);
	Rva00720BB0TreeType *type;
	Rva00720BB0TreeData *data;
	RenderObjClass *topple;
	RenderObjClass *pushAside;
	Matrix3D transform;
	const char *name;

	if (index >= m_entryCount || treeType < 0)
		return;

	type = treeTypeAt(this, treeType);
	if (request == reinterpret_cast<void *>(1)) {
		if (type->m_data->m_doShadow)
			return;
	} else if (request == reinterpret_cast<void *>(2)) {
		if (!type->m_data->m_doShadow)
			return;
	}

	data = type->m_data;
	*reinterpret_cast<int *>(record + 0x15dc) = data->m_toppleFrames;
	*reinterpret_cast<int *>(record + 0x15d0) = reinterpret_cast<int>(request);

	topple = *reinterpret_cast<RenderObjClass **>(record + 0x15e0);
	if (topple)
		topple->Release_Ref();
	*reinterpret_cast<RenderObjClass **>(record + 0x15e0) = 0;

	name = static_cast<const char *>(type->m_stumpName);
	if (name)
		name += 8;
	else
		name = reinterpret_cast<const char *>(0x107388b);
	topple = Create_Render_Obj(name);
	*reinterpret_cast<RenderObjClass **>(record + 0x15e0) = topple;
	j_00018fc0(topple, 0, name);
	g_bfmeGlobPB->Add_Render_Object(topple);
	transform = topple->Get_Transform();
	Matrix3 rotationValue(*reinterpret_cast<Matrix4 *>(record + 0x1558));
	transform.Set_Rotation(rotationValue);
	topple->Set_Transform(transform);

	pushAside = *reinterpret_cast<RenderObjClass **>(record + 0x15e4);
	if (pushAside)
		pushAside->Release_Ref();
	*reinterpret_cast<RenderObjClass **>(record + 0x15e4) = 0;

	if (*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + treeType * 0x5c + 0x1e1d2c) == -2)
		return;

	type = treeTypeAt(this, *reinterpret_cast<int *>(record + 0x15d8));
	data = type->m_data;
	name = static_cast<const char *>(data->m_modelName);
	if (name)
		name += 8;
	else
		name = reinterpret_cast<const char *>(0x107388b);
	pushAside = Create_Render_Obj(name);
	*reinterpret_cast<RenderObjClass **>(record + 0x15e4) = pushAside;
	j_00018fc0(pushAside, 0, name);
	g_bfmeGlobPB->Add_Render_Object(pushAside);
	transform = pushAside->Get_Transform();
	transform.Set_Rotation(rotationValue);
	pushAside->Set_Transform(transform);

	if (topple)
		Rva00739900Forward(topple, 1.0f);
	if (pushAside)
		Rva00739900Forward(pushAside, 0.0f);

	if (data->m_effect)
		j_0001593d(data->m_effect, record + 0x1548, 0, 0, 0);

	*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(this) + 0x1e1ccc) = 1;
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
