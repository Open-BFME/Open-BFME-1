// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/shims/dockupdate /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/AIUpdate.h"

// Keep this body in its own TU: the sibling setStatus/enableTurret definitions
// must remain opaque here so MSVC emits retail's this-pointer reloads between
// calls. The BFME module composition comes from the scoped DockUpdate shims;
// retail's Object::m_ai is at +0x204.
UpdateSleepTime BattlePlanUpdate::update()
{
	if( m_invalidSettings )
	{
		return UPDATE_SLEEP_NONE;
	}

	UnsignedInt now = TheGameLogic->getFrame();

	if( m_nextReadyFrame <= now )
	{
		switch( m_status )
		{
			case TRANSITIONSTATUS_IDLE:
				if( m_desiredPlan != PLANSTATUS_NONE )
				{
					m_currentPlan = m_desiredPlan;
					setStatus( TRANSITIONSTATUS_UNPACKING );
				}
				break;
			case TRANSITIONSTATUS_UNPACKING:
				setStatus( TRANSITIONSTATUS_ACTIVE );
				if( m_currentPlan == PLANSTATUS_BOMBARDMENT )
				{
					enableTurret( true );
				}
				break;
			case TRANSITIONSTATUS_ACTIVE:
				if( m_currentPlan != m_desiredPlan )
				{
					if( m_currentPlan == PLANSTATUS_BOMBARDMENT )
					{
						AIUpdateInterface *ai = *reinterpret_cast<AIUpdateInterface **>(
							reinterpret_cast<UnsignedByte *>( getObject() ) + 0x204 );
						if( ai )
						{
							if( isTurretInNaturalPosition() )
							{
								setStatus( TRANSITIONSTATUS_PACKING );
								m_centeringTurret = false;
								enableTurret( false );
							}
							else if( !m_centeringTurret )
							{
								ai->aiIdle( CMD_FROM_AI );
								recenterTurret();
								m_centeringTurret = true;
							}
						}
					}
					else
					{
						setStatus( TRANSITIONSTATUS_PACKING );
					}
				}
				break;
			case TRANSITIONSTATUS_PACKING:
				setStatus( TRANSITIONSTATUS_IDLE );
				break;
		}
	}

	return UPDATE_SLEEP_NONE;
}
