#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "types.h"
#include "fmath.h"

#define throw_errf(_err, ...) fprintf(stderr, _err, __VA_ARGS__); exit(1)
#define throw_err(_err) fprintf(stderr, _err); exit(1)

#endif
