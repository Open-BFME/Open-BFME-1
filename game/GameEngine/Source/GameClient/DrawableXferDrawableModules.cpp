// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib
// Drawable::xferDrawableModules (RVA 0x00417E20, 530 bytes through RET 4).
//
// Identity: the matched Drawable::xfer at 0x0041D290 (DrawableXfer.cpp) calls
// this body twice through its ILT under this name, and the body is the Zero
// Hour Drawable::xferDrawableModules: version 1, three module types, the
// "DrawableModule" block literal, keyToName on save and nameToKey on load.
//
// The retail BFME Xfer interface differs from the Zero Hour header.  Its slots
// are proven by this body's calls: IsStoring +0x08, beginBlock +0x14,
// endBlock +0x18, skipBlock +0x1c, xferVersion +0x28, xferSnapshot +0x30,
// xferAsciiString +0x68 and xferUnsignedShort +0x7c (the block names match
// game/Libraries/Source/xfer/xfer_load.cpp).  BFME replaced Zero Hour's
// skip(dataSize) with skipBlock("DrawableModule") on a missing module.  The
// declarations below are a TU-local ABI view, not a new Xfer identity.

#include "Common/AsciiString.h"

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef bool Bool;

// BFME's two-byte version record (Xfer::Version in xfer.h, one pointer to
// slot +0x28).  This body stores 1 into both bytes; initialising them in a
// constructor keeps retail's stack-slot order (plain assignments rotate it).
struct XferVersion
{
	XferVersion(UnsignedByte version) { data[0] = version; data[1] = version; }
	UnsignedByte data[2];
};

class Module;

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool IsStoring() const;
	virtual void slot03();
	virtual void slot04();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(Module *module);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(AsciiString *value);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void xferUnsignedShort(UnsignedShort *value);
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEYTYPE_FORCE_LONG = 0x7fffffff
};

// ModuleData's tag key is at +0x04 and BFME's Module keeps m_moduleData at
// +0x04 (Snapshot is its only polymorphic prefix); both are read by this body.
// Keep Zero Hour's two inline accessor layers, getModuleData() and
// getModuleTagNameKey(): folding them into one direct member read changes
// VC7.1's register choice for the keyToName return buffer and the load-path
// search (24 non-relocation bytes).
class ModuleData
{
public:
	NameKeyType getModuleTagNameKey() const { return m_moduleTagNameKey; }

private:
	void *m_vtable;
	NameKeyType m_moduleTagNameKey;
};

class Module
{
public:
	const ModuleData *getModuleData() const { return m_moduleData; }
	NameKeyType getModuleTagNameKey() const { return getModuleData()->getModuleTagNameKey(); }

private:
	void *m_vtable;
	const ModuleData *m_moduleData;
};

class NameKeyGenerator
{
public:
	AsciiString keyToName(NameKeyType key);
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// m_modules is Zero Hour's per-module-type list array; this body indexes it
// at this+0x150 with the module type.
class Drawable
{
protected:
	void xferDrawableModules(Xfer *xfer);

private:
	unsigned char m_opaque[0x150];
	Module **m_modules[3];
};

void Drawable::xferDrawableModules(Xfer *xfer)
{
	{
		XferVersion version(1);
		xfer->xferVersion(&version);
	}
	xfer->IsStoring();

	UnsignedShort moduleTypes = 3;
	xfer->xferUnsignedShort(&moduleTypes);

	AsciiString moduleIdentifier;
	for (UnsignedShort curModuleType = 0; curModuleType < moduleTypes; ++curModuleType)
	{
		Module **m;
		UnsignedShort moduleCount = 0;
		for (m = m_modules[curModuleType]; m && *m; ++m)
			++moduleCount;
		xfer->xferUnsignedShort(&moduleCount);

		if (xfer->IsStoring())
		{
			for (m = m_modules[curModuleType]; m && *m; ++m)
			{
				moduleIdentifier = TheNameKeyGenerator->keyToName((*m)->getModuleTagNameKey());
				xfer->xferAsciiString(&moduleIdentifier);
				xfer->beginBlock("DrawableModule");
				xfer->xferSnapshot(*m);
				xfer->endBlock();
			}
		}
		else
		{
			for (UnsignedShort j = 0; j < moduleCount; ++j)
			{
				xfer->xferAsciiString(&moduleIdentifier);
				NameKeyType moduleIdentifierKey = TheNameKeyGenerator->nameToKey(moduleIdentifier.str());

				Module *module = 0;
				for (Module **m = m_modules[curModuleType]; m && *m; ++m)
				{
					if (moduleIdentifierKey == (*m)->getModuleTagNameKey())
					{
						module = *m;
						break;
					}
				}

				if (module == 0)
				{
					xfer->skipBlock("DrawableModule");
				}
				else
				{
					xfer->beginBlock("DrawableModule");
					xfer->xferSnapshot(module);
					xfer->endBlock();
				}
			}
		}
	}
}
