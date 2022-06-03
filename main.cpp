#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm> // for std::copy
#include <iterator>
#include <matplotlibcpp.h>
#include <Eigen/Dense>
#include <catch.hpp>

int main()
{
    std::ifstream is("/home/bcd/programming/csv_read/bctrajectory_dump.csv");
    std::istream_iterator<double> start(is), end;
    std::vector<double> numbers(start, end);
    // std::cout << "Read " << numbers.size() << " numbers" << std::endl;

    // print the numbers to stdout
    // std::cout << "numbers read in:\n";
    // std::copy(numbers.begin(), numbers.end(),
    //           std::ostream_iterator<double>(std::cout, " "));        velx[i] = matrix[i][1];

    // std::cout << std::endl;

    int num_of_data = numbers.size();

    int num_of_cols = 12;
    int num_of_rows = num_of_data / num_of_cols;
    int initial_value = 0;
    std::vector<std::vector<double>> matrix;
    matrix.resize(num_of_rows, std::vector<double>(num_of_cols, initial_value));

    for (int i = 0; i < num_of_data; i++)
    {
        matrix[i / num_of_cols][i % num_of_cols] = numbers[i];
    }

    // for(int i=0; i<num_of_rows; i++)
    // {
    //     for(int j=0; j<num_of_cols; j++)
    //     {
    //         std::cout << matrix[i][j] << std::endl;
    //     }
    // }
    double sampleTime = 0.001;
    Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(num_of_rows, sampleTime, double(num_of_rows) * sampleTime);
    std::vector<double> time(x.size());


    for (int i = 0; i < x.size(); i++)
    {
        time[i] = x(i);
    }
    // Eigen::VectorXd y, z;
    // y = x.array().sin().exp().matrix();
    // z = x.array().cos().exp().matrix();

    // std::cout << time[100] << std::endl;

    std::vector<double> posx(num_of_rows);
    std::vector<double> velx(num_of_rows);

    for (int i = 0; i < num_of_rows; i++)
    {
        posx[i] = matrix[i][0];
        velx[i] = matrix[i][1];
    }

    matplotlibcpp::figure();
    matplotlibcpp::plot(time, posx, {{"label", "position"}});
    matplotlibcpp::plot(time, velx, {{"label", "velocity"}});

    matplotlibcpp::xlabel("Time [s]");
    matplotlibcpp::grid(true);
    matplotlibcpp::title("Trajectory");
    matplotlibcpp::legend();
    matplotlibcpp::save("/home/bcd/programming/csv_read/trajectory.png");
    matplotlibcpp::show();
}