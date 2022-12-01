UML-Maker

This is a mini-project aiming to create a universal uml generator for common programming languages.

## Requirements

- Doxygen<br>
  https://www.doxygen.nl/manual/index.html<br>
  Doxygen is a software(or command line tool) to produce documentation of source codes. It supports languages like C, C++, Python, Java, etc.It generates HTML, LaTeX, or XML documents of the code such that they can be documented or parsed to obtain contents of the code.<br> <br>
  **In our project,**<br>
  We use doxygen to generate an XML document of the source code, to get all the classes and properties of the classes of the source code.<br><br>
- Plantuml <br>https://plantuml.com/ <br>https://github.com/SamuelMarks/python-plantuml <br>**PlantUML** is an open-source tool allowing users to create diagrams from a specialized plain text language.<br><br>**In our project,**<br>We use plantuml-python integration(2nd link) to generate a png image from the .pu file already created after parsing the source code<br>
  
  #### **Installation**
  
  Use command *pip install plantuml* to install plantuml in your device<br>We also recommend to use command *pip install six* for better python compatibility<br>
  
  ## How to Run
  

- Clone this repository to your local system
- Run main.cpp from your system using git bash or cmd to generate main.exe or main.out file
- Copy main.exe/main.out to your project folder and run it
- You will see plantUml.png file in your folder, which contains the UML diagram
