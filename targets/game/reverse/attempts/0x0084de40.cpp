// _Rva0084DE40Tail
// partial score=0.78 date=2026-09-27
// cl: /O2 /MD

extern char locale_buffer_0084DE40[];

char *Rva0084DE40Tail(char *format)
{
    char *source = format;
    char *destination = locale_buffer_0084DE40;
    char year;
    year = 'y';

    if (*source != 0)
    {
        for (;;)
        {
            switch (*source)
            {
            case 'd':
            {
                char value;
                if (source[1] == 'd')
                {
                    if (source[2] == 'd')
                    {
                        value = source[3];
                        *destination++ = '%';
                        if (value == 'd')
                        {
                            *destination++ = 'A';
                            source += 3;
                        }
                        else
                        {
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
            }

            case 'M':
            {
                char value;
                if (source[1] == 'M')
                {
                    if (source[2] == 'M')
                    {
                        value = source[3];
                        *destination++ = '%';
                        if (value == 'M')
                        {
                            *destination++ = 'B';
                            source += 3;
                        }
                        else
                        {
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
            }

            case 'y':
                if (source[1] == year)
                {
                    if (source[2] == year)
                    {
                        if (source[3] == year)
                        {
                            *destination++ = '%';
                            *destination++ = 'Y';
                            source += 3;
                        }
                        else
                        {
                            *destination++ = '%';
                            *destination++ = year;
                            ++source;
                        }
                    }
                    else
                    {
                        *destination++ = '%';
                        *destination++ = year;
                        ++source;
                    }
                }
                else
                {
                    *destination++ = '%';
                    *destination++ = '#';
                    *destination++ = year;
                }
                break;

            case '%':
                *destination++ = '%';
                *destination++ = '%';
                break;

            case '\'':
            {
                char value;
                ++source;
                value = *source;
                while (value != '\'')
                {
                    if (value == 0)
                        goto done;
                    *destination++ = value;
                    value = *++source;
                }
                break;
            }

            default:
                *destination++ = *source;
                break;
            }

            if (*source == 0)
                break;
            if (*++source == 0)
                break;
        }
    }

done:
    *destination = 0;
    return locale_buffer_0084DE40;
}
