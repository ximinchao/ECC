#ifndef XECC_BIGNUM_H
#define XECC_BIGNUM_H

#include "ECCType.h"
#include <vector>

#define	BIGNUM_SUPPORT_PRINT //support print all the elements
#ifdef BIGNUM_SUPPORT_PRINT
#include <iostream>
#include <iomanip>
#endif

#include <cstring>

#define BIGNUM_DEF_INITSIZE	256

class BigNum
{
private:
	bool m_bPositive;
	std::vector<u8> m_vData;

	bool BN_Inc_abs();//absolute increase
	bool BN_Dec_abs();//absolute decrease
		
	i8 BN_Compare_abs(const BigNum& bn1, const BigNum& bn2) const;//absolute absolute value
	i8 BN_Compare_abs(const BigNum& bn, const u32 uiData) const;//absolute absolute value
	i8 BN_Compare_abs(const u32 uiData, const BigNum& bn) const;//absolute absolute value
	
	bool BN_IsZero() const;
	bool BN_IsLittleEndian() const;
	bool BN_Reorganize();//ajust the head zeros
	bool BN_ReverseBuffer(u8 *const pbData, const u32 uiDataSize) const;

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
	BigNum& operator = (const BigNum& bn);
	BigNum& operator += (const BigNum& bn);
	BigNum& operator -= (const BigNum& bn);
	BigNum& operator *= (const BigNum& bn);
	BigNum& operator /= (const BigNum& bn);
	BigNum& operator %= (const BigNum& bn);
	BigNum& operator ^= (const BigNum& bn);
	
	BigNum& operator = (const i32 iData);
	BigNum& operator += (const i32 iData);
	BigNum& operator -= (const i32 iData);
	BigNum& operator *= (const i32 iData);
	BigNum& operator /= (const i32 iData);
	BigNum& operator %= (const i32 iData);
	BigNum& operator ^= (const i32 iData);
	
	bool operator > (const BigNum& bn) const;
	bool operator >= (const BigNum& bn) const;
	bool operator < (const BigNum& bn) const;
	bool operator <= (const BigNum& bn) const;
	bool operator == (const BigNum& bn) const;
	bool operator != (const BigNum& bn) const;
	
	friend bool BN_Add_abs(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);//absolute add
	friend bool BN_Minus_abs(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);//absolute minus, make sure bn1>bn2
	friend bool BN_Multi_abs(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);//absolute multiply
	friend bool BN_Divide_abs(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);//absolute divide

	friend bool BN_Add(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
	friend bool BN_Minus (const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
	friend bool BN_Multi(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
	friend bool BN_Divide(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
	friend bool BN_Mode(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
	friend bool BN_Exp(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes);
};

#endif
