/* * Copyright (C) 2018 Leonardo Guilherme Lucena de Freitas
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include "ofLog.h"
#include "ofxAsap.h"

int main(int argc, char *argv[])
{
    /* Setting locale helps with local time format. It is not required. */
    setlocale(LC_ALL, "");

    // ################### date/time ###################
    std::cout << std::endl;
    std::cout << std::endl;
    ofLogNotice("date/time examples");
    std::cout << std::endl;
    std::cout << std::endl;
    /* If no arguments passed, its the same as asap::now() */
    asap::datetime d1;

    /* You can pass a string as a date or time. It tries its best to detect the format,
   * it defaults to asap::datetime(0). */
    asap::datetime d2("08/07/1987");

    /* You can also pass a format specifier. They're the same used by strftime */
    asap::datetime d3("08/07/1987 23:45:12", "%d/%m/%Y %H:%M:%S");

    /* A broken down time may be specified, in the order: year, month, day of month, hour, minute, second.
   * Be aware that months start at 0 for January (as most date/time APIs) */
    asap::datetime d4(1983, 6, 17);

    /* Default printing format is day-month-year hour:minute:second */
    std::cout << "d1          ->   " << d1 << std::endl;

    /* You can also pass a format to str(). Consult strftime manual for the available formats. */
    std::cout << "d2          ->   " << d2.str("%c") << std::endl;
    std::cout << "d3          ->   " << d3.str("date: %d/%m/%Y time: %H:%M") << std::endl;
    std::cout << "d4          ->   " << d4.str("%FT%T%z") << std::endl;
    std::cout << "now         ->   " << asap::now() << std::endl;
    std::cout << "tomorrow    ->   " << asap::tomorrow() << std::endl;
    std::cout << "yesterday   ->   " << asap::yesterday() << std::endl;

    // ################### duration ###################
    std::cout << std::endl;
    std::cout << std::endl;
    ofLogNotice("duration examples");
    std::cout << std::endl;
    std::cout << std::endl;

    /* duration types represent durations in various granularities, from seconds to days. */
    auto ten_years = asap::years(10);

    /* you can specify a fraction of a duration: */
    auto half_year = asap::years(0.5f);

    /* you can sum and subtract durations. be aware that the right operand will be converted to the first operand
   * granularity (i.e, when adding years + days, days will be converted to a fraction of a year) */
    auto one_year_and_quarter = asap::years(1) + asap::months(3);

    /* you can add or subtract a duration from a datetime */
    auto ten_years_from_now = asap::now() + ten_years;

    /* subtracting two datetimes yields a duration, in seconds */
    auto another_ten_years = ten_years_from_now - asap::now();

    std::cout << "ten_years            ->   " << ten_years << std::endl;
    std::cout << "one_year_and_quarter ->   " << one_year_and_quarter << std::endl;
    std::cout << "ten_years_from_now   ->   " << ten_years_from_now << std::endl;
    std::cout << "another_ten_years    ->   " << another_ten_years << std::endl;

    /* be aware that for printing and arithmethics, a month has 30 days, thus half an year
   * is actually 6 months, 2 days and 12 hours. asap::years(0.5) != asap::months(6) */
    std::cout << "half_year            ->   " << half_year << std::endl;

    // ################### literals ###################
    std::cout << std::endl;
    std::cout << std::endl;
    ofLogNotice("literals examples");
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "next day                    \t->   " << asap::now() + 1_day << std::endl;
    std::cout << "1_day + 1_hour              \t->   " << 1_day + 1_hour << std::endl;
    std::cout << "1_day - (1_hour + 1_minute) \t->   " << 1_day - (1_hour + 1_minute) << std::endl;

    // ################### period ###################
    std::cout << std::endl;
    std::cout << std::endl;
    ofLogNotice("period examples");
    std::cout << std::endl;
    std::cout << std::endl;
    /* Creates a period, from now until tomorrow. */
    auto period = asap::now().until(asap::tomorrow());

    /* Iterates from now until tomorrow, by every hour, using oldschool iterators.
   * Be aware that tomorrow happens to be next day *exactly* at midnight, which means
   * unless asap::now() is exactly at 0 minutes and 0 seconds, the next day will
   * never be printed. */
    auto everyhour = period.every(asap::hours(1));
    std::cout << "every hour until tomorrow:" << std::endl;
    for (auto i = everyhour.begin(); i != everyhour.end(); i++)
    {
        std::cout << "* " << *i << std::endl;
    }
    std::cout << std::endl;

    /* you can also use the newschool for :) */
    std::cout << "every 3 hours until tomorrow:" << std::endl;
    for (auto d : period.every(asap::hour(3)))
    {
        std::cout << "* " << d << std::endl;
    }

    return 0;
}
