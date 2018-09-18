#pragma once

#include <vector>
#include "Chromosome.h"
#include "Constraints.h"

const double infinity = 9999999999999;

class Population
{
public:

	enum Encoding
	{
		GRAY = 0,
		IEEE_754,
	};

	Population(void);
	~Population(void);

	void SetChromosomeEncoding( const int& type );
	void SetChromosomeSize( const int& size );
	void CreateRandomPopulation( const int& size );

	void Crossover( const int& index1,
		            const int& index2,
					const int& point );

	void Crossover( const int& index1,
		            const int& index2,
					const int& point1,
					const int& point2 );

	void Mutation( const int& index, const int& mutationRate );
	double EvaluatePopulation( float& bx, float& by );
	double CalcChromosomeFitness( const int& index,
								  float& xv,
								  float& yv);

	double GetChromosomeFitness( const int& index ) const;
	void CopyChromosome( const int& source, const int& dest );
	void SetConstraints(const Constraint& constraint);

private:
	Chromosome* CreateRandomChromosome();
	std::string GetXstring( Chromosome* chr );
	std::string GetYstring( Chromosome* chr );
	float GetFloat32_IEEE754( std::string Binary );
	float GetFloat32_Gray( std::string Binary );
	int Binary32ToHex( std::string Binary );
	double CalculateFitnessFunction( const float& x,
		                             const float& y );
	double CalcChromosomeFitness_IEEE754( const int& index,
										  float& xv,
										  float& yv);

	double CalcChromosomeFitnessGray( const int& index,
												  float& xv,
												  float& yv );
	std::string Gray2Bin( std::string gray );
	long Bin2Dec( std::string bin );

private:
	std::vector< Chromosome* > pop;
	int chrSize;
	int encoding;
	Constraint constraintType;
};

