// ?updateCellsTouched@PartitionData@@AAEXXZ
// partial score=0.35 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// Open-BFME5: PartitionData::updateCellsTouched, retail 0x008F8800,
// 959 bytes.  The body is the private rebuild reached by the canonical
// friend_updateCellsTouched facade at 0x008F8BF0.  The ZH header and source
// supply the method identity and geometry algorithm; the BFME dirty-list
// facade supplies the actual named caller chain.
//
// 2026-09-19 retail-tail audit: this ZH reconstruction emits only 357 bytes
// against BFME's 959-byte body.  BFME does not resume at the canonical
// worldToCell/getCellAt sequence after the fill.  At +0x188 it computes the
// current cell pair with floor((position-origin)*inverseCellSize), compares
// PartitionData+0xB4/+0xB8 and the +0xDC validity byte, then maintains an
// undo-reveal record (+0xBC/+0xC0), two reveal slots (+0xC4..+0xD8), and calls
// the shroud manager helpers at 0x008FA010/0x008FA070/0x008FBCB0.  It finally
// stores the new cell pair, calls the Object interface's cell-change slot,
// clears sixteen dwords at +0x24, and destroys the 0x34-byte local shape.
// The direct caller chain proves this remains PartitionData::updateCellsTouched,
// but name_oracle has no witnesses for the BFME-only +0xB4..+0xDC fields and
// the local-shape builder at 0x0087E190 is still unmatched.  Those layouts and
// signatures must be recovered before adding the missing tail as clean C++.

#include "GameLogic/GhostObject.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"

// ?updateCellsTouched@PartitionData@@AAEXXZ
void PartitionData::updateCellsTouched()
{
	GeometryType geom;
	Bool isSmall;
	Coord3D pos;
	Real angle,majorRadius,minorRadius;


	Object *obj = getObject();
	DEBUG_ASSERTCRASH(obj != NULL || m_ghostObject != NULL, ("must be attached to an Object here 1"));

	if (obj)
	{	
		//we have no object using this PartitionData but we still have a GhostObject so copy its data.
		geom = obj->getGeometryInfo().getGeomType();
		isSmall = obj->getGeometryInfo().getIsSmall();
		pos = *(obj->getPosition());
		angle = obj->getOrientation();
		majorRadius = obj->getGeometryInfo().getMajorRadius();
		minorRadius = obj->getGeometryInfo().getMinorRadius();
	}
	else if (m_ghostObject)
	{
		geom = m_ghostObject->getGeometryType();
		isSmall = m_ghostObject->getGeometrySmall();
		pos = *m_ghostObject->getParentPosition();
		angle = m_ghostObject->getParentAngle();
		majorRadius = m_ghostObject->getGeometryMajorRadius();
		minorRadius = m_ghostObject->getGeometryMinorRadius();
	}

	removeAllTouchedCells();
	if (isSmall)
	{
		doSmallFill(pos.x, pos.y, majorRadius);
	}
	else
	{
		switch(geom)
		{
			case GEOMETRY_SPHERE:
			case GEOMETRY_CYLINDER:
			{
				doCircleFill(pos.x, pos.y, majorRadius);
				break;
			}

			case GEOMETRY_BOX:
			{
				doRectFill(pos.x, pos.y, majorRadius, minorRadius, angle);
				break;
			}
		};
	}

	Int currentCellIndexX, currentCellIndexY;
	ThePartitionManager->worldToCell( pos.x, pos.y, &currentCellIndexX, &currentCellIndexY );
	const PartitionCell *currentCell = ThePartitionManager->getCellAt( currentCellIndexX, currentCellIndexY );
	if(obj && currentCell != m_lastCell )
	{
		// To not expose PartitionCells, he will think in terms of points.  He will
		// unlook at a point and look at the new point.  We do the rounding and the
		// changing into PartitionCells
		obj->onPartitionCellChange();
		m_lastCell = currentCell;
	}

	// if we have moved, our shroudedness status might be different for all players,
	// so it must all be invalidated.
	invalidateShroudedStatusForAllPlayers();

#ifdef INTENSE_DEBUG
	for (Int i = 0; i < m_coiInUseCount; i++)
	{
		for (Int j = 0; j < i; j++)
		{
			if (m_coiArray[i].getCell() == m_coiArray[j].getCell())
			{
				DEBUG_CRASH(("dup cells in COI array, this is bad"));
			}
		}
	}
#endif

}
