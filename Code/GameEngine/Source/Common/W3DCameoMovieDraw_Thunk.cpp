// cl: /DNDEBUG /MD /EHs-c-
// Lift the W3DCameoMovieDraw window callback to clean C++.
//
// Ask the global at 0x012F148C for the current movie image through its virtual
// at +0x148 and do nothing when there is none. Otherwise take the window's
// screen position and size and draw the image across that rectangle.
//
// The rectangle edges are converted from Int to Real with fild at the call, and
// the far corner is computed in integers BEFORE the conversion, not after.
// The trailing -1 is pushed first, so it is the last argument.
//
// Position and size are ICoord2D pairs rather than four loose Ints: the pairs
// have to be adjacent in the frame and in this order, and separate locals leave
// that to the allocator, which places them the other way round.

typedef int Int;
typedef float Real;

class Image;
class WinInstanceData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);			///< ILT thunk at 0x0002F94B
	Int winGetSize(Int *width, Int *height);			///< ILT thunk at 0x00036EBC
};

class MovieSourceShim
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void unused62();
	virtual void unused63();
	virtual void unused64();
	virtual void unused65();
	virtual void unused66();
	virtual void unused67();
	virtual void unused68();
	virtual void unused69();
	virtual void unused70();
	virtual void unused71();
	virtual void unused72();
	virtual void unused73();
	virtual void unused74();
	virtual void unused75();
	virtual void unused76();
	virtual void unused77();
	virtual void unused78();
	virtual void unused79();
	virtual void unused80();
	virtual void unused81();
	virtual Image *getCurrentMovieImage(void);			///< vtable +0x148
};

class DisplayShim
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void drawImage(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);	///< vtable +0xE0
};

extern MovieSourceShim *TheMovieSourceShim;				///< retail [0x012F148C]
extern DisplayShim *TheDisplayShim;						///< retail [0x012F1270]

// ?W3DCameoMovieDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DCameoMovieDraw(GameWindow *window, WinInstanceData *instData)
{
	Image *image = TheMovieSourceShim->getCurrentMovieImage();
	if (!image)
		return;

	ICoord2D origin, size;
	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	TheDisplayShim->drawImage(image,
		(Real)origin.x, (Real)origin.y,
		(Real)(origin.x + size.x), (Real)(origin.y + size.y), -1);
}
