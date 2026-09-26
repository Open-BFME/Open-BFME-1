// ?d_001f7b10@@YAXXZ
// partial score=0.88 date=2026-08-31
// cl: /O2 /Ob1 /G7

#include <algorithm>

class RvaDrawable
{
public:
	void setState( int state );
};

class RvaObject
{
	char m_pad_04[ 0x11C ];

public:
	unsigned int m_modelConditions;
	unsigned char m_status_124;
	char m_pad_125[ 0xDF ];
	void *m_module_204;

	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual RvaDrawable *getDrawable();

	unsigned int *getStatusPtr();
	void notifyModelConditionChanged();
};

class RvaObjectModuleBase
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
	virtual void v88(); virtual void v89(); virtual void v90(); virtual void v91();
	virtual void v92(); virtual void v93(); virtual void v94(); virtual void v95();
	virtual bool check();
};

class RvaModuleData
{
public:
	virtual void moduleDataAnchor();
	int m_tag;
};

class RvaClickReactionBehaviorModuleData : public RvaModuleData
{
public:
	int m_clickTimer;
	int m_reactionFrames[ 5 ];
};

class RvaUpdateModuleRoot
{
public:
	virtual ~RvaUpdateModuleRoot();
	virtual void updateModuleAnchor();

public:
	RvaClickReactionBehaviorModuleData *m_moduleData;
	RvaObject *m_object;

};

class RvaUpdateModuleIface1
{
public:
	virtual void updateModuleIface1();
};

class RvaUpdateModuleIface2
{
public:
	virtual void updateModuleIface2();
};

class RvaUpdateModule : public RvaUpdateModuleRoot,
	public RvaUpdateModuleIface1,
	public RvaUpdateModuleIface2
{
protected:
	int m_nextFrame;
	int m_index;
	int m_phase;
	RvaObject *getObject() const { return m_object; }
	RvaClickReactionBehaviorModuleData *getModuleData() const { return m_moduleData; }
};

class ClickReactionBehavior;

class ClickReactionBehaviorIface
{
public:
	virtual ~ClickReactionBehaviorIface();
	virtual void v0();
	virtual void onClick();
	virtual void update();
	int m_elapsed;
	int m_reactionFrames;
};

class ClickReactionBehavior : public RvaUpdateModule,
	public ClickReactionBehaviorIface
{
public:
	virtual ~ClickReactionBehavior();
	virtual void v0();
};

extern int GetGameLogicRandomValue( int min, int max, char *file, int line );

__forceinline RvaDrawable *getDrawableForClickReaction( RvaObject *object )
{
	return object->getDrawable();
}

void ClickReactionBehaviorIface::onClick()
{
	RvaClickReactionBehaviorModuleData *data;
	RvaObject *object = *(RvaObject **)((char *)this - 0x18);
	if( object == 0 )
		return;
	data = *(RvaClickReactionBehaviorModuleData **)((char *)this - 0x1c);
	RvaDrawable *drawable = getDrawableForClickReaction( object );
	if( drawable == 0 )
		return;
	if( *object->getStatusPtr() & 0x100 )
		return;
	if( object->m_modelConditions & 0x01000000 )
		return;
	if( object->m_status_124 & 4 )
		return;
	RvaObjectModuleBase *module =
		(RvaObjectModuleBase *)object->m_module_204;
	if( module == 0 || !module->check() )
		return;

	int timer = data->m_clickTimer;
	if( timer <= 0 )
		return;
	m_elapsed += timer;
	int max_elapsed = timer * 5;
	m_elapsed = std::min( m_elapsed, max_elapsed );
	if( m_reactionFrames > 0 )
		return;

	int reaction = m_elapsed / timer;
	if( reaction <= 3 )
		reaction = GetGameLogicRandomValue( 1, 3,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\ClickReactionBehavior.cpp",
			0x74 );
	if( reaction <= 0 )
		return;

	int index = reaction - 1;
	unsigned int condition;
	switch( index )
	{
	case 0: condition = 4; break;
	case 1: condition = 8; break;
	case 2: condition = 0x10; break;
	case 3: condition = 0x20; break;
	default: condition = 0x40; break;
	}
	if( ( object->m_modelConditions & condition ) == 0 )
	{
		object->m_modelConditions |= condition;
		object->notifyModelConditionChanged();
	}
	drawable->setState( 0 );
	if( index < 0 || index >= 5 )
		return;
	m_reactionFrames = data->m_reactionFrames[ index ];
}
