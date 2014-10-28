#ifndef LOCAL_H
#define LOCAL_H

#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>

#include "img.h"

class local{
    private:
        int id;
        int idReal;
        vector<img> imgs;
        vector<int> neighbors;

    public:
        local();

        void addImg(img m);
        vector<img> getImgs();

        int getSize();

        int getId();
        void setId(int i);

        int getIdReal();
        void setIdReal(int i);

        vector<int> getNeighbors();
        void setNeighbors(vector<int> n);
        int getNeighbor(int pos);
        void addNeighbor(int n);

};

#endif // LOCAL_H
