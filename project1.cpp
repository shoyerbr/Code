#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include "line.h"

void print(std::vector<line> q)
{
	std::cout << "[Q";
	for (int i =0; i < q.size(); i++)
		std::cout << " " << q[i].return_number();
	std::cout << "]";
}

int main(int argc, char **argv)
{	
	std::string temp;
	std::vector<line> q;
	std::ifstream input;
	std::vector<line> io;
	input.open(argv[1]);
	line cpu;
	int time = 0;
	bool dont = true;
	while(!input.eof())
	{
		line bucket;
		input >> temp;
		int pos = temp.find("|");
		std::string bar = temp.substr(0,pos);
		bucket.set_number(atoi(bar.c_str()));
		temp = temp.substr(pos + 1, temp.length());
		pos = temp.find("|");
		bar = temp.substr(0,pos);
		int tempp = atoi(bar.c_str());
		bucket.set_burst_time(tempp);
		bucket.set_burst_time_reserve(tempp);
		temp = temp.substr(pos + 1, temp.length());
		pos = temp.find("|");
		bar = temp.substr(0,pos);
		bucket.set_burst(atoi(bar.c_str()));
		temp = temp.substr(pos + 1, temp.length());
		pos =  temp.length();
		bar = temp.substr(0,pos);
		bucket.set_io(atoi(bar.c_str()));
		bucket.set_io_reserve(atoi(bar.c_str()));
		q.push_back(bucket);
	}
	bool go = true;
	bool start = true;
	int tcs = 13;
	std::cout << "time 0ms: Simulator started ";
	print(q);
	if (io.size() == 0)
		if (q.size() == 0)
			go = false;
	int counter  = 0;
	while (go)
	//for (int g = 0; g < 20; g++)
	{

		line foo;
		if (q.size() != 0){
			foo = q[0];
		}
		dont = true;
		 std::sort(io.begin(), io.end(), comp);
		 if (start && q.size() > 0)
		 {
		 	 for (int i = 0; i < io.size(); i++)
		 		io[i].set_io(io[i].return_io() - 13);
		 	 time += tcs;
		 	 foo = q[0];
		 	 cpu = foo;
		 	 std::cout << "\ntime " << time << "ms: P" << q[0].return_number() << "  Started using CPU  ";
		 	 q[0].reset_cpu();
		 	 cpu.reset_cpu();
		 	 cpu.reset();
		 	 q[0].reset();
		 	 q.erase(q.begin());
		 	 print(q);
		 	 start = false;
		 	 dont = false;
		 }
		 if (io.size() == 0)
		 {
			 time += cpu.return_burst_time();
			 start = true;
			 cpu.set_burst(cpu.return_burst() - 1);
			 if (cpu.return_burst() > 0)
			 {
			 	std::cout << "\ntime " << time << "ms: P" << cpu.return_number() << "  Completed its CPU burst ";
				io.push_back(cpu);
				print(q);
				cpu.reset();
				cpu.reset_cpu();
				std::cout << "\ntime " << time << "ms: P" << cpu.return_number() << "  Performing I/O  ";
				cpu.set_io(cpu.return_io() + 13);
				print(q);
			 }
			 else
			 {
			 	std::cout << "\ntime " << time << "ms: P" << cpu.return_number() << "  Terminated ";
			 	print(q);
			 }
		 }
		 else 
		 	if (q.size() == 0 && dont)
		 	{
				 foo = io[0];
				 time += foo.return_io();
				 std::cout << "\ntime " << time << "ms: p" << foo.return_number() << "  Completed I/O ";
				 for (int i = 0; i < io.size(); i++)
					 io[i].set_io(io[i].return_io() - foo.return_io());
				 if (foo.return_burst() >= 1)
					 q.push_back(foo);
				cpu.set_burst_time(cpu.return_burst_time() - foo.return_io() - 1);
				io.erase(io.begin());
				print(q);
		 	}
		 	else
			 {
				 if (io[0].return_io() < cpu.return_burst_time())
				 {
					 foo = io[0];
					 time += foo.return_io();
					 std::cout << "\ntime " << time << "ms: P" << foo.return_number() << "  Completed I/O  ";
					 for (int i = 0; i < io.size(); i++)
						 io[i].set_io(io[i].return_io() - foo.return_io() );
					 if (foo.return_burst() >= 1)
						 q.push_back(foo);
					cpu.set_burst_time(cpu.return_burst_time() - foo.return_io());
					io.erase(io.begin());
					print(q);
				 }
				 else 
				 {
					if (io[0].return_io() > cpu.return_burst_time())
					{
						time += cpu.return_burst_time();
						start = true;
						cpu.set_burst(cpu.return_burst() - 1);
						for (int i = 0; i < io.size(); i++)
							io[i].set_io(io[i].return_io() - cpu.return_burst_time());
						 if (cpu.return_burst() >= 1)
						 {
						 	std::cout << "\ntime " << time<< "ms: P" << cpu.return_number() << "  Completed its CPU burst  ";
							io.push_back(cpu);
							cpu.reset();
							cpu.reset_cpu();
							std::cout << "\ntime " << time << "ms: P" << cpu.return_number() << "  Performing I/O  ";
							print(q);
						 }
						  else
						 {
						 	std::cout << "\ntime " << time << "ms: P" << cpu.return_number() << "  Terminated ";
						 	print(q);
						 }
					}
				 }
			 }
		if (io.size() == 0)
			if (q.size() == 0)
				go = false;
	}
	std::cout << "\ntime " << time << "ms:  Simulator ended";
	std::cout << "\n";
}