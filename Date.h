#ifndef DATE_DATE_H
#define DATE_DATE_H

#include <iostream>

enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};
//TODO: при невалидной дате выбрасывать исключение
class CDate
{
public:
    CDate(unsigned day, Month month, unsigned year);

    explicit CDate(unsigned timestamp = 0);

    [[nodiscard]] unsigned GetDay()const;

    [[nodiscard]] Month GetMonth()const;

    [[nodiscard]] unsigned GetYear()const;

    [[nodiscard]] WeekDay GetWeekDay()const;

    [[nodiscard]] bool IsValid()const;

    bool operator ==(CDate const& other) const;
    bool operator !=(CDate const& other) const;

    bool operator <(CDate const& other) const;
    bool operator >(CDate const& other) const;

    bool operator >=(CDate const& other) const;
    bool operator <=(CDate const& other) const;

    CDate& operator +=(const int daysCount);
    CDate& operator -=(const int daysCount);

    CDate& operator ++();
    CDate operator ++(int);

    CDate& operator --();
    CDate operator --(int);

    CDate operator +(int daysCount) const;

    CDate operator-(int daysCount) const;
    int operator-(CDate const& other) const;

private:
    unsigned m_daysCount;
    bool m_isValidDate;
};
//TODO: реализовать число + дата
std::istream& operator>>(std::istream &stream, CDate& date);
std::ostream& operator<<(std::ostream& stream, CDate const& date);

#endif //DATE_DATE_H