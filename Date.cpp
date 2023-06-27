#include "Date.h"
#include <cmath>
#include <iostream>

const unsigned int daysIn400Years = 146097;
const unsigned int daysIn100Years = 36524;
const unsigned int daysIn4Years = 1461;
const unsigned int daysInYear = 365;

// TODO: убрать магические числа

const unsigned int MAX_YEAR = 9999;
const unsigned int MAX_TIMESTAMP = 2932896;

using namespace std;

bool IsLeapYear(unsigned int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

unsigned int GetCountDaysInMonth(Month month, unsigned int year)
{
    int monthNum = static_cast<int>(month);
    if (monthNum < 8)
    {
        if (monthNum % 2 != 0)
        {
            return 31;
        }
        if (monthNum == 2)
        {
            return IsLeapYear(year) ? 29 : 28;
        }
        return 30;
    }
    return (monthNum % 2 == 0) ? 31 : 30;
}

unsigned int GetDaysCountByYear(unsigned int year)
{
    unsigned int yearsDiff = year - 1970;
    unsigned int cnt400 = int(yearsDiff / 400);
    unsigned int cnt100 = int((yearsDiff - cnt400 * 400) / 100);
    unsigned int cnt4 = int((yearsDiff - cnt400 * 400 - cnt100 * 100) / 4);
    unsigned int cnt1 = int(yearsDiff - cnt400 * 400 - cnt100 * 100 - cnt4 * 4);

    return cnt400 * daysIn400Years + cnt100 * daysIn100Years + cnt4 * daysIn4Years + cnt1 * daysInYear;
}

unsigned int GetDaysCountByMonth(Month month, unsigned int year)
{
    int monthNum = static_cast<int>(month);
    unsigned int days = 0;
    for (int i = 1; i < monthNum; i++)
    {
        days += GetCountDaysInMonth(Month{i}, year);
    }
    return days;
}

CDate::CDate(unsigned int timestamp)
{
    if (timestamp < 0 || timestamp > MAX_TIMESTAMP)
    {
        m_daysCount = -1;
    }
    m_daysCount = timestamp;
}

CDate::CDate(unsigned int day, Month month, unsigned int year)
{

    if ((year < 1970 || year > MAX_YEAR) || (day < 1 || day > GetCountDaysInMonth(month, year)))
    {
        m_daysCount = -1;
        return;
    }

    unsigned int daysByYear = GetDaysCountByYear(year);
    unsigned int daysByMonth = GetDaysCountByMonth(month, year);
    m_daysCount = daysByYear + daysByMonth + day;
}

unsigned CDate::GetYear() const
{
    unsigned int cnt400 = int(m_daysCount / daysIn400Years);
    unsigned int cnt100 = int ((m_daysCount - cnt400 * daysIn400Years) / daysIn100Years);
    unsigned int cnt4 = int((m_daysCount - cnt400 * daysIn400Years - cnt100 * daysIn100Years) / daysIn4Years);
    unsigned int cnt1 = int(
            (m_daysCount - cnt400 * daysIn400Years - cnt100 * daysIn100Years - cnt4 * daysIn4Years) / daysInYear
            );
    // TODO: добавить поясняющий комментарий
    cnt1 = (cnt1 == 4) ? 3 : cnt1;
    unsigned int year = cnt400 * 400 + cnt100 * 100 + cnt4 * 4 + cnt1 + 1970;
    return year;
}

unsigned CDate::GetDay() const
{
    unsigned int cnt400 = int(m_daysCount / daysIn400Years) * daysIn400Years;
    unsigned int cnt100 = int ((m_daysCount - cnt400) / daysIn100Years) * daysIn100Years;
    unsigned int cnt4 = int((m_daysCount - cnt400 - cnt100) / daysIn4Years) * daysIn4Years;
    unsigned int cnt1 = int((m_daysCount - cnt400 - cnt100 - cnt4) / daysInYear);
    cnt1 = daysInYear * ((cnt1 == 4) ? 3 : cnt1);
    unsigned int daysFromYearStart = m_daysCount - (cnt400 + cnt100 + cnt4 + cnt1);
    unsigned int numOfStartDayInMonth = 0;
    for (int i = 1; i <= 12; i++)
    {
        if (daysFromYearStart <= numOfStartDayInMonth + GetCountDaysInMonth(static_cast<Month>(i), GetYear()))
        {
            return daysFromYearStart - numOfStartDayInMonth;
        }
        numOfStartDayInMonth += GetCountDaysInMonth(Month{i},GetYear());
    }
    return 0;
}

Month CDate::GetMonth() const
{
    unsigned int cnt400 = int(m_daysCount / daysIn400Years) * daysIn400Years;
    unsigned int cnt100 = int ((m_daysCount - cnt400) / daysIn100Years) * daysIn100Years;
    unsigned int cnt4 = int((m_daysCount - cnt400 - cnt100) / daysIn4Years) * daysIn4Years;
    unsigned int cnt1 = int((m_daysCount - cnt400 - cnt100 - cnt4) / daysInYear);
    cnt1 = daysInYear * ((cnt1 == 4) ? 3 : cnt1);
    unsigned int daysFromYearStart = m_daysCount - (cnt400 + cnt100 + cnt4 + cnt1);
    unsigned int numOfStartDayInMonth = 0;
    for (int i = 1; i <= 12; i++)
    {
        if (daysFromYearStart <= numOfStartDayInMonth + GetCountDaysInMonth(static_cast<Month>(i), GetYear()))
        {
            return static_cast<Month>(i);
        }
        numOfStartDayInMonth += GetCountDaysInMonth(Month{i},GetYear());
    }
    return Month::DECEMBER;
}

WeekDay CDate::GetWeekDay() const
{
    int weekdayNum = m_daysCount % 7 + 3;
    return static_cast<WeekDay>(weekdayNum);
}

bool CDate::IsValid() const
{
    return m_daysCount > 0 && m_daysCount <= MAX_TIMESTAMP;
}

bool CDate::operator==(const CDate &other) const
{
    return m_daysCount == other.m_daysCount;
}

bool CDate::operator!=(const CDate &other) const
{
    return m_daysCount != other.m_daysCount;
}

bool CDate::operator<(const CDate &other) const
{
    return m_daysCount < other.m_daysCount;
}

bool CDate::operator>(const CDate &other) const
{
    return m_daysCount > other.m_daysCount;
}

bool CDate::operator>=(const CDate &other) const
{
    return m_daysCount >= other.m_daysCount;
}

bool CDate::operator<=(const CDate &other) const
{
    return m_daysCount <= other.m_daysCount;
}

CDate &CDate::operator+=(const int daysCount)
{
    if (IsValid())
    {
        m_daysCount += daysCount;
    }
    m_isValidDate = IsValid();
    return *this;
}

CDate &CDate::operator-=(const int daysCount)
{
    if (IsValid())
    {
        m_daysCount -= daysCount;
    }
    m_isValidDate = IsValid();
    return *this;
}

CDate &CDate::operator++()
{
    if (IsValid())
    {
        ++m_daysCount;
    }
    m_isValidDate = IsValid();
    return *this;
}

CDate CDate::operator++(int)
{
    if (IsValid())
    {
        CDate tmpCopy(*this);
        ++*this;
        return tmpCopy;
    }
    m_isValidDate = IsValid();
    return *this;
}

CDate &CDate::operator--()
{
    if (IsValid())
    {
        --m_daysCount;
    }

    m_isValidDate = IsValid();
    return *this;
}

CDate CDate::operator--(int)
{
    if (IsValid())
    {
        CDate tmpCopy(*this);
        --*this;
        return tmpCopy;
    }
    m_isValidDate = IsValid();
    return *this;
}

CDate CDate::operator+(const int daysCount) const
{
    if (IsValid())
    {
        return CDate(m_daysCount + daysCount);
    }
    return *this;
}

CDate CDate::operator-(const int daysCount) const
{
    if (IsValid())
    {
        return CDate(m_daysCount - daysCount);
    }
    return *this;
}

int CDate::operator-(CDate const& other) const
{
    if (IsValid() && other.IsValid())
    {
        return m_daysCount - other.m_daysCount;
    }
    return 0;
}

std::istream& operator>>(std::istream &stream, CDate& date)
{
    unsigned int day, month, year;
    if ((stream >> day) && (stream >> month) && (stream >> year))
    {
        date = CDate(day, static_cast<Month>(month), year);
    }
    else
    {
        stream.setstate(std::ios_base::failbit | stream.rdstate());
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, CDate const& date)
{
    if (date.IsValid())
    {
        stream << static_cast<int>(date.GetDay()) << "."
               << static_cast<int>(date.GetMonth()) << "."
               << static_cast<int>(date.GetYear());
    } else
    {
        stream << "INVALID";
    }
    return stream;
}