# include <bits/stdc++.h>
# include <iostream>
# include <fstream>
# include "rapidxml/rapidxml.hpp"
using namespace std;

class DoxygenConfig
{
    private:
        void generateConfig()
        {
            system("doxygen -s -g");
        }

        void modifyConfig()
        {
            fstream doxy_file;
            string line;
            doxy_file.open("Doxyfile", ios::in | ios::out);
            while(doxy_file)
            {
                int st_location=doxy_file.tellg();
                getline(doxy_file,line);
                if(line=="-1")
                {
                    break;
                }
                else if(line=="EXTRACT_ALL            = NO")
                {
                    doxy_file.seekg(st_location);
                    doxy_file<<"EXTRACT_ALL           = YES"<<endl;
                }
                else if(line=="GENERATE_LATEX         = YES")
                {
                    doxy_file.seekg(st_location);
                    doxy_file<<"GENERATE_LATEX         = NO"<<endl;
                }
                else if(line=="GENERATE_XML           = NO")
                {
                    doxy_file.seekg(st_location);
                    doxy_file<<"GENERATE_XML          = YES"<<endl;
                }
                else if(line=="GENERATE_HTML          = YES")
                {
                    doxy_file.seekg(st_location);
                    doxy_file<<"GENERATE_HTML          = NO"<<endl;
                }
            }
        }
    
    public:
        DoxygenConfig()
        {
            ifstream file_exist_check;
            file_exist_check.open("Doxyfile");
            if(file_exist_check)
            {
                system("rm Doxyfile");
            }
            generateConfig();
            modifyConfig();
        }
};

class XMLParser
{
    private:
        void generateXMLFiles()
        {
            system("doxygen Doxyfile");
        }

    public:
        XMLParser()
        {
            generateXMLFiles();
        }
};

int main(void)
{
    DoxygenConfig tmp;
    XMLParser tmp2;

    return 0;
}