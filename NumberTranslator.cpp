/*
check if number is divisible by 100
	divide by 100 and use integer result as hundreds array index 
	add hundreds array string value to return string
	subtract 100
check is number is divisible by ten and use modulus to get remainder
	if divided by ten returns one
		use the modulus remainder as the teens array index '0'-> "ten";'1'-> "eleven"
		add teens array string value to return string and return the final result
	else if divided by ten returns more than one and modulus returns 0
		use the integer result as the tens array index
		add tens array string value to return string and return the final result
	else if divided by ten returns more than one and modulus returns 1 or greater
		use the integer result as the tens array index
		add tens array string value AND a dash "-" to the return string
		use the remainder as the ones array index
		add the ones array string value to the return string and return the final result 	

******************

***Divide by the magnitude to get a value EX. 4830 -> 4830 / 1000 = 4 remainder 830
***Use modulus to get remainder
***Next take the value apply the logic above
***Finally set input to the remainder which will be evaluated by the next independent if statement
*/
#define MAX_SIZE_UINT64 3875820019684212735  

#include <cstdint>
#include <cmath>
#include <string>
#include <iostream>
#include <locale>		//std::toupper , std::locale


using namespace std; 

//TO DO: Add input validation for when users enter strings instead of numbers


const string translateNumber(uint64_t user_number){
	
	string hundreds[9] = {"one hundred ", "two hundred ", "three hundred ", "four hundred ", "five hundred ", "six hundred ", "seven hundred ", "eight hundred ", "nine hundred "};

	string tens[9] = {"ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
	
	string teens[9] =  {"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
	
	string ones[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	
	string magnitude[8] = {""," thousand ", " million ", " billion ", " trillion ", " quadrillion "," quintillion ", " sextillion "};
	
	
	//make sure the number entered is within range.
	if (!(user_number <= MAX_SIZE_UINT64)){
		string error="Invalid input! Enter a positive number less than 3,875,820,019,684,212,736 ... ";
		return error;
	}else{

	
		uint64_t number_to_process,remainder,magnitude_value;
		int h_index,tens_index,teens_index,ones_index,first_3_digits;
		
		locale loc;
		string result;
		
		number_to_process = user_number;
		
		
		
		if (number_to_process == 0){
			result = "zero";
			return result;
		}
		
		for (int i = 18; i >= 0; i-=3){
			
			magnitude_value=pow(10,i);											//Establish the magnitude of the number: EX-> million, billion, etc...
			
			if(number_to_process >= magnitude_value){
				
							
			
				remainder = number_to_process % magnitude_value;					//Get the remainder. We will need it to isolate the first three digits
				
				first_3_digits = (number_to_process - remainder) / magnitude_value;	//Capture the first 3 digits
					
				
				//Check if the first digit has a value (the hundreds place)
				if((first_3_digits / 100 ) > 0){
					
					h_index = first_3_digits / 100;		 					//Capture the hundreds value
					result += hundreds[h_index-1];							//Append the corresponding hundreds string value to result. h_index-1 accounts for zero index offset.
					first_3_digits -= (h_index * 100);						//Update first 3 digits to reflect only what remains after accounting for the hundreds value.
				
				}
				
				//Check if the the remaining portion is a value in the teens (between 11 and 19)	
				if ((first_3_digits  > 10) && (first_3_digits < 20)){
					teens_index = first_3_digits % 10;						//Capture the teen index value through the remainder since these mumbers are greater than 10 and less than 20 (values 1-9)
					result += teens[teens_index - 1];						//Append corresponding teen array string. The teen_index-1 accounts for the zero index offset.
					first_3_digits -= (10 + teens_index);					//Update first 3 digits to reflect only what remains after accounting for the teens value.
					
				
				}
			
				//Check if the remaining portion is a multiple of ten
				if(first_3_digits / 10 > 0){
					tens_index = first_3_digits / 10;						//Capture the tens value	
					result += tens[tens_index - 1];							//Append corresponding tens string value. ten_index-1 accounts for zero index offset.
					if (first_3_digits % 10 > 0){							//Check if number requires a dash
						result += "-";
					}
													
					first_3_digits -= (tens_index * 10);					//Update first 2 digits to reflect only what value remains after processing tens place
					
				}
				
				
				//Check if the remaining portion is a value between 1 and 9
				if (first_3_digits > 0 && first_3_digits < 10){
					
					ones_index = first_3_digits;							//Capture the ones index using what value remains in the ones place
					result += ones[ones_index-1];							//Append the corresponding ones string value. ones_index-1 accounts for zero index offset.
					
					if ((first_3_digits -= ones_index) != 0){          		//Sanity check: Value should be zero bc everything is accounted for.
						cerr << "He's dead Jim! The math broke..."<<endl;
						break;
					}
				}
				result += magnitude[i/3];									//Append the magnitude
				number_to_process = remainder;								//Now we process what remains.
			}
		}
		result[0] = toupper(result[0],loc);									//Format first letter to be Uppercase before returning result. 
																	
		return result;
	}
										
	
		
}

int main(){
	string response;
	char proceed;
	uint64_t number;
	char ch;
	cout << "***********This program converts numbers into text.***********\n\n";

	do{
		proceed = 0;
		cout << "\nEnter a positive number: ";
		cin >> number;

		
		if (!(number > 0)){
			cout << "\nThat's not a valid input... Press enter to try again.\n";
			while ((ch=getchar()) != EOF && ch != '\n');
			cin.clear();
			cin.ignore();
			continue;
		}
		while ((ch=getchar()) != EOF && ch != '\n');
		
		cout << "Translation: "<< endl;
		cout << translateNumber(number) << endl << endl; 
		cout << "Press any key to continue or Enter 'q' to quit: ";
		proceed=getchar();
		while ((ch=getchar()) != EOF && ch != '\n');
		
	}while(proceed != 'q');
	

	return 0;
}
