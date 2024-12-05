#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int N = 9;
int flags[N], bs[N], pini_butoane[] = { A0, A1, A2, A3, A4, A5, A7, A8, A9 };

int cnt = 0, x = 1, joc_terminat = 0, cine_castiga = -1;  //castigator x = 1 / 0 = 0 / -1 = egal
char mat[3][3] = { { "___" }, { "___" }, { "___" } };

void setup() {
  Serial.begin(9600);
  initializare_butoane();
  Serial.println("-------");
  afisare_mat();
  Serial.println("-------");
}

void loop() {
  if (joc_terminat == 0){
    for (int i = 0; i < N; i++) {
      bs[i] = digitalRead(pini_butoane[i]);
      if (bs[i] == LOW && flags[i] == 0) {
        flags[i] = 1;
        // Serial.print("Buton: ");
        // Serial.println(i + 1);
        if (x == 1)
          mat[get_x(i)][get_y(i)] = 'X', x = 0;
        else
          mat[get_x(i)][get_y(i)] = '0', x = 1;

        afisare_mat();
        Serial.println("-------");
        verificare_matrice();
        cnt++;
        if (cnt == N) joc_terminat = 1;
      }
    }
  }
  else {
    if (cine_castiga == 1)
      Serial.println("X castiga");
    else if (cine_castiga == 0)
      Serial.println("0 castiga");
    else
      Serial.println("Egalitate");
    delay(3000);
  }
}

void initializare_butoane() {
  for (int i = 0; i < N; i++)
    pinMode(pini_butoane[i], INPUT_PULLUP);
}

int get_x(int n) {
  return n / 3;
}

int get_y(int n) {
  return n % 3;
}

void verificare_matrice() {
  int casigator_temp = -1;
  for (int i = 0; i < 3; i++) {
    if (mat[i][1] == mat[i][0] && mat[i][2] == mat[i][0] && mat[i][2] != '_') {
      if (mat[i][0] == 'X')
        casigator_temp = 1;
      else if (mat[i][0] == '0')
        casigator_temp = 0;
    }
    if (mat[1][i] == mat[0][i] && mat[2][i] == mat[0][i] && mat[2][i] != '_') {
      if (mat[0][i] == 'X')
        casigator_temp = 1;
      else if (mat[0][i] == '0')
        casigator_temp = 0;
    }
  }
  if (mat[1][1] == mat[0][0] && mat[1][1] == mat[2][2] && mat[1][1] != '_') {  //diagonala principala
    if (mat[1][1] == 'X')
      casigator_temp = 1;
    else if (mat[0][0] == '0')
      casigator_temp = 0;
  }

  if (mat[0][2] == mat[1][1] && mat[1][1] == mat[2][0] && mat[0][2] != '_') { // diagonala secundara
    if (mat[1][1] == 'X')
      casigator_temp = 1;
    else if (mat[0][0] == '0')
      casigator_temp = 0;
  }
  if (casigator_temp != -1) {
    cine_castiga = casigator_temp;
    joc_terminat = 1;
  }
}


void afisare_mat() {
  for (int i = 0; i < 3; i++) {
    Serial.print("|");
    for (int j = 0; j < 3; j++){
      Serial.print(mat[i][j]);
      Serial.print("|");
    }
    Serial.println();
  }
}
