#include "BigNum.h"

BigNum::BigNum()
{
	m_vData.reserve(BIGNUM_DEF_INITSIZE);
}

BigNum::BigNum(const BigNum& bn)
{
	std::copy(bn.m_vData.begin(), bn.m_vData.end(), back_inserter(m_vData));
}

BigNum::BigNum(const u8* const pbContent)
{
}

BigNum::~BigNum()
{
}

u32 BigNum::getSize()
{
	u32	uiDataSize = 0;

	uiDataSize = (u32)m_vData.size();

	return uiDataSize;
}

u8 BigNum::operator [](u32 idx)
{
	u8	ucData = 0;

	if (idx < m_vData.size())
	{
		ucData = m_vData.at(idx);
	}

	return ucData;
}

BigNum BigNum::operator ++()
{
	return *this;
}

BigNum BigNum::operator --()
{
	return *this;
}

BigNum BigNum::operator + (BigNum bn)
{
	return *this;
}

BigNum BigNum::operator - (BigNum bn)
{
	return *this;
}

BigNum BigNum::operator * (BigNum bn)
{
	return *this;
}

BigNum BigNum::operator / (BigNum bn)
{
	return *this;
}

BigNum BigNum::operator % (BigNum bn)
{
	return *this;
}

BigNum BigNum::operator ^ (BigNum bn)
{
	return *this;
}

BigNum BigNum::operator = (BigNum bn)
{
	return *this;
}

