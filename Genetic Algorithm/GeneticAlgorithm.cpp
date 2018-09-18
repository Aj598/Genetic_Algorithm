//Created by Himanshu Mehra on 21-12-2016


#include "GeneticAlgorithm.h"

#include <sstream>
#include <iostream>
#include <random>
#include <iomanip>

const std::string filepath = "C:\\dump\\best.txt";


GeneticAlgorithm::GeneticAlgorithm(void)
{
	// Give it some default parameters
	encoding        = 0;
	numberIterations = 10000;
	bestFitness = infinity;
}


GeneticAlgorithm::~GeneticAlgorithm(void)
{
}


// Initialize parameters, generate population etc
void GeneticAlgorithm::Initialize( const int& epoch,
	                               const int& prec,
								   const int& enc,
								   const int& crate,
								   const int& mrate,
								   const int& psize,
								   const int& iter,
								   const int& csize,
								   const int& tsize,
								   const std::string& path,
								   const Constraint& constr)
{
	SetParameters( enc, crate, mrate, psize, iter, csize, tsize, prec, epoch );
	CreatePopulation();
	SetConstraints(constr);
	log.Open( path.c_str() );
}


// Run the genetic algorithm
void GeneticAlgorithm::Run()
{
	float bx = -1;
	float by = -1;

	for ( int i = 0; i < numberIterations; i++ )
	{
		LogResult( Evaluate(), i );
		Select();
		Crossover();
		Mutate();
	}
}


// Evaulate fitnesses of population chromosomes
double GeneticAlgorithm::Evaluate()
{
	float bx = -1;
	float by = -1;

	double best = pop.EvaluatePopulation( bx, by );

	if ( best < bestFitness )
	{
		bestFitness = best;
		best_x = bx;
		best_y = by;
	}

	return bestFitness;
}


// Apply crossover to selected chromosome pairs
void GeneticAlgorithm::Crossover()
{
	for ( int i = 0; i < populationSize; i++ )
	{
		int r = rand() % 100;

		if ( r < crossoverRate )
		{
			// Select random pair for crossover
			int index1 = rand() % populationSize;
			int index2 = rand() % populationSize;

			while ( index1 == index2 )
			{
				index2 = rand() % populationSize;
			}

			if ( index1 > index2 )
			{
				int tmp = index1;
				index1 = index2;
				index2 = tmp;
			}
			// Get crossover points
			// Point1: 0 - 31
			int point1 = rand() % chromosomeSize;
			int point2 = rand() % chromosomeSize;


			while ( point1 == point2 )
			{
				point2 = rand() % chromosomeSize;
			}

			if ( point1 > point2 )
			{
				int tmp = point1;
				point1 = point2;
				point2 = tmp;
			}

			// Do 1-point crossover
			pop.Crossover( index1, index2, point1, point2 );
		}
	}
}


// Mutate selected chromosomes
void GeneticAlgorithm::Mutate()
{
	for ( int i = 0; i < populationSize; i++ )
	{
		int r = rand() % 100;

		//if ( r < mutationRate )
		{
			pop.Mutation( i, mutationRate );
		}
	}
}


// Select population chromosomes according to fitness
// Using a pairwise tournament selection mechanism
void GeneticAlgorithm::Select()
{
	// For each pair of chromosomes selected
	int i = 0;

	while ( i < tournamentSize )
	{
		// Get the chromosome pair for tournament selection
		int index1 = rand() % populationSize;
		int index2 = rand() % populationSize;

		while ( index1 == index2 )
		{
			index2 = rand() % populationSize;
		}

		double fitness1 = fabs( pop.GetChromosomeFitness( index1 ) );
		double fitness2 = fabs( pop.GetChromosomeFitness( index2 ) );

		// We seek to find [x,y] that minimizes this function
		// The bigget the value returned, the lower its fitness
		if ( fitness1 > fitness2 )
		{
			// Copy chromosome 1 elements into chromosome 2
			pop.CopyChromosome( index2, index1 );
		}
		else
		{
			// Copy chromosome 2 elements into chromosome 1
			pop.CopyChromosome( index1, index2 );
		}

		i++;
	}
}

// Set mutation rate, population size etc
void GeneticAlgorithm::SetParameters( const int& enc,
									  const int& crate,
									  const int& mrate,
									  const int& psize,
									  const int& iter,
									  const int& csize,
									  const int& tsize,
									  const int& prec,
									  const int& ep )
{
	mutationRate = mrate;
	crossoverRate = crate;
	populationSize = psize;
	numberIterations = iter;
	chromosomeSize = csize;
	tournamentSize = tsize;
	precision = prec;
	epoch = ep;
	pop.SetChromosomeEncoding( enc );
}


// Create initial random population of chromosomes
void GeneticAlgorithm::CreatePopulation()
{
	pop.CreateRandomPopulation( populationSize );
}

void GeneticAlgorithm::SetConstraints(const Constraint& constraint)
{
	pop.SetConstraints(constraint);
}


// Log the value to a text file
void GeneticAlgorithm::LogResult( const double& result,
								  const int& iter )
{
	if ( iter % 2000 == 0 )
	{
		std::stringstream ss;
		ss << iter << "\t" << result << "\t" << best_x << "\t" << best_y;
		log.Write( (char*) ss.str().c_str() );
	}

	if ( iter % epoch == 0 || iter < epoch )
	{
		std::cout << "Iteration = " << std::setw(6) << iter
				  << " X = "  << std::fixed << std::setprecision(precision) << std::setw(precision + 1) << best_x
			      << " Y = "  << std::fixed << std::setprecision(precision) << std::setw(precision + 1) << best_y
				  << " F(x,y) = " << std::setw(precision + 1) << bestFitness
		          << std::endl;
	}
}
