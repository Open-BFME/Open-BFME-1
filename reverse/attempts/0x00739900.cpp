// ?Rva00739900Forward@@YA_NPAXM@Z
// partial score=0.93 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// ?Rva00739900Forward@@YA_NPAXM@Z present-unmatched
//
// Walk a RenderObj tree and set VertexMaterialClass::Set_Opacity.  Retail
// identity is the reloc-named forwarder called from Rva006FCBD0ClampForward
// and W3DTreeBuffer topple/push-aside.  Get_Material_Info is vslot 0x150;
// otherwise recurse through Get_Num_Sub_Objects (0x6C) / Get_Sub_Object (0x74).
//
// Near-miss 212 vs 206: both loops match including `if (result || child)
// result = 1`.  Remaining wall is uchar->bool return (`test bl,bl; setne al`
// vs retail `mov al,bl`), which also drops the second-loop `lea esp,[esp]`
// align nop.  bool local spills (push ecx).  Matching byte return types
// coalesce result with al and spill.  __assume does not skip the convert.

class VertexMaterialClass
{
public:
	virtual void Delete_This( void );
	int NumRefs;

	void Add_Ref( void )
	{
		NumRefs++;
	}

	void Release_Ref( void )
	{
		NumRefs--;
		if ( NumRefs == 0 )
			Delete_This();
	}

	void Set_Opacity( float o );
};

class MaterialInfoClass
{
public:
	virtual void Delete_This( void );
	int NumRefs;					// +0x04
	int VectorVtable;				// +0x08 VectorClass vptr
	VertexMaterialClass **Vector;	// +0x0C
	int VectorMax;					// +0x10
	int VectorFlags;				// +0x14
	int ActiveCount;				// +0x18

	void Release_Ref( void )
	{
		NumRefs--;
		if ( NumRefs == 0 )
			Delete_This();
	}

	int Vertex_Material_Count( void ) const
	{
		return ActiveCount;
	}

	VertexMaterialClass *Get_Vertex_Material( int index )
	{
		if ( Vector[index] )
			Vector[index]->Add_Ref();
		return Vector[index];
	}
};

class RenderObjClass
{
public:
	virtual void Delete_This( void );					// 0x00
	virtual void v01( void );
	virtual void v02( void );
	virtual void v03( void );
	virtual void v04( void );
	virtual void v05( void );
	virtual void v06( void );
	virtual void v07( void );
	virtual void v08( void );
	virtual void v09( void );
	virtual void v10( void );
	virtual void v11( void );
	virtual void v12( void );
	virtual void v13( void );
	virtual void v14( void );
	virtual void v15( void );
	virtual void v16( void );
	virtual void v17( void );
	virtual void v18( void );
	virtual void v19( void );
	virtual void v20( void );
	virtual void v21( void );
	virtual void v22( void );
	virtual void v23( void );
	virtual void v24( void );
	virtual void v25( void );
	virtual void v26( void );
	virtual int Get_Num_Sub_Objects( void ) const;		// 0x6C slot 27
	virtual void v28( void );							// 0x70
	virtual RenderObjClass *Get_Sub_Object( int index ) const;	// 0x74 slot 29
	virtual void v30( void );
	virtual void v31( void );
	virtual void v32( void );
	virtual void v33( void );
	virtual void v34( void );
	virtual void v35( void );
	virtual void v36( void );
	virtual void v37( void );
	virtual void v38( void );
	virtual void v39( void );
	virtual void v40( void );
	virtual void v41( void );
	virtual void v42( void );
	virtual void v43( void );
	virtual void v44( void );
	virtual void v45( void );
	virtual void v46( void );
	virtual void v47( void );
	virtual void v48( void );
	virtual void v49( void );
	virtual void v50( void );
	virtual void v51( void );
	virtual void v52( void );
	virtual void v53( void );
	virtual void v54( void );
	virtual void v55( void );
	virtual void v56( void );
	virtual void v57( void );
	virtual void v58( void );
	virtual void v59( void );
	virtual void v60( void );
	virtual void v61( void );
	virtual void v62( void );
	virtual void v63( void );
	virtual void v64( void );
	virtual void v65( void );
	virtual void v66( void );
	virtual void v67( void );
	virtual void v68( void );
	virtual void v69( void );
	virtual void v70( void );
	virtual void v71( void );
	virtual void v72( void );
	virtual void v73( void );
	virtual void v74( void );
	virtual void v75( void );
	virtual void v76( void );
	virtual void v77( void );
	virtual void v78( void );
	virtual void v79( void );
	virtual void v80( void );
	virtual void v81( void );
	virtual void v82( void );
	virtual void v83( void );
	virtual MaterialInfoClass *Get_Material_Info( void );	// 0x150 slot 84

	void Release_Ref( void )
	{
		NumRefs--;
		if ( NumRefs == 0 )
			Delete_This();
	}

	int NumRefs;
};

typedef bool (*BoolForward)( void *, float );

unsigned char Rva00739900Forward( register void *object, float value )
{
	RenderObjClass *robj = (RenderObjClass *)object;
	if ( !robj )
		return false;

	register unsigned char result = 0;
	MaterialInfoClass *minfo = robj->Get_Material_Info();
	if ( minfo )
	{
		for ( int i = 0; i < minfo->Vertex_Material_Count(); i++ )
		{
			VertexMaterialClass *mat = minfo->Get_Vertex_Material( i );
			if ( mat )
			{
				mat->Set_Opacity( value );
				mat->Release_Ref();
				result = 1;
			}
		}
		minfo->Release_Ref();
		return result;
	}

	int count = robj->Get_Num_Sub_Objects();
	for ( int i = 0; i < count; i++ )
	{
		RenderObjClass *sub = robj->Get_Sub_Object( i );
		const bool child = ((BoolForward)Rva00739900Forward)( sub, value );
		if ( result || child )
			result = 1;
		if ( sub )
			sub->Release_Ref();
	}
	return result;
}
