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
	bool m_bPositive;
	std::vector<u8> m_vData;

	bool BN_IsZero() const;
	bool BN_Inc_abs();//absolute increase
	bool BN_Dec_abs();//absolute decrease
	bool BN_Reorganize();//ajust the negative flag and head zeros
	i8 BN_Compare_abs(const BigNum& bn1, const BigNum& bn2) const;//absolute absolute value
	i8 BN_Compare_abs(const BigNum& bn, const u32 uiData) const;//absolute absolute value
	i8 BN_Compare_abs(const u32 uiData, const BigNum& bn) const;//absolute absolute value
	bool BN_IsLittleEndian() const;
	bool BN_ReverseBuffer(u8 *const pbData, const u32 uiDataSize);

public:
	BigNum();
	BigNum(const BigNum& bn);
	BigNum(const u8* const pbContent, const u32 uiContentSize, const bool bPositive = true);
	~BigNum();

	u32 getSize() const;
#ifdef BIGNUM_SUPPORT_PRINT
	bool printContent() const;
#endif

	u8& operator [](u32 idx);//not safe, idx need to be valid
	bool setData(const u8* const pbContent, const u32 uiContentSize, const bool bPositive = true);

	BigNum& operator ++();
	BigNum& operator --();	
	BigNum& operator = (BigNum& bn);
	BigNum& operator += (BigNum& bn);
	BigNum& operator -= (BigNum& bn);
	BigNum& operator *= (BigNum& bn);
	BigNum& operator /= (BigNum& bn);
	BigNum& operator %= (BigNum& bn);
	BigNum& operator ^= (BigNum& bn);
	
	bool operator > (const BigNum& bn) const;
	bool operator >= (const BigNum& bn) const;
	bool operator < (const BigNum& bn) const;
	bool operator <= (const BigNum& bn) const;
	bool operator == (const BigNum& bn) const;
	bool operator != (const BigNum& bn) const;

	bool operator > (const u32 uiData) const;
	bool operator >= (const u32 uiData) const;
	bool operator < (const u32 uiData) const;
	bool operator <= (const u32 uiData) const;
	bool operator == (const u32 uiData) const;
	bool operator != (const u32 uiData) const;


	friend bool BN_Add(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
	friend bool BN_Minus (const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
	friend bool BN_Multi(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
	friend bool BN_Divide(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
	friend bool BN_Mode(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
	friend bool BN_Exp(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
};

#endif
