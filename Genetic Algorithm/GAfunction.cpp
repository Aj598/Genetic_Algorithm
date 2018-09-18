//Created by Himanshu Mehra on 21-12-2016


#include "Log.h"
#include <sstream>
#include "GeneticAlgorithm.h"
#include<tchar.h>

const int encoding_type   = 1;
const int crossover_rate  = 50;
const int mutation_rate   = 2;
const int population_size = 500;
const int number_iterations = 30000;
const int chromosome_size = 32;
const int tournament_size = population_size / 10;
const int precision = 6;
const int epoch = 30;


int _tmain(int argc, _TCHAR* argv[])
{
	// Run the GA!
	GeneticAlgorithm ga;

	// Set the function and fence type and hence constraints
	Constraint constraint = Constraint::Rosenbrock;

	ga.Initialize( epoch,
		           precision,
				   encoding_type,
		           crossover_rate,
		           mutation_rate,
				   population_size,
				   number_iterations,
				   chromosome_size,
				   tournament_size,
				   "C:\\Users\\Aman\\Desktop\\GAresult.txt",
				   constraint );
	ga.Run();

	return 0;
}

