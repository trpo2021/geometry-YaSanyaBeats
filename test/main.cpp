#define CATCH_CONFIG_MAIN
#include "../thirdparty/catch.hpp"
#include <iostream>
#include <libcalculate/calculate.h>
#include <string.h>
#include <vector>

TEST_CASE("Counting circle", "")
{
    SECTION("perim")
    {
        std::vector<double> a{0, 0, 5, 5, 5, 0, 0, 0};
        std::vector<double> b{0, 0, 5};
        std::vector<double> c{0, 0, 0, 5, 5, 5, 5, 0, 0, 0};
        CHECK(takePerimetr("triangle", a) == Approx(17.071));
        CHECK(takePerimetr("circle", b) == Approx(31.4159));
        CHECK(takePerimetr("poligon", c) == 20);
    }
    SECTION("area")
    {
        std::vector<double> a{0, 0, 5, 5, 5, 0, 0, 0};
        std::vector<double> b{0, 0, 5};
        std::vector<double> c{0, 0, 0, 5, 5, 5, 5, 0, 0, 0};
        CHECK(takeSquare("triangle", a) == 12.5);
        CHECK(takeSquare("circle", b) == Approx(78.5398));
        CHECK(takeSquare("poligon", c) == 25);
    }
    system("PAUSE");
}
/*TEST_CASE("for counting", "")
{
    SECTION("sqrSum")
    {
        std::vector<float> a{4, 0, 0};
        std::vector<float> b{0, 0, 0};
        std::vector<float> c{26.01, 29.58, 8.41};
        CHECK(sqrSum(2, 0) == a);
        CHECK(sqrSum(0, 0) == b);
        std::vector<float> temp = sqrSum(5.1, 2.9);
        for (int i=0; i<3; i++){
            CHECK(temp[i] == Approx(c[i]));
        }

        //CHECK(sqrSum(9.14, 4.32) == Approx(20.79673));
    }
    system("PAUSE");
}*/
