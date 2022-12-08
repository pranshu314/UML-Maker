# UML-Maker

This is a mini-project aiming to create a universal uml generator for c++ projects.
This project can be used to create UML-diagrams for C++ projects easily, using only a few commands.

## Requirements

- Doxygen<br>
  https://www.doxygen.nl/manual/index.html<br>
  Doxygen is a software(or command line tool) to produce documentation of source codes. It supports languages like C, C++, Python, Java, etc.It generates HTML, LaTeX, or XML documents of the code such that they can be documented or parsed to obtain contents of the code.<br>
  **In our project,**<br>
  &emsp;We use doxygen to generate an XML document of the source code, to get all the classes and properties of the classes of the source code.<br><br>
- Python/Python3 <br>
https://www.python.org/<br>
We use python to use the plantuml library to generate images.<br><br>
- Plantuml <br>https://plantuml.com/ <br>https://github.com/SamuelMarks/python-plantuml <br>**PlantUML** is an open-source tool allowing users to create diagrams from a specialized plain text language.<br>**In our project,**<br>&emsp;We use plantuml-python integration(2nd link) to generate a png image from the .pu file already created after parsing the source code<br>
  
  #### **Installation**
  &emsp;Use command *pip install plantuml* to install plantuml in your device<br>&emsp;We also recommend to use command *pip install six* for better python compatibility<br>
  
## How to Run
  

- Clone this repository to your local system
- Run main.cpp from your system using git bash or cmd to generate main.exe or main.out file
- Copy main.exe/main.out to your project folder and run it
- You will see plantUml.png file in your folder, which contains the UML diagram

## UML
![plantUml](https://user-images.githubusercontent.com/98077125/206403935-b1d61cc9-1a04-47bc-870b-567e59917923.png)

## Output
- UML for this project
![plantUml](https://user-images.githubusercontent.com/98077125/206411284-29626d33-2c5c-499c-8690-24930f2908e2.png)

## Constraints
- Can be used for one file only

## Creators
- Aswajith K K &emsp;&nbsp;&nbsp;211104 <br>
- Pranshu Goyal &ensp;211126
