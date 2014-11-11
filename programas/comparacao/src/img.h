#ifndef IMG_H
#define IMG_H

#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

class img{
    private:
        int id;
        vector<KeyPoint> kpsImg;
        Mat descImg;
    public:
        img();
        //getters and setters
        vector<KeyPoint> getkps();
        void setKps(vector<KeyPoint> v);
        Mat getDescs();
        void setDescs(Mat m);

        int getId();
        void setId(int ID);
//        void write(FileStorage& fs) const; //Write serialization for this class

//        void read(const FileNode& node);    //Read serialization for this class
//        //These write and read functions must be defined for the serialization in FileStorage to work
//        static void write(FileStorage& fs, const std::string&, const img& x);
//        static void read(const FileNode& node, img& x, const img& default_value = img());

//        // This function will print our custom class to the console
//        static ostream& operator<<(ostream& out, const img& m);
};

#endif // IMG_H
