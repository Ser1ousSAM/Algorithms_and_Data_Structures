#include<iostream>
#include<string>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int main(int argc, char* argv[]){
	vector<int> nums;
	for(int i = 2; i < argc; i++){
		string temp = argv[i];
		if (is_number(temp)){
			nums.push_back(atoi(argv[i]));	
		}else{
			cout << temp << "non-valid number in array\n";
			return 0;
		}
	}
	if (argc >=3){
		if (strcmp(argv[1], "inc")== 0){  
			sort(nums.begin(), nums.end());
		}else if(strcmp(argv[1], "dec")==0){
			sort(nums.begin(), nums.end(), greater<int>());
		}else{
			cout << "non-valid argv[]\n";
			return 0;
		}
	} else {
		cout << "arguments not enough\n";
		return 0;
	}
	for(auto i : nums){
		cout << i << " ";
	}
	cout << '\n';
}
