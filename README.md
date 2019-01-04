# DigitalCircuitAnalysis

This code was written as a final project for RIT's EEEE346 Advanced Programming for Engineers course.

This project presents a way of implementing data structures for simulating and analyzing digital logic gates. It also includes functionality for connecting multiple gates in a circuit network, including circuits that require feedback such as memory elements. There is basic file processing functionality to take a text file containing a circuit description and create a network of Gate objects representing it.

The primary functionality of this project is in the various classes it implements. The main.cpp file simply contains test code that verifies the functionality of different classes and does not represent a full application built around the class framework for creating and testing arbitrary circuits. The file processing capability is also currently limited as it does not currently fully allow for circuits with multiple outputs or with feedback (although the capabilities of the Circuit and Gate classes support these concepts).

The Boost libraries are required to compile this project. This project was written and tested using Visual Studio 2017 on Windows 10, but the code was designed to be portable and *should* compile and run on other platforms.
