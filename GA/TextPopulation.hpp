//
//  TextPopulation.hpp
//  GA
//
//  Created by András Zalavári on 2017. 02. 18..
//
//

#ifndef TextPopulation_hpp
#define TextPopulation_hpp

#include <stdio.h>
#include <vector>
#include "TextCandidate.hpp"
namespace GA{
    class TextPopulation{
    private:
        int generation {0};
        std::vector<TextCandidate> members;
        float crossover_rate {0.7};
        float mutation_rate {0.01};

    public:
        
        TextPopulation(int size=80);
        
        bool evaluate(std::string target);
        void evolve();
        TextCandidate get_best() const;
        
        float get_average_cost() const;
        float get_generation() const;
        std::vector<TextCandidate> get_members() const;
    };
}
#endif /* TextPopulation_hpp */
