#ifndef CRYPTOPP_CBCMAC_H
#define CRYPTOPP_CBCMAC_H

#include "seckey.h"
#include "secblock.h"

NAMESPACE_BEGIN(CryptoPP)

class CRYPTOPP_DLL CBC_MAC_Base : public MessageAuthenticationCode
{
public:
	CBC_MAC_Base() {}

	void CheckedSetKey(void *, Empty empty, const byte *key, unsigned int length, const NameValuePairs &params);
	void Update(const byte *input, unsigned int length);
	void TruncatedFinal(byte *mac, unsigned int size);
	unsigned int DigestSize() const {return const_cast<CBC_MAC_Base*>(this)->AccessCipher().BlockSize();}

protected:
	virtual BlockCipher & AccessCipher() =0;

private:
	void ProcessBuf();
	SecByteBlock m_reg;
	unsigned int m_counter;
};

//! <a href="http://www.weidai.com/scan-mirror/mac.html#CBC-MAC">CBC-MAC</a>
/*! Compatible with FIPS 113. T should be an encryption class.
	Secure only for fixed length messages. For variable length
	messages use DMAC.
*/
template <class T>
class CBC_MAC : public MessageAuthenticationCodeFinalTemplate<CBC_MAC_Base, CBC_MAC<T> >, public SameKeyLengthAs<T>
{
public:
	CBC_MAC() {}
	CBC_MAC(const byte *key, unsigned int length=DEFAULT_KEYLENGTH)
		{SetKey(key, length);}

	static std::string StaticAlgorithmName() {return std::string("CBC-MAC(") + T::StaticAlgorithmName() + ")";}

private:
	BlockCipher & AccessCipher() {return m_cipher;}
	typename T::Encryption m_cipher;
};

NAMESPACE_END

#endif
