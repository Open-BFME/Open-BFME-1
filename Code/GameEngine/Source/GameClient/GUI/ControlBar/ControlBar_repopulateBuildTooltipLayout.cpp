// cl: /DNDEBUG /MD /EHsc

// ControlBar::repopulateBuildTooltipLayout, retail 0x004C1920. Two pointers -
// +0x2F4 and +0x278 - both have to be there, and then the work is tail-jumped
// to, so this function is only the guard.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void repopulateBuildTooltipLayout( void );

	void doRepopulateBuildTooltipLayout( void );

private:
	unsigned char m_unmodelled_00[ 0x278 ];
	void *m_unmodelled_278;					// +0x278
	unsigned char m_unmodelled_27C[ 0x2F4 - 0x27C ];
	void *m_unmodelled_2F4;					// +0x2F4
};

// ?repopulateBuildTooltipLayout@ControlBar@@QAEXXZ
void ControlBar::repopulateBuildTooltipLayout( void )
{
	if( m_unmodelled_2F4 == 0 )
		return;

	if( m_unmodelled_278 == 0 )
		return;

	doRepopulateBuildTooltipLayout();
}
