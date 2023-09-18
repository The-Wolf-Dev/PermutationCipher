#ifndef PERMUTATIONCIPHER_HPP
#define PERMUTATIONCIPHER_HPP

#include <array>
#include <algorithm>
#include <numeric>
#include <climits>
#include <random>

template<size_t degree>
class PermutationCipher
{
	std::array<size_t, degree> m_perm;

	void removeSpaces(std::string& str)
	{
		auto noSpaceEnd{ std::remove(str.begin(), str.end(), ' ') };
		str.erase(noSpaceEnd, str.end());
	}

	void resize(std::string& str, size_t& charGroupCount)
	{
		++charGroupCount;
		str.resize(charGroupCount * degree);
	}

	void fill(std::string& str, const size_t oldSize)
	{
		std::srand((unsigned)std::time(NULL));
		for (size_t i{ oldSize }, end{ str.size() }; i < end; ++i)
			str[i] = rand() % UCHAR_MAX;
	}

public:
	PermutationCipher()
		: m_perm{}
	{
		std::iota(m_perm.begin(), m_perm.end(), 0);
		
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(m_perm.begin(), m_perm.end(), g);
	}

	void encode(std::string& str)
	{
		removeSpaces(str);

		// fill with random symbols if needed
		auto size{ str.size() };
		size_t charGroupCount{ size / degree };
		if (size % degree != 0)
		{
			resize(str, charGroupCount);
			fill(str, size);
		}

		std::string encodedStr{ str };
		for (size_t i{}; i < charGroupCount; ++i)
		{
			auto firstElemIndx{ i * degree };
			for (size_t j{}; j < degree; ++j)
			{
				encodedStr[firstElemIndx + m_perm[j]] = str[firstElemIndx + j];
			}
		}
		str = encodedStr;
	}

	void decode(std::string& str)
	{
		std::string decodedStr{ str };
		size_t charGroupCount{ str.size() / degree };
		for (size_t i{}; i < charGroupCount; ++i)
		{
			auto firstElemIndx{ i * degree };
			for (size_t j{}; j < degree; ++j)
			{
				decodedStr[firstElemIndx + j] = str[firstElemIndx + m_perm[j]];
			}
		}
		str = decodedStr;
	}
};

#endif // PERMUTATIONCIPHER_HPP