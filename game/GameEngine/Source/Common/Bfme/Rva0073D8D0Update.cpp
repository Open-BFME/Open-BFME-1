// 80-byte update with subobject test and vec3 copy

struct Vec3
{
	int x;
	int y;
	int z;
};

class SubObject0073D8D0
{
public:
	virtual void v0();
	virtual void pad1(); virtual void pad2(); virtual void pad3(); virtual void pad4();
	virtual void pad5(); virtual void pad6(); virtual void pad7(); virtual void pad8();
	virtual void pad9(); virtual void pad10(); virtual void pad11(); virtual void pad12();
	virtual void pad13(); virtual void pad14(); virtual void pad15(); virtual void pad16();
	virtual void pad17(); virtual void pad18();
	virtual bool test( int arg, const Vec3 *pos );
};

class Rva0073D8D0
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68();
	virtual void getPosition( Vec3 *out );

	void update( int arg );

	char              m_pad04[ 0x8 ];
	Vec3              m_vec0C;
	char              m_pad18[ 0x24A0 ];
	SubObject0073D8D0 m_subObject;
};

void Rva0073D8D0::update( int arg )
{
	Vec3 temp;
	getPosition( &temp );
	if ( m_subObject.test( arg, &temp ) )
	{
		m_vec0C = temp;
	}
}
