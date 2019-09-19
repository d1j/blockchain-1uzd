#ifndef HASH_H
#define HASH_H

#include "includes.h"

uint32_t _4byte_string_to_uint32_t(string);

string hash(string);

uint32_t F(uint32_t, uint32_t, uint32_t);

uint32_t G(uint32_t X, uint32_t Y, uint32_t Z);

uint32_t H(uint32_t X, uint32_t Y, uint32_t Z);

#endif