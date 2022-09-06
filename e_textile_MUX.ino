const int SPin_SIGDemux_SIG[4] = {10,11,12,13}; //デマルプレクサSIG接続用デマルチプレクサのS1~S4接続
const int SPin_Demux_SIG[4] = {26,27,28,29}; //eテキ接続用デマルチプレクサのS1~S4接続

const int SPin_SIGmux_SIG[4] = {3,4,5,6}; //マルチプレクサSIG接続用マルチプレクサのS1~S4接続
const int SPin_mux_SIG[4] = {22,23,24,25}; //eテキ接続用マルチプレクサのS1~S4接続

//const int mux_SIG = 8; // SIG pin

const char STable[16][4] = {
  // Crea un Array con i valori binari da richiamare in base al canale Y scelto
  // s0, s1, s2, s3, canale
  {0,  0,  0,  0}, // Y0
  {1,  0,  0,  0}, // Y1
  {0,  1,  0,  0}, // Y2
  {1,  1,  0,  0}, // Y3
  {0,  0,  1,  0}, // Y4
  {1,  0,  1,  0}, // Y5
  {0,  1,  1,  0}, // Y6
  {1,  1,  1,  0}, // Y7
  {0,  0,  0,  1}, // Y8
  {1,  0,  0,  1}, // Y9
  {0,  1,  0,  1}, // Y10
  {1,  1,  0,  1}, // Y11
  {0,  0,  1,  1}, // Y12
  {1,  0,  1,  1}, // Y13
  {0,  1,  1,  1}, // Y14
  {1,  1,  1,  1}  // Y15
};

inline void SIGDemux_Select(int Y){
  
  if(STable[Y][0] == 1){
    PORTB |=  0b00010000;
  }else{
    PORTB &=  ~0b00010000;
  }
  
  if(STable[Y][1] == 1){
    PORTB |=  0b00100000;
  }else{
    PORTB &=  ~0b00100000;
  }
  
  if(STable[Y][2] == 1){
    PORTB |=  0b01000000;
  }else{
    PORTB &=  ~0b01000000;
  }
  
  if(STable[Y][3] == 1){
    PORTB |=  0b10000000;
  }else{
    PORTB &=  ~0b10000000;
  }
  
  /*
  for(int i = 0; i < 4; i++){
    digitalWrite(SPin_SIGDemux_SIG[i], STable[Y][i]);;
  }
  */
  
}

inline void Demux_Select(int Y){
  
  if(STable[Y][0] == 1){
    PORTA |= 0b00010000;
  }else{
    PORTA &= ~0b00010000;
  }

  if(STable[Y][1] == 1){
    PORTA |= 0b00100000;
  }else{
    PORTA &= ~0b00100000;
  }

  if(STable[Y][2] == 1){
    PORTA |= 0b01000000;
  }else{
    PORTA &= ~0b01000000;
  }

  if(STable[Y][3] == 1){
    PORTA |= 0b10000000;
  }else{
    PORTA &= ~0b10000000;
  }
  
  /*
  for(int i = 0; i < 4; i++){
    digitalWrite(SPin_Demux_SIG[i], STable[Y][i]);;
  }
  */
  
}

inline void SIGmux_Select(int Y){
  
  if(STable[Y][0] == 1){
    PORTE |= 0b00100000;
  }else{
    PORTE &= ~0b00100000;
  }

  if(STable[Y][1] == 1){
    PORTG |= 0b00100000;
  }else{
    PORTG &= ~0b00100000;
  }

  if(STable[Y][2] == 1){
    PORTE |= 0b00001000;
  }else{
    PORTE &= ~0b00001000;
  }

  if(STable[Y][3] == 1){
    PORTH |= 0b00001000;
  }else{
    PORTH &= ~0b00001000;
  }
  
  /*
  for(int i = 0; i < 4; i++){
    digitalWrite(SPin_SIGmux_SIG[i], STable[Y][i]);;
  }
  */
}

inline void mux_Select(int Y){
  
  if(STable[Y][0] == 1){
    PORTA |= 0b00000001;
  }else{
    PORTA &= ~0b00000001;
  }

  if(STable[Y][1] == 1){
    PORTA |= 0b00000010;
  }else{
    PORTA &= ~0b00000010;
  }

  if(STable[Y][2] == 1){
    PORTA |= 0b00000100;
  }else{
    PORTA &= ~0b00000100;
  }

  if(STable[Y][3] == 1){
    PORTA |= 0b00001000;
  }else{
     PORTA &= ~0b00001000;
  }
  
  /*
  for(int i = 0; i < 4; i++){
    digitalWrite(SPin_mux_SIG[i], STable[Y][i]);;
  }
  */
  
}

void setup() {
  DDRH &= ~_BV(5);
  PORTH |= _BV(5);

    /* マルチプレクサ、デマルチプレクサ S1~S4のPIN初期化を行う */
  for(int i = 0; i < 4; i++){
    pinMode(SPin_SIGDemux_SIG[i], OUTPUT);
    digitalWrite(SPin_SIGDemux_SIG[i], LOW);
    pinMode(SPin_Demux_SIG[i], OUTPUT);
    digitalWrite(SPin_Demux_SIG[i], LOW);
    
    pinMode(SPin_SIGmux_SIG[i], OUTPUT);
    digitalWrite(SPin_SIGmux_SIG[i], LOW);
    pinMode(SPin_mux_SIG[i], OUTPUT);
    digitalWrite(SPin_mux_SIG[i], LOW);
  }

  
  Serial.begin(230400);
}

void loop(){
  while(1){
    short num = 0;
    for(char S_D_sel = 0; S_D_sel < 5; S_D_sel++){
      SIGDemux_Select(S_D_sel);
      for(char D_sel = 0; D_sel < 16; D_sel++){
        Demux_Select(D_sel);
        for(char S_M_sel = 0; S_M_sel < 1; S_M_sel++){
          SIGmux_Select(S_M_sel);
          for(char M_sel = 4; M_sel < 16; M_sel++){
            mux_Select(M_sel);
            //num += ((PINH>>5) & 0b00000001)^1;
            char sig = readInput();
            num += sig << (M_sel - 4);
          }
          Serial.println(num,HEX);
          num = 0;
        }
      }
    }
    Serial.print("t:");
    Serial.println(millis());
  }
}

inline char readInput(){
    char state;
    //state = digitalRead(8)^1;
    state = ((PINH>>5) & 0b00000001)^1;
    return state;
}
