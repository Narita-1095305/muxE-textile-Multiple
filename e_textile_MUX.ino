const int SPin_SIGDemux_SIG[4] = {3,4,5,6}; //デマルプレクサSIG接続用デマルチプレクサのS1~S4接続
const int SPin_Demux_SIG[4] = {10, 11, 12, 13}; //eテキ接続用デマルチプレクサのS1~S4接続

const int SPin_SIGmux_SIG[4] = {22,23,24,25}; //マルチプレクサSIG接続用マルチプレクサのS1~S4接続
const int SPin_mux_SIG[4] = {26,27,28,29}; //eテキ接続用マルチプレクサのS1~S4接続

const int demux_SIG = 9; // SIG pin
const int mux_SIG = 8; // SIG pin

const int STable[16][4] = {
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

void SIGDemux_Select(int Y){
  for(int i = 0; i < 4; i++){
    digitalWrite(SPin_SIGDemux_SIG[i], STable[Y][i]);;
  }
}

void Demux_Select(int Y){
  for(int i = 0; i < 4; i++){
    digitalWrite(SPin_Demux_SIG[i], STable[Y][i]);;
  }
}

void SIGmux_Select(int Y){
  for(int i = 0; i < 4; i++){
    digitalWrite(SPin_SIGmux_SIG[i], STable[Y][i]);;
  }
}

void mux_Select(int Y){
  for(int i = 0; i < 4; i++){
    digitalWrite(SPin_mux_SIG[i], STable[Y][i]);;
  }
}

void setup() {
  pinMode(demux_SIG, OUTPUT);
  digitalWrite(demux_SIG, HIGH);

  pinMode(mux_SIG, INPUT_PULLUP);

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

  Serial.begin(9600);
}

void loop(){
  for(int S_D_sel = 0; S_D_sel < 2; S_D_sel++){
    SIGDemux_Select(S_D_sel);
    for(int D_sel = 0; D_sel < 3; D_sel++){
      Demux_Select(D_sel);
      //delay(1000);
      for(int S_M_sel = 0; S_M_sel < 2; S_M_sel++){
        SIGmux_Select(S_M_sel);
        for(int M_sel = 0; M_sel < 3; M_sel++){
          mux_Select(M_sel);
          Serial.print(readInput());
        }
        Serial.print("|");
      }
    }
  }
  Serial.println("end");
}

int readInput(){
    int state;
    state = digitalRead(mux_SIG);
    return state;
}
