#ifndef XECC_BIGNUM_H
#define XECC_BIGNUM_H

#include "ECCType.h"

struct BNListNode
{
	u8 m_ucData;
	BNListNode *prev, *next;
};

class BNList
{
private:
	BNListNode *m_head, *m_end;
	u32 m_size;
public:
	BNList();
	~BNList();

	u32 getSize();
	bool addHead(u8 ucData);
	bool addEnd(u8 ucData);
	
}

class BigNum
{
private:
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
