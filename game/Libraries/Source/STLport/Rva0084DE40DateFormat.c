// cl: /O2 /MD
// STLport 4.5.3 Win32 locale helper: rewrites a GetLocaleInfoA date picture (dd, MMM, yyyy) as
// a strftime format in a static buffer. Called by _Locale_d_fmt and _Locale_long_d_fmt.

extern char locale_buffer_0084DE40[];

char *Rva0084DE40Tail(char *format)
{
    char *source = format;
    char *destination = locale_buffer_0084DE40;

    while (*source)
    {
        switch (*source)
        {
        case 'd':
            if (source[1] == 'd')
            {
                if (source[2] == 'd')
                {
                    if (source[3] == 'd')
                    {
                        *destination++ = '%';
                        *destination++ = 'A';
                        source += 3;
                    }
                    else
                    {
                        *destination++ = '%';
                        *destination++ = 'a';
                        source += 2;
                    }
                }
                else
                {
                    *destination++ = '%';
                    *destination++ = 'd';
                    ++source;
                }
            }
            else
            {
                *destination++ = '%';
                *destination++ = '#';
                *destination++ = 'd';
            }
            break;

        case 'M':
            if (source[1] == 'M')
            {
                if (source[2] == 'M')
                {
                    if (source[3] == 'M')
                    {
                        *destination++ = '%';
                        *destination++ = 'B';
                        source += 3;
                    }
                    else
                    {
                        *destination++ = '%';
                        *destination++ = 'b';
                        source += 2;
                    }
                }
                else
                {
                    *destination++ = '%';
                    *destination++ = 'm';
                    ++source;
                }
            }
            else
            {
                *destination++ = '%';
                *destination++ = '#';
                *destination++ = 'm';
            }
            break;

        case 'y':
            if (source[1] == 'y')
            {
                if (source[2] == 'y' && source[3] == 'y')
                {
                    *destination++ = '%';
                    *destination++ = 'Y';
                    source += 3;
                }
                else
                {
                    *destination++ = '%';
                    *destination++ = 'y';
                    ++source;
                }
            }
            else
            {
                *destination++ = '%';
                *destination++ = '#';
                *destination++ = 'y';
            }
            break;

        case '%':
            *destination++ = '%';
            *destination++ = '%';
            break;

        case '\'':
            ++source;
            while (*source != '\'')
            {
                if (*source == 0)
                    goto done;
                *destination++ = *source++;
            }
            break;

        default:
            *destination++ = *source;
            break;
        }

        if (*source == 0)
            break;
        ++source;
    }

done:
    *destination = 0;
    return locale_buffer_0084DE40;
}
