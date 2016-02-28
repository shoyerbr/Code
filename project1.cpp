#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <queue>
#include <math.h>
#include <fstream>
#include "line.h"

std::ofstream outfile;
float wait;
int context;
float ans;

void print(std::vector<line> q, int number)
{
	std::cout << "[Q";
	for (unsigned int i = number; i < q.size(); i++)
		std::cout << " " << q[i].return_number();
	std::cout << "]";
}

void inc_io(std::vector<line> &io, int number)
{
		for (unsigned int i = 0; i < io.size(); i++)
			io[i].set_io(io[i].return_io() - number);
}

void do_io(std::vector<line> &q, std::vector<line> &io,int &tme, int num)
{
	tme += io[0].return_io();
	q[0].set_burst_tme(q[0].return_burst_tme() - io[0].return_io());
	int number = io[0].return_io();
	if (q.size() > 1)
		wait += number*(q.size() - 1);
	std::cout << "\ntime " << tme << "ms: P" << io[0].return_number() << " completed I/O ";
	io[0].reset();
	q.push_back(io[0]);
	io.erase(io.begin());
	if ((num == 1) && (q.size() > 1))
		std::sort(q.begin() + 1, q.end(), cpu_comp);
	if (q.size() == 1)
		print(q,0);
	else
		print(q,1);
	inc_io(io, number);
	if (q.size() == 1)
	{
		tme += 9;
		inc_io(io,9);
		std::cout << "\ntime " << tme << "ms: P" << q[0].return_number() << " started using the CPU ";
		context++;
		print(q,1);
	}
		
}

void do_cpu(std::vector<line> &q, std::vector<line> &io,int &tme, int num)
{
	std::sort(io.begin(), io.end(), comp);
	tme += q[0].return_burst_tme();
	if (q.size() > 1)
		wait +=  q[0].return_burst_tme()*(q.size() - 1);
	inc_io(io, q[0].return_burst_tme());
	q[0].set_burst(q[0].return_burst() - 1);
	if (q[0].return_burst() == 0)
	{
		std::cout << "\ntime " << tme << "ms: P" << q[0].return_number() << " terminated ";
		q.erase(q.begin());	
		print(q,0);
	}
	else
	{
		std::cout << "\ntime " << tme << "ms: P" << q[0].return_number() << " completed its CPU burst ";
		print(q,1);
		q[0].reset_cpu();
		std::cout << "\ntime " << tme << "ms: P" << q[0].return_number() << " blocked on I/O ";
		print(q,1);
		io.push_back(q[0]);
		q.erase(q.begin());	
	}
	if (q.size() > 0)
	{
		if (io[0].return_io() > 9)
		{
			tme += 9;
			inc_io(io,9);
			wait += 9*(q.size() -1);
			std::cout << "\ntime " << tme << "ms: P" << q[0].return_number() << " started using the CPU ";
			context++;
			print(q,1);
		}
		else
			{
				int temp = io[0].return_io();
				do_io(q,io,tme, num);
				inc_io(io,9);
				if (q.size() > 1)
					wait += 9*(q.size() -1);
				std::cout << "\ntime " << tme + temp + 1 << "ms: P" << q[0].return_number() << " started using the CPU ";
				context++;
				tme += 9;
				print(q,1);
			}
	}
}


void SJF(std::vector<line> q, int total_burst)
{
	int tme = 0;
	std::vector<line> io;
	std::cout << "time 0ms: Simulator started for SJF ";
	std::sort(q.begin(), q.end(), cpu_comp);
	print(q,0);
	tme += 9;
	wait += 9*(q.size()-1);
	std::cout << "\ntime " << tme << "ms: P" << q[0].return_number() << " started using the CPU ";
	context++;
	print(q,1);
	
	while (q.size() > 0 || io.size() > 0)
	{
		std::sort(io.begin(), io.end(), comp);
		if (q.size() > 1)
			std::sort(q.begin() + 1, q.end(), cpu_comp);
		if (q.size() != 0 && (io.size() == 0 || q[0].return_burst_tme() < io[0].return_io()))
		{
			do_cpu(q,io,tme,1);
			//did_cpu = true;
		}
		else
			{
				do_io(q,io,tme,1);
				//did_io = true;
			}
		
	}
	
	std::cout << "\ntime " << tme << "ms: Simulator ended for SJF\n";
	float average_wait = wait/total_burst;
	outfile << "-- average wait time: " << std::setprecision(2) << std::fixed << average_wait <<" ms\n";
	outfile << "-- average turnaround time: "<< std::setprecision(2) << std::fixed << float(average_wait + ans + 9) <<" ms\n";
	outfile << "-- total number of context switches: " << context << "\n";
}

void FCFS(std::vector<line> q, int total_burst)
{
	int tme = 0;
	std::vector<line> io;
	std::cout << "time 0ms: Simulator started for FCFS ";
	print(q,0);
	tme += 9;
	wait += 9*(q.size()-1);
	std::cout << "\ntime " << tme << "ms: P" << q[0].return_number() << " started using the CPU ";
	context++;
	print(q,1);
	//bool did_cpu = false;
	//bool did_io = false;
	while (q.size() > 0 || io.size() > 0)
	{
		std::sort(io.begin(), io.end(), comp);
		if (q.size() != 0 && (io.size() == 0 || q[0].return_burst_tme() < io[0].return_io()))
		{
			do_cpu(q,io,tme,0);
			//did_cpu = true;
		}
		else if (q.size() == 0 || (io[0].return_io() < q[0].return_burst_tme()))
			{
				do_io(q,io,tme,0);
				//did_io = true;
			}
		
	}	
	
	std::cout << "\ntime " << tme << "ms: Simulator ended for FCFS\n\n";
	float average_wait = float(wait/total_burst);
	outfile << "-- average wait time: " << std::setprecision(2) << std::fixed << average_wait <<" ms\n";
	outfile << "-- average turnaround time: "<< std::setprecision(2) << std::fixed << float(average_wait + ans + 9) <<" ms\n";
	outfile << "-- total number of context switches: " << context << "\n";
}

int main(int argc, char **argv)
{	
	std::string temp;
	std::vector<line> q;
	std::ifstream input;
	input.open(argv[1]);
	int total_burst = 0;
	if (argv[2] != NULL)
	{
		outfile.open(argv[2]);
		while(std::getline(input,temp))
		{
			line bucket;
			//input >> temp;
			if (temp[0] != '#' && temp[0] != ' ' && temp.size() > 1)
			{
				int pos = temp.find("|");
				std::string bar = temp.substr(0,pos);
				bucket.set_number(atoi(bar.c_str()));
				temp = temp.substr(pos + 1, temp.length());
				pos = temp.find("|");
				bar = temp.substr(0,pos);
				int tempp = atoi(bar.c_str());
				bucket.set_burst_tme(tempp);
				bucket.set_burst_tme_reserve(tempp);
				temp = temp.substr(pos + 1, temp.length());
				pos = temp.find("|");
				bar = temp.substr(0,pos);
				bucket.set_burst(atoi(bar.c_str()));
				total_burst += atoi(bar.c_str());
				temp = temp.substr(pos + 1, temp.length());
				pos =  temp.length();
				bar = temp.substr(0,pos);
				bucket.set_io(atoi(bar.c_str()));
				bucket.set_io_reserve(atoi(bar.c_str()));
				q.push_back(bucket);
			}
		}	
		float num = 0;
		float den = 0;
		for (unsigned int i = 0; i < q.size(); i++)
		{
			num += q[i].return_burst_tme() * q[i].return_burst();
			den += q[i].return_burst();
		}
		ans = num/den;



		if (q.size() != 0)
		{
			outfile << "Algorithm FCFS\n";
			outfile << "-- average CPU burst time: " << std::setprecision(2) << std::fixed << ans << " ms\n";
			std::vector<line> other_q = q;
			std::sort(q.begin(), q.end(), num_comp);
			wait = 0;
			context = 0;
			FCFS(q, total_burst);
			wait = 0;
			context = 0;
			outfile << "Algorithm SJF\n";
			outfile << "-- average CPU burst time: " << std::setprecision(2) << std::fixed << ans << " ms\n";
			SJF(other_q, total_burst);
		}
		else
			perror("Error file not found");

	}
}