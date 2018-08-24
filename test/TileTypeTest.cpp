#include <iostream>
#include "TileType.hpp"


int main(void){
	
	std::cout << "Running test on TileType" << std::endl;
	
	std::cout << "Testing circle comparison" << std::endl;
	
	bool flag;
	unsigned a,b,c,d,e,f,g,h;
	
	a=1; b=2; c=3; d=4; e=2; f=3; g=4; h=1;
	flag=circle_comparison(a,b,c,d,e,f,g,h);
	std::cout << (flag? "OK" : "Fail") << std::endl;
	
	a=1; b=1; c=1; d=1; e=2; f=3; g=4; h=1;
	flag=circle_comparison(a,b,c,d,e,f,g,h);
	std::cout << (flag? "Fail" : "OK") << std::endl;
	
	a=1; b=2; c=3; d=4; e=1; f=2; g=3; h=4;
	flag=circle_comparison(a,b,c,d,e,f,g,h);
	std::cout << (flag? "OK" : "Fail") << std::endl;
	
	a=1; b=2; c=3; d=4; e=1; f=3; g=4; h=1;
	flag=circle_comparison(a,b,c,d,e,f,g,h);	
	std::cout << (flag? "Fail" : "OK") << std::endl;
	
	a=1; b=2; c=3; d=4; e=2; f=3; g=4; h=1;
	flag=circle_comparison(a,b,c,d,e,f,g,h);
	std::cout << (flag? "OK" : "Fail") << std::endl;
	
	a=1; b=1; c=1; d=1; e=1; f=1; g=1; h=1;
	flag=circle_comparison(a,b,c,d,e,f,g,h);
	std::cout << (flag? "OK" : "Fail") << std::endl;
	
	TileType* tile;
	
	tile = new TileType(field, field, field, castle, false, false);
	std::cout << *tile;
	delete tile;
	tile = new TileType(castle, castle, castle, castle, true, false);
	std::cout << *tile;
	delete tile;	
	tile = new TileType(field, field, field, field, false, false);
	std::cout << *tile;
	delete tile;	
	tile = new TileType(field, castle, field, castle, false, true);
	std::cout << *tile;
	delete tile;
	tile = new TileType(field, castle, field, castle, true, true);
	std::cout << *tile;
	delete tile;
	tile = new TileType(field, castle, field, castle, false, false);
	std::cout << *tile;
	delete tile;	
	tile = new TileType(road, castle, road, castle, false, false);
	std::cout << *tile;
	delete tile;	
	tile = new TileType(field, field, field, road);
	std::cout << *tile;
	delete tile;
	tile = new TileType(field, field, road, road);
	std::cout << *tile;
	delete tile;
	tile = new TileType(field, road, field, field);
	std::cout << *tile;
	delete tile;
	tile = new TileType(field, field, field, road);
	std::cout << *tile;
	delete tile;
	
	return 0;
	
}
