#pragma once

#include <math.h>
#include <memory>
#include <limits>

const double pi = 3.1415926;

struct Constraint
{
	double maxX, minX, maxY, minY;

    enum Function
    {
        Rosenbrock, Booth, Matya, McCormick, Easom, BukinNo6
    };

    Function _function;
    Constraint(Function f) : _function(f)
	{
		switch (_function)
		{
		case Booth:
		case Matya:
			maxX = 10;
			minX = -10;
			maxY = 10;
			minY = -10;
			break;

		case BukinNo6:
			maxX = -5;
			minX = -15;
			maxY = 3;
			minY = -3;
			break;

		case Easom:
			maxX = 100;
			minX = -100;
			maxY = 100;
			minY = -100;
			break;
		}
	}

	Constraint() : _function(Rosenbrock)
	{
		maxX = std::numeric_limits<double>::max();
		minX = -std::numeric_limits<double>::min();
		maxY = std::numeric_limits<double>::max();
		minY = -std::numeric_limits<double>::min();
	}

    operator Function () const {return _function;}

	double Fitness(const float& x, const float& y)
	{
		double fitness = 0.0;

		switch (_function)
		{
			// Rosenbrock: (1-x)^2  + 100(y-x*x)^2
			// (see http://en.wikipedia.org/wiki/Rosenbrock_function)
			// xover - 50  mtn - 2 pop - 500 sel -  /10
			case Rosenbrock:
				return ( pow( (double)( 1.0 - x ), 2 ) ) +
				     100 * ( pow( (double) ( y - ( x * x ) ), 2 ) ) ;

			// Booth's: (x + 2y - 7)^2 + (2x + y - 5)^2
			// f(1,3) = 0
			// xover - 50  mtn - 2 pop - 500 sel -  /10
			case Booth:
	        fitness = ( pow( (double)(x + 2*y - 7), 2 ) )+
		             ( pow( (double)(2*x + y - 5), 2 ) );
			if ( x > maxX || x < minX || y > maxY || y < minY )
			{
				return fitness * 1.25;
			}
			else
			{
				return fitness;
			}

			// Easom: -cos(x) * cos(y) * exp(-((x-pi)^2 + (y-pi)^2))
			// xover - 30 mtn - 30 pop - 400 sel -  /10
			// needs aggressive use of mutation!
			case Easom:
			fitness = -cos(x) * cos(y) * exp( -1.0 * ( pow((x-pi), 2) + pow((y-pi), 2) ) );
			if ( x > maxX || x < minX || y > maxY || y < minY )
			{
				return fitness * 1.25;
			}
			else
			{
				return fitness;
			}

			// Bukin N. 6
			case BukinNo6:
			fitness = 100.0 * sqrt( fabs(y - 0.01*x*x)  ) + 0.01 * fabs( x + 10.0  );
			if ( x > maxX || x < minX || y > maxY || y < minY )
			{
				return fitness * 1.25;
			}
			else
			{
				return fitness;
			}

			// Matya
			case Matya:
			fitness = 0.26 * ( x * x + y * y ) - ( 0.48 * x * y );
			if ( x > maxX || x < minX || y > maxY || y < minY )
			{
				return fitness * 1.25;
			}
			else
			{
				return fitness;
			}

			//  McCormick
			case McCormick:
			return sin(x+y) + ((x-y)*(x-y)) -  (1.5*x) + (2.5*y) +  1;
		}

		return 0.0;

	}

private:
   //prevent automatic conversion for any other built-in types such as bool, int, etc
   template<typename T>
    operator T () const;
};
