# Documentation directory

Project documentation (if I ever bothered to make it) goes here.
Uses [doxygen](http://www.doxygen.nl/), follow their website for installation procedure.

## Generate documentation

Go to the ```/src``` directory and run
```
make doc
```
to generate the documentation. Open ```index.html``` in ```/doc/html```. If you have latex intalled and wish for a pdf format, go to the ```/doc/latex``` directory and run 
```
make
```
The pdf file will be ```/doc/latex/refman.pdf```.
