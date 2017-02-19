//
//  Candidate.cpp
//  GA
//
//  Created by András Zalavári on 2017. 02. 18..
//
//
#include "TextCandidate.hpp"
#include <cstdlib>
#include <string>
#include <iostream>
#define RANDOM_NUM      ((float)rand()/(RAND_MAX))

#define ABC std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ?!.,-")
using namespace std;

GA::TextCandidate::TextCandidate(){
    chromosome.empty();
    int dna_length = 7500;
    for(int d=0; d < dna_length; d++){
        /* generate a gene in the range 0 to 255 */
        int cell = std::rand() % 255;
        chromosome.push_back(cell);
    }
}

GA::TextCandidate::TextCandidate(vector<int> chromo){
    chromosome = vector<int>(chromo);
}

std::vector<int> GA::TextCandidate::get_chromosome() const{
    return chromosome;
}

string GA::TextCandidate::get_phenotype() const{
    return phenotype;
}

void GA::TextCandidate::parse(){
    string text;
    for(int i=0;i<chromosome.size(); i++){
        int cell = chromosome.at(i);
        text += ABC.at(cell%ABC.length());
    }
    phenotype = string(text);
}

float GA::TextCandidate::get_cost() const{
    return cost;
}

void GA::TextCandidate::calcCost(std::string target){
    parse();
    float difference = 0;
    for(int i=0; i < phenotype.size(); i++){
        int diff = (int)phenotype.at(i) - (int)target.at(i);
        difference+=abs(diff);
    }
    cost = difference / phenotype.size();
}

void GA::TextCandidate::mutate(float mutation_rate){
    for(int i=0; i< chromosome.size(); i++){
        if(RANDOM_NUM < mutation_rate){
//            chromosome.at(i)+= RANDOM_NUM < mutation_rate ? -1 : +1;
            chromosome.at(i) = rand() % 255;
        }
    }
}

//void GA::TextCandidate::crossover(Candidate const &partner){
//    vector<int> child_dna;
//    for(int i=0; i < chromosome.size(); i++){
//        if(RANDOM_NUM<0.5){
//            child_dna.push_back(chromosome.at(i));
//        } else{
//            child_dna.push_back(partner.chromosome.at(i));
//        }
//    }
//    return Candidate(child_dna);
//}

vector<GA::TextCandidate> GA::TextCandidate::crossover(TextCandidate const &a, TextCandidate const &b){
    vector<int> child_a_dna;
    vector<int> child_b_dna;
    for(int i=0; i < a.chromosome.size(); i++){
        if(RANDOM_NUM<0.5){
            child_a_dna.push_back(a.get_chromosome().at(i));
            child_b_dna.push_back(b.get_chromosome().at(i));
        } else{
            child_a_dna.push_back(b.get_chromosome().at(i));
            child_b_dna.push_back(a.get_chromosome().at(i));
        }
    }
    vector<TextCandidate> children;
    children.push_back(TextCandidate(child_a_dna));
    children.push_back(TextCandidate(child_b_dna));
    return children;
}

