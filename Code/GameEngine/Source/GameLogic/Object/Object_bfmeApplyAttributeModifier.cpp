// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	unsigned int length() const
	{
		return m_data ? m_data->m_length : 0;
	}

	AsciiStringData *m_data;
};

class AttributeModifierRedirect
{
public:
	virtual void slot000(); virtual void slot001(); virtual void slot002(); virtual void slot003();
	virtual void slot004(); virtual void slot005(); virtual void slot006(); virtual void slot007();
	virtual void slot008(); virtual void slot009(); virtual void slot010(); virtual void slot011();
	virtual void slot012(); virtual void slot013(); virtual void slot014(); virtual void slot015();
	virtual void slot016(); virtual void slot017(); virtual void slot018(); virtual void slot019();
	virtual void slot020(); virtual void slot021(); virtual void slot022(); virtual void slot023();
	virtual void slot024(); virtual void slot025(); virtual void slot026(); virtual void slot027();
	virtual void slot028(); virtual void slot029(); virtual void slot030(); virtual void slot031();
	virtual void slot032(); virtual void slot033(); virtual void slot034(); virtual void slot035();
	virtual void slot036(); virtual void slot037(); virtual void slot038(); virtual void slot039();
	virtual void slot040(); virtual void slot041(); virtual void slot042(); virtual void slot043();
	virtual void slot044(); virtual void slot045(); virtual void slot046(); virtual void slot047();
	virtual void slot048(); virtual void slot049(); virtual void slot050(); virtual void slot051();
	virtual void slot052(); virtual void slot053(); virtual void slot054(); virtual void slot055();
	virtual void slot056(); virtual void slot057(); virtual void slot058(); virtual void slot059();
	virtual void slot060(); virtual void slot061(); virtual void slot062(); virtual void slot063();
	virtual void slot064(); virtual void slot065(); virtual void slot066(); virtual void slot067();
	virtual void slot068(); virtual void slot069(); virtual void slot070(); virtual void slot071();
	virtual void slot072(); virtual void slot073(); virtual void slot074(); virtual void slot075();
	virtual void slot076(); virtual void slot077(); virtual void slot078(); virtual void slot079();
	virtual void slot080(); virtual void slot081(); virtual void slot082(); virtual void slot083();
	virtual void slot084(); virtual void slot085(); virtual void slot086(); virtual void slot087();
	virtual void slot088(); virtual void slot089(); virtual void slot090(); virtual void slot091();
	virtual void slot092(); virtual void slot093(); virtual void slot094(); virtual void slot095();
	virtual void slot096(); virtual void slot097(); virtual void slot098(); virtual void slot099();
	virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103();
	virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107();
	virtual void applyAttributeModifier(const AsciiString &name, Bool unknown, int duration);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual AttributeModifierRedirect *getAttributeModifierRedirect();
};

class AttributeModifierPoolUpdate
{
public:
	Bool bfmeApplyAttributeModifier(const AsciiString &name, int duration);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool bfmeApplyAttributeModifier(const AsciiString &name, int duration);

private:
	AttributeModifierPoolUpdate *bfmeFindAttributeModifierPoolUpdate() const;
	unsigned char m_pad000[0x1fc];
	ContainModuleInterface *m_contain;
};

Bool Object::bfmeApplyAttributeModifier(const AsciiString &name, int duration)
{
	if (name.length() == 1)
		return false;

	ContainModuleInterface *contain = m_contain;
	if (contain)
	{
		AttributeModifierRedirect *redirect =
			contain->getAttributeModifierRedirect();
		if (redirect)
		{
			redirect->applyAttributeModifier(name, false, duration);
			return true;
		}
	}

	AttributeModifierPoolUpdate *pool = bfmeFindAttributeModifierPoolUpdate();
	if (pool)
	{
		Bool applied = pool->bfmeApplyAttributeModifier(name, duration);
		return applied ? true : false;
	}
	return false;
}
