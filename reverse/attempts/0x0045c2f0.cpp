// ?getScreenCornerWorldPointsAtZ@View@@UAEXPAUCoord3D@@000M@Z
// partial score=0.99 date=2026-09-10
// BFME's View class inserts extra virtuals relative to the ZH layout this TU
// compiles View against: 2 slots before setWidth (matches the Display.cpp
// BFMERetailTacticalViewVTable shim) and 70 more between getOrigin and
// screenToWorldAtZ, independently confirmed by the matched W3DView override at
// 0x00741610 sitting in vtable slot 90 (+0x168). Route these four calls through
// the retail slot shape instead of the ZH-declared one.
class BFMEViewCornerVTable
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void setWidth( Int width ) = 0;             // +0x38
	virtual Int getWidth() = 0;                          // +0x3c
	virtual void setHeight( Int height ) = 0;            // +0x40
	virtual Int getHeight() = 0;                         // +0x44
	virtual void setOrigin( Int x, Int y ) = 0;          // +0x48
	virtual void getOrigin( Int *x, Int *y ) = 0;        // +0x4c
	virtual void gap20() = 0;
	virtual void gap21() = 0;
	virtual void gap22() = 0;
	virtual void gap23() = 0;
	virtual void gap24() = 0;
	virtual void gap25() = 0;
	virtual void gap26() = 0;
	virtual void gap27() = 0;
	virtual void gap28() = 0;
	virtual void gap29() = 0;
	virtual void gap30() = 0;
	virtual void gap31() = 0;
	virtual void gap32() = 0;
	virtual void gap33() = 0;
	virtual void gap34() = 0;
	virtual void gap35() = 0;
	virtual void gap36() = 0;
	virtual void gap37() = 0;
	virtual void gap38() = 0;
	virtual void gap39() = 0;
	virtual void gap40() = 0;
	virtual void gap41() = 0;
	virtual void gap42() = 0;
	virtual void gap43() = 0;
	virtual void gap44() = 0;
	virtual void gap45() = 0;
	virtual void gap46() = 0;
	virtual void gap47() = 0;
	virtual void gap48() = 0;
	virtual void gap49() = 0;
	virtual void gap50() = 0;
	virtual void gap51() = 0;
	virtual void gap52() = 0;
	virtual void gap53() = 0;
	virtual void gap54() = 0;
	virtual void gap55() = 0;
	virtual void gap56() = 0;
	virtual void gap57() = 0;
	virtual void gap58() = 0;
	virtual void gap59() = 0;
	virtual void gap60() = 0;
	virtual void gap61() = 0;
	virtual void gap62() = 0;
	virtual void gap63() = 0;
	virtual void gap64() = 0;
	virtual void gap65() = 0;
	virtual void gap66() = 0;
	virtual void gap67() = 0;
	virtual void gap68() = 0;
	virtual void gap69() = 0;
	virtual void gap70() = 0;
	virtual void gap71() = 0;
	virtual void gap72() = 0;
	virtual void gap73() = 0;
	virtual void gap74() = 0;
	virtual void gap75() = 0;
	virtual void gap76() = 0;
	virtual void gap77() = 0;
	virtual void gap78() = 0;
	virtual void gap79() = 0;
	virtual void gap80() = 0;
	virtual void gap81() = 0;
	virtual void gap82() = 0;
	virtual void gap83() = 0;
	virtual void gap84() = 0;
	virtual void gap85() = 0;
	virtual void gap86() = 0;
	virtual void gap87() = 0;
	virtual void gap88() = 0;
	virtual void gap89() = 0;
	virtual void screenToWorldAtZ( const ICoord2D *screen, Coord3D *world, Real z ) = 0; // +0x168
};

//-------------------------------------------------------------------------------------------------
/** project the 4 corners of this view into the world and return each point as a parameter,
		the world points are at the requested Z */
//-------------------------------------------------------------------------------------------------
// ?getScreenCornerWorldPointsAtZ@View@@UAEXPAUCoord3D@@000M@Z present-unmatched
void View::getScreenCornerWorldPointsAtZ( Coord3D *topLeft, Coord3D *topRight,
																					Coord3D *bottomLeft, Coord3D *bottomRight,
																					Real z )
{
	ICoord2D screenTopLeft, screenTopRight, screenBottomLeft, screenBottomRight;
	ICoord2D origin;
	Int viewWidth = reinterpret_cast<BFMEViewCornerVTable *>( this )->getWidth();
	Int viewHeight = reinterpret_cast<BFMEViewCornerVTable *>( this )->getHeight();

	// sanity
	if( topLeft == NULL || topRight == NULL || bottomLeft == NULL || bottomRight == NULL )
		return;

	// setup the screen coords for the 4 corners of the viewable display
	reinterpret_cast<BFMEViewCornerVTable *>( this )->getOrigin( &origin.x, &origin.y );
	screenTopLeft.x     = origin.x;								// upper left
	screenTopLeft.y     = origin.y;								// upper left
	screenTopRight.x    = origin.x + viewWidth;		// upper right
	screenTopRight.y    = origin.y;								// upper right
	screenBottomLeft.x  = origin.x + viewWidth;		// lower right
	screenBottomLeft.y  = origin.y + viewHeight;  // lower right
	screenBottomRight.x = origin.x;								// lower left
	screenBottomRight.y = origin.y + viewHeight;	// lower left

	// project
	reinterpret_cast<BFMEViewCornerVTable *>( this )->screenToWorldAtZ( &screenTopLeft, topLeft, z );
	reinterpret_cast<BFMEViewCornerVTable *>( this )->screenToWorldAtZ( &screenTopRight, topRight, z );
	reinterpret_cast<BFMEViewCornerVTable *>( this )->screenToWorldAtZ( &screenBottomLeft, bottomLeft, z );
	reinterpret_cast<BFMEViewCornerVTable *>( this )->screenToWorldAtZ( &screenBottomRight, bottomRight, z );

}  // end getScreenCornerWorldPointsAtZ
