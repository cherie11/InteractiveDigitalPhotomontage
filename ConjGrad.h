//
//  ConjGrad.hpp
//  2017cv
//
//  Created by  cherie Wang on 18/5/20.
//  Copyright © 2018年 Wang. All rights reserved.
//

#ifndef ConjGrad_h
#define ConjGrad_h

#include <iostream>
#include <set>
#include <vector>
using namespace std;
/*
 Col element represent the value and its col index
 */
class Col{
private:
    int index;
    float value;
public:
    //3 constructors
    Col(int index,float value){
        this->index=index;
        this->value=value;
    }
    Col(const Col &c){
        this->index=c.index;
        this->value=c.value;
    }
    Col(int index){
        this->index=index;
        this->value=0;
    }
    // cpmpare operation
    bool operator<(const Col& right)const{
        if(index==right.index){
            return false;
        }
        else return index<right.index;
    }
    //add a value for current node
    Col add(const float right)const{
        return Col(index,this->value+right);
    }
    //get the value
    float getValue()const{
        return value;
    }
    int getIndex()const{
        return index;
    }
};

/*
 Sparce Matrix representation
 */
class SparseMatrix{
private:
    vector< set<Col> > matrix;
    int row_num;
public:
    int getSize(){
        return row_num;
    }
    vector<set<Col> > getMat(){
        return matrix;
    }
    SparseMatrix(){row_num=0;};
    SparseMatrix(int row_num){
        this->row_num=row_num;
        matrix= vector<set<Col> >(row_num);
    };
    //multiply by a double number
    SparseMatrix dot(double e){
        SparseMatrix res(row_num);
        for(int i=0;i<matrix.size();i++){
            set<Col>::iterator iter=matrix[i].begin();
            res.insert(iter->getValue()*e,i,iter->getIndex());
        }
        return res;
    }
    //add operation of 2 matrix
    SparseMatrix add(SparseMatrix b){
        SparseMatrix res(row_num);
        for(int i=0;i<matrix.size();i++){
            set<Col>::iterator iter=matrix[i].begin();
            set<Col>::iterator iter1=b.getMat()[i].begin();
            if(iter==matrix[i].end()&&iter1==b.getMat()[i].end()){
                continue;
            }
            else{
                if(iter->getIndex()==iter1->getIndex())
                    res.insert(iter->getValue()+iter1->getValue(),i,iter->getIndex());
                else if(iter==matrix[i].end())
                    res.insert(iter1->getValue(),i,iter1->getIndex());
                else if(iter1==b.getMat()[i].end())
                    res.insert(iter->getValue(),i,iter->getIndex());
            }
            
        }
        return res;
    }
    //matrix mat multiply a vector
    vector<float > dot(vector<float >b){
        vector<float > res;
        
        for(auto p:matrix){
            
            float sum=0;
            for(auto ele:p){
                sum+=ele.getValue()*b[ele.getIndex()];
            }
            res.push_back(sum);
        }
        return res;
    }
    //Initialize by vectors
    void initializeFromVector(const vector<int >& rows,const vector<int>& cols,const vector<float>& vals){
        
        row_num=rows.size()-1;
        matrix=  vector<set<Col> >(row_num);
        
        int i=0;
        pair<set<Col>::iterator,bool> res;
        for(int j=0;j<rows.size()-1;j++){
            int k=rows[j];
            while (k<rows[j+1]) {
                res=matrix[i].insert(Col(cols[k],vals[k]));
                //if the position conflict,just add them
                if(!res.second){
                    set<Col>::iterator pNext = res.first;
                    pNext++;
                    Col tmp=res.first->add(vals[k]);
                    matrix[i].erase(res.first);
                    matrix[i].insert(pNext,tmp);
                }
                
                k++;
            }
            i++;
            
        }
    }
    //insert new value
    void insert(float val, int row, int col){
        pair<set<Col>::iterator,bool> res=matrix[row].insert(Col(col,val));
        if(!res.second){
            set<Col>::iterator pNext = res.first;
            pNext++;
            matrix[row].erase(res.first);
            matrix[row].insert(pNext,Col(col,val));
        }
        
    }
    //get element by position
    float at(int row,int col){
        set<Col>::iterator p= matrix[row].find(Col(col));
        if(p==matrix[row].end()){
            return 0;
        }
        else return p->getValue();
        
    }
    string toString(){
        string res="";
        for(auto p:matrix){
            int i=0;
            for (auto ele: p){
                if(i<ele.getIndex()){
                    while(++i<ele.getIndex()){
                        res+="0 ";
                    }
                }
                else i+=1;
                res+=to_string(ele.getValue())+" ";
                
            }
            if(i++<matrix.size()){
                res+="0 ";
            }
            res+="\n";
        }
        return res;
    }
    
};


#endif /* ConjGrad_h */
