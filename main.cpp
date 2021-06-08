#include <iostream>
#include <vector>
#include <string>
#include <map>


std::vector<std::string> StopChecker(const std::map<std::string, std::vector<std::string>> buses,
	const std::string& stop_place) {
	std::vector<std::string> result;
	for (const auto& elem : buses) {
		for (int j = 0; j < elem.second.size(); ++j) {
			if (elem.second[j] == stop_place) {
				result.push_back(elem.first);
				
			}
		}
	}
	return result;
}


int main() {
	std::string command;
	std::map<std::string, std::vector<std::string>> buses;
	std::vector<std::string> order;
	int q;
	bool flag_only_one = true;
	std::cin >> q;
	int stop_count;
	std::string bus;
	std::string stop_no, stop_place;
	std::vector<std::string> buses_for_stop;
	
	for (int i = 0; i < q; ++i) {
		std::cin >> command;

		if (command == "NEW_BUS") {
			std::cin >> bus >> stop_count;
			order.push_back(bus);

			for (int j = 0; j < stop_count; ++j) {
				std::cin >> stop_no;
				buses[bus].push_back(stop_no);
			}
		}
		else if (command == "BUSES_FOR_STOP") {
			std::cin >> stop_place;
			buses_for_stop = StopChecker(buses, stop_place);

			if (buses_for_stop.size() != 0) {
				for (const auto& ord : order) {
					for (const auto& elem : buses_for_stop) {
						if (ord == elem) {
							std::cout << ord << " ";
						}
					}
					
				}
				std::cout << std::endl;
			}
			else {
				std::cout << "No stop" << std::endl;
			}



		}
		else if (command == "STOPS_FOR_BUS") {
			std::cin >> bus;

			for (const auto& elemm : order) {
			}
			if (buses[bus].size() > 0) {

				for (const auto& elem : buses[bus]) {
						
						buses_for_stop = StopChecker(buses, elem);
						std::cout << "Stop " << elem << ": ";
						
						if (buses_for_stop.size() == 1) {
							std::cout << "no interchange";
						}
						else {
							for (const auto& ord : order) {

								for (int kk = 0; kk < buses_for_stop.size(); ++kk) {
									if (ord == buses_for_stop[kk]) {

										if (buses_for_stop[kk] != bus) {
											std::cout << buses_for_stop[kk] << " ";

										}

									}

								}


							}

			

						}
						std::cout << std::endl;
				}
				
			}
			else {
				std::cout << "No bus" << std::endl;
				buses.erase(bus);
				
			}


		}
		else if (command == "ALL_BUSES") {
			if (buses.size() > 0) {
				for (const auto& elem : buses) {
					std::cout << "Bus " << elem.first << ":";
					for (int i = 0; i < elem.second.size(); ++i) {
						std::cout << " " << elem.second[i];
					}
					std::cout << std::endl;
				}
			}
			else {
				std::cout << "No buses" << std::endl;
			}
		}



	}


	return 0;
}
