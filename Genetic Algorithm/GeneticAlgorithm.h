#pragma once

#include "Population.h"
#include "Log.h"
#include "Constraints.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(void);
	~GeneticAlgorithm(void);

	void Initialize( const int& epoch,
		             const int& prec,
					 const int& enc,
					 const int& crate,
					 const int& mrate,
					 const int& psize,
					 const int& iter, 
					 const int& csize,
					 const int& tsize,
					 const std::string& path,
					 const Constraint& constr);

	void SetConstraints(const Constraint& constraint);

	void Run();

private:

	void CreatePopulation();
	double Evaluate();
	void Crossover();
	void Mutate();
	void Select();

	void SetParameters( const int& enc,
		                const int& crate,
		                const int& mrate,
						const int& psize,
						const int& iter,
						const int& csize,
						const int& tsize,
						const int& prec,
						const int& epoch );

	void LogResult( const double& result, 
		            const int& iter );

private:
	int encoding;
	int precision;
	int mutationRate;
	int crossoverRate;
	int populationSize;
	int numberIterations;
	int chromosomeSize;
	int tournamentSize;
	int epoch;

	int bestFitnessIndex;
	double bestFitness;
	float best_x;
	float best_y;

	Population pop;
	Log log;
};

