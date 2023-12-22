/** 
* @file md5.h
* @author Kancerov L. E.
* @version 1.0
* @date 25.11.2023
* @copyright IBST PGU
* @brief Header file for Connect
*/

#pragma once
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <vector>

#include <string>
#include <locale>
#include <codecvt>

using namespace std;

/** 
* @brief Class connect server
* @param ip_addr addr serv
* @param port port serv
* @param name_original_file name file for read vector
* @param name_result_file name file for read write result
* @param name_auto_file name file for login and password
* @param username lofin client
* @param pswd password client
*/

class Connect{
    public:
        int ip_addr;
        int port;
        string name_original_file;
        string name_result_file;
        string name_auto_file;
        string username;
        string pswd;
        int Connect_to_server(string str1, string str2);
        void GetLoginPassword();

};


/** @brief Class error_proj
* @details Output error message
*/
class error_proj: public std::invalid_argument
{
public:
	explicit error_proj (const std::string& what_arg):
		std::invalid_argument(what_arg) {}
	explicit error_proj (const char* what_arg):
		std::invalid_argument(what_arg) {}
};

