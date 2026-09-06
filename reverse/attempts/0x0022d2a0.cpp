// ?d_0022d2a0@@YAXXZ
// partial score=0.98 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: TransportContain::createPayload, retail 0x0022D2A0.

typedef bool Bool;

extern const char g_bfmeEmptyAscii[];

class AsciiString
{
public:
	const char *str() const
	{
		const char *data = m_data;
		return data ? data + 8 : g_bfmeEmptyAscii;
	}

	const char *m_data;
};

class ThingTemplate;
class Object;

class ThingFactory
{
};

class BFMEThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

#define CONTAIN_SLOT(n) virtual void containSlot##n();

class ContainModuleInterface
{
public:
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
	CONTAIN_SLOT(28) CONTAIN_SLOT(29) CONTAIN_SLOT(30) CONTAIN_SLOT(31)
	CONTAIN_SLOT(32) CONTAIN_SLOT(33) CONTAIN_SLOT(34) CONTAIN_SLOT(35)
	CONTAIN_SLOT(36) CONTAIN_SLOT(37) CONTAIN_SLOT(38) CONTAIN_SLOT(39)
	CONTAIN_SLOT(40) CONTAIN_SLOT(41) CONTAIN_SLOT(42) CONTAIN_SLOT(43)
	CONTAIN_SLOT(44) CONTAIN_SLOT(45) CONTAIN_SLOT(46) CONTAIN_SLOT(47)
	CONTAIN_SLOT(48) CONTAIN_SLOT(49) CONTAIN_SLOT(50) CONTAIN_SLOT(51)
	CONTAIN_SLOT(52) CONTAIN_SLOT(53) CONTAIN_SLOT(54) CONTAIN_SLOT(55)
	CONTAIN_SLOT(56) CONTAIN_SLOT(57) CONTAIN_SLOT(58) CONTAIN_SLOT(59)
	CONTAIN_SLOT(60) CONTAIN_SLOT(61) CONTAIN_SLOT(62) CONTAIN_SLOT(63)
	CONTAIN_SLOT(64) CONTAIN_SLOT(65) CONTAIN_SLOT(66) CONTAIN_SLOT(67)
	CONTAIN_SLOT(68) CONTAIN_SLOT(69) CONTAIN_SLOT(70) CONTAIN_SLOT(71)
	CONTAIN_SLOT(72) CONTAIN_SLOT(73) CONTAIN_SLOT(74) CONTAIN_SLOT(75)
	CONTAIN_SLOT(76) CONTAIN_SLOT(77)
	virtual void enableLoadSounds(Bool enable);
};

#undef CONTAIN_SLOT

class PayloadCreatorInterface
{
public:
	virtual void createPayload(const ThingTemplate *payloadTemplate,
		ContainModuleInterface *contain, Object *object, const char *name,
		Bool initialPayload);
};

struct InitialPayloadNode
{
	InitialPayloadNode *m_next;
	InitialPayloadNode *m_prev;
	AsciiString m_name;
	int m_count;
};

class TransportContainModuleData
{
public:
	unsigned char m_pad[0x174];
	InitialPayloadNode *m_initialPayload;
};

class TransportContain
{
protected:
	virtual void createPayload();
};

void TransportContain::createPayload()
{
	TransportContain *self = this;
	TransportContainModuleData *moduleData = *(TransportContainModuleData **)((char *)self + 4);
	InitialPayloadNode *node = moduleData->m_initialPayload->m_next;
	InitialPayloadNode *end = moduleData->m_initialPayload;

	if (node != end)
	{
		do
		{
			AsciiString *payloadName = &node->m_name;
			int count = node->m_count;
			if (count <= 0)
				return;

			const ThingTemplate *payloadTemplate =
				((BFMEThingFactory *)TheThingFactory)->findTemplate(*payloadName);
			if (payloadTemplate == 0)
				return;

			Object *object = *(Object **)((char *)self + 8);
			if (object == 0)
				return;

			ContainModuleInterface *contain = *(ContainModuleInterface **)((char *)object + 0x1fc);
			if (contain != 0)
			{
				contain->enableLoadSounds(false);
				for (int i = 0; i < count; ++i)
				{
					const char *name = payloadName->str();
					((PayloadCreatorInterface *)((char *)self + 0xd4))->createPayload(
						payloadTemplate, contain, object, name, true);
				}
				contain->enableLoadSounds(true);
			}
			node = *(InitialPayloadNode **)((char *)node);
		} while (node != moduleData->m_initialPayload);
	}
}
