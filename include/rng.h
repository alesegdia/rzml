#pragma once

#include <random>

namespace aether {
namespace math {

int randi(int min, int max);

int randi(int max);


size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);

class WeightedRandomGenerator
{
public:
	WeightedRandomGenerator()
	{
		m_weights.push_back(1);
	}

	void AddWeight(int index, int weight)
	{
		if (index >= m_weights.size())
		{
			m_weights.resize(index + 1, 0);
		}
		m_weights[index] = weight;
	}

	int GetRandomIndex()
	{
		int total = 0;
		for (int i = 0; i < m_weights.size(); i++)
		{
			total += m_weights[i];
		}
		int random = rand() % total;
		int sum = 0;
		for (int i = 0; i < m_weights.size(); i++)
		{
			sum += m_weights[i];
			if (random < sum)
			{
				return i;
			}
		}
		return 0;
	}

private:
	std::vector<int> m_weights;

};

}
}
