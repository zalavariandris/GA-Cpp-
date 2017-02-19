//
//  Candidate.hpp
//  GA
//
//  Created by András Zalavári on 2017. 02. 18..
//
//

#ifndef TextCandidate_hpp
#define TextCandidate_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <cmath>

namespace GA{
    class TextCandidate{
    private:
        std::vector<int> chromosome;
        float cost {FP_INFINITE};
        std::string phenotype;
    
    private:
        void parse();
    
    public:
        TextCandidate();
        TextCandidate(std::vector<int>);
        void calcCost(std::string target);
        void mutate(float mutation_rate);
        static std::vector<TextCandidate> crossover(TextCandidate const &a, TextCandidate const &b);
    
        bool operator<(TextCandidate const &rhs) const{
            return cost < rhs.get_cost();
        }
    
        std::vector<int> get_chromosome() const;
        float get_cost() const;
        std::string get_phenotype() const;
    };
}
#endif /* TextCandidate_hpp */
