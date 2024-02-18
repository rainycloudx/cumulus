
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream file("output.bin", ios::binary);

    char cmd = 'c';
    char token[] = "eyJhbGciOiJSUzI1NiIsImtpZCI6IjAzZDA3YmJjM2Q3NWM2OTQyNzUxMGY2MTc0ZWIyZjE2NTQ3ZDRhN2QiLCJ0eXAiOiJKV1QifQ.eyJpc3MiOiJodHRwczovL3NlY3VyZXRva2VuLmdvb2dsZS5jb20vY3VtdWx1cy0wIiwiYXVkIjoiY3VtdWx1cy0wIiwiYXV0aF90aW1lIjoxNjk3NjYyNzM4LCJ1c2VyX2lkIjoicTVaQ1cyZ3lCTmFjelQzUTR6OWs2Sk1IQWpWMiIsInN1YiI6InE1WkNXMmd5Qk5hY3pUM1E0ejlrNkpNSEFqVjIiLCJpYXQiOjE2OTc2NjI3MzgsImV4cCI6MTY5NzY2NjMzOCwiZW1haWwiOiJzaGFudGFudS5iYW5lcmplZS52dEBnbWFpbC5jb20iLCJlbWFpbF92ZXJpZmllZCI6ZmFsc2UsImZpcmViYXNlIjp7ImlkZW50aXRpZXMiOnsiZW1haWwiOlsic2hhbnRhbnUuYmFuZXJqZWUudnRAZ21haWwuY29tIl19LCJzaWduX2luX3Byb3ZpZGVyIjoicGFzc3dvcmQifX0.qI8Ll--WABInLv8IDLw_CMQleHCtLsREogBouC_lBx5mcv5BW7NxKQx_Tx8U4NTKICuajPzgG9kfyB1OmbNQmPpq4iX7JNfLMCMDhyDqIqSPDsuSlktxw4CSD_vBGCN3PdcNtWqK6NRMwAZRVdwlGGAmOEmuIrsD99Ou6ZT66Cy5JJUyDJEH9IU5pm6zS1BdFhXwvuXIrv1rWsLDNfgPH1nmc8I3_h2GnGdFOtxFuGjljXq453deRU-Xeaarfq_WSzxSbuF_cqVthBDj1iQ5Ss76GT-pEVQF2JmSKM976hXbjmIJMJIhdOluGdHCCvQ1reJ0loRV-CBBHXKRzC_4WQ";
    unsigned int len = std::strlen(token);

    file.write(&cmd, 1);
    file.write((char *) &len, sizeof(unsigned int));
    file.write(token, len);

}

