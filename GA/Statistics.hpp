//
//  Statistics.hpp
//  GA
//
//  Created by András Zalavári on 2017. 02. 19..
//
//

#ifndef Statistics_hpp
#define Statistics_hpp

#include <stdio.h>
#include <cstdlib> //rand, RAND_MAX
#include <math.h> //M_SQRT1_2
#include <iostream>
#include <vector>
#define RANDOM_NUM      ((float)rand()/(RAND_MAX))

#pragma mark - STATS
/* Cumulative Normal Distribution Function in C/C++ */
double normalCFD(double x)
{
    return 0.5 * erfc(-x * M_SQRT1_2);
}

/* Standard deviation */
float STD(std::vector<float> data)
{
    float sum = 0.0, mean, standardDeviation = 0.0;
    
    int i;
    
    for(i = 0; i < 10; ++i)
    {
        sum += data.at(i);
    }
    
    mean = sum/10;
    
    for(i = 0; i < 10; ++i)
        standardDeviation += pow(data.at(i) - mean, 2);
    
    return sqrt(standardDeviation / 10);
}

template <class T>
std::vector<T> weighted_sample(int n, const std::vector<T> &items, const std::vector<float> &weights){
    /*
     
     */
    std::vector<float> w(weights);
    std::vector<int> indices;
    /* numbr of coices */
    int num_choices = (int)w.size();
    
    for(int i=0; i<n; i++){
        /* calculate sum of weights */
        float sum_of_weight = 0;
        for(int i=0; i<num_choices; i++) {
            sum_of_weight += w.at(i);
        }
        
        /* initialize random seed: */
        float rnd = RANDOM_NUM;
        rnd *= sum_of_weight;
        // cout << "rnd: " << rnd << " sum:" << sum_of_weight << endl;
        // cout << rnd << endl;
        for(int i=0;i<num_choices; i++){
            
            if(rnd < w.at(i)){
                // cout << "selected index: " << i << endl;
                indices.push_back(i);
                w.at(i) = 0;
                break;
            }
            rnd -= w.at(i);
        }
    }
    std::vector<T> choices;
    for(int i=0; i<indices.size(); i++){
        int idx = indices.at(i);
        choices.push_back(items.at(idx));
    }
    return choices;
}

template <class T>
std::vector<T> sample(int n, const std::vector<T>items){
    std::vector<float> weights;
    for (int i=0; i<items.size(); i++) {
        weights.push_back(1.0);
    }
    return weighted_sample(n, items, weights);
}

#endif /* Statistics_hpp */
