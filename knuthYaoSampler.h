//
//  knuthYaoSampler.h
//  AonoEnc
//
//  Created by Mayank Rathee on 25/08/17.
//  Copyright © 2017 Mayank Rathee. All rights reserved.
//

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <pari/pari.h>
#include <time.h>
#include <string.h>
#define PARI_OLD_NAMES
#include <iostream>

using namespace std;

//mulir(sinv, gexp( gdiv(gneg(gpow(gdiv(gsub(point, center), sigma), stoi(2), precision)), strtor("2.00", precision)), precision));

GEN getGuassProbability(GEN point, GEN sigma, GEN center, int precision){
    GEN twopi = mulir(stoi(2), mppi(precision));
    GEN s = mulir(sigma, sqrtr(twopi));
    GEN sinv = invr(s);
    
    // if point is 0
    if(gcmp(point, strtor("0.00", precision)) == 0)
        return sinv;
    else{
        return gmul(sinv, gexp( gdiv(gneg(gpow(gdiv(gsub(point, center), sigma), stoi(2), precision)), strtor("2.00", precision)), precision));
    }
}

// Function to generate the probability matrix which is a substitute of the DDT Tree. Some really fine optimizations are not considered here which help prune this matrix

void getProbabilityMatrix(int sigma, char* c, int precision, int tailprune){
    GEN center;
    center = strtor(c, precision);
    
    GEN tempP, beginAddressP, ProbofPoints;
    int bounds = tailprune*sigma;
    // Now Points will run in [-bound, bound]. Since, all the points here except 0 will have 2 occurences, one of positive side and one on negative side (like x and -x). So, the probablility of 0 will be reduced to half later in this function
    // We consider only the positive points along with 0 (with half probability)
    ProbofPoints = cgetg(bounds+2, t_REAL); // extra 1 for 0
    // For a 64-bit machine the number of bits in long is 64
    int bitprecision = 64*(precision-2);
    cout<<"Knuth Yao Probability matrix is moving forward with a bit precision of "<<bitprecision<<endl;
    
    tempP = cgetg(bitprecision, t_VEC);
    for(int i=1; i<=bitprecision; i++){
        GEN temp = cgetg(bounds+2, t_INT);
        gel(tempP, i) = temp;
    }
    //cout<<GENtostr(gexp(stoi(-1), precision));
    //cout<<GENtostr(gdiv(center, stoi(2)));
    //cout<<GENtostr(gpow(strtor("2.00", precision), stoi(2), precision));
    
    cout<<GENtostr(getGuassProbability(strtor("6.00", precision), stoi(sigma), center, precision));
    
    
}