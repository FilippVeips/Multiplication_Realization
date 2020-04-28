#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <chrono>
#include <windows.h>
#include <fstream>

using namespace std;

class Number 
{
public:
	Number(initializer_list<int> input) :container(input) {};
	Number() {};
	Number(int size)
	{
		for (int i = 0; i != size; i++) {
			container.push_back(0);
		}
	};

	void push_back(int element) 
	{
		this->container.push_back(element);
	}

	int& operator[](int index) 
	{
		return this->container[index];
	}
	 
	static int get_size(Number numbervector) 
	{
		return numbervector.container.size();
	}

	static Number get_first_zero (Number origin, int size) 
	{
		Number newNumber(get_size(origin) + size);
		for (int i = get_size(origin)-1; i >= 0; i--)
		{
			newNumber[i + size] = origin[i];
		}
		return newNumber;
	}

	Number operator+(Number added)
	{
		int maximum = 0;
		if (get_size(*this) > get_size(added))
		{
			maximum = get_size(*this);
			added = get_first_zero(added, maximum - get_size(added));
		}
		else if(get_size(*this) < get_size(added))
		{
			maximum = get_size(added);
			*this= get_first_zero(*this, maximum - get_size(*this));
		}
		else
		{
			maximum = get_size(*this);
		}
		int mind_number = 0;
		for (int i = maximum-1; i >=0; i--) 
		{
			this->container[i] = this->container[i] + added[i]+mind_number;
			mind_number = this->container[i] / 10;
			this->container[i] = this->container[i] % 10;
		}
		if (mind_number > 0) 
		{
			this->container.push_back(0);
			for (int i = maximum; i > 0; i--)
			{
				this->container[i] = this->container[i - 1];
			}
			this->container[0] = mind_number;
		}
		return *this;
	}

	Number operator-(Number subtrahend) 
	{
		Number result;
		Number max_number;
		Number min_number;
		if (get_size(*this) > get_size(subtrahend))
		{
			max_number = *this;
			subtrahend = get_first_zero(subtrahend, get_size(max_number)-get_size(subtrahend));
			min_number = subtrahend;
		}
		else if(get_size(*this) == get_size(subtrahend))
		{
			for (int i = 0; i != get_size(*this); i++) 
			{
				if (this->container[i] > subtrahend[i])
				{
					max_number = *this;
					min_number = subtrahend;
					break;
				}
				else if (this->container[i] < subtrahend[i])
				{
					max_number = subtrahend;
					min_number = *this;
					break;
				}
				else
				{
					max_number = *this;
					min_number = subtrahend;
				}
			}
		}
		else
		{
			max_number = subtrahend;
			*this = get_first_zero(*this, get_size(max_number)-get_size(*this));
			min_number = *this;
		}
		for (int i = get_size(max_number)-1; i >= 0; i--)
		{
			if ((max_number[i] - min_number[i])<0) 
			{
				result.push_back(10 + max_number[i] - min_number[i]);
				for (int j = i - 1; j >= 0; j--) 
				{
					max_number[j]--;
					if (max_number[j] >= 0) 
					{
						break;
					}
					else 
					{
						max_number[j] = max_number[j] + 10;
					}
				}
			}
			else 
			{
				result.push_back(max_number[i] - min_number[i]);
			}
		}
		int indikator_of_non_zero_elements = 0;
		Number answer;
		for (int i = Number::get_size(result)-1; i >=0; i--)
		{
			if (result[i]!=0 or indikator_of_non_zero_elements == 1)
			{
				answer.push_back(result[i]);
				indikator_of_non_zero_elements = 1;
			}
		}
		return answer;
	}
	
	static pair<Number,Number> split(Number origin, int border) 
	{
		pair<Number, Number> devided_num;
		for (int i = 0; i != get_size(origin); i++) 
		{
			if (i < border)
			{
				devided_num.first.push_back(origin[i]);
			}
			else
			{
				devided_num.second.push_back(origin[i]);
			}
		}
		return devided_num;
	}

private:
	vector<int> container;
};

class Multiplicator
{
public:

	static Number generate_random_number(int size)
	{
		Number result;
		std::mt19937 gen(clock());
		std::uniform_int_distribution<> dis(0, 9);
		for (int i = 0; i != size; i++)
		{
			result.push_back(dis(gen));
		}
		result[0] = result[0] == 0 ? 1 : result[0];
		return result;
	}

	static Number Grade_School_Multiplication(Number MN1, Number MN2) //MN is for Multiplicated Number
	{
		Number multiplication_result = Number(Number::get_size(MN2)*2);;
		vector<Number> summurised_numbers;
		int resulting_size = Number::get_size(MN1) + Number::get_size(MN2);
		Number maximum;
		Number minimum;
		if (Number::get_size(MN1) >= Number::get_size(MN2))
		{
			maximum = MN1;
			minimum = MN2;
		}
		else
		{
			maximum = MN2;
			minimum = MN1;
		}
		for (int i = Number::get_size(maximum) -1; i >= 0; i--)
		{
			int mind_number = 0;
			Number resulting_number = Number(resulting_size);
			for (int j = Number::get_size(minimum)-1; j >= 0 ; j--)
			{
				resulting_number[j+i+1] = (minimum[j] * maximum[i]) % 10 +mind_number;
				mind_number= (minimum[j] * maximum[i]) / 10;
			}
			if (mind_number > 0)
			{
				resulting_number[i] = mind_number;
			}
			summurised_numbers.push_back(resulting_number);
		}
		int mind_number = 0;
		for (int j = resulting_size-1; j >= 0; j--) 
		{
			for (int i = 1; i != summurised_numbers.size(); i++)
			{
				summurised_numbers[i][j] = (summurised_numbers[i][j] + summurised_numbers[i - 1][j]);
			}
		}
		for (int j = resulting_size - 1; j >= 0; j--)
		{
			summurised_numbers[summurised_numbers.size() -1][j] = summurised_numbers[summurised_numbers.size() -1][j] + mind_number;
			mind_number = summurised_numbers[summurised_numbers.size()-1][j] / 10;
			summurised_numbers[summurised_numbers.size() -1][j] = summurised_numbers[summurised_numbers.size() -1][j] % 10;
		}
		Number answer;
		int indikator_of_non_zero_elements = 0;
		for (int i = 0; i != resulting_size; i++) 
		{
			if (summurised_numbers[summurised_numbers.size() - 1][i] != 0 or indikator_of_non_zero_elements == 1)
			{
				answer.push_back(summurised_numbers[summurised_numbers.size() - 1][i]);
				indikator_of_non_zero_elements = 1;
			}
		}
		return answer;
	}

	static Number Divide_and_Conquer_Algorithm(Number MN1, Number MN2)
	{
		Number result;
		pair<Number, Number> devided_numbers_pair_1;
		pair<Number, Number> devided_numbers_pair_2;
		int border_1 = 0;
		int border_2 = 0;
		Number min_number;
		if (Number::get_size(MN1) > Number::get_size(MN2)) 
		{
			border_2 = Number::get_size(MN2)-Number::get_size(MN2)/2;
			border_1 = Number::get_size(MN1) - (Number::get_size(MN2)-border_2);
			min_number = MN2;
		}
		else if (Number::get_size(MN1) < Number::get_size(MN2))
		{
			border_1 = Number::get_size(MN1)-Number::get_size(MN1) / 2;
			border_2 = Number::get_size(MN2) - (Number::get_size(MN1)-border_1);
			min_number = MN1;
		}
		else
		{
			border_1 = Number::get_size(MN1)-Number::get_size(MN1) / 2;
			border_2 = Number::get_size(MN2)-Number::get_size(MN2) / 2;
			min_number = MN1;
		}
		if (Number::get_size(MN1) > 1)
		{
			devided_numbers_pair_1 = Number::split(MN1,border_1);
		}
		if (Number::get_size(MN2) > 1)
		{
			devided_numbers_pair_2 = Number::split(MN2,border_2);
		}
		int multiplicator;
		if (Number::get_size(MN1) == 1 or Number::get_size(MN2) == 1)
		{
			return(Grade_School_Multiplication(MN1, MN2));
		}
		if (Number::get_size(min_number) % 2 != 0)
		{
			multiplicator = Number::get_size(min_number) - 1;
		}
		else
		{
			multiplicator = Number::get_size(min_number);
		}
		if (Number::get_size(MN1) > Number::get_size(MN2))
		{
			while (Number::get_size(MN1) > Number::get_size(MN2))
			{
				MN2.push_back(0);
			}
		}
		if (Number::get_size(MN2) > Number::get_size(MN1))
		{
			while (Number::get_size(MN2) > Number::get_size(MN1))
			{
				MN1.push_back(0);
			}
		}
		Number ac= Divide_and_Conquer_Algorithm(devided_numbers_pair_1.first, devided_numbers_pair_2.first);
		Number ad = Divide_and_Conquer_Algorithm(devided_numbers_pair_1.first, devided_numbers_pair_2.second);
		Number bc = Divide_and_Conquer_Algorithm(devided_numbers_pair_1.second, devided_numbers_pair_2.first);
		Number bd = Divide_and_Conquer_Algorithm(devided_numbers_pair_1.second, devided_numbers_pair_2.second);
		Number summa = ad + bc;
		for (int i = 0; i != multiplicator; i++) 
		{
			ac.push_back(0);
		}
		for (int i = 0; i != multiplicator/2; i++)
		{
			summa.push_back(0);
		}
		return ac + summa + bd;
	}

	static Number Karatsuba_Multiplication(Number MN1, Number MN2)
	{
		Number result;
		pair<Number, Number> devided_numbers_pair_1;
		pair<Number, Number> devided_numbers_pair_2;
		int border_1 = 0;
		int border_2 = 0;
		Number min_number;
		if (Number::get_size(MN1) > Number::get_size(MN2))
		{
			border_2 = Number::get_size(MN2) - Number::get_size(MN2) / 2;
			border_1 = Number::get_size(MN1) - (Number::get_size(MN2) - border_2);
			min_number = MN2;
		}
		else if (Number::get_size(MN1) < Number::get_size(MN2))
		{
			border_1 = Number::get_size(MN1) - Number::get_size(MN1) / 2;
			border_2 = Number::get_size(MN2) - (Number::get_size(MN1) - border_1);
			min_number = MN1;
		}
		else
		{
			border_1 = Number::get_size(MN1) - Number::get_size(MN1) / 2;
			border_2 = Number::get_size(MN2) - Number::get_size(MN2) / 2;
			min_number = MN1;
		}
		if (Number::get_size(MN1) > 1)
		{
			devided_numbers_pair_1 = Number::split(MN1, border_1);
		}
		if (Number::get_size(MN2) > 1)
		{
			devided_numbers_pair_2 = Number::split(MN2, border_2);
		}
		int multiplicator;
		if (Number::get_size(MN1) == 1 or Number::get_size(MN2) == 1)
		{
			return(Grade_School_Multiplication(MN1, MN2));
		}
		if (Number::get_size(min_number) % 2 != 0)
		{
			multiplicator = Number::get_size(min_number) - 1;
		}
		else
		{
			multiplicator = Number::get_size(min_number);
		}
		if (Number::get_size(MN1) > Number::get_size(MN2))
		{
			while (Number::get_size(MN1) > Number::get_size(MN2))
			{
				MN2.push_back(0);
			}
		}
		if (Number::get_size(MN2) > Number::get_size(MN1))
		{
			while (Number::get_size(MN2) > Number::get_size(MN1))
			{
				MN1.push_back(0);
			}
		}
		Number ac = Karatsuba_Multiplication(devided_numbers_pair_1.first, devided_numbers_pair_2.first);
		Number bd = Karatsuba_Multiplication(devided_numbers_pair_1.second, devided_numbers_pair_2.second);
		Number devided_numbers_pair_1_first_copyed = devided_numbers_pair_1.first;
		Number devided_numbers_pair_1_second_copyed = devided_numbers_pair_1.second;
		Number devided_numbers_pair_2_first_copyed = devided_numbers_pair_2.first;
		Number devided_numbers_pair_2_second_copyed = devided_numbers_pair_2.second;
		Number ab = devided_numbers_pair_1_first_copyed + devided_numbers_pair_1_second_copyed;
		Number cd = devided_numbers_pair_2_first_copyed + devided_numbers_pair_2_second_copyed;
		Number the_big_summa = Karatsuba_Multiplication(ab, cd);
		Number summa = the_big_summa - ac-bd;
		for (int i = 0; i != multiplicator; i++)
		{
			ac.push_back(0);
		}
		for (int i = 0; i != multiplicator / 2; i++)
		{
			summa.push_back(0);
		}
		return ac + summa + bd;
	}

};



int main()
{
	ofstream OutputFile;
	OutputFile.open("Result.csv");
	Number number_1;
	Number number_2;
	for (int i = 1; i != 1000; i++) 
	{
		double Grade_School_Multiplication_mean_value;
		double Divide_and_Conquer_Algorithm_mean_value;
		double Karatsuba_Multiplication_mean_value;
		for (int j = 0; j != 3; j++)
		{
			number_1 = Multiplicator::generate_random_number(i);
			Sleep(1);
			number_2 = Multiplicator::generate_random_number(i);

			double Grade_School_Multiplication_start = clock();
			Multiplicator::Grade_School_Multiplication(number_1, number_2);
			double Grade_School_Multiplication_stop = clock();

			double Divide_and_Conquer_Algorithm_start = clock();
			Multiplicator::Divide_and_Conquer_Algorithm(number_1, number_2);
			double Divide_and_Conquer_Algorithm_stop = clock();

			double Karatsuba_Multiplication_start = clock();
			Multiplicator::Karatsuba_Multiplication(number_1, number_2);
			double Karatsuba_Multiplication_stop = clock();

			Grade_School_Multiplication_mean_value = Grade_School_Multiplication_mean_value + (Grade_School_Multiplication_stop - Grade_School_Multiplication_start);
			Divide_and_Conquer_Algorithm_mean_value = Divide_and_Conquer_Algorithm_mean_value + (Divide_and_Conquer_Algorithm_stop - Divide_and_Conquer_Algorithm_start);
			Karatsuba_Multiplication_mean_value = Karatsuba_Multiplication_mean_value + (Karatsuba_Multiplication_stop - Karatsuba_Multiplication_start);
		}
		Grade_School_Multiplication_mean_value = Grade_School_Multiplication_mean_value / 3;
		Divide_and_Conquer_Algorithm_mean_value = Divide_and_Conquer_Algorithm_mean_value / 3;
		Karatsuba_Multiplication_mean_value = Karatsuba_Multiplication_mean_value / 3;
		OutputFile << (int)(i) << ',';
		OutputFile << (double)(Grade_School_Multiplication_mean_value) / CLOCKS_PER_SEC << ',';
		OutputFile << (double)(Divide_and_Conquer_Algorithm_mean_value) / CLOCKS_PER_SEC << ',';
		OutputFile << (double)(Karatsuba_Multiplication_mean_value) / CLOCKS_PER_SEC << '\n';
	}
}
