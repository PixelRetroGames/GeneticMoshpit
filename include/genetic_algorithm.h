#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include "..\include\individual.h"

class Genetic_algorithm
{
 private:
 std::vector<Individual> population;
 int generation=1;

 public:
 Genetic_algorithm(int size_population);
 ~Genetic_algorithm();
 void Simulate();
 void Breed();

 void Save_generation();
};

int *Get_random_genome();

int Get_rating(int gen);

#endif // GENETIC_ALGORITHM_H
