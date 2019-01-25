#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

class Individual
{
 public:
 int genome[6];
 std::vector<int> genome2;
 int rating;
 double hp=0,dmg=0,defense=0,speed=0,crit_rate=0,evasion_rate=0;

 int hp_points=0,dmg_points=0,defense_points=0,speed_points=0,crit_rate_points=0,evasion_rate_points=0;

 public:
 Individual()
 {
 }
 Individual(int *_genome,int _rating);
 void Init_attributes();
 void Print(int pos,FILE *out);
};

bool Fight(Individual *A,Individual *B);

void Attack(Individual *attacker,double *action_points,
            Individual *attacked);

Individual Breed_individuals(Individual *A,Individual *B,int rating);

#endif // INDIVIDUAL_H
