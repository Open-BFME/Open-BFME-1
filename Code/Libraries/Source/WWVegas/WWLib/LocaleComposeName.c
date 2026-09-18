// cl: /O2 /MD
// STLport 4.5.3 Win32 _Locale_compose_name.

__declspec(dllimport) int __cdecl strcmp(const char *left, const char *right);
__declspec(dllimport) char *__cdecl strcpy(char *destination, const char *source);
__declspec(dllimport) char *__cdecl strcat(char *destination, const char *source);

char *_Locale_compose_name(
    char *buf,
    const char *ctype,
    const char *numeric,
    const char *time,
    const char *collate,
    const char *monetary,
    const char *messages)
{
    if (!strcmp(ctype, numeric) &&
        !strcmp(ctype, time) &&
        !strcmp(ctype, collate) &&
        !strcmp(ctype, monetary) &&
        !strcmp(ctype, messages))
        return strcpy(buf, ctype);

    strcpy(buf, "LC_CTYPE=");
    strcat(buf, ctype);
    strcat(buf, ";");
    strcat(buf, "LC_TIME=");
    strcat(buf, time);
    strcat(buf, ";");
    strcat(buf, "LC_NUMERIC=");
    strcat(buf, numeric);
    strcat(buf, ";");
    strcat(buf, "LC_COLLATE=");
    strcat(buf, collate);
    strcat(buf, ";");
    strcat(buf, "LC_MONETARY=");
    strcat(buf, monetary);
    strcat(buf, ";");
    strcat(buf, "LC_MESSAGES=");
    strcat(buf, messages);
    strcat(buf, ";");
    return buf;
}
