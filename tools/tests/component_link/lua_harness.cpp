/* Test driver for tools/component_link.py lua: EA's Lua 4.0.1 fork, the
   objects the census links, driven through lua.h/lualib.h only. Any symbol
   defined here that the component needs is a TEST DOUBLE and is listed in
   component_link.py's COMPONENTS["lua"]["doubles"]; the script reports each. */
#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lualib.h"

static int failures;

static void check(int ok, const char *what)
{
    printf("%s %s\n", ok ? "PASS" : "FAIL", what);
    if (!ok)
        failures++;
}

static double number(lua_State *L, const char *name)
{
    double value;
    lua_getglobal(L, name);
    value = lua_isnumber(L, -1) ? lua_tonumber(L, -1) : -12345.0;
    lua_pop(L, 1);
    return value;
}

static int string_is(lua_State *L, const char *name, const char *expected)
{
    int same;
    lua_getglobal(L, name);
    same = lua_isstring(L, -1) && strcmp(lua_tostring(L, -1), expected) == 0;
    lua_pop(L, 1);
    return same;
}

static void run(lua_State *L, const char *chunk, const char *what)
{
    int rc = lua_dostring(L, chunk);
    char label[256];
    sprintf(label, "run: %s (lua_dostring -> %d)", what, rc);
    check(rc == 0, label);
}

int main(void)
{
    lua_State *L = lua_open(0);
    check(L != 0, "lua_open");
    lua_baselibopen(L);
    lua_strlibopen(L);
    lua_mathlibopen(L);

    run(L, "x = 1 + 2 * 3 - 8 / 4", "arithmetic");
    check(number(L, "x") == 5.0, "arithmetic result");

    run(L, "function fib(n) if n < 2 then return n end return fib(n - 1) + fib(n - 2) end r = fib(20)",
        "recursion");
    check(number(L, "r") == 6765.0, "fib(20) = 6765");

    run(L, "t = {} for i = 1, 100 do t[i] = i * i end s = 0 for i = 1, getn(t) do s = s + t[i] end",
        "tables and loops");
    check(number(L, "s") == 338350.0, "sum of squares 1..100");

    run(L, "function mk(a) return function(b) return %a + b end end add5 = mk(5) u = add5(10)", "upvalues");
    check(number(L, "u") == 15.0, "closure over an upvalue");

    run(L, "up = strupper('mordor') .. strlen('abc') g = gsub('hello world', 'o', '0') "
           "f = format('%5.2f|%d|%s', 3.14159, 42, 'x') sub = strsub('gandalf', 2, 4)",
        "string library");
    check(string_is(L, "up", "MORDOR3"), "strupper .. strlen");
    check(string_is(L, "g", "hell0 w0rld"), "gsub");
    check(string_is(L, "f", " 3.14|42|x"), "format");
    check(string_is(L, "sub", "and"), "strsub");

    run(L, "m = floor(sqrt(81)) + mod(10, 3) + abs(-2)", "math library");
    check(number(L, "m") == 12.0, "floor(sqrt(81)) + mod(10,3) + abs(-2)");

    /* EA's boolean: comparisons and the true/false keywords. */
    run(L, "if 1 == 1 then c = 1 else c = 2 end if 1 == 2 then d = 1 else d = 2 end "
           "if false then e = 1 else e = 2 end if true then h = 1 else h = 2 end "
           "if not false then k = 1 else k = 2 end",
        "EA boolean tag");
    check(number(L, "c") == 1.0 && number(L, "d") == 2.0, "comparison results branch correctly");
    check(number(L, "e") == 2.0 && number(L, "h") == 1.0 && number(L, "k") == 1.0, "true/false keywords");
    lua_getglobal(L, "d");
    lua_pop(L, 1);
    lua_dostring(L, "bt = (1 == 1)");
    lua_getglobal(L, "bt");
    check(lua_type(L, -1) == 6, "a comparison yields EA's boolean tag 6");
    lua_pop(L, 1);

    run(L, "n = 0 for i = 1, 20000 do local s = 'garbage' .. i n = n + strlen(s) end", "string churn");
    run(L, "collectgarbage()", "collectgarbage");
    check(number(L, "n") > 200000.0, "string churn result");

    check(lua_dostring(L, "x = = 1") != 0, "a syntax error is reported");
    check(lua_dostring(L, "error('boom')") != 0, "a runtime error is reported");
    check(number(L, "x") == 5.0, "state survives the errors");

    lua_close(L);
    printf("%s: %d failure(s)\n", failures ? "FAIL" : "PASS", failures);
    return failures ? 1 : 0;
}
