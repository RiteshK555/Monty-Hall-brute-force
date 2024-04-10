#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char *argv[]){
	
	if(argc == 1){

		//check for args
		std::cout << "arguments not provided" << "\n";

	}	
	else if(argc == 2){

		//check for args
		std::cout << "num doors opened by host, num simulations not provided" << "\n";

	}
	else if(argc == 3){

		//check for args
		std::cout << "num simulations not provided" << "\n";

	}
	else if(argc == 4){

		//num doors
		int num_doors = 0;
		try{
			num_doors = std::stoi(argv[1]);

			if(num_doors <= 0){

				//strictly positive values allowed
				std::cout << "only positive values allowed" <<  "\n";
				return 0;

			}
		}
		catch(const std::invalid_argument& e){

			//check invalid args
			std::cout << "invalid argument " << e.what() << "\n";
			return 0;

		}
		catch(const std::out_of_range& e){

			//check out of range
			std::cout << "out of range " << e.what() << "\n";
			return 0;

		}

		//num doors opened by host
		int num_doors_opened_by_host = 0;
		try{
			num_doors_opened_by_host = std::stoi(argv[2]);

			if(num_doors_opened_by_host <= 0){

				//strictly positive values allowed
				std::cout << "strictly positive values allowed" << "\n";
				return 0;

			}
		}
		catch(const std::invalid_argument& e){

			//check invalid args
			std::cout << "invalid argument " << e.what() << "\n";
			return 0;

		}
		catch(const std::out_of_range& e){

			//check out of range 
			std::cout << "out of range " << e.what() << "\n";
			return 0;

		}

		//num simulations
		int num_simulations = 0;
		try{
			num_simulations = std::stoi(argv[3]);

			if(num_simulations <= 0){

				//strictly positive values allowed
				std::cout << "strictly positive values allowed" << "\n";
				return 0;

			}
		}
		catch(const std::invalid_argument& e){

			//check invalid args
			std::cout << "invalid argument " << e.what() << "\n";
			return 0;

		}
		catch(const std::out_of_range& e){

			//check out of range
			std::cout << "out of range " << e.what() << "\n";
			return 0;

		}

		if(num_doors_opened_by_host + 2 > num_doors){

			//check if possible to open doors
			std::cout << "it is not possible to open the doors specified" << "\n";
			return 0;

		}

		//total num of itrs
		int total_itrs = num_simulations;

		//count itrs in which switch results in winning
		int switch_itrs = 0;

		//count itrs in which sticking results in winning
		int stick_itrs = 0;

 		//SIMULATION FOR STICKING:
 		//we need not simulate opening of doors because it won't effect the
 		//probability at all
		for(int i = 0; i < total_itrs; i++){

			//first assign a prize position
			int prize_position = rng() % num_doors;

			//then assign contestant door position
			int contestant_door_position = rng() % num_doors;

			//check for first chairs
			if(prize_position == contestant_door_position){
				stick_itrs++;
			}

		}

		//SIMULATION FOR SWITCHING:
		for(int i = 0; i < total_itrs; i++){

			//first assign contestant position
			int contestant_position = rng() % num_doors;

			//second assign prize position
			int prize_position = rng() % num_doors;

			//create unopened doors list
			std::vector<int>unopened_doors;

			//push prize and contestant position
			if(contestant_position != prize_position)unopened_doors.push_back(prize_position);

			//create a vec or all selections 
			std::vector<int>all_selections;
			for(int i = 0; i < num_doors; i++){
				if(i != prize_position and i != contestant_position){
					all_selections.push_back(i);
				}
			}

			//shuffle selections to get opened doors
			shuffle(all_selections.begin(), all_selections.end(), rng);

			//select unopened positions
			for(int i = 0; i < all_selections.size(); i++){
				if(i >= num_doors_opened_by_host){
					unopened_doors.push_back(all_selections[i]);
				}
			}

			//shuffle unopened doors
			std::shuffle(unopened_doors.begin(), unopened_doors.end(), rng);

			//count itrs
			if(unopened_doors[0] == prize_position){
				switch_itrs++;
			}
		}

 		//output
		std::cout << "--- output ---" << "\n";
		std::cout << "switching : " << ((float)switch_itrs / total_itrs) * 100 << "\n";
		std::cout << "sticking : " <<  ((float)stick_itrs / total_itrs) * 100 << "\n";

	}
	else{

		//more args provided
		std::cout << "more than 4 arguments provided" << "\n";	

	}

	return 0;
}