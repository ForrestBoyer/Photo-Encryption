#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"

// Function to encrypt image using LFSR
void transform(sf::Image& image, FibLFSR* lfsr){

    // p is a pixelimage.getPixel(x, y);
        sf::Color p;

        // Vector representing size of image
        sf::Vector2u size = image.getSize();

        for (int x = 0; x < int(size.x); x++) {
            for (int y = 0; y < int(size.y); y++) {
                p = image.getPixel(x, y);
                // Generates new rgb values
                p.r = (p.r ^ lfsr->generate(8));
                p.g = (p.g ^ lfsr->generate(8));
                p.b = (p.b ^ lfsr->generate(8));
                image.setPixel(x, y, p);
            }
        }
}

int main(int argc, char *argv[])
{
    // Checking correct number of inputs in command line
	if(argc != 4){
        std::cout << "Incorrect number of command line arguments" << std::endl;
        return -1;
    }

    // Loading image from input file
    sf::Image image;
	if (!image.loadFromFile(argv[1]))
		return -1;

    // Converting alphanumeric input password into 16 0's and 1's for LFSR input
    string pass = argv[3];

    // Checks that input password is 16 characters long
    if(int(pass.size()) != 16){
        std::cout << "Incorrect password length, must be 16 characters" << std::endl;
        return -1;
    }
    
    string bits = "";
    // Loop through each letter in input string
    for(int i = 0; i < int(pass.size()); i++){
        int val = int(pass[i]);
        // If the ascii value of the letter is even add a 0 to the LFSR starting bits, if it's odd add a 1
        if(val % 2 == 0){
            bits.append("0");
        }
        else{
            bits.append("1");
        }
    }
    FibLFSR lfsr(bits);

    // Renders window #1 for pre-encrypted image
    sf::Vector2u size = image.getSize();
    sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Meow");

    // Sets textures for window
	sf::Texture texture;
	texture.loadFromImage(image);

    // Created sprites for window
	sf::Sprite sprite;
	sprite.setTexture(texture);

    // Calls transform function to encrypt image
    transform(image, &lfsr);

    // Saving image to output file
	if (!image.saveToFile(argv[2]))
		return -1;

    // Loading encrypted image as image 2
    sf::Image image2;
	if (!image2.loadFromFile(argv[2]))
		return -1;

    // Renders window 2 for post-encrypted image
    sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "Meow Encrypted");

    // Sets textures for window 2
	sf::Texture texture2;
	texture2.loadFromImage(image2);

    // Created sprites for window 2
	sf::Sprite sprite2;
	sprite2.setTexture(texture2);


    // Event loop to run windows to display images
	while (window1.isOpen() && window2.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window1.close();
        }
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window2.close();
        }
        window1.clear();
        window1.draw(sprite);
        window1.display();
        window2.clear();
        window2.draw(sprite2);
        window2.display();
    }

	return 0;
}