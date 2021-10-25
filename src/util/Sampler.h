#pragma once

#include <cassert>
#include <vector>

// could probably be put inside Sampler class since Sample shouldnt be used elsewhere
template<typename T>
struct Sample
{
	const T value;
	const int count;
};

template<typename T>
class Sampler
{
private:
	std::vector<Sample<T>> samples;
	bool sizeUpToDate{ true };
	int size{};

public:
	Sampler(const std::initializer_list<Sample<T>> samples)
		:
		samples{ samples }
	{}

	const std::vector<Sample<T>>& getVector() const
	{
		return samples;
	}
	std::vector<Sample<T>>& getVector()
	{
		sizeUpToDate = false;
		return samples;
	}

	const int getSize()
	{
		size = 0;

		for (const Sample<T>& sample : samples)
			size += sample.count;

		sizeUpToDate = true;
		return size;
	}

	const T& devectorizeSample(const float noise)
	{
		if (!sizeUpToDate)
			size = getSize();

		const int uncompressedIndex{ static_cast<int>(noise * size) };

		assert(uncompressedIndex >= 0);

		int uncompressedCounter{};

		for (int i = 0; i < samples.size(); ++i)
		{
			if (uncompressedCounter + samples[i].count >= uncompressedIndex)
				return samples[i].value;

			uncompressedCounter += samples[i].count;
		}

		return samples[samples.size()].value;
	}
};