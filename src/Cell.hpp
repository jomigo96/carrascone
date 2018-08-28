#ifndef CELL_HPP
#define CELL_HPP
/*!
 * \file Cell.hpp
 * \brief Cell class
 */


#include <cstdlib>
#define CELL_DIM 78

/*!
 * \class Cell
 * \brief Grid system, with the same axis as the SFML window
 *
 */
class Cell{
public:
	/*!
     * \brief Default contructor
     */
	Cell();
	
	/*!
     * \brief Constructor
     * 
     * \param x x grid coordinate
     * \param y y grid coordinate
     */
	Cell(int x, int y);
	
	/*!
     * \brief Destructor
     */
	~Cell();
	
	/*!
     * \brief Copy assignment
     */
	Cell& operator=(const Cell& other);
	
	/*!
     * \brief Comparison operator
     * 
     * Returns true if and only if both coordinates are the same
     */
	bool operator==(const Cell& other)const;
	
	bool operator<(const Cell& other)const;
	
	/*!
     * \brief subtraction operator
     * 
     * The result is a displacement, analogous to a cartesian vector
     */
	Cell operator-(const Cell& other)const;
	
	/*!
     * \brief adition operator
     * 
     * Analogous to adding vectors
     */
	Cell operator+(const Cell& other)const;
	
	/*!
     * \brief Return the greatest coordinate
     */	
	int greatest()const;
	
	/*!
     * \brief Return X coordinate
     */
	int getX()const;
	
	/*!
     * \brief Return Y coordinate
     */
	int getY()const;
    
private:	
	int x;
	int y;
};


#endif /* CELL_HPP */
