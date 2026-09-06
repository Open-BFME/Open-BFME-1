// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?setCopiedFromDefault@ThingTemplate@@QAEXXZ: Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp
// Grok promote from masm_dumps — retail 0x0013FDB0 size 71
// was: Code/masm_dumps/ThingTemplate_setCopiedFromDefault.asm

class ThingTemplateSubobjectShim { public: void set(int); };
class ThingTemplate { public: void setCopiedFromDefault(void); };

// ?setCopiedFromDefault@ThingTemplate@@QAEXXZ
void ThingTemplate::setCopiedFromDefault(void)
{
	ThingTemplateSubobjectShim *first = (ThingTemplateSubobjectShim *)((unsigned char *)this + 0x294);
	*(unsigned char *)((unsigned char *)this + 0x489) = 1;
	*(unsigned char *)((unsigned char *)this + 0x48A) = 1;
	first->set(1);
	ThingTemplateSubobjectShim *second = (ThingTemplateSubobjectShim *)((unsigned char *)this + 0x2A0);
	second->set(1);
	ThingTemplateSubobjectShim *third = (ThingTemplateSubobjectShim *)((unsigned char *)this + 0x2AC);
	third->set(1);
	ThingTemplateSubobjectShim *fourth = (ThingTemplateSubobjectShim *)((unsigned char *)this + 0x2B8);
	fourth->set(1);
}

