/**
 * @file Connect.cpp
 */
#include "Connect.h"
#include "md5.h"

/**
 * @brief Recv Login and password
*/
void Connect::GetLoginPassword(){
    // Open auth file
    ifstream fa(name_auto_file);
    if(!fa.is_open()){
        fa.close();
        throw error_proj(std::string("fun:GetLoginPassword, param:name_auto_file.\nError opening the authentication file!"));
    }

    string line;
    if(fa.peek() == EOF){
        fa.close();
        throw error_proj(std::string("fun:GetLoginPassword, param:name_auto_file.\nError opening the file for authentication! The file is empty!"));
    }
    getline(fa, line);
    int k = line.find(" ");
    string u = line.substr(0, k);
    string p = line.erase(0, k+1);
    username = u;
    pswd = p;

}

/**
* @brief Use to server
* @param str1 addr serv
* @param str2 port serv
* @throw error_proj if error
*/
int Connect::Connect_to_server(string str1, string str2)
{
    GetLoginPassword();

    // Open vector file

    ifstream fin(name_original_file, ios::binary);
    if(!fin.is_open()){
        throw error_proj(std::string("fun:Connect_to_server, param:name_original_file.\nError opening the vector file!"));
    }

    string line;
    if(fin.peek() == EOF){
        fin.close();
        throw error_proj(std::string("fun:Connect_to_server, param:name_original_file.\nError opening the file. The vector file is empty!"));
    }

    // Open result file
    fstream fout(name_result_file);
    if (!fout.is_open()){
        fout.close();
        throw error_proj(std::string("fun:Connect_to_server, param:name_result_file.\nThe file for the result cannot be opened or created!"));
    }

    try{
        ip_addr = stoi(str1);
    }
    catch (...){
        throw error_proj(std::string("fun:Connect_to_server, param:ip_addr.\nIt is not possible to get an address!"));
    }

    try{
        port = stoi(str2);
    }
    catch (...){
        throw error_proj(std::string("fun:Connect_to_server, param:port.\nIt is not possible to get a port!"));
    }
    
    char buf[1024];
    int bytes_read;

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {   
        throw error_proj(std::string("fun:Connect_to_server, param:sock.\nError creating a sock!"));
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); 
    addr.sin_addr.s_addr = htonl(ip_addr);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        throw error_proj(std::string("fun:Connect_to_server, param:sock.\nServer connection error!"));
    }

    // send login client
    strcpy(buf,username.c_str());
    send(sock, buf, username.length(), 0);

    // Recv str SALT or ERR
    bytes_read = recv(sock, buf, sizeof(buf), 0);
    buf[bytes_read] = '\0';
    string s1 = string(buf);
    if (s1 == "ERR"){
        close(sock);
        throw error_proj(std::string("fun:Connect_to_server, param:username.\nIdentification error!"));
    }

    // Hash = SALT+PASSWORD
    string s2 = s1 + pswd;
    s2 = MD5_hash(s2);

    // Recv Hash = SALT+PASSWORD
    strcpy(buf,s2.c_str());
    send(sock, buf, s2.length(), 0);

    //Send resylt auth
    bytes_read = recv(sock, buf, sizeof(buf), 0);
    buf[bytes_read] = '\0';
    string s3 = string(buf);
    if (s3 == "ERR"){
        close(sock);
        throw error_proj(std::string("fun:Connect_to_server, param:pswd.\nAuthentication error!"));
    }
    
    // Recv KOL-VO vect
    getline(fin, line);



    float len = 0;
    FILE *f;
    const char * c = name_original_file.c_str();
    f = fopen(c, "rb");
    fread(&len, sizeof(float),1,f);
    try{
        len = stoi(line);
    }
    catch (...){
        throw error_proj(std::string("fun:Connect_to_server, param:line\nIt is not possible to get the number of vectors!"));
    }
    fout.write(reinterpret_cast<char*>(&len), sizeof(len)) << endl;

    // Send KOL-VO vect
    send(sock, &len, sizeof(len), 0);

    // Recv vectors
    for(int l = 0; l < len; l++){
        getline(fin, line);

        // Send len vect
        string s = line;
        float j = 0;
        int k = s.find(" ");
        string L = s.substr(0, k);
        s = s.erase(0, k+1);
        int Len = 0;
        try{
            Len = stoi(L);
        }
        catch (...){
            throw error_proj(std::string("fun:Connect_to_server, param:line.It is not possible to get the size of the vector!"));
        }
        
        float array[Len] = {0};
        for(int j = 0; j < Len; j++){
            string a;
            int i = s.find(" ");
            a = s.substr(0, i);
            s = s.erase(0, i+1);

            try{
                array[j] = stof(a);
            }
            catch (...){
                throw error_proj(std::string("fun:Connect_to_server, param:s-string.It is not possible to get a vector!"));
            }

        }

        send(sock, &Len, sizeof(Len), 0);
        send(sock, &array, sizeof(array), 0);
        float sum = 0;
        recv(sock, &sum, sizeof(sum), 0);
        
        fout << sum << endl;
    }

    // Close file
    fin.close();
    fout.close();

    // Save result in file 
    cout << "The result is saved in a file: " << name_result_file << endl;
    close(sock);

    return 0;
}
