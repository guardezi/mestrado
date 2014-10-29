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
    cout <<"Detectores: IORB, ORB, SURF, SIFT"<<endl;
    cout <<"Descritores: ORB, SURF, SIFT"<<endl;
}

int main(int argc, char *argv[]){
    if(argc<4){
        help();
        return 0;
    }

    string a=argv[1];
    string b=argv[2];

    string detect=argv[3];
    string describ=argv[4];

    //cout << imgA<< imgB<<detect<<describ<<endl;

    Mat imgA,imgB;
    imgA=imread(a.c_str(),0);
    imgB=imread(b.c_str(),0);

    imshow("img A",imgA);
    //imshow("img B",imgB);

    waitKey();

    vector<KeyPoint> kpA,kpB;
    Mat descA,descB;


    Mat imagem=imread(a.c_str(),0);
    vector<KeyPoint> kp;
    //detector
    if(detect.compare("IGFTT")==0){//IORB
        IGFTT g;
        g.detect(imagem,kp);
    }else{//Others
        Ptr<FeatureDetector> detector;
        detector = FeatureDetector::create(detect);
        detector->detect(imgA,kp);
    }

    drawKeypoints(imgA,kp,imgA,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
    imshow("KEYPOINTS A",imgA);
//    imshow("img B",b);

    waitKey();

//        //read the first node
//        int t=43;
//        for (; arquivo.at(t)!='/';t++);
//        l=local();
//        inf= arquivo.substr(43,t-43);
//        for(int p=3;p<inf.size();p+=3){
//            l.addNeighbor(atoi(inf.substr(p,2).c_str()));
//        }
//        l.setId(atoi(inf.substr(0,2).c_str()));


//        Mat img1;
//        while(!cin.eof()){
//            cin >> arquivo;
//                img imagem;

//                img1  = imread(arquivo.c_str(),0);

//                vector<KeyPoint> kp;
//                Mat desc;

//                //detector
//                if(detect.compare("IORB")==0){//IORB
//                    IGFTT g;
//                    g.detect(img1,kp);
//                }else{//Others
//                    Ptr<FeatureDetector> detector;
//                    detector = FeatureDetector::create(detect);
//                    detector->detect(img1,kp);
//                }
//                //descritor
//                Ptr<DescriptorExtractor> extractor;
//                extractor = DescriptorExtractor::create(describ);//ORB
//                extractor->compute(img1,kp,desc);


//                imagem.setDescs(desc);
//                imagem.setKps(kp);

//                //verificar por local
//                for (t=43; arquivo.at(t)!='/';t++);
//                //cout << inf <<endl;// <<"  "<<  inf.compare(arquivo.substr(43,t-43)) << endl;

//                //verifica se esta em um novo lugar...
//                if(inf.compare(arquivo.substr(43,t-43))!=0){ //Noovo lugar
//                    locais.push_back(l);
//                    l=local();
//                    inf= arquivo.substr(43,t-43);
//                    for(int p=3;p<inf.size();p+=3){
//                        l.addNeighbor(atoi(inf.substr(p,2).c_str()));
//                    }
//                    l.setId(atoi(inf.substr(0,2).c_str()));

//                }
//                l.addImg(imagem);
////            }

//            i++;
//        }
//        locais.push_back(l);
//        FileStorage fs(filename, FileStorage::WRITE);
//        i = locais.size();
////        fs <<"sizenodes" << i;

//        fs <<"nodes"<< "{";
//        for(int o=0;o<locais.size();o++){
//            i=locais.at(o).getId();
//                fs <<"id"+to_string(o)<<i; //id
//                fs <<"neibs"+to_string(o)<< locais.at(o).getNeighbors(); //neibs
//            fs <<"imgs"+to_string(o) <<"{";
//            for(int q=0;q<locais.at(o).getImgs().size();q++){
////                fs << "" + "_" + to_string(q);
//                fs <<"KeyPoints"+ to_string(q) << locais.at(o).getImgs().at(q).getkps();
//                fs <<"Descriptor"+ to_string(q) << locais.at(o).getImgs().at(q).getDescs();    //descriptors
//            }
//            fs <<"}";
//    //        fs << "desc" << locallll.getImgs().at(0).getDescs();


//            //cout << "id: " << locais.at(o).getId()<<" neib: ";
//            //for(int k=0;k<locais.at(o).getNeighbors().size();k++){
//                //cout <<  " "<< locais.at(o).getNeighbors().at(k);
//            //}
//            //cout<< endl;
//        }
//        fs<<"}";
//        fs.release();
//        //cout << "locais: "<< locais.size()<<endl;
//    }
//    //Lendo do arquivo YML
//    else{
//        vector<local> nos;
//        FileStorage fs;
//        fs.open(filename, FileStorage::READ);
//        FileNode node =fs["nodes"];
//        if (node.empty()){
//            return 0;
//        }
//        int i =0,id,j=0;
//        FileNodeIterator current = node.begin(), it_end = node.end(); // Go through the node
//        for (; current != it_end; ++current){
//            //cout << "teste load"<<endl;
//            int id;
//            local l;

//            //getting id
//            FileNode item = *current;
//            item >> id;
//            l.setId(id);

//            //getting neiborhods
//            ++current;
//            item = *current;
//            vector<int> neibs;
//            read(item,neibs);
//            l.setNeighbors(neibs);

//            //get keypoint and descriptors
//            ++current;
//            item = *current;
//            FileNode imgsNode =item;
//            FileNodeIterator current2 = imgsNode.begin(), it2_end = imgsNode.end();
//            for(;current2!=it2_end;++current2){
//                vector<KeyPoint> kp;
//                Mat desc;
//                img picture;

//                FileNode itm = *current2;
//                //read keypoints
//                read(itm,kp);

//                //read descriptors
//                ++current2;
//                itm = *current2;
//                itm >> desc;

//                //add to img and to vector
//                picture.setKps(kp);
//                picture.setDescs(desc);
//                l.addImg(picture);
//            }
//            nos.push_back(l);
//        }
//        int pos[21];
//        for(int iw=0;iw<=20;iw++){
//            pos[iw]=0;
//        }

//        int ide;
//        for(int iw=0;iw<20;iw++){

//            string arquivo;
//            cin>>arquivo;
//            Mat imagem = imread(arquivo.c_str(),0);

//            vector<KeyPoint> kp;
//            Mat desc;

//            //detector
//            if(detect.compare("IORB")==0){//IORB
//                IGFTT g;
//                g.detect(imagem,kp);
//            }else{//Others
//                Ptr<FeatureDetector> detector;
//                detector = FeatureDetector::create(detect);
//                detector->detect(imagem,kp);
//            }
//            //descritor
//            Ptr<DescriptorExtractor> extractor;
//            extractor = DescriptorExtractor::create(describ);//ORB
//            extractor->compute(imagem,kp,desc);

//            int maior =0;
//            ide=0;
//            for(vector<local>::iterator it=nos.begin();it!=nos.end();++it){
//                local l=*it;
//                //cout << "teste0"<<endl;
//                BFMatcher *matcher;
//                matcher = new BFMatcher(NORM_HAMMING,true);

//                vector<img> imgIt=l.getImgs();
//    //            cout<<"imgs: " << imgIt.size() <<endl;
//                for(int i=0;i<imgIt.size();i++){
//                    img a=imgIt.at(i);
//                    vector<DMatch> matches;
//                    Mat desc1=a.getDescs();
//    //                cout << "cols1: "<< desc.cols << "cols2: "<<desc1.cols<<endl;
//                    //matcher->knnMatch(desc1,desc,matches);
//                    if(matches.size()>maior){
//                        maior=matches.size();
//                        ide=l.getId();
//                    }
//                    //cout <<"id: "<<l.getId()<<" matchs: "<<matches.size()<<endl;
//                }
//            }
//            cout<<iw << " - maior: "<< maior << " id: "<<ide<<endl; //exibe os resultados.
//            pos[ide]++;
//        }
//        ide =0;
//        for(int i=0;i<20;i++){
//            cout<< pos[i]<<" ";
//            if(pos[i]>ide){
//                ide=i;
//            }
//            pos[i]=0;
//        }
//        cout << endl <<"id:" <<ide<<endl;


//        int contador=0;

//        while(!cin.eof()){
//            contador++;
//            string seg;
//            int ide2;
//            vector<KeyPoint> kp2;
//            Mat desc2;
//            Mat imagem;
//            int maior2=0;

//            cin >> seg;
//            imagem = imread(seg.c_str(),0);

//            //detector
//            if(detect.compare("IORB")==0){//IORB
//                IGFTT g;
//                g.detect(imagem,kp2);
//            }else{//Others
//                Ptr<FeatureDetector> detector;
//                detector = FeatureDetector::create(detect);
//                detector->detect(imagem,kp2);
//            }
//            //descritor
//            Ptr<DescriptorExtractor> extractor;
//            extractor = DescriptorExtractor::create(describ);//ORB
//            extractor->compute(imagem,kp2,desc2);
//            cout<< "verificando os vizinhos do nó: "<< ide<<endl;
//            for(int it=0;it<nos.size();it++){//percorre todos os nós
//                local l=nos.at(it);
//                if(l.getId()==ide){//entrando apenas no ide
//                    for(int it2=0; it2<l.getNeighbors().size();it2++){//percorre todos os vizinhos do ide
//                        int viz = l.getNeighbors().at(it2);
//                        for(vector<local>::iterator it3=nos.begin(); it3!=nos.end(); it3++){//todos os nós vizinhos
//                            local l2 =(local)*it3;
//                            if(l2.getId() == viz || l2.getId() == ide){
//                                // cout <<"ID_VIZINHO: "<< l2.getId() << endl;
//                                BFMatcher *matcher2;
//                                matcher2 = new BFMatcher(NORM_HAMMING,true);
//                                vector<img> imgIt=l2.getImgs();
//                                for(int i=0;i<imgIt.size();i++){
//                                    img at=imgIt.at(i);
//                                    vector<DMatch> matches2;
//                                    matches2.clear();
//                                    Mat desc1=at.getDescs();
//                                    try{
//                                        matcher2->match(desc1,desc2,matches2);
//                                        int tam=matches2.size();

//                                        if(maior2<tam){
//                                            maior2=tam;
//                                            ide2=l2.getId();
//                                        }
//                                    }catch(int e){
//                                        ide2=0;
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//            pos[ide2]++;

//            if(contador==10 || cin.eof()){
//                ide=0;
//                for(int i=1;i<20;i++){//verificando qual é o maior e limpando...
//                    cout<< pos[i]<<" ";
//                    if(pos[i]>ide){
//                        ide=i;
//                    }
//                    pos[i]=0;
//                }
//                cout << endl<<contador << " - id:" <<ide<<endl;
//                if (contador!=10){
//                    break;
//                }else{
//                    contador=0;
//                }
//            }

//        }
//    }

//    cout << "time:\t"<< ((double)getTickCount() - inicial)/getTickFrequency()<<endl;

//	return 0;
}
