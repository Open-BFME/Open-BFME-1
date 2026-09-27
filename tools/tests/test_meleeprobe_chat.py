"""Exercise the payload's actual UTF-16 JSON encoder without a game process."""
import json
import shutil
import subprocess
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]


@pytest.fixture(scope="module")
def encoder(tmp_path_factory):
    compiler = shutil.which("c++")
    if not compiler:
        pytest.skip("native C++ compiler required")
    tmp = tmp_path_factory.mktemp("chat-json")
    source = tmp / "encoder.cpp"
    source.write_text(r'''
#include <cstdio>
#include "chat_json.h"
int main() {
    unsigned short text[1025] = {0};
    unsigned count, value;
    if (scanf("%u", &count) != 1 || count > 1024) return 1;
    for (unsigned i = 0; i < count; ++i) {
        if (scanf("%u", &value) != 1 || value > 65535) return 2;
        text[i] = (unsigned short)value;
    }
    ProbeChatText out;
    escape_chat_text(text, out);
    printf("{\"text\":\"%s\",\"units\":%u,\"truncated\":%u}\n",
           out.text, out.codeUnits, out.truncated);
}
''')
    binary = tmp / "encoder"
    subprocess.run([compiler, "-std=c++98", "-Wall", "-Wextra", "-Werror",
                    "-I", str(ROOT / "mods/features/052-meleeprobe/src"),
                    str(source), "-o", str(binary)], check=True, capture_output=True)
    return binary


@pytest.mark.parametrize("text", [
    "", 'AC succeeded: \"quoted\" \\ slash / %s %n', "line\n\t\r\x01",
    "日本語 😀", "a" * 512, "b" * 513,
])
def test_chat_roundtrip_and_explicit_truncation(encoder, text):
    encoded = text.encode("utf-16-le")
    units = [int.from_bytes(encoded[i:i + 2], "little") for i in range(0, len(encoded), 2)]
    result = subprocess.run([str(encoder)], input=" ".join(map(str, [len(units), *units])),
                            text=True, capture_output=True, check=True)
    record = json.loads(result.stdout)
    assert record == {
        "text": encoded[:1024].decode("utf-16-le", errors="surrogatepass"),
        "units": min(len(units), 512),
        "truncated": int(len(units) > 512),
    }
