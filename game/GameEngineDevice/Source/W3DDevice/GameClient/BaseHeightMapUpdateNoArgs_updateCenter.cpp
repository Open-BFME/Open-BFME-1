// cl: /DNDEBUG /MD /EHsc

// BaseHeightMapUpdateNoArgs::updateCenter, retail 0x00704910.  The road
// update helper's dirty byte is at +0x51 in BFME; BaseHeightMap calls this
// method when its rendered center needs a refresh.

class BaseHeightMapUpdateNoArgs
{
private:
	unsigned char m_unmodelled_00[ 0x51 ];
	unsigned char m_centerNeedsUpdate;

public:
	void updateCenter( void );
};

// ?updateCenter@BaseHeightMapUpdateNoArgs@@QAEXXZ
void BaseHeightMapUpdateNoArgs::updateCenter( void )
{
	m_centerNeedsUpdate = 1;
}
