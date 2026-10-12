
#include "constants.h"
#include "util.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <thread>
#include <vector>

using namespace constant;
using namespace RustTypedefs; 

struct vector3
{
    double x;
    double y;
    double z;
};

struct rotation_matrix
{
    vector3 xYaw;
    vector3 yRoll;
    vector3 zPitch;
};

struct physicalObject
{
    rotation_matrix rotation;

    double x;
    double y;
    double z;
    double x_velocity;
    double y_velocity;
    double z_velocity;
    unsigned short id;
};

struct duration // goofy ah time code
{
    using clock = std::chrono::steady_clock;
    using millisecond = std::chrono::milliseconds;

    //clock::time_point start{ std::chrono::steady_clock::now() }
    clock::time_point start;
    clock::time_point end;

    void timestamp() { start = clock::now(); }

    millisecond getDuration()
    {
        end = clock::now();
        return std::chrono::duration_cast<millisecond>(start - end);
    }
};

namespace vec
{
    constexpr double dotproduct( const vector3& a, const vector3& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }
    constexpr double dotproduct(const physicalObject& a, const physicalObject& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    double magnitude(const vector3& a)
    {
        return std::sqrt(std::pow(a.x, 2) + std::pow(a.y, 2) + std::pow(a.z, 2));
    }
    double magnitude(const physicalObject& a)
    {
        return std::sqrt(std::pow(a.x, 2) + std::pow(a.y, 2) + std::pow(a.z, 2));
    }

    vector3 normalise(const vector3& a)
    {
        double magn{ magnitude(a) };
        return { a.x / magn, a.y / magn, a.z / magn };
    }
    physicalObject normalise(const physicalObject& a)
    {
        double magn{ magnitude(a) };
        return { a.x / magn, a.y / magn, a.z / magn };
    }

    /// In progress angle setting 
    //physicalObject& setYaw( const physicalObject& mut_a, float angle)
    //{
    //     
    //    

    //}


}

void simulate(  physicalObject& object, double delta_time )
{
    object.y_velocity = object.y_velocity - (g_gravity * delta_time);
    
    if (object.y > 0)
    { 
    object.y = object.y + object.y_velocity;
    }
    else
    {

    }
}

void pretty_print_state(physicalObject& object)
{
    using std::cout;
    cout << object.id << ":\n" ;
    cout << "XYZ: " << object.x << " " << object.y << " " << object.z << '\n';
    cout << "XYZ velocities: " << object.x_velocity << " " << object.y_velocity << " " << object.z_velocity << "\n\n";
}

int main()
{

    int z{5};
    int x{5};
    double g{5.5};
    z = static_cast<int>(g + z);

    physicalObject ball{};
    physicalObject joe{};

    ball.id = 1;
    joe.id = 2;

    ball.x = 2;
    ball.y = 2;

    joe.x = 2;
    joe.y = 2;

    //while (true)
    //{ 

    //physicalObject normball = vec::normalise(ball);
    //physicalObject normjoe = vec::normalise(joe);

    //double check = std::atan2(normball.y, normball.x);

    //vec::dotproduct( normball, normjoe );

    //difference.x = ball.x - joe.x;
    //difference.y = ball.y - joe.y;

    //}

    double d_tick{0.0};
    double tick{0.0};   // in seconds
    double last_tick{0.0};

    double simulate_for_time{0.0};

    


    std::cout << "give ball height" << "\n";  
    std::cin >> ball.y;
    std::cout << "give simulation time" << "\n";
    std::cin >> simulate_for_time;

    for (short prints{ 1 }; tick <= simulate_for_time; ++tick)
    {
        d_tick = tick - last_tick;

        simulate(ball, d_tick);
        std::cout << " time: " << tick << " | ";
        pretty_print_state(ball);

        prints += 1;
        if (prints % 2 == 0) { std::cout << "\n"; }

        last_tick = tick; // set old time to new time.
    }
    return 0;
}