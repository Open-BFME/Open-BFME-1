#pragma once

// EA basetype.h typedef wchar_t WideChar; native compiler must independently prove unsigned-short identity in every consumer.
#include <stddef.h>

typedef wchar_t WideChar;
