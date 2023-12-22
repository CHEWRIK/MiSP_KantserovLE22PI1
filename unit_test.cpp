#include <UnitTest++/UnitTest++.h>
#include "Connect.h"

using namespace std;

struct Cons_fix {
	Connect * p;
	Cons_fix() {
		p = new Connect();
	}
	~Cons_fix() {
		delete p;
	}
};

SUITE(Connect_to_server)
{
	TEST_FIXTURE(Cons_fix, NormalTestCase){
		//1 Successful scenario
		p->name_original_file = "/home/stud/C++Projects/kur-main/client/my.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/vclient.conf";
		p->Connect_to_server("2130706433", "33333");
		CHECK(true);	
	}

	TEST_FIXTURE(Cons_fix, InvalidServerAddress){
		//2 Connecting to the server. The wrong address was entered
		p->name_original_file = "/home/stud/C++Projects/kur-main/client/my.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/vclient.conf";
		CHECK_THROW(p->Connect_to_server("2130707717", "33333"), error_proj);
			
	}

	TEST_FIXTURE(Cons_fix, InvalidServerPort){
		//3 Connecting to the server. The wrong port has been entered
		p->name_original_file = "/home/stud/C++Projects/kur-main/client/my.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/vclient.conf";
		CHECK_THROW(p->Connect_to_server("2130706433", "3445"), error_proj);
			
	}

	TEST_FIXTURE(Cons_fix, PasswordFileDoesNotExist){
		//4 Identification error. The wrong address for the file with usernames and passwords
		p->name_original_file = "/home/stud/C++Projects/kur-main/client/my.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/qwe//vclient.conf";
		CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);
			
	}

	TEST_FIXTURE(Cons_fix, InvalidLogin){
		//5 Identification error. The wrong username was entered
		p->name_original_file = "/home/stud/C++Projects/kur-main/client/my.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/ErrorLogin.conf";
		CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);
			
	}

	TEST_FIXTURE(Cons_fix, InvalidPassword){
		//6 Authentication error. The wrong password was entered
		p->name_original_file = "//home/stud/C++Projects/kur-main/client/my.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/ErrorPassword.conf";
		CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);
			
	}

	TEST_FIXTURE(Cons_fix, VectorFileOpeningError){
		//7 Error opening a vector file
		p->name_original_file = "/home/stud/C++Projects/kur-main/client/qwe//123.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/vclient.conf";
		CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);
			
	}

	TEST_FIXTURE(Cons_fix, VectorFileReadError){
		//8 Error reading from a vector file
		p->name_original_file = "/home/stud/C++Projects/kur-main/client/None.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/vclient.conf";
		CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);
			
	}

	TEST_FIXTURE(Cons_fix, SumFileReadError){
		//9 Error opening the file to record the amount
		p->name_original_file = "/home/stud/C++Projects/kur-main/client/my.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/@/@/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/vclient.conf";
		CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);
			
	}

	TEST_FIXTURE(Cons_fix, WrongIpAddressEntered){
		//10 The ip address is entered incorrectly
		p->name_original_file = "/home/stud/C++Projects/kur-main/client/my.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/vclient.conf";
		CHECK_THROW(p->Connect_to_server("string", "33333"), error_proj);
			
	}

	TEST_FIXTURE(Cons_fix, WrongPortEntered){
		//11 The port was entered incorrectly
		p->name_original_file = "/home/stud/C++Projects/kur-main/client/my.txt";
		p->name_result_file = "/home/stud/C++Projects/kur-main/client/resultat.txt";
		p->name_auto_file = "/home/stud/C++Projects/kur-main/client/config/vclient.conf";
		CHECK_THROW(p->Connect_to_server("2130706433", "string"), error_proj);
			
	}
	
}

int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}
