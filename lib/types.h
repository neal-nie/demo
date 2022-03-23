/*
 * Copyright (c) 2022-2022 Neal Nie. All rights reserved.
 * Description: this file provid alias for common used types
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef unsigned char uint8;
typedef char sint8;
typedef unsigned short uint16;
typedef short sint16;
typedef unsigned int uint32;
typedef int sint32;
typedef float real32;
typedef double real64;

#define UINT8_MIN 0
#define UINT8_MAX 255

#define SINT8_MIN -128
#define SINT8_MAX 127

#define UINT16_MIN 0
#define UINT16_MAX 65535

#define SINT16_MIN -32768
#define SINT16_MAX 32767

#define UINT32_MIN 0
#define UINT32_MAX 4294967295

#define SINT32_MIN -2147483648
#define SINT32_MAX 2147483647

#endif // !TYPES_H
