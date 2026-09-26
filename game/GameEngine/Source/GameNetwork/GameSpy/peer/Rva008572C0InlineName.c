// cl: /DNDEBUG /MD

char *Rva008572C0InlineName(void *record)
{
    char *name = (char *)record + 0x60;
    return *name ? name : 0;
}
