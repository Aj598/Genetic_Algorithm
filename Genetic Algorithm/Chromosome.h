#pragma once

#include <memory>

class Chromosome
{
public:
	Chromosome(const int& size);
	~Chromosome(void);

	void SetChromosome( const int& index, const unsigned char& value );
	unsigned char GetChromosome( const int& index );
	void SetFitness( const double& value );
	double GetFitness() const;
	int size() const;
	void Print( const int& index ) const;

private:

	std::unique_ptr<int[]> chr;
	double fitness;
	int chrSize;
};

