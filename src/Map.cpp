/*!
 * \file Map.cpp
 * \brief Map class implementation
 * \author João Gonçalves
 */

#include "Map.hpp"
#include <cstdlib>
#include <sys/time.h>
#include <stack>
#include <list>


Map::Map(sf::RenderWindow& window, const std::string& path): window(window){

	//Load tile textures
	const int count = 'x' - 'a';
	char file[] = "tile-a.png";
	sf::Texture tex;

	//Build deck
	const int weights[] = TILE_WEIGHTS;

	for(int i=0; i<=count; i++){

		file[5] = 'a' + i;

		if( !tex.loadFromFile( path + std::string(file) ) ){
			std::cout << "Error loading file: "<< file << std::endl;
			throw std::runtime_error("png file error");
		}
		TileType tipe = TileType('a' + i);
		textures.emplace(tipe, tex);
		deck.emplace(tipe, weights[i]);

	}
	struct timeval tp;
	gettimeofday(&tp, NULL);
	srand(tp.tv_usec);

	std::shared_ptr<Tile> first(new Tile('d'));
	first->rotate_counter_clockwise();
	this->play(first, START_POSITION);


	playable = nullptr;
	last_played = nullptr;
}

Map::~Map(){

	for(auto it=map.begin(); it!=map.end(); it++){
		it->second.reset();
	}
	playable.reset();

	for(auto it=items.begin(); it!=items.end(); it++){
		it->reset();
	}
}

TileType const& Map::draw(void){

	const int count = this->deck_count();
	if(count == 0)
		throw std::length_error("Deck seems to be empty");


	// To extract one random tile, must be fair with regard to the total number of tiles.
	int v = rand() % count;

	for (auto i = deck.begin(); i != deck.end(); i++){

		if(i->second==0) //This type is all out
			continue;

		if((v-i->second) > 0){ //Not going to land here

			v-=i->second;
		}else{ //Lands here

			return i->first;
		}
	}
	// By default returns the first I guess
	std::cout << "Warning: Random tile pull failed, returning first" << std::endl;
	return deck.begin()->first;
}

int Map::deck_count(void) const{

	int count = 0;

	for (std::map<TileType, int>::const_iterator i = deck.cbegin(); i != deck.cend();  i++){
		count += i->second;
	}

	return count;
}

bool Map::play(std::shared_ptr<Tile> tile, Cell cell){

	//Check if it is the first piece to be set
	if(map.size() == 0){
		map.insert( std::pair<Cell, std::shared_ptr<Tile>>(cell, tile) );

		items.emplace_back(new Field(tile, field1));
		items.emplace_back(new Field(tile, field2));
		items.emplace_back(new Road(tile, road1));
		items.emplace_back(new Castle(tile, castle1));

		return true;
	}

	//Checking if piece fits
	if(this->cellOccupied(cell))
		return false;

	TileType surroundings = this->getSurroundings(cell);
	if(surroundings.getTile() == EMPTY_TILE){
		return false;
	}

	bool flag;

	try{
		flag = fits( (*tile), surroundings);

	}catch( std::exception ){
		// Weird error, should never happen
		return false;
	}

	// Play that piece and decrement the deck
	if(flag){

		map.insert( std::pair<Cell, std::shared_ptr<Tile>>(cell, tile) );
		std::map<TileType, int>::iterator it = deck.find(*tile);
		if (it!=deck.end()){
			if (it->second >0){
				it->second--;
			}else
				return false;
		}else
			return false;

	}else
		return false;

	//	Create and merge MapItems
	//  Im ashamed of this, dont look

	std::list<std::shared_ptr<MapItem>> items;

	switch(tile->getTile()){
		case 'a':{
			std::shared_ptr<Field> f(new Field(tile, field1));
			std::shared_ptr<Road> r(new Road(tile, road1));
			std::shared_ptr<Cloister> c(new Cloister(tile, cloister));
			items.push_back(f);
			items.push_back(r);
			items.push_back(c);
			break;
		}
		case 'b':{
			std::shared_ptr<Field> f(new Field(tile, field1));
			std::shared_ptr<Cloister> c(new Cloister(tile, cloister));
			items.push_back(f);
			items.push_back(c);
			break;
		}
		case 'c':{
			std::shared_ptr<Castle> c(new Castle(tile, castle1));
			items.push_back(c);
			break;
		}
		case 'd':{
			std::shared_ptr<Field> f1(new Field(tile, field1));
			std::shared_ptr<Field> f2(new Field(tile, field2));
			std::shared_ptr<Road> r(new Road(tile, road1));
			std::shared_ptr<Castle> c(new Castle(tile, castle1));
			items.push_back(f1);
			items.push_back(f2);
			items.push_back(r);
			items.push_back(c);
			break;
		}
		case 'e':{
			std::shared_ptr<Field> f(new Field(tile, field1));
			std::shared_ptr<Castle> c(new Castle(tile, castle1));
			items.push_back(f);
			items.push_back(c);
			break;
		}
		case 'f':
		case 'g':{
			std::shared_ptr<Field> f1(new Field(tile, field1));
			std::shared_ptr<Field> f2(new Field(tile, field2));
			std::shared_ptr<Castle> c(new Castle(tile, castle1));
			items.push_back(f1);
			items.push_back(f2);
			items.push_back(c);
			break;
		}
		case 'h':
		case 'i':{
			std::shared_ptr<Field> f(new Field(tile, field1));
			std::shared_ptr<Castle> c1(new Castle(tile, castle1));
			std::shared_ptr<Castle> c2(new Castle(tile, castle2));
			items.push_back(c1);
			items.push_back(c2);
			items.push_back(f);
			break;
		}
		case 'j':
		case 'k':{
			std::shared_ptr<Field> f1(new Field(tile, field1));
			std::shared_ptr<Field> f2(new Field(tile, field2));
			std::shared_ptr<Castle> c(new Castle(tile, castle1));
			std::shared_ptr<Road> r(new Road(tile, road1));
			items.push_back(c);
			items.push_back(r);
			items.push_back(f1);
			items.push_back(f2);
			break;
		}
		case 'l':{
			std::shared_ptr<Field> f1(new Field(tile, field1));
			std::shared_ptr<Field> f2(new Field(tile, field2));
			std::shared_ptr<Field> f3(new Field(tile, field3));
			std::shared_ptr<Castle> c(new Castle(tile, castle1));
			std::shared_ptr<Road> r1(new Road(tile, road1));
			std::shared_ptr<Road> r2(new Road(tile, road2));
			std::shared_ptr<Road> r3(new Road(tile, road3));
			items.push_back(c);
			items.push_back(r1);
			items.push_back(r2);
			items.push_back(r3);
			items.push_back(f1);
			items.push_back(f2);
			items.push_back(f3);
			break;
		}
		case 'm':
		case 'n':{
			std::shared_ptr<Field> f(new Field(tile, field1));
			std::shared_ptr<Castle> c(new Castle(tile, castle1));
			items.push_back(c);
			items.push_back(f);
			break;
		}
		case 'o':
		case 'p':{
			std::shared_ptr<Field> f1(new Field(tile, field1));
			std::shared_ptr<Field> f2(new Field(tile, field2));
			std::shared_ptr<Castle> c(new Castle(tile, castle1));
			std::shared_ptr<Road> r(new Road(tile, road1));
			items.push_back(c);
			items.push_back(r);
			items.push_back(f1);
			items.push_back(f2);
			break;
		}
		case 'q':
		case 'r':{
			std::shared_ptr<Field> f(new Field(tile, field1));
			std::shared_ptr<Castle> c(new Castle(tile, castle1));
			items.push_back(c);
			items.push_back(f);
			break;
		}
		case 's':
		case 't':{
			std::shared_ptr<Field> f1(new Field(tile, field1));
			std::shared_ptr<Field> f2(new Field(tile, field2));
			std::shared_ptr<Castle> c(new Castle(tile, castle1));
			std::shared_ptr<Road> r(new Road(tile, road1));
			items.push_back(c);
			items.push_back(r);
			items.push_back(f1);
			items.push_back(f2);
			break;
		}
		case 'u':
		case 'v':{
			std::shared_ptr<Field> f1(new Field(tile, field1));
			std::shared_ptr<Field> f2(new Field(tile, field2));
			std::shared_ptr<Road> r(new Road(tile, road1));
			items.push_back(r);
			items.push_back(f1);
			items.push_back(f2);
			break;
		}
		case 'w':{
			std::shared_ptr<Field> f1(new Field(tile, field1));
			std::shared_ptr<Field> f2(new Field(tile, field2));
			std::shared_ptr<Field> f3(new Field(tile, field3));
			std::shared_ptr<Road> r1(new Road(tile, road1));
			std::shared_ptr<Road> r2(new Road(tile, road2));
			std::shared_ptr<Road> r3(new Road(tile, road3));
			items.push_back(r1);
			items.push_back(r2);
			items.push_back(r3);
			items.push_back(f1);
			items.push_back(f2);
			items.push_back(f3);
			break;
		}
		case 'x':{
			std::shared_ptr<Field> f1(new Field(tile, field1));
			std::shared_ptr<Field> f2(new Field(tile, field2));
			std::shared_ptr<Field> f3(new Field(tile, field3));
			std::shared_ptr<Field> f4(new Field(tile, field4));
			std::shared_ptr<Road> r1(new Road(tile, road1));
			std::shared_ptr<Road> r2(new Road(tile, road2));
			std::shared_ptr<Road> r3(new Road(tile, road3));
			std::shared_ptr<Road> r4(new Road(tile, road4));
			items.push_back(r1);
			items.push_back(r2);
			items.push_back(r3);
			items.push_back(r4);
			items.push_back(f1);
			items.push_back(f2);
			items.push_back(f3);
			items.push_back(f4);
			break;
		}
		default: break;
	}

	this->mergeItems(cell, items);

	last_played=tile;
	playable=nullptr;

	return true;
}

void Map::render(void) const{

	sf::Sprite sprite;
	const int radius = 8;
	const float sqrt2 = 0.7071068;

	for(auto i = map.begin(); i!= map.end(); i++){

		Cell cell = i->first;
		Tile tile = *(i->second);

		std::map<TileType, sf::Texture>::const_iterator it = textures.find(tile);
		if(it == textures.end()){
			//std::cout << "Error looking up texture" << std::cout;
			continue;
		}

		sprite.setTexture(it->second);
		sprite.setRotation(tile.getOrientation());
		int mod_x=(tile.getOrientation()==90 || tile.getOrientation()==180) ? 1 : 0;
		int mod_y=(tile.getOrientation()>90) ? 1 : 0;
		sprite.setPosition(sf::Vector2f(CELL_DIM*(cell.getX()+mod_x), CELL_DIM*(cell.getY()+mod_y)));
		window.draw(sprite);
	}
	if(playable){
		std::map<TileType, sf::Texture>::const_iterator it = textures.find(*playable);
		if(it == textures.cend())
			return; //Maybe exception
		sprite.setTexture(it->second);
		sprite.setRotation(playable->getOrientation());
		int mod_x=(playable->getOrientation()==90 || playable->getOrientation()==180) ? CELL_DIM/2 : -CELL_DIM/2;
		int mod_y=(playable->getOrientation()>90) ? CELL_DIM/2 : -CELL_DIM/2;
		sprite.setPosition(playable_pos+sf::Vector2f(mod_x, mod_y));
		window.draw(sprite);
	}
	if(last_played){
		Cell c;
		//Pull cell
		for(auto it = map.cbegin(); it!= map.cend(); it++){
			if(it->second == last_played){
				c=it->first;
				break;
			}
		}
		sf::CircleShape circle(radius, 30);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(1);
		circle.setOrigin(radius*sqrt2, radius*sqrt2);
		sf::Vector2f o_position(c.getX()*CELL_DIM, c.getY()*CELL_DIM);

		std::list<TypeIdentifier> list;
		this->getFreeRealEstate(last_played, list);

		sf::Vector2f offset;

		for(auto it=list.cbegin(); it!=list.cend(); it++){
			offset=last_played->getItemPosition(*it);
			circle.setPosition(o_position+offset);
			window.draw(circle);
		}
	}
}


std::ostream& operator<<(std::ostream& os, const Map& map){

	/*
	// Show deck contents

	os << std::endl << "showing deck" << std::endl;
	const int weights[] = TILE_WEIGHTS;
	for(auto it = map.deck.cbegin(); it != map.deck.cend(); it++){

		os << it->first.getDescription() << " -- count: "
		   << it->second << '/' << weights[(int)it->first.getTile()-'a']
		   << std::endl;

	}
	*/

	/*
	// Show MapItems
	os<< "-------------------------------------"<<std::endl;

	for(auto it=map.items.cbegin(); it!=map.items.cend(); it++){
		os << "Showing Item:"<< std::endl << **it << std::endl;
	}
	*/

	// Count MapItems
	int count=0;
	for(auto it=map.items.cbegin(); it!=map.items.cend(); it++){
		count++;
	}
	os << "Map has " << count << " items." << std::endl;


	return os;
}

void Map::setPlayable(std::shared_ptr<const Tile> tile){

	playable = tile;

}
void Map::setPlayablePos(int x, int y){

	playable_pos.x=x;
	playable_pos.y=y;
}

void Map::clearPlayable(void){

	playable.reset();

}

TileType Map::getSurroundings(const Cell& c) const{

	Cell aux = c + Cell(1,0); // cell to the right

	ItemType up, right, down, left;

	try{
		right = map.at(aux)->getLeft();
	}catch(std::out_of_range){
		right = none;
	}

	aux = c + Cell(0,1); // Cell to the bottom

	try{
		down = map.at(aux)->getUp();
	}catch(std::out_of_range){
		down = none;
	}

	aux = c + Cell(-1, 0); // Cell to the left

	try{
		left = map.at(aux)->getRight();
	}catch(std::out_of_range){
		left = none;
	}

	aux = c + Cell(0, -1); // Cell to the top

	try{
		up = map.at(aux)->getDown();
	}catch(std::out_of_range){
		up = none;
	}

	return TileType(up, right, down, left);
}

bool Map::cellOccupied(const Cell& c)const{

	return (bool)map.count(c);

}

std::shared_ptr<const Tile> Map::getTileAt(Cell c)const{

	for(auto it=map.cbegin(); it!=map.cend(); it++){

		if(it->first == c)
			return it->second;

	}

	return nullptr;
}

bool Map::mergeItems(Cell c, std::list<std::shared_ptr<MapItem>>& newitems){

	std::shared_ptr<Tile> tile, other;
	std::tuple<TypeIdentifier, TypeIdentifier, TypeIdentifier> t1, t2;
	std::shared_ptr<MapItem> item1, item2;

	if(!this->cellOccupied(c))
		throw std::length_error("Tile not found");

	tile=this->map[c];

	Cell nei;
	Direction dir1, dir2;

	for(int i=0; i<4; i++){

		if(i==0){//Up
			nei=c+Cell(0,-1);
			dir1=up;
			dir2=down;
		}
		if(i==1){//Right
			nei=c+Cell(1,0);
			dir1=right;
			dir2=left;
		}
		if(i==2){//Down
			nei=c+Cell(0,1);
			dir1=down;
			dir2=up;
		}
		if(i==3){//Left
			nei=c+Cell(-1,0);
			dir1=left;
			dir2=right;
		}
		if(this->cellOccupied(nei)){

			other=this->map[nei];
			t1=tile->getMapItems(dir1);
			t2=other->getMapItems(dir2);

			if(tile->getSide(dir1) != road){

				item1=getItem(newitems, tile, std::get<0>(t1));
				if(item1 == nullptr){
					item1=getItem(this->items, tile, std::get<0>(t1));

					if(item1 == nullptr){std::cout << "Failed at Alpha "<<i << std::endl; return false;}


					//this->items.remove(item1);
				}
				else{
					newitems.remove(item1);
				}
				item2=getItem(this->items, other, std::get<0>(t2));
				if(item2 == nullptr){std::cout << "Failed at Bravo "<<i << std::endl; return false;}
				if((this->mapItemExists(item1))&&(this->mapItemExists(item2))&&(item1 != item2))
					this->items.remove(item1);
				item2->mergeWith(item1);

			}else{
				item1=getItem(newitems, tile, std::get<0>(t1));
				if(item1 == nullptr){
					item1=getItem(this->items, tile, std::get<0>(t1));

					if(item1 == nullptr){std::cout << "Failed at Charlie "<<i << std::endl; return false;}


					//this->items.remove(item1);
				}
				else{
					newitems.remove(item1);
				}
				item2=getItem(this->items, other, std::get<1>(t2));
				if(item2 == nullptr){std::cout << "Failed at Echo "<<i << std::endl; return false;}
				if((this->mapItemExists(item1))&&(this->mapItemExists(item2))&&(item1 != item2))
					this->items.remove(item1);
				item2->mergeWith(item1);

				/////////////////////////////////////////

				item1=getItem(newitems, tile, std::get<1>(t1));
				if(item1 == nullptr){
					item1=getItem(this->items, tile, std::get<1>(t1));

					if(item1 == nullptr){std::cout << "Failed at Delta "<<i << std::endl; return false;}


					//this->items.remove(item1);
				}
				else{
					newitems.remove(item1);
				}
				item2=getItem(this->items, other, std::get<0>(t2));
				if(item2 == nullptr){std::cout << "Failed at Foxtrot " <<i<< std::endl; return false;}
				if((this->mapItemExists(item1))&&(this->mapItemExists(item2))&&(item1 != item2))
					this->items.remove(item1);
				item2->mergeWith(item1);

				///////////////////////////////////////////////////

				item1=getItem(newitems, tile, std::get<2>(t1));
				if(item1 == nullptr){
					item1=getItem(this->items, tile, std::get<2>(t1));

					if(item1 == nullptr){std::cout << "Failed at Golf" << std::endl; return false;}


					//this->items.remove(item1);
				}
				else{
					newitems.remove(item1);
				}
				item2=getItem(this->items, other, std::get<2>(t2));
				if(item2 == nullptr){std::cout << "Failed at Hotel" << std::endl; return false;}
				if((this->mapItemExists(item1))&&(this->mapItemExists(item2))&&(item1 != item2))
					this->items.remove(item1);
				item2->mergeWith(item1);
			}

		}
	}

	//Insert remaining items
	for(auto it=newitems.begin(); it!=newitems.end(); it++){
		this->items.push_back(*it);
	}
	return true;

}

std::shared_ptr<MapItem> getItem(std::list<std::shared_ptr<MapItem>>& origin, std::shared_ptr<Tile> tile, TypeIdentifier type){

	for(auto it=origin.begin(); it!=origin.end(); it++){
		if((**it).hasItem(tile, type))
			return *it;
	}
	return nullptr;
}

bool Map::mapItemExists(std::shared_ptr<MapItem> item)const{

	for(auto it=this->items.cbegin(); it!=this->items.cend(); it++){
		if(item == *it)
			return true;
	}
	return false;
}


void Map::getFreeRealEstate(std::shared_ptr<Tile> tile, std::list<TypeIdentifier>& target)const{

	for(auto it=this->items.cbegin(); it!=this->items.cend(); it++){

		if((*it)->hasTile(tile)){

			(*it)->freeRealEstate(tile, target);

		}

	}

}

bool Map::setPiece(TypeIdentifier t, std::shared_ptr<Player> player){

	if(!player->hasPieces())
		return false;

	for(auto it=items.begin(); it!=items.end(); it++){

		if((*it)->hasItem(last_played, t)){
			if((*it)->claim(last_played, t, player)){
				//player->takePiece();
				return true;
			}
		}

	}

	return false;

}


bool Map::selectItemAt(sf::Vector2f pos, std::shared_ptr<Player> player){
	//player->takePiece();



	last_played=nullptr;
	return (true || pos.x==0); //Stub
}
