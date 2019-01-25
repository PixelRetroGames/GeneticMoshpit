#include "../include/genetic_algorithm.h"

int main()
{
 Genetic_algorithm gen(200);
 //gen.Save_generation();

 for(int i=0;i<600;i++)
     {
      gen.Simulate();
      gen.Breed();
      gen.Save_generation();
     }
 return 0;
}
