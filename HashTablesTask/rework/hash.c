#include "hash.h"
#include <string.h>

uint64_t hash_function(const char* String)
{
    const int p = 53;
    uint64_t hash = 0, p_pow = 1;
    for (const char* i = String; *i; ++i)
    {
        hash += (*i - 'a' + 1) * p_pow;
        p_pow *= p;
    }
    return hash;
}