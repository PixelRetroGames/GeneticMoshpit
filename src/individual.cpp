#include "../include/individual.h"

Individual::Individual(int *_genome,int _rating)
{
 genome2.resize(100);
 int *attributes[6]={&hp_points,&dmg_points,&defense_points,&speed_points,&crit_rate_points,&evasion_rate_points};
 rating=_rating;
 memcpy(genome,_genome,6*(sizeof (int)));
 for(int r=0;r<rating;r++)
     {
      int p=rand()%100;
      for(int i=0,p1=0;i<6;i++)
          {
           if(p1<=p && p<p1+genome[i])
              {
               (*attributes[i])++;
               break;
              }
           p1+=genome[i];
          }
     }

 for(int i=0,p=0;i<6;i++)
     {
      for(int j=0;j<genome[i];j++)
          genome2[p++]=i;
     }
 std::random_shuffle(genome2.begin(),genome2.end());

 Init_attributes();
}

const int HP_MIN=30;
const int DMG_MIN=5;

void Individual::Init_attributes()
{
 hp=HP_MIN+10*hp_points;
 dmg=DMG_MIN+3*dmg_points;
 defense=15*std::sqrt(1.0*(defense_points+1));
 speed=1.0+0.5*std::sqrt(1.0*speed_points);
 crit_rate=10*std::sqrt(1.0+1.0*crit_rate_points);
 evasion_rate=10*std::sqrt(1.0+1.0*evasion_rate_points);
}

void Individual::Print(int pos,FILE *out)
{
 fprintf(out,"#%d {hp=%d, dmg=%d, def=%d, speed=%d, crit=%d, ev=%d}\n",pos,hp_points,dmg_points,defense_points,speed_points,crit_rate_points,evasion_rate_points);
}

bool Fight(Individual *A,Individual *B)
{
 Individual a=*A;
 Individual b=*B;

 double action_point_a=0,action_point_b=0;
 while(a.hp>0 && b.hp>0)
       {
        action_point_a+=a.speed;
        action_point_b+=b.speed;
        Attack(&a,&action_point_a,&b);
        Attack(&b,&action_point_b,&a);
       }
 return (a.hp>b.hp);
}

void Attack(Individual *attacker,double *action_points,
            Individual *attacked)
{
 while(*action_points>=1)
       {
        (*action_points)-=1;
        int p=rand()%100;
        if(p<attacked->evasion_rate)
           continue;

        int dmg=attacker->dmg*(100.0-attacked->defense)/100.0;
        p=rand()%100;
        if(p<attacker->crit_rate)
           dmg+=dmg/2;

        attacked->hp-=dmg;
       }
}

Individual Breed_individuals(Individual *A,Individual *B,int rating)
{
 int p=rand()%100;
 std::vector<int> genome2(100);

 for(int i=0;i<p;i++)
     genome2[i]=A->genome2[i];
 for(int i=p;i<100;i++)
     genome2[i]=B->genome2[i];

 int genome[6]={0,0,0,0,0,0};
 for(int i=0;i<100;i++)
     genome[genome2[i]]++;
 return Individual(genome,rating);
}
