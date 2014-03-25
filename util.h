#ifndef XECC_UTIL_H
#define XECC_UTIL_H

#include "ECCType.h"

bool Util_IsLittleEndian();

bool Util_ModExponent(const u32 uiBase, const u32 uiExp, const u32 uiMod, u32* const puiRes);

#endif
