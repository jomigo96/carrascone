/*!
 * \file Field.hpp
 * \brief Field header file
 * \author João Gonçalves
 */

#ifndef FIELD_HPP
#define FIELD_HPP

#include "MapItem.hpp"
#include <ostream>

/*!
 * \class Field
 * \brief 
 * */
class Field : public MapItem{
	
public:
	Field();
	Field(std::shared_ptr<Tile> tile, TypeIdentifier key);
	~Field();
	
	std::ostream& myprint(std::ostream& os, const Field& f)const;

private:

};
#endif /* FIELD_HPP */
