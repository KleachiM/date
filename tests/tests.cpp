#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "../Date.h"

TEST_CASE("15.06.2023 year == 2023")
{
    CDate today(19523);
    REQUIRE(today.GetYear() == 2023);
}

TEST_CASE("31.12.9999 year == 9999")
{
    CDate today(2932896);
    REQUIRE(today.GetYear() == 9999);
}

TEST_CASE("01.01.1970 year == 1970")
{
    CDate today(0);
    REQUIRE(today.GetYear() == 1970);
}

TEST_CASE("01.01.9999 year == 9999")
{
    CDate today(2932532);
    REQUIRE(today.GetYear() == 9999);
}

TEST_CASE("31.12.9998 year == 9998")
{
    CDate today(2932531);
    REQUIRE(today.GetYear() == 9998);
}

TEST_CASE("01.01.9998 year == 9998")
{
    CDate y_9998(2932167);
    REQUIRE(y_9998.GetYear() == 9998);
}

TEST_CASE("31.12.9997 year == 9997")
{
    CDate y_9997{2932166};
    REQUIRE(y_9997.GetYear() == 9997);
}

TEST_CASE("Default constructor with timestamp")
{
    CDate d;
    REQUIRE(d.GetYear() == 1970);
}

TEST_CASE("Construct with params")
{
    CDate d_df{2932166}, d_par{31, Month::DECEMBER, 9997};
    REQUIRE(d_df.GetYear() == d_par.GetYear());
}

TEST_CASE("Get day")
{
    CDate d_df{2932166}, d_par{01, Month::JANUARY, 9998};
    REQUIRE(d_df.GetDay() == 31);
    REQUIRE(d_par.GetDay() == 1);
}

TEST_CASE("Get month")
{
    CDate d_df{2932166}, d_par{01, Month::JANUARY, 9998};
    REQUIRE(d_df.GetMonth() == Month::DECEMBER);
    REQUIRE(d_par.GetMonth() == Month::JANUARY);
}

TEST_CASE("Get weekday")
{
    CDate d{1,Month::JANUARY,1970}, today{15, Month::JUNE, 2023};
    REQUIRE(d.GetWeekDay() == WeekDay::THURSDAY);
    REQUIRE(today.GetWeekDay() == WeekDay::THURSDAY);
}

TEST_CASE("Creating object")
{
    CDate d{21, static_cast<Month>(6), 2023};
    REQUIRE(d.GetYear() == 2023);
    REQUIRE(d.GetMonth() == Month::JUNE);
    REQUIRE(d.GetDay() == 21);
}

TEST_CASE(">> operation")
{
    CDate d;
    std::stringstream ss("21 06 2023");
    ss >> d;
    REQUIRE(d.GetYear() == 2023);
    REQUIRE(d.GetMonth() == Month::JUNE);
    REQUIRE(d.GetDay() == 21);
}
//TODO: вывод месяца как 06
//TODO: ввод через разделители
TEST_CASE("<< operation")
{
    CDate d{21, Month::JUNE, 2023};
    std::ostringstream os("");
    os << d;
    REQUIRE(os.str() == "21.6.2023");
}

TEST_CASE("Not valid date 1.1.10000")
{
    CDate d{1, Month::JANUARY, 10000};
    std::ostringstream os("");
    os << d;
    REQUIRE(os.str() == "INVALID");
}

TEST_CASE("Not valid date 31.12.1969")
{
    CDate d{31, Month::DECEMBER, 1969};
    std::ostringstream os("");
    os << d;
    REQUIRE(os.str() == "INVALID");
}

TEST_CASE("== operator")
{
    CDate d1{1, Month::JUNE, 2000};
    CDate d2{1, Month::JUNE, 2000};
    CDate d3{1, Month::JUNE, 2010};
    REQUIRE(d1 == d2);
    REQUIRE_FALSE(d1 == d3);
}

TEST_CASE("!= operator")
{
    CDate d1{1, Month::JUNE, 2000};
    CDate d2{1, Month::JUNE, 2000};
    CDate d3{1, Month::JUNE, 2010};
    REQUIRE(d1 != d3);
    REQUIRE_FALSE(d1 != d2);
}

TEST_CASE("> operator")
{
    CDate d1{1, Month::JUNE, 2000};
    CDate d2{2, Month::JUNE, 2000};
    REQUIRE(d2 > d1);
    REQUIRE_FALSE(d1 > d2);
}

TEST_CASE("< operator")
{
    CDate d1{1, Month::JUNE, 2000};
    CDate d2{2, Month::JUNE, 2000};
    REQUIRE(d1 < d2);
    REQUIRE_FALSE(d2 < d1);
}

TEST_CASE(">= operator")
{
    CDate d1{1, Month::JUNE, 2000};
    CDate d2{2, Month::JUNE, 2000};
    CDate d3{2, Month::JUNE, 2000};
    REQUIRE(d2 >= d1);
    REQUIRE(d3 >= d2);
    REQUIRE_FALSE(d1 >= d2);
}

TEST_CASE("<= operator")
{
    CDate d1{1, Month::JUNE, 2000};
    CDate d2{2, Month::JUNE, 2000};
    CDate d3{2, Month::JUNE, 2000};
    REQUIRE(d1 <= d2);
    REQUIRE(d2 <= d3);
    REQUIRE_FALSE(d3 <= d1);
}

TEST_CASE("+= operator valid")
{
    CDate d{23, Month::JUNE, 2023};
    d += 1;
    REQUIRE(d.GetDay() == 24);
}

TEST_CASE("Invalid date after +=")
{
    CDate d{31, Month::DECEMBER, 9999};
    d += 1;
    REQUIRE_FALSE(d.IsValid());

    d = CDate{1, Month::JANUARY, 1970};
    REQUIRE(d.IsValid());
    d += -1;
    REQUIRE_FALSE(d.IsValid());
}

TEST_CASE("+= operator invalid")
{
    CDate d{31, Month::DECEMBER, 99999};
    CDate d2{31, Month::DECEMBER, 99999};
    d += 1;
    REQUIRE(d == d2);
}

TEST_CASE("-= operator valid")
{
    CDate d{23, Month::JUNE, 2023};
    d -= 1;
    REQUIRE(d.GetDay() == 22);
}

TEST_CASE("Invalid date after -=")
{
    CDate d{31, Month::DECEMBER, 9999};
    d -= -1;
    REQUIRE_FALSE(d.IsValid());

    d = CDate{1, Month::JANUARY, 1970};
    REQUIRE(d.IsValid());
    d -= 1;
    REQUIRE_FALSE(d.IsValid());
}

TEST_CASE("-= operator invalid")
{
    CDate d{31, Month::DECEMBER, 99999};
    CDate d2{31, Month::DECEMBER, 99999};
    d -= 1;
    REQUIRE(d == d2);
}

TEST_CASE("Increment of valid date")
{
    CDate d{23, Month::JUNE, 2023};
    d++;
    REQUIRE(d.GetDay() == 24);
    ++d;
    REQUIRE(d.GetDay() == 25);
}

TEST_CASE("Increment of invalid date")
{
    CDate d{31, Month::DECEMBER, 99999};
    CDate d2{31, Month::DECEMBER, 99999};
    d++;
    REQUIRE(d == d2);
    ++d;
    REQUIRE(d == d2);
}

TEST_CASE("Decrement of valid date")
{
    CDate d{23, Month::JUNE, 2023};
    d--;
    REQUIRE(d.GetDay() == 22);
    --d;
    REQUIRE(d.GetDay() == 21);
}

TEST_CASE("Decrement of invalid date")
{
    CDate d{31, Month::DECEMBER, 99999};
    CDate d2{31, Month::DECEMBER, 99999};
    d--;
    REQUIRE(d == d2);
    --d;
    REQUIRE(d == d2);
}

TEST_CASE("Add days to valid date")
{
    CDate d{23, Month::JUNE, 2023};
    CDate d2;
    d2 = d + 1;
    REQUIRE(d2.GetDay() == 24);
}

TEST_CASE("Add days to not valid date")
{
    CDate d{31, Month::DECEMBER, 9999};
    CDate d2;
    d2 = d + 1;
    REQUIRE_FALSE(d2.IsValid());
}

TEST_CASE("Substr days from valid date")
{
    CDate d1{21,Month::JUNE,2023};
    CDate d2;
    d2 = d1 - 1;
    REQUIRE(d2.GetDay() == 20);
}

TEST_CASE("Substr days from not valid date")
{
    CDate d1{21,Month::JUNE,20223};
    CDate d2, d3;
    d2 = d1 - 1;
    REQUIRE_FALSE(d2.IsValid());
//    REQUIRE(d2 == d3);
}

TEST_CASE("Not valid date after substr")
{
    CDate d1{1, Month::JANUARY, 1970};
    CDate d2 = d1 - 2;
    REQUIRE_FALSE(d2.IsValid());
}

TEST_CASE("Substr valid date from valid date")
{
    CDate d1{22, Month::JUNE, 2023};
    CDate d2{23, Month::JUNE, 2023};
    REQUIRE((d2 - d1) == 1);
    REQUIRE((d1 - d2) == -1);
}

TEST_CASE("Substr not valid date from valid date")
{
    CDate dValid{1, Month::JANUARY, 1970};
    CDate dNotValid{31, Month::DECEMBER, 1969};
    REQUIRE((dValid - dNotValid) == 0);
}

TEST_CASE("Substr valid date from not valid date")
{
    CDate dValid{1, Month::JANUARY, 1970};
    CDate dNotValid{31, Month::DECEMBER, 1969};
    REQUIRE((dNotValid - dValid) == 0);
}

TEST_CASE("asdf")
{
    CDate d{22, Month::JUNE, 2023};
    REQUIRE(d.GetWeekDay() == WeekDay::THURSDAY);
}