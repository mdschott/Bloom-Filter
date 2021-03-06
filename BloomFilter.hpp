/***************************************************************
Michael Schott
BloomFilter.hpp
Program 4
Contains all the necessary functions to implement a BloomFilter.
Implements the MurmurHash3 from the provided code and it is therefore
included into this file. Contains the functions: add, possiblyContains,
hash, and nthHash.
***************************************************************/

#pragma once


#include "MurmurHash3.h"
#include <vector>
#include <array>



class BloomFilter
{

public:
	uint8_t m_numHashes;
	std::vector<bool> m_bits;

	BloomFilter::BloomFilter(uint64_t size, uint8_t numHashes)
		:m_bits(size),
		m_numHashes(numHashes) {}

	std::array<uint64_t, 2> hash(const uint8_t *data, std::size_t len) const
	{
		std::array<uint64_t, 2> hashValue;

		MurmurHash3_x64_128(data, len, 0, hashValue.data());

		return hashValue;
	}

	inline uint64_t nthHash(uint8_t n, uint64_t hashA, uint64_t hashB, uint64_t filterSize) const
	{
		return (hashA + n * hashB) % filterSize;
	}

	void BloomFilter::add(const uint8_t *data, std::size_t len)
	{
		auto hashValues = hash(data, len);

		for (int n = 0; n < m_numHashes; n++) {
			m_bits[nthHash(n, hashValues[0], hashValues[1], m_bits.size())] = true;
		}
	}

	bool BloomFilter::possiblyContains(const uint8_t *data, std::size_t len) const 
	{
		auto hashValues = hash(data, len);

		for (int n = 0; n < m_numHashes; n++) 
		{
			if (!m_bits[nthHash(n, hashValues[0], hashValues[1], m_bits.size())]) 
			{
				return false;
			}
		}

		return true;
	}
};