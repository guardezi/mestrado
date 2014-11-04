#include "igftt.h"
#include "img.h"
#include "local.h"
#include <fstream>

#include <iostream>
#include <string>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <ctime>

using namespace cv;
using namespace std;


void help(){
    cout <<"./compara <imgA> <imgB> <Detector> <Descritor>"<<endl;
    cout <<"Detectores: IGFTT, ORB, SURF, SIFT"<<endl;
    cout <<"Descritores: ORB, SURF, SIFT"<<endl;
}

int main(int argc, char *argv[]){
    if(argc<4){
        help();
        return 0;
    }

    cv::initModule_nonfree();
    string a=argv[1];
    string b=argv[2];

    string detect=argv[3];
    string describ=argv[4];


    Mat imgA,imgB;
    imgA=imread(a.c_str(),0);
    imgB=imread(b.c_str(),0);

    //detecting and describing points
    vector<KeyPoint> kpA,kpB;
    Mat descA,descB;

    //detector
    if(detect.compare("IGFTT")==0){//IORB
        IGFTT g;
        g.detect(imgA,kpA);
        g.detect(imgB,kpB);
    }else{//Others
        Ptr<FeatureDetector> detector;
        detector = FeatureDetector::create(detect);
        detector->detect(imgA,kpA);
        detector->detect(imgB,kpB);
    }

    //descritor
    Ptr<DescriptorExtractor> extractor;
    extractor = DescriptorExtractor::create(describ);
    extractor->compute(imgA,kpA,descA);
    extractor->compute(imgB,kpB,descB);

    //matching
    BFMatcher *matcher;
    matcher = new BFMatcher(NORM_L1,true);
    vector<DMatch> matches;
    matcher->match(descA,descB,matches);


    Mat saida;
    drawMatches(imgA,kpA,imgB,kpB,matches,saida, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::DEFAULT);
    imshow("Resultado",saida);
    waitKey();

    printf("%s %s %s %s %d \n",a.c_str(),b.c_str(),detect.c_str(),describ.c_str(),matches.size());

    return 0;
}
