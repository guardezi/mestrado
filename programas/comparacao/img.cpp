#include "img.h"

img::img(){}

//getters and setters
vector<KeyPoint> img::getkps(){
    return kpsImg;
}

void img::setKps(vector<KeyPoint> v){
    kpsImg = v;
}

Mat img::getDescs(){
    return descImg;
}

void img::setDescs(Mat m){
    descImg = m;
}

int img::getId(){
    return id;
}

void img::setId(int ID){
    id = ID;
}


//void write(FileStorage& fs) const                        //Write serialization for this class
//{
//  fs << "{" << "kp" << kpsImg << "desc" << descImg  << "}";
//}

//void read(const FileNode& node)                          //Read serialization for this class
//{
//  kpsImg = (vector<KeyPoint>)node["kp"];
//  descImg = (Mat)node["desc"];
//}
