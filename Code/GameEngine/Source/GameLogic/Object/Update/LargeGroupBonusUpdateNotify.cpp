// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00297820: LargeGroupBonusUpdate helper sitting between the
// constructor at 0x00297640 and destructor at 0x00297930. Walks a 4-byte
// vector at module-data +0x20/+0x24 and invokes a sink from object vtable
// slot +0x28.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	char *m_data;
};

class S4Sink004135C0
{
public:
	void invoke(const AsciiString &name, int a, int b, int c, int d);
	void finish();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual S4Sink004135C0 *getSink();
};

class LargeGroupBonusUpdateModuleData
{
private:
	unsigned char m_pad00[0x20];

public:
	AsciiString *m_begin;
	AsciiString *m_end;
};

class LargeGroupBonusUpdate
{
public:
	void notify(int value);

private:
	void *m_vtable;
	const LargeGroupBonusUpdateModuleData *m_moduleData;
	Object *m_object;
};

// ?notify@LargeGroupBonusUpdate@@QAEXH@Z
void LargeGroupBonusUpdate::notify(int value)
{
	const LargeGroupBonusUpdateModuleData *data = m_moduleData;
	if (data->m_begin == data->m_end)
		return;
	S4Sink004135C0 *sink = m_object->getSink();
	if (!sink)
		return;
	if (!m_object)
		return;
	AsciiString *it = data->m_begin;
	if (it != data->m_end)
	{
		do
		{
			sink->invoke(*it, value, 0, 0, 0);
			it++;
		} while (it != data->m_end);
	}
	sink->finish();
}
