#include "TileType.hpp"
#include <stdint.h>

TileType::TileType(ItemType up, ItemType right, ItemType down, ItemType left, bool shield, bool connected):
up(up), right(right), down(down), left(left), shield(shield), connected(connected){
	
	tile = 0;
	this->attribute();
}

TileType::TileType(ItemType up, ItemType right, ItemType down, ItemType left):
up(up), right(right), down(down), left(left){
	
	connected=false;
	shield=false;
	tile = 0;
	this->attribute();
}
	
TileType::TileType(char tile): tile(tile){
		
	if(tile == 0)
		throw std::invalid_argument("Can't call with 0, asshole");
		
	this->attribute();
}
	
TileType::~TileType(){}
	
// Will return true if they have the same letter, always false if any is an incomplete tile
bool TileType::operator==(const TileType& other) const{
	
	char tile2 = other.getTile();
	
	if((tile >= 'a') && (tile2 >= 'a'))
		return tile==tile2;
	else
		return false;
}
	
bool TileType::operator!=(const TileType& other) const{

	return !(*this==other);
}
	
std::ostream& operator<<( std::ostream& out, const TileType& type ){
	
	if(type.getTile()>='a'){
		
		out << "This tile is a " << type.getDescription() << std::endl;
	}
	else{
		out << "Tile type --- " << "Up: " << type.up << " Right: "<< type.right << 
		" Down: " << type.down << " Left: " << type.left << 
		(type.connected ? " - Castles connected - " : " - castles not connected - ") <<
		(type.shield ? "No shield" : "With shield") << std::endl;
	}
	return out;
}
	
	
bool TileType::operator[](const TileType& other) const{

	return false;
}
	
bool TileType::isValid(void) const{
	
	return tile>='a';
}
	
bool TileType::hasShield(void) const{

	return shield;
}

char TileType::getTile(void) const{
	
	return tile;
}

std::string const& TileType::getDescription(void) const{
	
	return description;
}

void TileType::attribute(void){
	
	bool flag=true;
	
	if(tile == 0){
		// assigned with each boundary
		
		if((up==none)||(right==none)||(down==none)||(left==none)){
			tile=INCOMPLETE_TILE;
			return;
		}else{
			
			for(char c='a'; c<='x'; c++){
				
				TileType p(c);
				if(circle_comparison((unsigned)up, (unsigned)right,
					(unsigned)down, (unsigned)left, (unsigned)p.getUp(),
					(unsigned)p.getRight(), (unsigned)p.getDown(), 
					(unsigned)p.getLeft())){	
					
					if((connected==p.isConnected())&&(shield==p.hasShield())){
						tile=c;
						flag=false;
						break;
					}
				}
			}
			if(flag){
				tile=INVALID_TILE;
				return;
			}
		}
		
	}
		// assigned by key	
		
		switch (tile){
		
			case 'a':
				up=field;
				right=field;
				down=road;
				left=field;
				description = std::string("Cloister with road");
				shield=false;
				connected=false;
				break;
			case 'b':
				up=field;
				right=field;
				down=field;
				left=field;
				description = std::string("Cloister");
				shield=false;
				connected=false;		
				break;				
			case 'c':
				up=castle;
				right=castle;
				down=castle;
				left=castle;
				description = std::string("4-sided castle");
				shield=true;
				connected=false;			
				break;	
					
			case 'd':
				up=road;
				right=castle;
				down=road;
				left=field;
				description = std::string("Single castle with road horizontal");
				shield=false;
				connected=false;			
				break;
			case 'e':
				up=castle;
				right=field;
				down=field;
				left=field;
				description = std::string("Single castle");
				shield=false;
				connected=false;
				break;				
			case 'f':
				up=field;
				right=castle;
				down=field;
				left=castle;
				description = std::string("Horizontal castle, no shield");
				shield=false;
				connected=true;			
				break;				
			case 'g':
				up=castle;
				right=field;
				down=castle;
				left=field;
				description = std::string("Horizontal castle, shielded");
				shield=true;
				connected=true;
				break;				
			case 'h':
				up=field;
				right=castle;
				down=field;
				left=castle;
				description = std::string("Castles across, divided");
				shield=false;
				connected=false;
				break;				
			case 'i':
				up=field;
				right=castle;
				down=castle;
				left=field;
				description = std::string("Side by side castles, divided");
				shield=false;
				connected=false;				
				break;				
			case 'j':
				up=castle;
				right=road;
				down=road;
				left=field;
				description = std::string("Single castle, right turn");
				shield=false;
				connected=false;
				break;				
			case 'k':
				up=road;
				right=castle;
				down=field;
				left=road;
				description = std::string("Single castle, left turn");
				shield=false;
				connected=false;
				break;				
			case 'l':
				up=road;
				right=castle;
				down=road;
				left=road;
				description = std::string("Single castle and intersection");
				shield=false;
				connected=false;
				break;				
			case 'm':
				up=castle;
				right=field;
				down=field;
				left=castle;
				description = std::string("Turning castle, shielded");
				shield=true;
				connected=true;
				break;				
			case 'n':
				up=castle;
				right=field;
				down=field;
				left=castle;
				description = std::string("Turning castle, unshielded");
				shield=false;
				connected=true;
				break;				
			case 'o':
				up=castle;
				right=road;
				down=road;
				left=castle;
				description = std::string("Turning castle and turning road, shielded");
				shield=true;
				connected=true;				
				break;			
			case 'p':
				up=castle;
				right=road;
				down=road;
				left=castle;
				description = std::string("Turning castle and turning road, unshielded");
				shield=false;
				connected=true;
				break;				
			case 'q':
				up=castle;
				right=castle;
				down=field;
				left=castle;
				description = std::string("3-Way castle, no road, shielded");
				shield=true;
				connected=false;
				break;				
			case 'r':
				up=castle;
				right=castle;
				down=field;
				left=castle;
				description = std::string("3-Way castle, no road, unshielded");
				shield=false;
				connected=false;
				break;				
			case 's':
				up=castle;
				right=castle;
				down=road;
				left=castle;
				description = std::string("3-Way castle, road, shielded");
				shield=true;
				connected=false;
				break;				
			case 't':
				up=castle;
				right=castle;
				down=road;
				left=castle;
				description = std::string("3-Way castle, road, unshielded");
				shield=false;
				connected=false;
				break;					
			case 'u':
				up=road;
				right=field;
				down=road;
				left=field;
				description = std::string("Straight road");
				shield=false;
				connected=false;
				break;				
			case 'v':
				up=field;
				right=field;
				down=road;
				left=road;
				description = std::string("Road turn");
				shield=false;
				connected=false;
				break;
			case 'w':
				up=field;
				right=road;
				down=road;
				left=road;
				description = std::string("3-way intersection");
				shield=false;
				connected=false;
				break;				
			case 'x':
				up=road;
				right=road;
				down=road;
				left=road;
				description = std::string("4-way intersection");
				shield=false;
				connected=false;
				break;
			default:
				tile=INVALID_TILE;
				up=none;
				right=none;
				down=none;
				left=none;
				shield=false;
				description = std::string("Invalid tile");
				break;																	
		}
		return;
	
}

bool TileType::isConnected() const{
	return connected;		
}

int TileType::getUp() const{
	return up;
}
	
int TileType::getRight() const{
	return right;
}
	
int TileType::getLeft() const{
	return left;
}
	
int TileType::getDown() const{
	return down;
}


// Non member functions

bool circle_comparison(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h){
	
	const uint16_t mask = 15; // 0000 0000 0000 1111
	
	uint16_t tag1 = a & mask;
	tag1 <<= 4;
	tag1 += b & mask;
	tag1 <<= 4;
	tag1 += c & mask;
	tag1 <<= 4;
	tag1 += d & mask;
	
	uint16_t tag2 = e & mask;
	tag2 <<= 4;
	tag2 += f & mask;
	tag2 <<= 4;
	tag2 += g & mask;
	tag2 <<= 4;
	tag2 += h & mask;	
	
	for(int i=0; i<4; i++){
		
		if(tag1 == tag2)
			return true;
			
		tag1 = (tag1 << 4) | (tag1 >> 12);	
	}
	return false;
}



