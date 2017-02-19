//
//  Population.cpp
//  GA
//
//  Created by András Zalavári on 2017. 02. 18..
//
//

#include "TextPopulation.hpp"
#include <cstdlib> //rand, RAND_MAX
#include <math.h> //M_SQRT1_2
#include <iostream>
#include "Statistics.hpp"
#define RANDOM_NUM      ((float)rand()/(RAND_MAX))
using namespace std;

#pragma mark - POPULATION
GA::TextPopulation::TextPopulation(int size){
    for(int i=0; i<size; i++){
        GA::TextCandidate aTextCandidate = GA::TextCandidate();
        members.push_back(aTextCandidate);
    }
}

GA::TextCandidate GA::TextPopulation::best() const{
    GA::TextCandidate _best = members.at(0);
    for(int i=1; i<members.size(); i++)
        if(members.at(i).get_cost()<_best.get_cost())
            _best = members.at(i);
    return _best;
}

float GA::TextPopulation::get_average_cost() const{
    float average=0;
    for (int i=0; i<members.size(); i++) {
        average+=members.at(i).get_cost();
    }
    average/=members.size();
    return average;;
};

float GA::TextPopulation::get_generation() const{
    return generation;
};

std::vector<GA::TextCandidate> GA::TextPopulation::get_members() const{
    return members;
};

bool GA::TextPopulation::evaluate(std::string target){
//    cout<<"calcCosts"<<endl;
    for(int i=0; i<members.size(); i++){
        members.at(i).calcCost(target);
        if(members.at(i).get_cost()==0)
            return true;
    }
    return false;
}

void GA::TextPopulation::evolve(){
    
    /* SELECTION */
    sort(members.begin(), members.end());
    vector<TextCandidate> selection;
    
    int retain_length = (int)members.size()*0.2;
    for (int i=0; i<retain_length; i++) {
        selection.push_back(members.at(i));
    }
    for(int i=retain_length; i<members.size(); i++ ){
        if(RANDOM_NUM<0.05)
            selection.push_back(members.at(i));
    }

    /* BREED */
    float mutation_rate = 0.001;
    float crossover_rate = 0.65;
    vector<GA::TextCandidate> offsprings;
    offsprings.push_back(members.at(0));
    while (offsprings.size()<members.size()){
        vector<GA::TextCandidate> parents = sample(2, selection);
        GA::TextCandidate c1 = parents.at(0);
        GA::TextCandidate c2 = parents.at(1);

        vector<GA::TextCandidate> children;
        if (RANDOM_NUM < crossover_rate) {
            children = GA::TextCandidate::crossover(c1, c2);
            offsprings.push_back(children.at(0));
            offsprings.push_back(children.at(1));
        } else {
            offsprings.push_back(GA::TextCandidate(c1.get_chromosome()));
            offsprings.push_back(GA::TextCandidate(c2.get_chromosome()));
        }
    }

    /* mutate */
    for (int i=0; i<offsprings.size(); i++) {
        offsprings.at(i).mutate(mutation_rate);
    }

    /* replace */
    members = vector<GA::TextCandidate>(offsprings);
    generation++;
}

//void select_a_few_members(vector<TextCandidate> members){
//    float max_cost = 0;
//    for (int i=0; i<members.size(); i++) {
//        max_cost += members.at(i).cost;
//    }
//    
//    vector<TextCandidate> pool;
//    for (int i=0; i<members.size(); i++) {
//        if (RANDOM_NUM < members.at(i).cost/max_cost) {
//            pool.push_back(members.at(i));
//        }
//    }
//    
//    return pool;
//}








