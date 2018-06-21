//
//  ConjGrad.cpp
//  2017cv
//
//  Created by  cherie Wang on 18/5/20.
//  Copyright © 2018年 Wang. All rights reserved.
//

#include "ConjGrad.h"
//
//  lab3.cpp
//
//
//  Created by  cherie Wang on 3/20/18.
//  Copyright © 2018 Wang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include <math.h>
using namespace std;


/*
 Conjugate Gradient Solution
 */
class ConjugateGradient{
public:
    //dot product of 2 vectors
    double mul(const vector<float> & a,const vector<float>&  b){
        float result;
        for(int i=0;i<a.size();i++)
            result+=a[i]*b[i];
        return result;
    }
    //product of matrix and vector
    double mul( SparseMatrix & a,const vector<float>&  b){
        float result;
        for(int i=0;i<b.size();i++)
            result+=a.at(i,0)*b[i];
        return result;
    }
    //sovle the result
    vector<float> calculate(SparseMatrix A,vector<float> B){
        double delta=0.0000001;
        double diff=1;
        vector<float> r(B);
        vector<float> p(r);
        vector<float> x(B.size(),0);
        while(1){
            vector<float> r1(r);
            
            vector<float> tmp=A.dot(p);
            
            double a=mul(r,r)/mul(p,tmp);
            
            for(int i=0;i<B.size();i++){
                x[i]=x[i]+a*p[i];
            }
            
            tmp=A.dot(x);
            for(int i=0;i<B.size();i++){
                r[i]=B[i]-tmp[i];
            }
            double m=0;
            for(int i=0;i<B.size();i++){
                m+=B[i]*B[i];
            }
            m=sqrt(m);
            double sum=0;
            for(int i=0;i<B.size();i++){
                sum+=pow(tmp[i]-B[i],2);
                
            }
            sum=sqrt(sum);
            diff=sum/m;
            if(diff<delta){
                break;
            }
            else{
                m=0;
                for(int i=0;i<r1.size();i++){
                    m+=r1[i]*r1[i];
                }
                sum=0;
                for(int i=0;i<r.size();i++){
                    sum+=r[i]*r[i];
                }
                for(int i=0;i<p.size();i++){
                    p[i]=r[i]+sum/m*p[i];
                }
                
                
                
            }
            
            
            
            
        }
        return x;
    }
    
};
/*
int main(){
    SparseMatrix matA;
 
    // int a[] = { 0,3,7,11,14};
    // int b[]={0,1,2,0,1,2,3,0,1,2,3,1,2,3};
    // int c[]={10,-1,2,-1,11,-1,3,2,-1,10,-1,3,-1,8};
 
    int dim;
    vector<int >rows;//(a,a+sizeof( a ) / sizeof( a[0] ));
    vector<int>cols;//( b, b+ sizeof( b ) / sizeof( b[0] ));
    vector<float> vals;//( c, c + sizeof( c ) / sizeof( c[0] ));
    
    
    //int d[]={6,25,-11,15};
    vector<float> matB;//(begin(d), end(d));
    
    cout<<"Using Compressed sparse row!\nInput the dimension of matrix A:"<<endl;
    cin>>dim;
    cout<<"For matrix A"<<endl;
    cout<<"Input the rows:"<<endl;
    for(int i=0;i<dim+1;i++){
        int ele;
        cin>>ele;
        rows.push_back(ele);
        
    }
    cout<<"Input the non-zero element amount:"<<endl;
    int num;
    cin>>num;
    cout<<"Input the cols :"<<endl;
    for(int i=0;i<num;i++){
        int ele;
        cin>>ele;
        cols.push_back(ele);
        
    }
    cout<<"Input the value:"<<endl;
    for(int i=0;i<num;i++){
        int ele;
        cin>>ele;
        vals.push_back(ele);
        
    }
    cout<<"For vector b:"<<endl;
    for(int i=0;i<dim;i++){
        float ele;
        cin>>ele;
        matB.push_back(ele);
        
    }
    matA.initializeFromVector(rows, cols, vals);

    ConjugateGradient CG;
    vector<float> res;
    cout<<"GaussSeidel:\n x="<<endl;
    for(auto p:res){
        cout<<p<<" ";
    }
    cout<<endl;
    res=CG.calculate(matA, matB);
    cout<<"ConjugateGradient:\n x="<<endl;
    for(auto p:res){
        cout<<p<<" ";
    }
    cout<<endl;
    
    
}*/
