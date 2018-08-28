#include "Cell.hpp"

Cell::Cell(){
	x=0;
	y=0;
}

Cell::Cell(int x, int y) : x(x), y(y) {}

Cell::~Cell(){}

Cell& Cell::operator=(const Cell& other){

	this->x=other.getX();
	this->y=other.getY();
	
	return *this;
}

bool Cell::operator==(const Cell& other)const{
	
	return ((this->x==other.getX()) && (this->y==other.getY()));
}

Cell Cell::operator+(const Cell& other)const{
	
	return Cell(this->x+other.getX(), this->y+other.getY());
}

Cell Cell::operator-(const Cell& other)const{
	
	return Cell(this->x-other.getX(), this->y-other.getY());
}
		
int Cell::getX()const{
	
	return x;
}

int Cell::getY()const{
	
	return y;
}

int Cell::greatest()const{
	
	return (abs(x)>abs(y)) ? abs(x) : abs(y);
}

bool Cell::operator<(const Cell& other)const{
	
	if (x==other.getX())
		return y<other.getY();
	return x<other.getX();
}
