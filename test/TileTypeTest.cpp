#include <iostream>
#include "TileType.hpp"


int main(void){
	
	std::cout << "Running test on TileType" << std::endl;
		
	TileType tile(field, field, field, castle);
	
	std::cout << tile;
	
	return 0;
	
}
