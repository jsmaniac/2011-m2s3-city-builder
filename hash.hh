#ifndef _HASH_HH_
#define _HASH_HH_

#include "all_includes.hh"

unsigned int hash2(unsigned int a, unsigned int b);
unsigned int hash3(unsigned int seed, int x, int y);
int hashInRange(int seed, int n, int a, int b);
int newSeed(int seed, int n);

#endif