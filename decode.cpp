#include <iostream>
<<<<<<< HEAD
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <arpa/inet.h>
=======

#include <cstdlib>
#include <ctime>
>>>>>>> 2b94839796891daa5c6525f4e9e80a37967f6db5

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

bool loopFlag = false;
char msgChar;
char dCryptChar;
string storeChars;

<<<<<<< HEAD
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

=======
>>>>>>> 2b94839796891daa5c6525f4e9e80a37967f6db5
bool bitVal(char msgChar, int bitPos) {
	msgChar = msgChar >> bitPos;
	if(msgChar & 1){
		return true;
	}
	else
		return false;
}

char dCrypt (char ch){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	srand(ltm -> tm_yday);
	dCryptChar = ch - ltm->tm_min - rand();
	return dCryptChar;
}

int main(int argc, char** argv) {
<<<<<<< HEAD
	metaDataStruct metaData;
	getPngMeta(argv[1], metaData);
	ofstream outFile;
	outFile.open("decodeOutput.txt");
=======
	ofstream decodeOutput;
>>>>>>> 2b94839796891daa5c6525f4e9e80a37967f6db5
	Mat image = imread(argv[1]);
	char msgChar = 0;
	int bitCount = 0;
	int xDimMax = image.rows;
	int yDimMax = image.cols;
<<<<<<< HEAD
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
=======
	int xDim=0; 
	int yDim=0;
	decodeOutput.open("decodeOutput.txt");

	while(xDim<xDimMax && loopFlag == false) {
		while(yDim<yDimMax && loopFlag == false) {
			for(int zDim=0; zDim < 3; zDim++) {
>>>>>>> 2b94839796891daa5c6525f4e9e80a37967f6db5
				Vec3b operatingPixel = image.at<Vec3b>(Point(xDim,yDim));

				if(bitVal(operatingPixel.val[zDim],0))
					msgChar |= 1;
				bitCount++;

				switch(bitCount){
				case(8):
					if(msgChar == '\0'){
						loopFlag = true;
						break;
					}

					bitCount = 0;
					dCrypt(msgChar);
<<<<<<< HEAD
					outFile << dCryptChar;
=======
					decodeOutput << dCryptChar;
>>>>>>> 2b94839796891daa5c6525f4e9e80a37967f6db5
					msgChar = 0;
				
				default:
					msgChar = msgChar << 1;
				}
			}
		yDim++;
		}
	xDim++;
	}
<<<<<<< HEAD
	outFile.close();
=======
	decodeOutput.close();
>>>>>>> 2b94839796891daa5c6525f4e9e80a37967f6db5
	return 0;
}
