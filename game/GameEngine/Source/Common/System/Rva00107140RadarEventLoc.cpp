// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME retail 0x00107140 (203 bytes): Radar method called from
// CommandTranslator::translateGameMessage (retail call 0x5b019a) exactly where
// the Zero Hour twin calls Radar::getLastEventLoc before
// TheTacticalView->lookAt.  BFME grew the body: it cycles backwards through
// the event ring from the cursor at +0x1430 while the last jump at +0x1434 is
// under 60 client frames old.  The method keeps the caller's address-derived
// pin until the renamed identity is settled.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// Spelled as the landed caller (CommandXlat.cpp) spells it, so the decorated
// name is the pinned ?rva00107140@Radar@@QAE_NPAVCoord3D@@@Z.
class Coord3D
{
public:
	Real x, y, z;
};

// The retail GameClient vtable's getFrame entry is slot 0x68 (same view as
// Win32Mouse_translateEvent.cpp).
class ClientRoot4120
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual UnsignedInt getFrame();
};

extern ClientRoot4120 *TheGameClient;

// Event layout as RadarXferObjectList.cpp witnesses it (0x50 bytes).
struct RadarEvent
{
	Int type;
	Int dword_4;
	UnsignedInt createFrame;
	Int dword_c[10];
	Coord3D worldLoc;
	Int dword_40[4];
};

class Radar
{
public:
	bool rva00107140(Coord3D *eventPos);

private:
	unsigned char m_pad00[0x28];
	RadarEvent m_event[64];
	Int m_nextFreeRadarEvent;
	Int m_lastRadarEvent;
	Int m_field1430;
	UnsignedInt m_field1434;
};

bool Radar::rva00107140(Coord3D *eventPos)
{
	if (m_lastRadarEvent != -1)
	{
		if (eventPos)
		{
			UnsignedInt now = TheGameClient->getFrame();
			Int cursor = m_field1430;
			if (cursor >= 0 && (Int)(m_field1434 - m_event[m_lastRadarEvent].createFrame) > 0 &&
				(Int)(now - m_field1434) < 60)
			{
				Int index = cursor;
				for (;;)
				{
					if (index > 0)
						--index;
					else
						index = 63;
					if (index == cursor)
						break;
					Int type = m_event[index].type;
					if (type != 6 && type < 11)
						break;
				}
				m_field1430 = index;
			}
			else
				m_field1430 = m_lastRadarEvent;
			*eventPos = m_event[m_field1430].worldLoc;
			m_field1434 = TheGameClient->getFrame();
		}
		return true;
	}
	return false;
}
