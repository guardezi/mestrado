/*

*/

#include "igftt.h"
#include <iostream>


IGFTT::IGFTT(int _nfeatures, float _scaleFactor, int _nlevels,int _firstLevel,
            double _qualityLevel,double _minDistance,int _blockSize, int _aperture_size):
    nfeatures(_nfeatures),
    scaleFactor(_scaleFactor),
    nlevels(_nlevels),
    firstLevel(_firstLevel),
    qualityLevel(_qualityLevel),
    minDistance(_minDistance),
    blockSize(_blockSize),
    aperture_size(_aperture_size)
{}

template<typename T> struct greaterThanPtr
{
    bool operator()(const T* a, const T* b) const { return *a > *b; }
};

inline float IGFTT::getScale(int level)
{
    return (float)std::pow(scaleFactor, (double)(level - firstLevel));
}

inline void IGFTT::computeOrientation(Mat img, vector<KeyPoint> &pts){

        const uchar* ptr00 = img.ptr<uchar>();

        int step = (int)(img.step/img.elemSize1());
        int r = blockSize/2;
        int ptsize = pts.size();
        AutoBuffer<int> ofsbuf(blockSize*blockSize);
        int* ofs = ofsbuf;

        for( int i = 0; i < blockSize; i++ )
            for( int j = 0; j < blockSize; j++ )
                ofs[i*blockSize + j] = (int)(i*step + j);

        for( int ptidx = 0; ptidx < ptsize; ptidx++ )
        {
            int x0 = cvRound(pts[ptidx].pt.x - r);
            int y0 = cvRound(pts[ptidx].pt.y - r);

            const uchar* ptr0 = ptr00 + y0*step + x0;
            float a = 0, b = 0, c = 0;

            for( int k = 0; k < blockSize*blockSize; k++ )
            {
                const uchar* ptr = ptr0 + ofs[k];
                int Ix = (ptr[1] - ptr[-1])*2 + (ptr[-step+1] - ptr[-step-1]) + (ptr[step+1] - ptr[step-1]);
                int Iy = (ptr[step] - ptr[-step])*2 + (ptr[step-1] - ptr[-step-1]) + (ptr[step+1] - ptr[-step+1]);
                a += Ix*Ix;
                b += Iy*Iy;
                c += Ix*Iy;
            }

            float u = (a + c)*0.5;
            float v = std::sqrt((a - c)*(a - c)*0.25 + b*b);
            float l2 = u - v;

            float x = b;
            float y = l2 - a;
            float e = fabs(x);

            if( e + fabs(y) < 1e-4 )
            {
                y = b;
                x = l2 - c;
                e = fabs(x);
                if( e + fabs(y) < 1e-4 )
                {
                    e = 1./(e + fabs(y) + FLT_EPSILON);
                    x *= e, y *= e;
                }
            }

            float d = 1./std::sqrt(x*x + y*y + DBL_EPSILON);
            pts[ptidx].angle = fastAtan2(y*d,x*d);
        }
}

float IGFTT::Mom_Angle(const Mat& image, const int half_k, Point2f pt, const vector<int> & u_max)
{
    int m_01 = 0, m_10 = 0;

    const uchar* center = &image.at<uchar> (cvRound(pt.y), cvRound(pt.x));

    // Treat the center line differently, v=0
    for (int u = -half_k; u <= half_k; ++u)
        m_10 += u * center[u];

    // Go line by line in the circular patch
    int step = (int)image.step1();
    for (int v = 1; v <= half_k; ++v)
    {
        // Proceed over the two lines
        int v_sum = 0;
        int d = u_max[v];
        for (int u = -d; u <= d; ++u)
        {
            int val_plus = center[u + v*step], val_minus = center[u - v*step];
            v_sum += (val_plus - val_minus);
            m_10 += u * (val_plus + val_minus);
        }
        m_01 += v * v_sum;
    }

    return fastAtan2((float)m_01, (float)m_10);
}

void IGFTT::computeOrientationOrb(const Mat& image, vector<KeyPoint>& keypoints,int halfPatchSize, const vector<int>& umax)
{
    // Process each keypoint
    for (vector<KeyPoint>::iterator keypoint = keypoints.begin(),
         keypointEnd = keypoints.end(); keypoint != keypointEnd; ++keypoint)
    {
        keypoint->angle = Mom_Angle(image, halfPatchSize, keypoint->pt, umax);
    }
}

inline void IGFTT::computeKeyPoints(const vector<Mat>& imagePyramid,
                             vector<vector<KeyPoint> >& allKeypoints)
{
    int nlevels = (int)imagePyramid.size();

    allKeypoints.resize(nlevels);

    for (int level = 0; level < nlevels; ++level)
    {
        allKeypoints[level].reserve(nfeatures*2);

        vector<KeyPoint> & keypoints = allKeypoints[level];

        float sf = getScale(level);

        GFTTDetector g(nfeatures,qualityLevel,minDistance,blockSize);
        g.detect(imagePyramid[level],keypoints);

        for (vector<KeyPoint>::iterator keypoint = keypoints.begin(),
             keypointEnd = keypoints.end(); keypoint != keypointEnd; ++keypoint)
        {
            keypoint->octave = level;
            keypoint->size =blockSize*sf;
            keypoint->pt *= sf;
        }

        //computeOrientation(imagePyramid[level],keypoints);

        //compute ORB orientation
        /*int halfPatchSize = blockSize / 2;
        vector<int> umax(halfPatchSize + 2);

        int v, v0, vmax = cvFloor(halfPatchSize * sqrt(2.f) / 2 + 1);
        int vmin = cvCeil(halfPatchSize * sqrt(2.f) / 2);
        for (v = 0; v <= vmax; ++v)
            umax[v] = cvRound(sqrt((double)halfPatchSize * halfPatchSize - v * v));

        // Make sure we are symmetric
        for (v = halfPatchSize, v0 = 0; v >= vmin; --v)
        {
            while (umax[v0] == umax[v0 + 1])
                ++v0;
            umax[v] = v0;
            ++v0;
        }
        computeOrientationOrb(imagePyramid[level], keypoints, halfPatchSize, umax);
        */
    }
}

void IGFTT::detect(Mat image, vector<KeyPoint>& _keypoints)
{

    vector<Mat> imagePyramid(nlevels);
    image.copyTo(imagePyramid[0]);
    for (int level = 1; level < nlevels; ++level)
    {
        float scale= 1/getScale(level);

        Size sz(cvRound(image.cols*scale), cvRound(image.rows*scale));
        resize(imagePyramid[level-1], imagePyramid[level], sz);
    }

    // Pre-compute the keypoints (we keep the best over all scales, so this has to be done beforehand
    vector < vector<KeyPoint> > allKeypoints;
    computeKeyPoints(imagePyramid, allKeypoints);

    //Mat descriptors;
    _keypoints.clear();
    //int offset = 0;
    for (int level = 0; level < (int)imagePyramid.size(); ++level)
    {
        // Get the features and compute their orientation
        vector<KeyPoint>& keypoints = allKeypoints[level];

        // Compute the descriptors
        /*Mat desc;
        if (!descriptors.empty())
        {
            desc = descriptors.rowRange(offset, offset + nkeypoints);
        }

        offset += nkeypoints;

        // preprocess the resized image
        Mat& workingMat = imagePyramid[level];
        //boxFilter(working_mat, working_mat, working_mat.depth(), Size(5,5), Point(-1,-1), true, BORDER_REFLECT_101);
        GaussianBlur(workingMat, workingMat, Size(7, 7), 2, 2, BORDER_REFLECT_101);
        computeDescriptors(workingMat, keypoints, desc, pattern, descriptorSize(), WTA_K);*/

        // And add the keypoints to the output
        _keypoints.insert(_keypoints.end(), keypoints.begin(), keypoints.end());
    }
}
