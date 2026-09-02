// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class Thing;
class ModuleData;

class TransitionDamageFXShapePrimary005FEA50
{
public:
	TransitionDamageFXShapePrimary005FEA50( Thing *, const ModuleData * );
	virtual void primarySlot();

private:
	unsigned int m_storage[ 4 ];
};

class TransitionDamageFXShapeInterfaceA005FEA50
{
public:
	virtual void interfaceASlot();
};

class TransitionDamageFXShapeInterfaceB005FEA50
{
public:
	virtual void interfaceBSlot();
};

class TransitionDamageFXShapeMemberBase005FEA50
{
public:
	TransitionDamageFXShapeMemberBase005FEA50();
	virtual void memberBaseSlot();
};

class TransitionDamageFXShapeMember005FEA50
	: public TransitionDamageFXShapeMemberBase005FEA50
{
public:
	TransitionDamageFXShapeMember005FEA50()
		: TransitionDamageFXShapeMemberBase005FEA50() {}
	virtual void memberSlot();
};

class TransitionDamageFXShapeBase005FEA50
	: public TransitionDamageFXShapePrimary005FEA50,
	  public TransitionDamageFXShapeInterfaceA005FEA50,
	  public TransitionDamageFXShapeInterfaceB005FEA50
{
public:
	TransitionDamageFXShapeBase005FEA50( Thing *thing, const ModuleData *moduleData )
		: TransitionDamageFXShapePrimary005FEA50( thing, moduleData ) {}
	virtual void baseShapeSlot();

private:
	TransitionDamageFXShapeMember005FEA50 m_member;
};

class TransitionDamageFXShape005FEA50
	: public TransitionDamageFXShapeBase005FEA50
{
public:
	TransitionDamageFXShape005FEA50( Thing *, const ModuleData * );
	virtual void shapeSlot();
};

TransitionDamageFXShape005FEA50::TransitionDamageFXShape005FEA50(
	Thing *thing, const ModuleData *moduleData )
	: TransitionDamageFXShapeBase005FEA50( thing, moduleData ) {}
