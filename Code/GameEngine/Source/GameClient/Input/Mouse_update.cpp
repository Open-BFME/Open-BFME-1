// cl: /DNDEBUG /MD /EHsc
// readable body of ?update@Mouse@@: Code/GameEngine/Source/GameClient/Input/Mouse.cpp

// Mouse::update, retail 0x005A44E0.  The BFME Mouse layout puts the input
// frame counter at +0x4D98; the shared ZH header places it earlier.  This
// translation-unit ABI slice keeps the retail member offset local while the
// body retains the real Mouse behavior: advance the frame and collect input.

class Mouse
{
public:
	virtual void update( void );

private:
	unsigned char m_unmodelled_00[ 0x4D98 - 4 ];
	unsigned int m_inputFrame;

	protected:
	void updateMouseData( void );
};

// ?update@Mouse@@UAEXXZ
void Mouse::update( void )
{
	++m_inputFrame;
	updateMouseData();
}
