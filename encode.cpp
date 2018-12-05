#include <iostream>
#include <fstream>
#include <arpa/inet.h>

#include <cstdlib>
#include <ctime>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

bool loopFlag = false;
char msgChar;
char getChar;

struct metaDataStruct {
    int width;
    int height;
    int depth;
    int color;
};

bool getPngMeta(const char *fileName, metaDataStruct &is) {
    std::ifstream file(fileName, std::ios_base::binary | std::ios_base::in);

    if (!file.is_open() || !file) {
        file.close();
        return false;
    }

    file.seekg(8, std::ios_base::cur);
    file.seekg(4, std::ios_base::cur);
    file.seekg(4, std::ios_base::cur);

    int width, height, depth, color;

    file.read((char*)&width, 4);
    file.read((char*)&height, 4);
    file.read((char*)&depth, 1);
    file.read((char*)&color, 1);

    is.width = width;
    is.height = height;
    is.depth = depth;
    is.color  =color;

    width=ntohl(width);
    height=ntohl(height);
    file.close();

    return true;
}

bool bitVal(char msgChar, int bitPos) {
	msgChar = msgChar >> bitPos;
	if(msgChar & 1){
		return true;
	}
	else
		return false;
}

char crypt (char ch){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	srand(ltm -> tm_yday);
	msgChar = ch + ltm->tm_min + rand();
	return msgChar;
}

int main(int argc, char** argv) {
	metaDataStruct metaData;
	Mat image = imread(argv[1]);
	getPngMeta(argv[1], metaData);
	ifstream file(argv[2]);


	file.get(getChar);
	crypt(getChar);
	int bitCount = 0;
	bool eofNull = false;
	bool isEncoded = false;

	int xDimMax = image.rows;
	int yDimMax = image.cols;
	int zDimMax = 0;
	int xDim=0; 
	int yDim=0;

	if (metaData.color=0)
		zDimMax = 1;
	else if (metaData.color=2)
		zDimMax = 3;
	else if (metaData.color=4)
		zDimMax = 2;
	else if (metaData.color=6)
		zDimMax	= 4;

	while(xDim<xDimMax && loopFlag == false) {
		while(yDim<yDimMax && loopFlag == false) {
			for(int zDim=0; zDim < zDimMax; zDim++) {
				Vec3b operatingPixel = image.at<Vec3b>(Point(xDim,yDim));
				if(bitVal(msgChar,7-bitCount))
					operatingPixel.val[zDim] |= 1;
				else
					operatingPixel.val[zDim] &= ~1;
				image.at<Vec3b>(Point(xDim,yDim)) = operatingPixel;
				bitCount++;
				if(eofNull && bitCount == 8) {
					isEncoded  = true;
					loopFlag = true;
					break;
				}
				else if(bitCount == 8) {
					bitCount = 0;
					file.get(getChar);
					crypt(getChar);
					if(file.eof()) {
						eofNull = true;
						msgChar = '\0';
					}
				}

			}
		yDim++;
		}
	xDim++;
	}
	if(!isEncoded) {
		cout << "msg too large" << endl;
		exit(-1);
	}
	imwrite(argv[3],image);
    return 0;
}
