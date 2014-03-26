#ifndef XECC_BIGNUM_H
#define XECC_BIGNUM_H

#include "ECCType.h"
#include <vector>

#define	BIGNUM_SUPPORT_PRINT //support print all the elements
#ifdef BIGNUM_SUPPORT_PRINT
#include <iostream>
#include <iomanip>
#endif

#define BIGNUM_DEF_INITSIZE	256

class BigNum
{
private:
	std::vector<u8> m_vData;
public:
	BigNum();
	BigNum(const BigNum& bn);
	BigNum(const u8* const pbContent, const u32 uiContentSize);
	~BigNum();

	u32 getSize();
#ifdef BIGNUM_SUPPORT_PRINT
	bool printContent();
#endif

	u8 operator [](u32 idx) const;
	
	BigNum& operator ++();
	BigNum operator ++(int);//too slow, not recommanded
	
	BigNum& operator --();
	BigNum operator --(int);//too slow, not recommanded
	
	friend BigNum operator + (BigNum& bn1, BigNum& bn2);//too slow, not recommanded
	friend BigNum operator - (BigNum& bn1, BigNum& bn2);//too slow, not recommanded
	friend BigNum operator * (BigNum& bn1, BigNum& bn2);//too slow, not recommanded
	friend BigNum operator / (BigNum& bn1, BigNum& bn2);//too slow, not recommanded
	friend BigNum operator % (BigNum& bn1, BigNum& bn2);//too slow, not recommanded
	friend BigNum operator ^ (BigNum& bn1, BigNum& bn2);//too slow, not recommanded
	
	BigNum& operator = (BigNum& bn);
	friend BigNum& operator += (BigNum& bn1, BigNum& bn2);
	friend BigNum& operator -= (BigNum& bn1, BigNum& bn2);
	friend BigNum& operator *= (BigNum& bn1, BigNum& bn2);
	friend BigNum& operator /= (BigNum& bn1, BigNum& bn2);
	friend BigNum& operator %= (BigNum& bn1, BigNum& bn2);
	friend BigNum& operator ^= (BigNum& bn1, BigNum& bn2);
};

#endif
