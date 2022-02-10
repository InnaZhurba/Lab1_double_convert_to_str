// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <atomic>


std::string file1, file2;
long long full_execution_time = 0;

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

int method_1(double d){
    //auto start_time = get_current_time_fenced();
    // Including header file sstream is a must.
    // For large numbers, ostringstream automatically
    // converts it to scientific notation
    std::ostringstream num;

    //num.precision(15);//changing default precision to our value

    num<<std::fixed<<d; //It has a default precision of six digits //num<<std::scientific<<d;
    //num<<d;
    std::string str = num.str();

    /*auto finish_time = get_current_time_fenced();
    auto total_time = finish_time - start_time;
    full_execution_time += to_us(total_time);
     */

    return (int)str.length();
}
int method_2(double d){
    //auto start_time = get_current_time_fenced();
    //It has a default precision of six
    // digits which cannot be changed
    std::string str = std::to_string(d);

    /*auto finish_time = get_current_time_fenced();
    auto total_time = finish_time - start_time;
    full_execution_time += to_us(total_time);
    */

    return (int)str.length();
}

int method_3(double d){
    //auto start_time = get_current_time_fenced();

    std::string str;
    str = boost::lexical_cast<std::string>(d);

    /*auto finish_time = get_current_time_fenced();
    auto total_time = finish_time - start_time;
    full_execution_time += to_us(total_time);
     */

    return (int)str.length();
}

void write_file(int amount, double average){
    std::ofstream out;
    out.open(file2, std::ios::app);

    if(!out.is_open()){
        std::cout<<"Error opening file (write_file)"<< std::endl;
        exit(4);
    }

    out<<amount<<std::endl;
    out<<average<<std::endl;

    //std::cout<<"done writing"<<std::endl;

    out.close();
}

void pre_method(int n, const std::vector<double>& data){
    int characters_amount = 0;
    int data_size = (int)data.size();

    auto start_time = get_current_time_fenced();
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
            exit(3);
    }
    auto finish_time = get_current_time_fenced();
    full_execution_time = to_us(finish_time - start_time);

    double average = (double)characters_amount/data_size;
    write_file(characters_amount, average);
}

double sciToDub(const std::string& str) {

    std::stringstream ss(str);
    double d = 0;
    ss >> d;

    if (ss.fail()) {}

    return (d);
}

std::vector<double> read_file(){
    std::ifstream in(file1, std::ios::in);
    std::vector<double> data;
    std::string d;

    if(!in.is_open()){
        std::cout<<"Error opening file (read_file)"<< std::endl;
        in.close();
        exit(4);
    }

    while(in>>d){
        data.push_back(sciToDub(d));
    }
    in.close();
    return data;
}

int main(int argc, char* argv[]) {

    int n;
    if(argc>4){
        std::cout<<"Error: too many arguments."<< std::endl;
        exit(2);
    }
    if(argc>1){
        //std::cout<<argv[1]<<std::endl;
        //std::cout<<argv[2]<<std::endl;
        //std::cout<<argv[3]<<std::endl;
        n = atoi(argv[1]);
        file1 = argv[2];
        file2 = argv[3];
    }
    else{

        std::cin>>n>>file1>>file2;

    }

    std::vector<double> file_data = read_file();

    pre_method(n,file_data);

    //туту буде вивід виміряного часу
    std::cout<<full_execution_time<<std::endl;
    return 0;
}
