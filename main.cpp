// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <boost/lexical_cast.hpp>//до того ж методу що ще не працює

std::string file1, file2;

int method_1(double d){
    // Including header file sstream is a must.
    // For large numbers, ostringstream automatically
    // converts it to scientific notation
    std::ostringstream num;
    num.precision(15);//changing default precision to our value

    num<<std::fixed<<d; //It has a default precision of six digits
    //num<<std::scientific<<d;
    //num<<d;
    std::string str = num.str();

    //std::cout << str << std::endl;
    return str.length();
}
int method_2(double d){
    //It has a default precision of six
    // digits which cannot be changed
    std::string str = std::to_string(d);

    //std::cout<< str<<std::endl;
    return str.length();
}
//ще не працює, розбираюсь ще з ним
int method_3(double d){
    std::string str;
    str = std::lexical_cast<std::string>(d);

    std::cout<< str<<std::endl;
    return str.length();
}

void write_file(int amount, double average){
    std::ofstream out;
    out.open(file2, std::ios::app);

    if(!out.is_open()){
        std::cout<<"Error opening file (write_file)"<< std::endl;
        exit(1);
    }

    out<<amount<<"\n"<<average<<std::endl;

    out.close();
    // create new file + write there
    /*std::ofstream outfile("test.txt");
    outfile<<"hey you! you are soooo cutty^^"<<std::endl;
    outfile.close();
     */

}

void pre_method(int n, const std::vector<double>& data){
    int characters_amount = 0;
    int data_size = data.size();
    switch(n) {
        case 1:
            for (double d : data) {
                characters_amount += method_1(d);
            }
            break;
        case 2:
            for (double d : data) {
                characters_amount += method_2(d);
            }
            break;
        case 3:
            for (double d : data) {
                characters_amount += method_3(d);
            }
            break;
        default:
            std::cout<<"No such method (pre_method)"<< std::endl;
            break;
    }
    double average = (double)characters_amount/data_size;
    write_file(characters_amount, average);
}

std::vector<double> read_file(){//(const std::string& file){
    std::ifstream in(file1, std::ios::in);
    std::vector<double> data;
    double d = 0.0;

    if(!in.is_open()){
        std::cout<<"Error opening file (read_file)"<< std::endl;
        exit(1);
    }

    while(in>>d){
        data.push_back((double)d);
    }
    return data;
}

int main() {
    int n;

    std::cin>>n>>file1>>file2;

    std::vector<double> file_data = read_file();

    pre_method(n,file_data);

    return 0;
}
