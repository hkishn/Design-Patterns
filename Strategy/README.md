# Definition
The strategy pattern defines a family of algorithms, encapsulates each one, and make them interchangeable.
Strategy lets the algorithm vary independenlty from client that uses it.

# Design principle of strategy desing pattern
## 1. Identify the aspects of your application that vary and separate them from what stays the same.
This means take the parts that vary and encapsulate them, so that later you can alter or extend the parts that vary without affecting those don't change.

# Design beneifts
This will give two advantages:
a) Take what varies and "encapsulate" it so it won't affect the rest of your code.
b) Fewer unintended consequences from code changes anf more flexibility in your systems.

## 2. Program to an interface, not an implementation.

# Installation
Clone the GitHub repository and compile the source code 

$ git clone https://github.com/hkishn/Design-Patterns/edit/master/Strategy/
$ cd Strategy
$ g++ -o strategy Strategy.cpp
$ ./strategy

# License
The source code is distributed under the MIT license
