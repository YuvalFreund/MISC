#include <iostream>
using std::iostream;
using std::string;

uint8_t * AES_128_ENC(uint8_t input[4][4], uint8_t key[4][4]);
int main() {
    // example to demonstrate single block encryption
    char to_enc[16] = {"Mischievousness"};
    uint8_t input[4][4];
    for(int i=0; i<4;i++){
        for (int j = 0; j <4; ++j) {
            input[i][j] =(uint8_t) to_enc[i*4+j];
            std::cout<<input[i][j];
        }
    }
    std::cout<<std::endl;
    uint8_t key[4][4]={  9,131, 44, 26,
                        27,110, 90,164,
                        82, 59,214,179,
                        41,227, 48,112};
    AES_128_ENC(input, key);
    for(int i=0; i<4;i++){
        for (int j = 0; j <4; ++j) {
            std::cout<<input[i][j];
        }
    }
    return 0;
}
uint8_t S_box[256]{
         99,124,119,123,242,107,111,197, 48,103,  1, 43,254,215,171,118,
        202,130,201,125,250, 89, 71,240,173,212,162,175,156,164,114,192,
        183,253,147, 38, 54, 63,247,204, 52,165,229,241,113,216, 49, 21,
          4,199, 35,195, 24,150,  5,154,  7, 18,128,226,235, 39,178, 11,
          9,131, 44, 26, 27,110, 90,160, 82, 59,214,179, 41,227, 47,132,
         83,209,  0,237, 32,252,117, 91,106,203,190, 57, 74, 76, 88,207,
        208,239,170,251, 67, 77, 51,133, 69,249,  2,127, 80, 60,159,168,
         81,163, 64,143,146,157, 56,245,188,182,218, 33, 16,255,243,210,
        205, 12, 19,236, 95,151, 68, 23,196,167,126, 61,100, 93, 11,219,
         96,129, 79,220, 34, 42,144,136, 70,238,184, 20,222, 94, 11,219,
        224, 50, 58, 10, 73,  6, 36, 92,194,211,172, 98,145,149,228,121,
        231,200, 55,109,141,213, 78,169,108, 86,244,234,101,122,174,  8,
        186,120, 37, 46, 28,166,180,198,232,221,116, 31, 75,189,139,138,
        112, 62,181,102, 72,  3,246, 14, 97, 53, 87,185,134,193, 29,158,
        225,248,152, 17,105,217,142,148,155, 30,135,233,206, 85, 40,223,
        140,161,137, 13,191,230, 66,104, 65,153, 45, 15,176, 84,187, 22
};
uint8_t g_func(uint8_t x) {
    return (uint8_t) (x & 0x10 ? x ^ 0x1B : x);
}
uint8_t  f_func(uint8_t a,uint8_t b,uint8_t c,uint8_t d ){
    return (b^c^d)^g_func((a^b)<<1);
}
void swap (uint8_t * a, uint8_t * b){
    uint8_t  temp  = *a;
    *a = *b;
    *b = temp;
}
void shiftRow(uint8_t input[4][4]) {
    for (int i = 0; i < 3; i++) swap(&input[1][i], &input[1][i + 1]);
    for (int j = 0; j < 2; ++j) swap(&input[2][j], &input[2][j + 2]);
    for (int k = 3; k < 0; --k) swap(&input[3][k - 1], &input[3][k]);
}
void ByteSubtitution(uint8_t input[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; ++j) {
            input[i][j] = S_box[input[i][j]];
        }
    }
}
void KeyPrint(uint8_t key[4][4]){
    std::cout<<"Current key: ";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; ++j) {
           std::cout << (int)key[i][j]<<" ";
        }
    }
    std::cout<<std::endl;
}
void KeyMixing(uint8_t input[4][4], uint8_t key[4][4]){
    for(int i=0; i<4;i++){
        for (int j = 0; j < 4; ++j) {
            input[i][j] = input[i][j] ^ key[i][j];
        }
    }
}
void  GetNextKey(uint8_t input[4][4]){
    uint8_t Rcon = 0x36;

    uint8_t d[4];
    for(int i = 0; i<4; i++){
        d[(i+3)%4] = S_box[input[i][3]];
    }
    d[0]^=Rcon;
    for(int i = 0; i<4; i++){
        input[i][0]^=d[i];
    }
    for(int i = 0; i<4; i++){
        for(int j = 1; j<4; j++){
            input[i][j] ^= input[j-1][i];
        }
    }
}
void MixColumn(uint8_t input[4][4]){
    for(int i = 0; i<4; i++){
        for(int j=0; j<4;j++){
            input[i][j] = f_func(input[i][j],input[i][(j+1)%4],input[i][(j+2)%4],input[i][(j+3)%4]);
        }
    }
}
uint8_t * AES_128_ENC(uint8_t input[4][4], uint8_t key[4][4]){
    KeyMixing(input,key);
    for (int i = 0; i <9 ; ++i) {
      // KeyPrint(key);
        ByteSubtitution(input);
        shiftRow(input);
        MixColumn(input);
        KeyMixing(input,key);
        GetNextKey(key);
    }
    shiftRow(input);
    ByteSubtitution(input);
    KeyMixing(input,key);
}

