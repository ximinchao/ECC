#ifndef XECC_BIGNUM_H
#define XECC_BIGNUM_H

#include "ECCType.h"
#include <vector>

#define BIGNUM_DEF_INITSIZE	256

class BigNum
{
private:
	std::vector<u8> m_vData;
public:
	BigNum();
	BigNum(const BigNum& bn);
	BigNum(const u8* const pbContent);
	~BigNum();

	u32 getSize();

	u8 operator [](u32 idx);
	BigNum operator ++();
	BigNum operator --();
	BigNum operator + (BigNum bn);
	BigNum operator - (BigNum bn);
	BigNum operator * (BigNum bn);
	BigNum operator / (BigNum bn);
	BigNum operator % (BigNum bn);
	BigNum operator ^ (BigNum bn);
	BigNum operator = (BigNum bn);
};

#endif
