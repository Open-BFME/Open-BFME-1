// cl: /GS
//
// Retail 0x007F1220 writes the FESL blob result fields and its attribute list.
// The literal field keys and the six stack arguments identify this as a blob
// writer, but the original class and method name are not present in the tree.

#include <stdio.h>

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	void reset();
	void addString(const char *key, const char *value);
	void addInt(const char *key, int value);
	void addInt64(const char *key, FeslInt64 value);
	char m_pad00[0x1c];
	unsigned int m_category;
};

class BfmeThingCIC
{
public:
	void bfmeGoCIC(void *key, void *value);
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *key, void *value);
};

class BfmeMsgVIX
{
};

class BfmeThingVIY
{
public:
	void bfmeSubVIY(BfmeMsgVIX *message, void *content, void *size);
};

struct Rva007F1220Owner
{
	FeslInt64 owner;
	int ownerType;
};

struct Rva007F1220Attribute
{
	const char *type;
	const char *name;
};

struct Rva007F1220Record
{
	int formatType;
	int unused04;
	FeslInt64 iconId;
	const char *creator;
	const char *name;
	const char *version;
	const char *shortDescription;
	const char *longDescription;
	const char *locale;
	Rva007F1220Attribute *attributes;
	int downloadCount;
};

#define g_Rva0130A5D0 (*(void **)0x0130A5D0)

class Rva007F1220BlobWriter
{
public:
	void write(Rva007E8810Message *message,
		const Rva007F1220Owner *owner,
		int iconId,
		void *content,
		void *contentSize,
		const Rva007F1220Record *record);
};

void Rva007F1220BlobWriter::write(Rva007E8810Message *message,
	const Rva007F1220Owner *owner,
	int iconId,
	void *content,
	void *contentSize,
	const Rva007F1220Record *record)
{
	const char *txn = *(const char **)0x0130A5D0;
	message->reset();
	message->m_category = 'blob';
	message->addString("TXN", txn);
	message->addInt64("ownerId", owner->owner);
	message->addInt("ownerType", owner->ownerType);
	message->addInt("type", iconId);
	message->addInt("formatType", record->formatType);
	message->addInt64("iconId", record->iconId);
	message->addString("creator", record->creator);
	message->addString("name", record->name);
	message->addString("version", record->version);
	message->addString("shortDescription", record->shortDescription);
	message->addString("longDescription", record->longDescription);
	message->addString("locale", record->locale);
	((BfmeThingVIY *)this)->bfmeSubVIY((BfmeMsgVIX *)message, content, contentSize);
	message->addInt("attributes.[]", record->downloadCount);

	unsigned int index = 0;
	if ((unsigned int)record->downloadCount <= 0)
		goto attributes_done;
	attributes_loop:
	{
		char key[64] = { 0 };
		sprintf(key, "attributes.%d.name", index);
		message->addString(key, record->attributes[index].type);
		sprintf(key, "attributes.%d.type", index);
		message->addInt(key, 0);
		sprintf(key, "attributes.%d.value", index);
		message->addString(key, record->attributes[index].name);
	}
	++index;
	if (index < (unsigned int)record->downloadCount)
		goto attributes_loop;
	attributes_done:;
}
