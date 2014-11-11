#ifndef IGFTT_H
#define IGFTT_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace std;
using namespace cv;

class IGFTT
{
    public:
        IGFTT(int _nfeatures=200,
              float _scaleFactor=1.2f,
              int _nlevels=8,
              int _firstLevel=0,
              double _qualityLevel=0.01,
              double _minDistance = 10,
              int _blockSize = 31,
              int _aperture_size = 3);
        void detect(Mat image, vector<KeyPoint>& _keypoints);
protected:
        int nfeatures;
        float scaleFactor;
        int nlevels;
        int firstLevel;
        double qualityLevel;
        double minDistance;
        int blockSize;
        int aperture_size;
        inline float getScale(int level);
        inline void computeKeyPoints(const vector<Mat> &imagePyramid, vector<vector<KeyPoint> > &allKeypoints);
        void computeOrientation(Mat img, vector<KeyPoint> &kp);
        float Mom_Angle(const Mat &image, const int half_k, Point2f pt, const vector<int> &u_max);
        void computeOrientationOrb(const Mat &image, vector<KeyPoint> &keypoints, int halfPatchSize, const vector<int> &umax);
};

#endif // IGFTT_H
