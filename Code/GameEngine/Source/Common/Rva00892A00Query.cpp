// cl: /DNDEBUG /MD /EHs-c-

struct Rva00892A00First
{
    char m_prefix[0x58];
    void *m_value;
};

struct Rva00892A00Root
{
    Rva00892A00First *m_first;
};

struct Rva00892A00Value
{
    char m_prefix[4];
    unsigned flags;
    char m_middle[0x48];
    void *m_output;
};

struct Rva00892A00Output
{
    char m_prefix[0xc];
    void *m_nested;
};

struct Rva00892A00Nested
{
    char m_prefix[0x1c];
    void *m_first;
    void *m_second;
};

struct Rva00892A00Holder
{
    char m_prefix[0x122c];
    Rva00892A00Root *m_root;
};

extern Rva00892A00Holder *g_bfmeHolderBU;

// ?query@Rva00892A00@@YAXPAPAX0@Z
void __cdecl Rva00892A00Query(void **firstResult, void **secondResult)
{
      Rva00892A00Holder *holder = g_bfmeHolderBU;
      if (!holder)
          return;

      Rva00892A00Root *root = holder->m_root;
      Rva00892A00First *first = root->m_first;
      Rva00892A00Value *value = (Rva00892A00Value *)first->m_value;
      if (!value)
          goto fail;
      unsigned flags = value->flags;
      unsigned char highFlag = (unsigned char)(flags >> 15);
      if ((flags & 0x3f) != 0x12 || (((unsigned char)~highFlag) & 1) != 0)
          goto fail;

      Rva00892A00Output *output = (Rva00892A00Output *)value->m_output;
      if (firstResult)
      {
          Rva00892A00Nested *nested = (Rva00892A00Nested *)output->m_nested;
          *firstResult = nested->m_first;
      }
      if (secondResult)
      {
          Rva00892A00Nested *nested = (Rva00892A00Nested *)output->m_nested;
          *secondResult = nested->m_second;
      }
      return;

  fail:
      if (firstResult)
          *firstResult = 0;
      if (secondResult)
          *secondResult = 0;
  }
