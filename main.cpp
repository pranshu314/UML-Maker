# include <bits/stdc++.h>
# include <iostream>
# include <fstream>
//# include <boost/regex.hpp>
# include <regex>
# include <string.h>
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
                else if(line=="CASE_SENSE_NAMES       = SYSTEM")
                {
                    doxy_file.seekg(st_location);
                    doxy_file<<"CASE_SENSE_NAMES       = YES"<<endl;
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

class Class_txtGenerator
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

        void finalizeClasses_txt()
        {
            vector<string> class_vector;
            vector<string>::iterator v_itr;
            fstream class_file;
            string line;
            class_file.open("class.txt", ios::in | ios::out);
            while(class_file)
            {
                int st_location=class_file.tellg();
                getline(class_file,line);
                if(line=="-1")
                {
                    break;
                }
                else if(line.size()!=0)
                {
                    int l=line.length()-13;
                    string req_line=line.substr(6,l);
                    class_vector.push_back(req_line);
                }
            }
            class_file.close();
            system("rm class.txt");
            ofstream class_file1;
            class_file1.open("class.txt", ios::app);
            for(v_itr=class_vector.begin(); v_itr!=class_vector.end(); v_itr++)
            {
                string req=*v_itr;
                class_file1<<req<<endl;
            }
        }

    public:
        Class_txtGenerator()
        {
            generateXMLFiles();
            getClasses();
            finalizeClasses_txt();
        }
};

class IndividualClassParser
{
    private:
        void singleClassFileGenerator(string class_name, string singleFileName)
        {
            system("mkdir uml_files");
            //cout<<"\n1\n";
            cout<<singleFileName;
            cout<<"\n";
            regex derived_regex(".*<derivedcompoundref refid=.*");
            regex derived_name_regex(">.*<");
            regex variable_regex(".*<memberdef kind=\"variable\" .*");
            regex function_regex(".*<memberdef kind=\"function\" .*");
            regex friend_regex(".*<memberdef kind=\"friend\" .*");

            ifstream work_file;
            string line;
            string line2;
            work_file.open(singleFileName);
            while(work_file)
            {
                //cout<<"\n2\n";
                getline(work_file,line);
                if(line!="-1" && line2!=line)
                {
                    if(regex_match(line,derived_regex))
                    {
                        //cout<<"\n3\n";
                        smatch match_flag;
                        regex_search(line,match_flag,derived_name_regex);
                        ofstream inheritance_file;
                        inheritance_file.open("uml_files/inheritance.txt", ios_base::app);
                        inheritance_file<<class_name<<" : ";
                        for(auto x : match_flag)
                        {
                            inheritance_file<<x<<endl;
                        }
                    }
                    if(regex_match(line,variable_regex))
                    {
                        //cout<<"\n4\n";
                        string tmp_line;
                        string prot;
                        string _static;
                        string type;
                        string name;

                        size_t found_prot = line.find("prot=");
                        if(line.substr(int(found_prot)+6,6)=="public")
                        {
                            prot="public";
                        }
                        else if(line.substr(int(found_prot)+6,7)=="private")
                        {
                            prot="private";
                        }
                        else if(line.substr(int(found_prot)+6,9)=="protected")
                        {
                            prot="protected";
                        }

                        size_t found_static = line.find("static=");
                        if(line.substr(int(found_static)+8,3)=="yes")
                        {
                            _static="static";
                        }
                        else if(line.substr(int(found_static)+8,2)=="no")
                        {
                            _static="";
                        }
                        
                        regex type_regex(".*<type>.*</type>");
                        getline(work_file,tmp_line);
                        if(regex_match(tmp_line,type_regex))
                        {
                            regex type_2_regex(".*<type><ref .*>.*</ref></type>");
                            if(regex_match(tmp_line,type_2_regex))
                            {
                                size_t found_type = tmp_line.find(">");
                                found_type=tmp_line.find(">",found_type+1);
                                type=tmp_line.substr(int(found_type)+1,tmp_line.length()-13-int(found_type)-1);
                            }
                            else
                            {
                                type=tmp_line.substr(14,tmp_line.length()-21);
                            }
                        }
                        getline(work_file,tmp_line);
                        getline(work_file,tmp_line);
                        regex name_regex(".*<name>.*</name>");
                        getline(work_file,tmp_line);
                        if(regex_match(tmp_line,name_regex))
                        {
                            name=tmp_line.substr(14,tmp_line.length()-21);
                        }
                        string var="variable :: ";
                        string tmp_colon=" : ";
                        string tmp_semicolon=" ; ";
                        string tmp_space=" ";
                        string final_member_name = var+prot+tmp_colon+name+tmp_semicolon+_static+tmp_space+type;

                        int copy_check=0;
                        ifstream copy_file;
                        copy_file.open("uml_files/"+class_name+".txt");
                        while(copy_file)
                        {
                            string line_from_file;
                            getline(copy_file,line_from_file);
                            if(line_from_file==final_member_name)
                            {
                                copy_check+=1;
                            }
                            else if(line=="-1")
                            {
                                break;
                            }
                        }
                        
                        if(copy_check==0)
                        {
                            ofstream single_class_file;
                            string file_name="uml_files/"+class_name+".txt";
                            single_class_file.open(file_name, ios_base::app);
                            single_class_file<<final_member_name<<endl;
                        }

                    }
                    if(regex_match(line,function_regex))
                    {
                        //cout<<"\n5\n";
                        string tmp_line;
                        string prot;
                        string _static;
                        string constant;
                        string virt;
                        string type;
                        string argsstring;
                        string name;

                        size_t found_prot = line.find("prot=");
                        if(line.substr(int(found_prot)+6,6)=="public")
                        {
                            prot="public";
                        }
                        else if(line.substr(int(found_prot)+6,7)=="private")
                        {
                            prot="private";
                        }
                        else if(line.substr(int(found_prot)+6,9)=="protected")
                        {
                            prot="protected";
                        }

                        size_t found_static = line.find("static=");
                        if(line.substr(int(found_static)+8,3)=="yes")
                        {
                            _static="static";
                        }
                        else if(line.substr(int(found_static)+8,2)=="no")
                        {
                            _static="";
                        }

                        size_t found_const = line.find("const=");
                        if(line.substr(int(found_const)+7,3)=="yes")
                        {
                            constant="const";
                        }
                        else if(line.substr(int(found_const)+7,2)=="no")
                        {
                            constant="";
                        }

                        size_t found_virtual = line.find("virt=");
                        if(line.substr(int(found_virtual)+6,11)=="non-virtual")
                        {
                            virt="";
                        }
                        else if(line.substr(int(found_virtual)+6,7)=="virtual")
                        {
                            virt="virtual";
                        }

                        regex type_regex(".*<type>.*</type>");
                        regex argsstring_regex(".*<argsstring>.*</argsstring>");
                        regex name_regex(".*<name>.*</name>");
                        getline(work_file,tmp_line);
                        if(regex_match(tmp_line,type_regex))
                        {
                            regex type_2_regex(".*<type><ref .*>.*</ref></type>");
                            if(regex_match(tmp_line,type_2_regex))
                            {
                                size_t found_type = tmp_line.find(">");
                                found_type=tmp_line.find(">",found_type+1);
                                type=tmp_line.substr(int(found_type)+1,tmp_line.length()-13-int(found_type)-1);
                            }
                            else
                            {
                                type=tmp_line.substr(14,tmp_line.length()-21);
                            }
                        }
                        getline(work_file,tmp_line);
                        getline(work_file,tmp_line);
                        if(regex_match(tmp_line,argsstring_regex))
                        {
                            argsstring=tmp_line.substr(20,tmp_line.length()-33);
                        }
                        getline(work_file,tmp_line);
                        if(regex_match(tmp_line,name_regex))
                        {
                            name=tmp_line.substr(14,tmp_line.length()-21);
                        }

                        string func="function :: ";
                        string tmp_colon=" : ";
                        string tmp_semicolon=" ; ";
                        string tmp_space=" ";
                        string final_member_name=func+prot+tmp_colon+name+argsstring+tmp_semicolon+virt+tmp_space+_static+tmp_space+constant+tmp_space+type;

                        int copy_check=0;
                        ifstream copy_file;
                        copy_file.open("uml_files/"+class_name+".txt");
                        while(copy_file)
                        {
                            string line_from_file;
                            getline(copy_file,line_from_file);
                            if(line_from_file==final_member_name)
                            {
                                copy_check+=1;
                            }
                            else if(line=="-1")
                            {
                                break;
                            }
                        }
                        
                        if(copy_check==0)
                        {
                            ofstream single_class_file;
                            string file_name="uml_files/"+class_name+".txt";
                            single_class_file.open(file_name, ios_base::app);
                            single_class_file<<final_member_name<<endl;
                        }
                    }
                    if(regex_match(line,friend_regex))
                    {
                        string tmp_line;
                        string prot;
                        string final_member_name;
                        regex definition_regex(".*<definition>.*</definition>");

                        size_t found_prot = line.find("prot=");
                        if(line.substr(int(found_prot)+6,6)=="public")
                        {
                            prot="public";
                        }
                        else if(line.substr(int(found_prot)+6,7)=="private")
                        {
                            prot="private";
                        }
                        else if(line.substr(int(found_prot)+6,9)=="protected")
                        {
                            prot="protected";
                        }

                        getline(work_file,tmp_line);
                        getline(work_file,tmp_line);
                        if(regex_match(tmp_line,definition_regex))
                        {
                            final_member_name=tmp_line.substr(20,tmp_line.length()-33);
                        }
                        final_member_name="friend :: "+prot+" ; "+final_member_name;

                        int copy_check=0;
                        ifstream copy_file;
                        copy_file.open("uml_files/"+class_name+".txt");
                        while(copy_file)
                        {
                            string line_from_file;
                            getline(copy_file,line_from_file);
                            if(line_from_file==final_member_name)
                            {
                                copy_check+=1;
                            }
                            else if(line=="-1")
                            {
                                break;
                            }
                        }
                        
                        if(copy_check==0)
                        {
                            ofstream single_class_file;
                            string file_name="uml_files/"+class_name+".txt";
                            single_class_file.open(file_name, ios_base::app);
                            single_class_file<<final_member_name<<endl;
                        }

                    }

                    line2=line;
                }
                else if(line==line2)
                {
                    continue;
                }
                else
                {
                    break;
                }
            }

        }

        void singleClassFileNameGenerator()
        {
            ifstream class_file;
            string line;
            class_file.open("class.txt");
            while(class_file)
            {
                getline(class_file,line);
                if(line=="-1")
                {
                    break;
                }
                else
                {
                    string class_name=line;
                    string singleFileName="class";
                    string tmp1=".xml";
                    string tmp2="xml/";
                    singleFileName+=class_name;
                    singleFileName+=tmp1;
                    singleFileName=tmp2+singleFileName;
                    singleClassFileGenerator(class_name,singleFileName);
                }
            }
        }

    public:
        IndividualClassParser()
        {
            singleClassFileNameGenerator();
        }

};

class RemoverOfExtraFiles
{
    private:
        void removeFiles()
        {   
            system("rm -r xml/");
            system("rm Doxyfile");
        }

    public:
        RemoverOfExtraFiles()
        {
            removeFiles();
        }
};

int main(void)
{
    DoxygenConfig tmp1;
    Class_txtGenerator tmp2;
    IndividualClassParser tmp3;
    RemoverOfExtraFiles tmp4;

    return 0;
}