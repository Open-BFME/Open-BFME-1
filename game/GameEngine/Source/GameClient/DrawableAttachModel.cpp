// ?attachModel@Drawable@@QAEXVAsciiString@@_NH@Z
// The AttachedModelFXNugget caller reaches this body through ILT 0x00042EDD.
// Drawable stores its draw-module list at +0x150, and the attached-model
// interface occupies slot 31 in each module's object-draw interface.

#include "../../../../inputs/reference/shims/stringinline/StringInline.h"

class BfmeAttachedModelInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void attachModel(AsciiString, bool, int);
};

class BfmeDrawModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual BfmeAttachedModelInterface *getObjectDrawInterface();
};

class Drawable
{
public:
	void attachModel(AsciiString, bool, int);

private:
	char m_padding00[0x150];
	BfmeDrawModule **m_drawModules;
};

void Drawable::attachModel(AsciiString modelName, bool randomlyRotate, int expireTimer)
{
	for (BfmeDrawModule **dm = m_drawModules; *dm; ++dm)
	{
		BfmeAttachedModelInterface *interface = (*dm)->getObjectDrawInterface();
		if (interface)
			interface->attachModel(modelName, randomlyRotate, expireTimer);
	}
}
