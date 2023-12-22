/**
 * @file 
 */

#include "md5.h"
/**
* @brief Getting a hash code using the md5 algorithm
* @param msg messages for hashing
* @return hash code
*/
std::string MD5_hash(std::string msg)
{
    using namespace CryptoPP;

    // Creating a "hashing" object for MD5
    Weak::MD5 hash;

    // where will we record the result
    std::string digest;

    // creating a conversion chain
    StringSource(msg, true,             // source-stock
                 new HashFilter(hash,       // the "hashing" filter
                                new HexEncoder(     // encoder to a string of numbers
                                //new Base64Encoder(   // alternative - base64 encoder
                                    new StringSink(digest))));  // receiver string
    // output the message and its hash
    return digest;
}
