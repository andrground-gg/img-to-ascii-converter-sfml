#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Image.hpp>
#include<iostream>
#include<string.h>
#include<fstream>

#define RED 0.2126
#define GREEN 0.7152
#define BLUE 0.0722

int main() {
	std::string inputPath;
	std::string outputPath = "";
	int scaleX;
	std::string ascii = "@%#=+|!:. "; 

	std::cout << "Input: ";
	std::cin >> inputPath;

	for (int i = 0; i < inputPath.length(); i++) {
		if (inputPath[i] == '.') break;
		outputPath += inputPath[i];
	}
	outputPath += ".txt";

	std::cout << "Scale: ";
	std::cin >> scaleX;

	int c;
	sf::Image img;
	img.loadFromFile(inputPath);
	sf::Image grayImg(img);
	for (int i = 0; i < img.getSize().x; i++) {
		for (int j = 0; j < img.getSize().y; j++) {
			c = img.getPixel(i, j).r * RED + img.getPixel(i, j).g * GREEN + img.getPixel(i, j).b * BLUE;
			grayImg.setPixel(i, j, sf::Color(c, c, c));
		}
	}
	char symb;
	grayImg.saveToFile("grayImg.png");
	
	int scaleY = scaleX * 2;
	sf::Image lowResImg(img);
	for (int i = 0; i < img.getSize().x - scaleX; i += scaleX) {
		for (int j = 0; j < img.getSize().y - scaleY; j += scaleY) {
			for (int x = 0; x < scaleX; x++) {
				for (int y = 0; y < scaleY; y++) {
					c += grayImg.getPixel(i + x, j + y).r;
				}
			}
			c /= scaleX * scaleY + 1;
			for (int x = 0; x < scaleX; x++) {
				for (int y = 0; y < scaleY; y++) {
					lowResImg.setPixel(i + x, j + y, sf::Color(c, c, c));
				}
			}
		}
	}
	lowResImg.saveToFile("lowResImg.png");

	std::ofstream fout(outputPath, std::ios::trunc);
	for (int j = 0; j < lowResImg.getSize().y; j += scaleY) {
		for (int i = 0; i < lowResImg.getSize().x; i += scaleX)
			fout << ascii[(int)lowResImg.getPixel(i, j).r / 255.f * ascii.size()];
		fout << std::endl;
	}


	return 0;
}