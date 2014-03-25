#ifndef XECC_BIGNUM_H
#define XECC_BIGNUM_H

#include "ECCType.h"

class BigNum
{
public:
	BigNum();
	BigNum(const BigNum& bn);
	BigNum(const u8* const pbContent);
	~BigNum();

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
