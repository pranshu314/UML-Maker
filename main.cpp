# include <bits/stdc++.h>
# include <iostream>
# include <fstream>
# include <regex>
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

        void getClasses()
        {
            //system("cd xml");
            string line;
            regex class_regex("(  <compound refid=\".*\" kind=\"class\">.*)");
            regex class_name("(<name>.*</name>)");
            ifstream index;
            index.open("./xml/index.xml");
            while(index)
            {
                getline(index,line);
                if(line=="-1")
                {
                    break;
                }
                else if(regex_match(line,class_regex))
                {
                    smatch match_flag;
                    regex_search(line,match_flag,class_name);
                    ofstream class_file;
                    class_file.open("class.txt",ios_base::app);
                    int i=1;
                    for(auto x : match_flag)
                    {
                        if(i==1)
                        {
                            class_file<<x<<endl;                        
                        }
                        i=(i+1)%2;
                    }
                }
            }
        }

    public:
        XMLParser()
        {
            generateXMLFiles();
            getClasses();
        }
};

int main(void)
{
    DoxygenConfig tmp1;
    XMLParser tmp2;

    return 0;
}