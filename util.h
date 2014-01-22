#ifndef XECC_UTIL_H
#define XECC_UTIL_H

bool Util_IsLittleEndian();

bool Util_ModExponent(const unsigned int uiBase, const unsigned int uiExp, const unsigned int uiMod, unsigned int* const puiRes);

#endif
