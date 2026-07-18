#pragma once

#ifndef __CollideModule_H_
#define __CollideModule_H_

#include "Common/Module.h"
#include "GameLogic/Module/BehaviorModule.h"

class CollideModuleInterface
{
public:
	virtual void onCollide( Object *other, const Coord3D *loc, const Coord3D *normal ) = 0;
	virtual Bool wouldLikeToCollideWith(const Object* other) const = 0;
	virtual Bool isHijackedVehicleCrateCollide() const = 0;
	virtual Bool isSabotageBuildingCrateCollide() const = 0;
	virtual Bool isCarBombCrateCollide() const = 0;
	virtual Bool isRailroad() const = 0;
	virtual Bool isSalvageCrateCollide() const = 0;
};

class CollideModuleData : public BehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse& p)
	{
		BehaviorModuleData::buildFieldParse(p);
	}
};

class RetailCollideModuleDataBase : public ModuleData
{
public:
	RetailCollideModuleDataBase();
	static void buildFieldParse(MultiIniFieldParse& p)
	{
		BehaviorModuleData::buildFieldParse(p);
	}

private:
	char m_bfmeLayoutPadding[ 0x5C ];
};

class RetailCollideModuleData : public RetailCollideModuleDataBase
{
public:
	RetailCollideModuleData()
	{
	}
};

class CollideModule : public BehaviorModule, public CollideModuleInterface
{
	MEMORY_POOL_GLUE_ABC( CollideModule )
	MAKE_STANDARD_MODULE_MACRO_ABC( CollideModule )
	MAKE_STANDARD_MODULE_DATA_MACRO_ABC(CollideModule, RetailCollideModuleData)

public:
	CollideModule( Thing *thing, const ModuleData* moduleData );
	static Int getInterfaceMask() { return MODULEINTERFACE_COLLIDE; }
	virtual CollideModuleInterface* getCollide() { return this; }
	virtual void onCollide( Object *other, const Coord3D *loc, const Coord3D *normal ) = 0;
	virtual Bool wouldLikeToCollideWith(const Object* other) const { return false; }
	virtual Bool isHijackedVehicleCrateCollide() const { return false; }
	virtual Bool isSabotageBuildingCrateCollide() const { return false; }
	virtual Bool isCarBombCrateCollide() const { return false; }
	virtual Bool isRailroad() const { return false; }
	virtual Bool isSalvageCrateCollide() const { return false; }
};

inline CollideModule::CollideModule( Thing *thing, const ModuleData* moduleData ) :
	BehaviorModule( thing, moduleData )
{
}

inline CollideModule::~CollideModule()
{
}

#endif
