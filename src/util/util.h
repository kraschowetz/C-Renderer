#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "types.h"
#include "fmath.h"

#define THROW_ERRF(_err, ...) fprintf(stderr, _err, __VA_ARGS__); exit(1)
#define THROW_ERR(_err) fprintf(stderr, _err); exit(1)

#endif
