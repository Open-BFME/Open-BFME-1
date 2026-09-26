// ?bfmeCall929E@@YAXPAXPAPAX@Z
extern "C" char* __cdecl strcpy(char*, const char*);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" int __cdecl sprintf(char*, const char*, ...);
#pragma intrinsic(strcpy, strlen)
struct Rva00892230Name { int m_0; int m_4; char m_chars[1]; };
struct Rva00892230Node { int m_0; int m_4; int m_id; Rva00892230Name* m_name; char m_pad[0x4c - 0x10]; Rva00892230Node* m_parent; };
extern char bfmeFmtDYG[];
void bfmeCall929E(void* nodePtr, void** outPtr)
{
	Rva00892230Node* node = (Rva00892230Node*)nodePtr;
	char** out = (char**)outPtr;
	if (node->m_parent) {
		bfmeCall929E(node->m_parent, outPtr);
		*(*out)++ = '/';
		strcpy(*out, node->m_name->m_chars);
	} else {
		sprintf(*out, bfmeFmtDYG, node->m_id);
	}
	*out += strlen(*out);
}
