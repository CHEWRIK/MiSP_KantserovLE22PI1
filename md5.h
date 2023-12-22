/** 
* @file md5.h
* @author Kancerov L. E.
* @version 1.0
* @date 25.11.2023
* @copyright IBST PGU
* @brief Header file for module md5
*/

#include <iostream>
#include <vector>

#include <cryptopp/hex.h> // HexEncoder

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h> // MD% 
std::string MD5_hash(std::string msg);