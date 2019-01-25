#include "..\include\genetic_algorithm.h"

Genetic_algorithm::Genetic_algorithm(int size_population)
{
 for(int i=0;i<size_population;i++)
     {
      population.push_back(Individual(Get_random_genome(),1));
     }
 generation=1;
}

Genetic_algorithm::~Genetic_algorithm()
{
}

void Genetic_algorithm::Simulate()
{
 std::random_shuffle(population.begin(),population.end());
 int pl=population.size();
 for(int i=0;i<pl/2;i++)
     {
      if(Fight(&population[i],&population[i+1]))
         population.erase(population.begin()+i+1);
      else
         population.erase(population.begin()+i);
     }
}

void Genetic_algorithm::Breed()
{
 std::vector<Individual> new_population;

 std::random_shuffle(population.begin(),population.end());
 for(int i=0;i<population.size();i+=2)
     {
      new_population.push_back(Breed_individuals(&population[i],&population[i+1],Get_rating(generation)));
      new_population.push_back(Breed_individuals(&population[i+1],&population[i],Get_rating(generation)));
     }
 for(int i=0;i<population.size();i++)
     new_population.push_back(population[i]);
 generation++;
 population.clear();
 population=new_population;
}

void reverse(char s[])
{
 int i,j;
 char c;
 for(i=0,j=strlen(s)-1;i<j;i++,j--)
     {
      c=s[i];
      s[i]=s[j];
      s[j]=c;
     }
}

void itoa(int n, char s[])
{
 int i,sign;
 if((sign=n)<0)
     n=-n;
 i=0;
 do
   {
    s[i++]=n%10+'0';
   }
 while((n/=10)>0);
 if(sign<0)
    s[i++]='-';
 s[i]='\0';
 reverse(s);
}

void Genetic_algorithm::Save_generation()
{
 std::string filename;
 char pl[100]={NULL};
 itoa(generation,pl);
 filename="saved/gen";
 filename+=pl;
 filename+=".gen";
 FILE *out=fopen(filename.c_str(),"w");
 printf("%d ",population.size());
 for(int i=0;i<population.size();i++)
     {
      population[i].Print(i,out);
     }
 fclose(out);
}

int *Get_random_genome()
{
 int probabilities[]={20,16,16,16,16,16};
 int *genome;
 genome=new int[6];
 for(int i=0;i<6;i++)
     genome[i]=0;

 for(int j=0;j<100;j++)
     {
      int p=rand()%100;
      for(int i=0,p1=0;i<6;i++,p1+=probabilities[i-1])
          {
           if(p1<=p && p<p1+probabilities[i])
              {
               //printf("%d ",i);
               genome[i]++;
               break;
              }
          }
     }

 return genome;
}

int Get_rating(int gen)
{
 return 1+std::floor(std::log(1.0*gen));
}
