/** 
 *  @author Anonymous (do not change)
 *  
 *  Question 8: 
 *  
 *  You are given the following information, but you may prefer 
 *  to do some research for yourself.
 *   •	1 Jan 1900 was a Monday.
 *   •	Thirty days has September, April, June and November. All the rest 
 *      have thirty-one, saving February alone, which has twenty-eight, rain 
 *      or shine. And on leap years, twenty-nine.
 *   •	A leap year occurs on any year evenly divisible by 4, but not on a 
 *      century unless it is divisible by 400.
 *      
 *  How many Tuesdays fell on the first of the month during the twentieth 
 *  century (1 Jan 1901 to 31 Dec 2000)?
 *      
 *  Note, this problem is inspired by Project Euler so, as stated in the 
 *  rules of Project Euler, your solution should return an answer under 
 *  60 seconds.
*/

import java.util.Calendar;
import java.util.Date;

public class CWK2Q8 {

	public static int getDayOfMonth(Date iter_date, Calendar new_cal) {

		return new_cal.get(Calendar.DAY_OF_MONTH);

	}

	public static int getDayOfWeek(Date iter_date, Calendar new_cal) {

		return new_cal.get(Calendar.DAY_OF_WEEK);

	}

	public static Date addDays(Date iter_date, int days, Calendar new_cal) {

		new_cal.add(Calendar.DATE, days);
		return new_cal.getTime();

	}

	public static Date createDate(int year, int month, int day_of_month) {

		Calendar my_calendar = Calendar.getInstance();
		my_calendar.set(year, month, day_of_month);
		return my_calendar.getTime();

	}

	public static int howManyTuesdays() {

		int count_tuesdays = 0;

		// Creating general calendar instance
		Calendar new_cal = Calendar.getInstance();

		// Start date
		Date iter_date = createDate(1901, 0, 1);

		// Final date
		Date end_date = createDate(2000, 11, 31);
		
		while (iter_date.compareTo(end_date) < 0) {

			new_cal.setTime(iter_date);

			if (getDayOfWeek(iter_date, new_cal) == 3 && getDayOfMonth(iter_date, new_cal) == 1)

				count_tuesdays++;

			iter_date = addDays(iter_date, 7, new_cal);

		}

		return count_tuesdays;

	}
	
	public static void main(String[] args) {

		int result = CWK2Q8.howManyTuesdays();
		System.out.println("Number of Tuesdays = " + result);

	}

}
